//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProfileEditUnit.h"
#include "Bcb_pgm.h"
#include "ProfileDefines.h"
#include "ProfileInteractionEditUnit.h"
#include "ProfileSwitchEditUnit.h"
#include "ModulatorsEditUnit.h"
#include "GroupTriggerUnit.h"
#include "IOEditorUnit.h"

#include "MotorAndForceEditUnit.h"
#include "ThresholdGroupSettingsUnit.h"

#include "ProfileGeneratorUnit.h"
#include "ForceSurfaceUnit.h"


#define ImageRect1  Rect( 0, 0, Image1->Width, Image1->Height)
#define ImageRect2  Rect( 0, 0, Image2->Width, Image2->Height)
#define PROFILE_HOR_DRAWING_AREA 896
#define PROFILE_VERT_DRAWING_AREA 256
#define PROFILE_HOR_DRAWING_BORDERS 64
#define PROFILE_VERT_DRAWING_BORDERS 64
/*
Editing??

the Profile Defines list contains data on what element in a profile packet array
relates to which variable or pointer.

To configure a variable the value typed into an edit box is placed into the
appropriate slot in the relevant data array

To configure a variable source (Pointer) the pointer to edit is determined by
the listbox being used and the actual value placed in the data array is taken
from the define list

EG to set the SOURCE for the positive threshold 1 value to its default value
you place the #defined value of _PT1Default into the pointers array at
index _PT1Value_ptr

To do variables . . .

*/

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProfileEditForm *ProfileEditForm;
//---------------------------------------------------------------------------
__fastcall TProfileEditForm::TProfileEditForm(TComponent* Owner)
        : TForm(Owner)
{
        //AnsiString FileName = "D:\\Projects\\SERIALCONTROLTOOLS\\PGSTesting1\\ConfigurationFiles\\VariableList16.txt";
        AnsiString FileName = "ConfigurationFiles\\VariableList16.txt";
        VariableList16 = new TStringList; // declare the list
        VariableList16->LoadFromFile(FileName);

        FileName = "ConfigurationFiles\\VariableList8.txt";
        VariableList8 = new TStringList;
        VariableList8->LoadFromFile(FileName);

        FileName = "ConfigurationFiles\\PointerList16.txt";
        PointerList16 = new TStringList;
        PointerList16->LoadFromFile(FileName);

        FileName = "ConfigurationFiles\\PointerList8.txt";
        PointerList8 = new TStringList;
        PointerList8->LoadFromFile(FileName);

        CurrentEditingProfile = REMOTE->EditingProfileNo;
        Title = "Editing Profile No: ";
        Title += CurrentEditingProfile;
        ProfileEditForm->Caption = Title;
        SelectProfileBox->ItemIndex = CurrentEditingProfile;
        
        ImageXScalarValue = 12;


        ScaleToImageXConstant = ((100.00/16.00)*ImageXScalarValue)/100.00;
        ScaleToAngleConstant = 100.00/(ScaleToImageXConstant*100.00);

        ProfileHeight = 256;
        VPBorder = 32;
        HPStart = 128;
        HPEnd = HPStart+(63*ImageXScalarValue);
        VPStart = 16;
        VPEnd = VPStart+VPBorder+VPBorder+ProfileHeight;

        ProfileZero = VPStart+VPBorder+(ProfileHeight/2);
        VPMax = ProfileZero - (ProfileHeight/2);
        VPMin = ProfileZero + (ProfileHeight/2);

        AngleThresholdDragHeight = 16;
        ImageWidth = Image1->Width;
        ImageHeight = Image1->Height;

        for(int n = 0; n < 4; n++)
        {
        	ImageAngleThresholds[0][n] = 1024; //[PAT, NAT][1-4];
            ImageAngleThresholds[1][n] = -1;
            ImageAngleActive[0][n] = 0;
            ImageAngleActive[01][n] = 0;
            ForceThresholdValues[0][n] = ProfileZero-128; //[PAT, NAT][1-4];
            ForceThresholdValues[1][n] = ProfileZero+128;
            ForceThresholdActive[0][n] = 0;
            ForceThresholdActive[1][n] = 0;
        }

        CopyToLocalArrays->Execute();
        SetupComboBoxes->Execute();
        CheckThresholdsForAngle->Execute();
        EQImagePosition = ConvertXAngleToMouse(  TempSI16Var[ _EQAngle ] );
        DrawProfile->Execute();
        Panel1->DoubleBuffered = true;
        RedrawAndRefresh->Execute();

        ThresholdClickEdit = 0;
        ModulatorClickEdit = 0;
        OutputsClickEdit = 0;
        InteractionsClickEdit = 0;

        //REMOTE->RedrawAndRefresh->Execute();

        //if( (CurrentEditingProfile&1) == 1 ) StaticText1->Caption = "ODD";
       //else if( (CurrentEditingProfile&1) == 0 ) StaticText1->Caption = "EVEN";
}
//---------------------------------------------------------------------------
void __fastcall TProfileEditForm::RefreshImageExecute(TObject *Sender)
{
   //refresh the visible image with the image buffer (image1)
    //PaintBox1->Canvas->CopyMode = cmSrcCopy;
    //PaintBox1->Canvas->CopyRect(ImageRect1, Image1->Canvas, ImageRect1);
    PaintBox2->Canvas->CopyMode = cmSrcCopy;
    PaintBox2->Canvas->CopyRect(ImageRect2, Image2->Canvas, ImageRect2);

}
//---------------------------------------------------------------------------
void __fastcall TProfileEditForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{

        REMOTE->EditingProfileNo = CurrentEditingProfile;
        //delete VariableList16;
        //delete PointerList16;
        //delete VariableList8;
        //delete PointerList8;

        //VariableList16 = NULL;
        //PointerList16 = NULL;
        //VariableList8 = NULL;
        //PointerList8 = NULL;

}
//---------------------------------------------------------------------------
void __fastcall TProfileEditForm::SetupComboBoxesExecute(TObject *Sender)
{
        double TempDouble;
        UniDampSourceBox->Items = VariableList16;
        UniDampSourceBox->ItemIndex = TempSI16Ptr[ _UniformDamping_ptr ];
        TempDouble = TempSI16Var[ _DefaultUniformDamping ];
        TempDouble /= 10;
        UniDampDefaultEdit->Text = TempDouble;

        TimerThresholdEdit->Text = TempSI16Var[ _TimerThreshold ];

        if( TempI8Var[ _SummedProfile ] > 0)
        {
        	ProfileSummationBox->Checked = true;
        }
        else
        {
        	ProfileSummationBox->Checked = false;
        }
        if( (CurrentEditingProfile&1) == 0 )
        {
        	//If the profile is ODD numbered grey out the check box
        	ProfileSummationBox->Enabled = true;
        }
        else if( (CurrentEditingProfile&1) == 1 )
        {
        	//If the profile is ODD numbered grey out the check box
        	ProfileSummationBox->Enabled = false;
            //Check to see if the profile below (EVEN numbered) is summed, if so set this check box to
            //Checked
            if( REMOTE->ArrayOfProfileData[CurrentEditingProfile-1]->Int8Variables[_SummedProfile] != 0)
            {
            	ProfileSummationBox->Checked = true;
            }
        }

         //StaticText1->Caption = "ODD";

/*
Need to add checks to make sure thet the box is checked depending on the master of the group
in other words if this is an ODD numbered profile then check the box if the one below is checked
and grey the box out.
If it is EVEN then set the next profile up (ODD) to whatever this one is
*/
}
//---------------------------------------------------------------------------
void __fastcall TProfileEditForm::DrawProfileExecute(TObject *Sender)
{
        //Draws the selected Profile to the image

        int XPos, YPos;
        int CircleSize = 2;

        XPos = HPStart;
        YPos = ProfileZero;


        DrawProfileBackground->Execute();
        DrawProfileGraphAndText->Execute();
        
        if(DrawNDampCheckBox->Checked == true)
        {
                // draw the NDamp profile(Change later to have user selectable drawing order)
                //YCentre = Image1->Height/2;
                XPos = HPStart;
                //YPos = ProfileZero;
                Image1->Canvas->Pen->Color = clBlue;
                Image1->Canvas->Brush->Color = clBlue;
                YPos = ProfileZero - TempNDamp[0];
                Image1->Canvas->MoveTo(XPos,YPos);
                //Draw a little circle if required for each datapoint
                Image1->Canvas->Ellipse(XPos-CircleSize, YPos-CircleSize, XPos+CircleSize, YPos+CircleSize);
                for(int n = 1; n < 64; n++)
                {
                        XPos += ImageXScalarValue;
                        YPos = ProfileZero - TempNDamp[n];
                        Image1->Canvas->LineTo(XPos, YPos);
                        Image1->Canvas->Ellipse(XPos-CircleSize, YPos-CircleSize, XPos+CircleSize, YPos+CircleSize);
                }
        }
        if(DrawPDampCheckBox->Checked == true)
        {
                // draw the PDamp profile(Change later to have user selectable drawing order)
                //YCentre = Image1->Height/2;
                XPos = HPStart;
                YPos = ProfileZero;
                Image1->Canvas->Pen->Color = clOlive;
                Image1->Canvas->Brush->Color = clOlive;
                YPos = ProfileZero - TempPDamp[0];
                Image1->Canvas->MoveTo(XPos,YPos);
                //Draw a little circle if required for each datapoint
                Image1->Canvas->Ellipse(XPos-CircleSize, YPos-CircleSize, XPos+CircleSize, YPos+CircleSize);
                for(int n = 1; n < 64; n++)
                {
                        XPos += ImageXScalarValue;
                        YPos = ProfileZero - TempPDamp[n];
                        Image1->Canvas->LineTo(XPos, YPos);
                        Image1->Canvas->Ellipse(XPos-CircleSize, YPos-CircleSize, XPos+CircleSize, YPos+CircleSize);
                }
        }
        if(DrawForceCheckBox->Checked == true)
        {
                //Now draw the force profile(Change later to have user selectable drawing order)
                //YCentre = Image1->Height/2;
                XPos = HPStart;
                YPos = ProfileZero;
                Image1->Canvas->Pen->Color = clRed;
                Image1->Canvas->Brush->Color = clRed;
                YPos = ProfileZero - ( TempFPro[0] / 16 );
                Image1->Canvas->MoveTo(XPos,YPos);
                //Draw a little circle if required for each datapoint
                Image1->Canvas->Ellipse(XPos-CircleSize, YPos-CircleSize, XPos+CircleSize, YPos+CircleSize);
                for(int n = 1; n < 64; n++)
                {
                        XPos += ImageXScalarValue;
                        YPos = ProfileZero - ( TempFPro[n] / 16 );
                        Image1->Canvas->LineTo(XPos, YPos);
                        Image1->Canvas->Ellipse(XPos-CircleSize, YPos-CircleSize, XPos+CircleSize, YPos+CircleSize);
                }
        }


        //Now draw any thresholds
        DrawForceThresholds->Execute();
        DrawAngleThresholds->Execute();
        DrawEQP->Execute();
                
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::CopyToLocalArraysExecute(TObject *Sender)
{
        //Copies the selected profile data to a local storage array
        for(int n = 0; n < 64; n++)
        {
                TempFPro[n] = REMOTE->ArrayOfProfileData[CurrentEditingProfile]->GetFValue(n);
                TempPDamp[n] = REMOTE->ArrayOfProfileData[CurrentEditingProfile]->PDamptable[n];
                TempNDamp[n] = REMOTE->ArrayOfProfileData[CurrentEditingProfile]->NDamptable[n];
                TempSI16Ptr[n] = REMOTE->ArrayOfProfileData[CurrentEditingProfile]->SInt16Pointers[n];
                TempI8Ptr[n] = REMOTE->ArrayOfProfileData[CurrentEditingProfile]->Int8Pointers[n];
        }
        for(int n = 0; n < 32; n++)
        {

                TempSI16Var[n] = REMOTE->ArrayOfProfileData[CurrentEditingProfile]->SInt16Variables[n];
                TempI8Var[n] = REMOTE->ArrayOfProfileData[CurrentEditingProfile]->Int8Variables[n];

        }
}
//---------------------------------------------------------------------------



void __fastcall TProfileEditForm::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        //edit the profile - work out which to edit
        //Check to see which index you are closest to

        //if(Y < VPStart) return;
        if( Button == mbLeft  ) //Shift.Contains(ssLeft)
        {
        	Timer1->Enabled = true;
        	ThresholdBeingDragged = DetermineImageDragItem(X, Y);
            return;
        }
        if(Button != mbRight ) return;
        Timer1->Enabled = true;
        int XPos, YPos;
        int CircleSize = 2;

        int AdjustedXPos;
        int YMousePos;
        int DisplayYValue = 0;


        //YCentre = Image1->Height/2;
        
        AdjustedXPos = X-HPStart;
        AdjustedXPos +=4 ;
        AdjustedXPos /=ImageXScalarValue;

        YMousePos = 0+ProfileZero-Y;

        //use the global YMousePos for orthogonal dragging with shift

        //If control is not pressed then record the mouse position
        //so you can use it later for point to point clicks
        if( !Shift.Contains(ssCtrl) )
        {
                GlobalMouseYPos = YMousePos;
                GlobalMouseXPos = AdjustedXPos;
        }
        //StaticText1->Caption = YMousePos;

        //if Alt is pressed then set to zero
        if(Shift.Contains(ssAlt) ) YMousePos = 0;

        //if shift is pressed then set the shift start state to 1
        //so that the mouse move function will know that you pressed shift
        if(Shift.Contains(ssShift))
        {
                ShiftStartState = 1;
        }
        else ShiftStartState = 0;

        if( Shift.Contains(ssCtrl) )
        {
                //this allows a point to point line with interpolation
                //Draw a line from the current global mouse pos to the new local one
                //then interpolate
                double DifferenceX, DifferenceY;
                double YValue1, YIterator;
                int StartPos, EndPos;

                DifferenceY = (double)(GlobalMouseYPos - YMousePos);

                if( GlobalMouseXPos > AdjustedXPos)
                {
                	YValue1 = (double)YMousePos;
                	DifferenceX = (double)(GlobalMouseXPos - AdjustedXPos);
                    YIterator = -(DifferenceY/DifferenceX);
                    StartPos = AdjustedXPos;
                    EndPos = GlobalMouseXPos;

                    
                }
                if( GlobalMouseXPos < AdjustedXPos)
                {
                	YValue1 = (double)GlobalMouseYPos;
                	DifferenceX = AdjustedXPos - GlobalMouseXPos;
                    YIterator = DifferenceY/DifferenceX;
                    //StaticText1->Caption = YIterator;
                    StartPos =  GlobalMouseXPos;
                    EndPos = AdjustedXPos;

                }
                if( GlobalMouseXPos == AdjustedXPos )
                {
                    DifferenceX = 0;
                    YIterator = 0;
                    StartPos =  GlobalMouseXPos;
                    EndPos = GlobalMouseXPos;
                }
                for(int n = StartPos; n < EndPos+1; n++)
                {

                	if(EditPDampProfileRadio->Checked == true)
                	{
        				if(YValue1 < -128) YValue1 = -128;
                		if(YValue1 > 127) YValue1 = 127;
                		TempPDamp[n] = YValue1;
                        DisplayYValue = TempPDamp[n];
                	}
                    if(EditNDampProfileRadio->Checked == true)
                	{
        				if(YValue1 < -128) YValue1 = -128;
                		if(YValue1 > 127) YValue1 = 127;
                		TempNDamp[n] = YValue1;
                        DisplayYValue = TempNDamp[n];
                	}
                	if(EditForceProfileRadio->Checked == true)
                	{
                		TempFPro[n] = YValue1*16;
                        DisplayYValue = TempFPro[n];
                	}

                        //TempFPro[n] = YValue1*16;
                	YValue1 -= YIterator;
                }
                GlobalMouseYPos = YMousePos;
                GlobalMouseXPos = AdjustedXPos;
                AngleText->Caption = AdjustedXPos*16;
                ValueText->Caption = DisplayYValue;
                RedrawAndRefresh->Execute();
                return;

        }

        int Result = YMousePos;
        double DResult;
        if(EditPDampProfileRadio->Checked == true)
        {
        	if(Result < -128) Result = -128;
        	if(Result > 127) Result = 127;
        	TempPDamp[AdjustedXPos] = Result;
            DResult = Result;
            DResult /=10;
            ValueText->Caption = DResult;
        }
        else if(EditNDampProfileRadio->Checked == true)
        {
        	if(Result < -128) Result = -128;
        	if(Result > 127) Result = 127;
        	TempNDamp[AdjustedXPos] = Result;
            DResult = Result;
            DResult /=10;
            ValueText->Caption = DResult;
        }
        else
        {
        	Result *=16;
            TempFPro[AdjustedXPos] = Result;
            ValueText->Caption = Result;
        }
        AngleText->Caption = AdjustedXPos*16;
        //RedrawAndRefresh->Execute();

}
//---------------------------------------------------------------------------


void __fastcall TProfileEditForm::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{

        //if(Y < VPStart) return;
        if( Shift.Contains(ssLeft) )
        {

        	DragAngleThresholds(X, Y);
            return;
        }
		//Adjusts the profile when dragging the mouse to draw a line
		//exit if left Mouse button not pressed
        static int ShiftChange = 0;
        if(!Shift.Contains(ssRight) ) return;

        //int XStart = PROFILE_HOR_DRAWING_BORDERS, YStart = 16;
        //int XEnd = XStart + (63*ImageXScalarValue);
        //int YEnd = Image1->Height - YStart;
        //int YCentre;

        //exit if you are outside the profile
        if(X < HPStart-4 || X > HPEnd+4) return;


        int XPos, YPos;
        int CircleSize = 2;

        int AdjustedXPos;
        int YMousePos;
       // YCentre = Image1->Height/2;

        AdjustedXPos = X-HPStart;
        AdjustedXPos +=4 ;
        AdjustedXPos /=ImageXScalarValue;

        YMousePos = 0+ProfileZero-Y;
        //if the shift key was pressed on mouse click use the global ypos
        if(Shift.Contains(ssShift) && ShiftStartState == 1) YMousePos = GlobalMouseYPos;
        //if the shift key is pressed while dragging use the local YYPos and set the ShiftStartState to 1
        //and the global YPos to this local one
        else if(Shift.Contains(ssShift) && ShiftStartState == 0)
        {
                YMousePos = 0+ProfileZero-Y;
                GlobalMouseYPos = YMousePos;

                ShiftStartState = 1;
        }
        else if(!Shift.Contains(ssShift) ) ShiftStartState = 0;
        GlobalMouseXPos = AdjustedXPos;
        if(Shift.Contains(ssAlt) ) YMousePos = 0;

        int Result = YMousePos;
        double DResult;
        if(EditPDampProfileRadio->Checked == true)
        {
        	if(Result < -128) Result = -128;
        	if(Result > 127) Result = 127;
        	TempPDamp[AdjustedXPos] = Result;
            DResult = Result;
            DResult /=10;
            ValueText->Caption = DResult;
        }
        else if(EditNDampProfileRadio->Checked == true)
        {
        	if(Result < -128) Result = -128;
        	if(Result > 127) Result = 127;
        	TempNDamp[AdjustedXPos] = Result;
            DResult = Result;
            DResult /=10;
            ValueText->Caption = DResult;
        }
        else
        {
        	Result *=16;
            TempFPro[AdjustedXPos] = Result;
            ValueText->Caption = Result;
        }
        AngleText->Caption = (AdjustedXPos*16)-512;
        //RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::UpdateMainProfileDataExecute(
      TObject *Sender)
{

        //First update local arrays with any changes to the listboxes on the main form
        double TempDouble;
        int TempInt;
        TempSI16Ptr[ _UniformDamping_ptr ] = UniDampSourceBox->ItemIndex;

        TempDouble = UniDampDefaultEdit->Text.ToDouble();
        TempInt = (TempDouble*10);
        TempSI16Var[ _DefaultUniformDamping ] = TempInt;

        TempSI16Var[ _TimerThreshold ] = TimerThresholdEdit->Text.ToInt();
        if( TempSI16Var[ _TimerThreshold ] < 0) TempSI16Var[ _TimerThreshold ] = 0;
        if( TempSI16Var[ _TimerThreshold ] > TIMERSATURATION) TempSI16Var[ _TimerThreshold ] = TIMERSATURATION+1;

/*
For profile summation:
If this profile is EVEN then set the next profile up (ODD) to whatever this one is
*/
        if( ProfileSummationBox->Checked == true )
        {
        	TempI8Var[ _SummedProfile ] = 1;
        }
        else TempI8Var[ _SummedProfile ] = 0;

        if( (CurrentEditingProfile&1) == 0 )
        {
        	//If the profile is EVEN numbered set the profile above to match
            //its profile summation status
            REMOTE->ArrayOfProfileData[CurrentEditingProfile+1]->Int8Variables[_SummedProfile]
            		= TempI8Var[ _SummedProfile ];
        }
        //if( (CurrentEditingProfile&1) == 1 ) //Odd number
        //REMOTE->ArrayOfProfileData[CurrentEditingProfile+1]->Int8Variables[n]
        //Copies the contents of all the local arrays back - for exit

         //Copies the selected profile data to a local storage array
        for(int n = 0; n < 64; n++)
        {
                REMOTE->ArrayOfProfileData[CurrentEditingProfile]->SetFValue(TempFPro[n], n);
                REMOTE->ArrayOfProfileData[CurrentEditingProfile]->SetPDampValue(TempPDamp[n], n);
                REMOTE->ArrayOfProfileData[CurrentEditingProfile]->SetNDampValue(TempNDamp[n], n);
                REMOTE->ArrayOfProfileData[CurrentEditingProfile]->SInt16Pointers[n] = TempSI16Ptr[n];
                REMOTE->ArrayOfProfileData[CurrentEditingProfile]->Int8Pointers[n] = TempI8Ptr[n];
        }
        for(int n = 0; n < 32; n++)
        {
                REMOTE->ArrayOfProfileData[CurrentEditingProfile]->SInt16Variables[n] = TempSI16Var[n];
                REMOTE->ArrayOfProfileData[CurrentEditingProfile]->Int8Variables[n] = TempI8Var[n];
        }
        REMOTE->RedrawProfileBitmapX(CurrentEditingProfile);
        
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::RedrawAndRefreshExecute(TObject *Sender)
{
        DrawProfile->Execute();
        //RedrawVelocityGraphics->Execute();
        //DrawVelocityThresholds->Execute();
        
        RefreshImage->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TProfileEditForm::FormActivate(TObject *Sender)
{
        RedrawAndRefresh->Execute();
        ProfileEditForm->Caption = Title;         
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::SelectProfileBoxChange(TObject *Sender)
{
	//Change to a different profile
    //First save existing data
    UpdateMainProfileData->Execute();

    //Reload everything andredraw the images using thenew selected profile
    CurrentEditingProfile = SelectProfileBox->ItemIndex;
    REMOTE->EditingProfileNo = CurrentEditingProfile;
    Title = "Editing Profile No: ";
    Title += CurrentEditingProfile;
    ProfileEditForm->Caption = Title;

    for(int n = 0; n < 4; n++)
    {
    	ImageAngleThresholds[0][n] = 1024; //[PAT, NAT][1-4];
    	ImageAngleThresholds[1][n] = -1;
    	ImageAngleActive[0][n] = 0;
    	ImageAngleActive[01][n] = 0;
    	ForceThresholdValues[0][n] = ProfileZero-128; //[PAT, NAT][1-4];
    	ForceThresholdValues[1][n] = ProfileZero+128;
    	ForceThresholdActive[0][n] = 0;
    	ForceThresholdActive[1][n] = 0;
    }

    CopyToLocalArrays->Execute();
    SetupComboBoxes->Execute();
    CheckThresholdsForAngle->Execute();
    EQImagePosition = ConvertXAngleToMouse(  TempSI16Var[ _EQAngle ] );
    DrawProfile->Execute();
    RedrawVelocityGraphics->Execute();
    RedrawAndRefresh->Execute();

}

//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::OKButtonClick(TObject *Sender)
{
	//save and close
    UpdateMainProfileData->Execute();
    ProfileEditForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::CancelButtonClick(TObject *Sender)
{
	//close without saving
    ProfileEditForm->Close();
}
//---------------------------------------------------------------------------






void __fastcall TProfileEditForm::DrawAngleThresholdsExecute(
      TObject *Sender)
{
	//Draws the angle thresholds

    int PT, NT;
    AnsiString Text;
    int DrawingOffset=0;
    int BoxHeight = 14;
    int TextOffset= 1;
    Image1->Canvas->Font->Color = clWhite;
    Image1->Canvas->Font->Name = "Arial";
    Image1->Canvas->Font->Size = 7;
    	//Image1->Canvas->Brush->Color = clLtGray;
    	//Image1->Canvas->Font->Style = TFontStyles()<< fsBold;
     for(int n = 0; n < 4; n++)
     {
     	if(ImageAngleActive[0][n] !=0 || ImageAngleActive[1][n] !=0)
        {
        	//draw the positive threshold
            Image1->Canvas->Pen->Width = 3;

            //check to see if it should be greyed
            if( ImageAngleActive[0][n] == 1 )
            {
            	Image1->Canvas->Pen->Color = clBlue;
            	Image1->Canvas->Brush->Color = clBlue;
            }
            if( ImageAngleActive[0][n] == 2 )
            {
            	Image1->Canvas->Pen->Color = clDkGray	;
            	Image1->Canvas->Brush->Color = clDkGray	;
            }
            Image1->Canvas->MoveTo(ImageAngleThresholds[0][n]+50, VPStart);
            Image1->Canvas->LineTo(ImageAngleThresholds[0][n], VPStart);
            Image1->Canvas->LineTo(ImageAngleThresholds[0][n], VPEnd+DrawingOffset);
            Image1->Canvas->Pen->Width = 1;
            Image1->Canvas->Pen->Color = clBlack	;
            Image1->Canvas->Rectangle(ImageAngleThresholds[0][n], VPEnd+DrawingOffset
            							, ImageAngleThresholds[0][n]+50, VPEnd+BoxHeight+DrawingOffset);
            //Copy the rectangle coords to the array for dragging later
            ThresholdDragStartX[0][n] = ImageAngleThresholds[0][n];
        	ThresholdDragStartY[0][n] = VPEnd+DrawingOffset;
        	ThresholdDragEndX[0][n] = ImageAngleThresholds[0][n]+50;
        	ThresholdDragEndY[0][n] = VPEnd+BoxHeight+DrawingOffset;

            Image1->Canvas->Pen->Color = clWhite;
            Text= "PT";
            Text += n+1;
            Text += " ";
            Text += ConvertXMouseToAngle(ImageAngleThresholds[0][n]);
            Image1->Canvas->TextOutA(ImageAngleThresholds[0][n]+2, VPEnd+TextOffset, Text);

            //Now the negative threshold
            Image1->Canvas->Pen->Width = 3;
            if( ImageAngleActive[1][n] == 1 )
            {
            	Image1->Canvas->Pen->Color = clGreen;
            	Image1->Canvas->Brush->Color = clGreen;
            }
            if( ImageAngleActive[1][n] == 2 )
            {
            	Image1->Canvas->Pen->Color = clDkGray	;
            	Image1->Canvas->Brush->Color = clDkGray	;
            }
            Image1->Canvas->MoveTo(ImageAngleThresholds[1][n]-50, VPStart);
            Image1->Canvas->LineTo(ImageAngleThresholds[1][n], VPStart);
            Image1->Canvas->LineTo(ImageAngleThresholds[1][n], VPEnd+DrawingOffset);
            Image1->Canvas->Pen->Width = 1;
            Image1->Canvas->Pen->Color = clBlack;
            Image1->Canvas->Rectangle(ImageAngleThresholds[1][n], VPEnd+DrawingOffset
            							, ImageAngleThresholds[1][n]-50, VPEnd+BoxHeight+DrawingOffset);
            //Copy the rectangle coords to the array for dragging later
            ThresholdDragStartX[1][n] = ImageAngleThresholds[1][n]-50;
        	ThresholdDragStartY[1][n] = VPEnd+DrawingOffset;
        	ThresholdDragEndX[1][n] = ImageAngleThresholds[1][n];
        	ThresholdDragEndY[1][n] = VPEnd+BoxHeight+DrawingOffset;

        	//Now draw the text
            Image1->Canvas->Pen->Color = clWhite;

            Text= "NT";
            Text += n+1;
            Text += " ";
            Text += ConvertXMouseToAngle(ImageAngleThresholds[1][n]);
            Image1->Canvas->TextOutA(ImageAngleThresholds[1][n]-48, VPEnd+TextOffset, Text);
        }
        DrawingOffset += 15;
        TextOffset += 15;
     }
}
//---------------------------------------------------------------------------

void TProfileEditForm::DragAngleThresholds(int X, int Y)
{
 	//Works out which anglethreshold you are over and drags it

    int XValue = X-ThresholdDragOffset;
    int YValue = Y-ThresholdDragOffset;

    int Angle = ConvertXMouseToAngle(XValue);
    int Force = ConvertYMouseToForceValue(YValue);

    if(Angle > 511) XValue = ConvertXAngleToMouse(512);
	if(Angle < -512) XValue = ConvertXAngleToMouse(-513);
    if(Force > 2176) YValue = ConvertForceValueToYMouse(2176);
	if(Force < -2176) YValue = ConvertForceValueToYMouse(-2176);
    switch (ThresholdBeingDragged)
    {
    case -1:
    	//StaticText1->Caption = "None Enabled";
        break;
    case 0:
        //StaticText1->Caption = X;
        //Drag PAT1
        ImageAngleThresholds[0][0] = XValue;
        //StaticText1->Caption = ImageAngleThresholds[0][0];
        break;
    case 1:
        //StaticText1->Caption = "NAT1";
        ImageAngleThresholds[1][0] =XValue;
        //StaticText1->Caption = ImageAngleThresholds[1][0];
        break;
    case 2:
        //Drag PAT2
        ImageAngleThresholds[0][1] = XValue;
        //StaticText1->Caption = ImageAngleThresholds[0][1];
        break;
    case 3:
        //Drag NAT2
        ImageAngleThresholds[1][1] = XValue;
        //StaticText1->Caption = ImageAngleThresholds[1][1];
        break;
    case 4:
        //Drag PAT3
        ImageAngleThresholds[0][2] = XValue;
        //StaticText1->Caption = ImageAngleThresholds[0][2];
        break;
    case 5:
        //Drag NAT3
        ImageAngleThresholds[1][2] = XValue;
        //StaticText1->Caption = ImageAngleThresholds[1][2];
        break;
    case 6:
        //Drag PAT4
        ImageAngleThresholds[0][3] = XValue;
        //StaticText1->Caption = ImageAngleThresholds[0][3];
        break;
    case 7:
        //Drag NAT4
        ImageAngleThresholds[1][3] = XValue;
        //StaticText1->Caption = ImageAngleThresholds[1][3];
        break;
    case 8:
        //StaticText1->Caption = X;
        //Drag PAT1
        ForceThresholdValues[0][0] = YValue;
        //StaticText1->Caption = ImageAngleThresholds[0][0];
        break;
    case 9:
        //StaticText1->Caption = "NAT1";
        ForceThresholdValues[1][0] =YValue;
        //StaticText1->Caption = ImageAngleThresholds[1][0];
        break;
    case 10:
        //Drag PAT2
        ForceThresholdValues[0][1] = YValue;
        //StaticText1->Caption = ImageAngleThresholds[0][1];
        break;
    case 11:
        //Drag NAT2
        ForceThresholdValues[1][1] = YValue;
        //StaticText1->Caption = ImageAngleThresholds[1][1];
        break;
    case 12:
        //Drag PAT3
        ForceThresholdValues[0][2] = YValue;
        //StaticText1->Caption = ImageAngleThresholds[0][2];
        break;
    case 13:
        //Drag NAT3
        ForceThresholdValues[1][2] = YValue;
        //StaticText1->Caption = ImageAngleThresholds[1][2];
        break;
    case 14:
        //Drag PAT4
        ForceThresholdValues[0][3] = YValue;
        //StaticText1->Caption = ImageAngleThresholds[0][3];
        break;
    case 15:
        //Drag NAT4
        ForceThresholdValues[1][3] = YValue;
        //StaticText1->Caption = ImageAngleThresholds[1][3];
        break;
    case 16:
        //Drag EQP
         EQImagePosition = XValue;
       // StaticText1->Caption = "Dragging EQP";
        break;
    default:
        //StaticText1->Caption = "Defaulting";
        break;
    }


}
//---------------------------------------------------------------------------

void DragForceThresholds(int X, int Y)
{
     //works out which force threshold you are over and drags it

}
//---------------------------------------------------------------------------

int TProfileEditForm::ConvertXMouseToProfile(int XMouse)
{
	//Converts the X Mouse position on the image to the X position in the profile
    return 0;
}
//---------------------------------------------------------------------------

int TProfileEditForm::ConvertForceValueToYMouse(int ForceVal)
{
    //Converts a raw int value to a force position on the Y axis of the image
    double result;
    result = ForceVal;
    result /= 16;
    return (int)(ProfileZero - result);
}

//---------------------------------------------------------------------------

int TProfileEditForm::ConvertYMouseToForceValue(int YMouse)
{
    //Converts a the YMouse Pos to a force value
    double result;
    result = (double)(ProfileZero - YMouse);
    result *= 16;
    return (int)result;
}

//---------------------------------------------------------------------------

double TProfileEditForm::ConvertXAngleToMouse(int XAngle)
{
    //Converts the X position as an angle to the X position in image
    double Result = (double)XAngle;
    if(Result > 511) Result = 512;
    if(Result < -512) Result = -513;
    Result += 512;
    //StaticText2->Caption = Result * XScalar;
    Result = Result * ScaleToImageXConstant;//0.876;
    //Result = (Result/16)*ImageXScalarValue;
    //StaticText1->Caption = Result;
    Result+=HPStart;
    return Result;

}
//---------------------------------------------------------------------------

int TProfileEditForm::ConvertXMouseToAngle(double XMouse)
{
    //Converts the X Mouse pos to an angle
    double Result = XMouse;
	Result -= HPStart;
    Result = Result * ScaleToAngleConstant;//1.1428571428571;
    //Result /= ImageXScalarValue;
    //Result *=16;
    Result -= 512;
    if(Result > 511) Result = 512;
    if(Result < -512) Result = -513;
    return (int)Result;
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::DrawProfileBackgroundExecute(
      TObject *Sender)
{
	//
    //Clear the Image
        Image1->Canvas->Pen->Color = clBlack;
        Image1->Canvas->Brush->Color = clWhite;
        Image1->Canvas->Rectangle(0, 0, Image1->Width, Image1->Height);

        //Draw some borders aroung the profile extents
        Image1->Canvas->Pen->Width = 1;
        Image1->Canvas->Pen->Color = clLtGray;
        Image1->Canvas->Brush->Color = clLtGray;
        Image1->Canvas->Rectangle(0, 0, Image1->Width, VPStart);
        Image1->Canvas->Rectangle(0, 0, HPStart, Image1->Height);
        Image1->Canvas->Rectangle(HPEnd, 0, Image1->Width, Image1->Height);
        Image1->Canvas->Rectangle(0, VPEnd, Image1->Width, Image1->Height);

        //Next draw the graph lines
        Image1->Canvas->Pen->Color = clBlack;
        Image1->Canvas->Pen->Width = 3;
        Image1->Canvas->MoveTo(HPStart,VPStart);
        Image1->Canvas->LineTo(HPStart,VPEnd);
        Image1->Canvas->MoveTo(HPEnd,VPStart);
        Image1->Canvas->LineTo(HPEnd,VPEnd);
        //Now draw the centre line
        Image1->Canvas->Pen->Width = 1;
        Image1->Canvas->MoveTo(HPStart-16,ProfileZero);
        Image1->Canvas->LineTo(HPEnd+16,ProfileZero);

}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::DrawProfileGraphAndTextExecute(
      TObject *Sender)
{
	//
    //draw the Max and Min lines
        int XPos;
        Image1->Canvas->Pen->Color = clBlack;
        Image1->Canvas->Pen->Width = 1;
        Image1->Canvas->MoveTo(HPStart-16,VPMin);
        Image1->Canvas->LineTo(HPEnd+16,VPMin);

        Image1->Canvas->MoveTo(HPStart-16,VPMax);
        Image1->Canvas->LineTo(HPEnd+16,VPMax);

        XPos = HPStart;


        //Now the vertical index lines if required
        /*Image1->Canvas->Pen->Color = clLtGray;
        for(int n = 0; n < 64; n++)
        {
                Image1->Canvas->MoveTo(XPos, VPStart);
                Image1->Canvas->LineTo(XPos, VPEnd);
                XPos += ImageXScalarValue;
        } */

        //Now draw thein/max text
        int VertTextOffset = 8;
        int AngleTextStart = (Image1->Width/2);
    	Image1->Canvas->Font->Color = clBlack;
        Image1->Canvas->Brush->Color = clWhite;
        Image1->Canvas->Font->Name = "Arial";
    	Image1->Canvas->Font->Size = 10;
    	//Image1->Canvas->Font->Style = TFontStyles()<< fsBold;

        Image1->Canvas->TextOutA(AngleTextStart, VPEnd-20,"Angle");
        Image1->Canvas->Brush->Color = clLtGray;
    	Image1->Canvas->TextOutA(HPStart-84, ProfileZero - (128+VertTextOffset), "+Max Force");
    	Image1->Canvas->TextOutA(HPStart-84, ProfileZero + (128-VertTextOffset), "-Max Force");
    	Image1->Canvas->TextOutA(HPStart-84, ProfileZero - VertTextOffset, "Zero Force");
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::CheckThresholdsForAngleExecute(
      TObject *Sender)
{
	//checks the thresholds to see if they are mapped to the angle or force
    //then prepares an array of data ready for drawing
    int IndexVal = _Threshold1Input_ptr;
    int PDefaultVal = _PT1Default;
 	int NDefaultVal = _NT1Default;
    int ValuePtr = _PT1Value_ptr;
    int EnablePtr = _PT1Enabled_ptr;
    int DrawAngles = 0, DrawForces = 0;
    //ForceThresholdActive[2][4];
    int TempEnable;

    for(int n = 0; n < 4; n++)
    {
        ImageAngleThresholds[0][n] = 0;
        ImageAngleThresholds[1][n] = 0;
        ImageAngleActive[0][n] = 0;
        ImageAngleActive[1][n] = 0;
        ForceThresholdValues[0][n] = 0;
        ForceThresholdValues[1][n] = 0;
        ForceThresholdActive[0][n] = 0;
        ForceThresholdActive[1][n] = 0;

        // TempSI16Ptr[IndexVal] == _ModifiedAngle || TempSI16Ptr[IndexVal] == _NOTModifiedAngle
        //TempSI16Ptr[IndexVal] == _Angle || TempSI16Ptr[IndexVal] == _NOTAngle
        if(  TempSI16Ptr[IndexVal] == _ModifiedAngle || TempSI16Ptr[IndexVal] == _NOTModifiedAngle )
        {
        	 ImageAngleThresholds[0][n] = ConvertXAngleToMouse(TempSI16Var[PDefaultVal]);
             ImageAngleThresholds[1][n] = ConvertXAngleToMouse(TempSI16Var[NDefaultVal]);
             ImageAngleActive[0][n] = 2;
             ImageAngleActive[1][n] = 2;
             TempEnable = TempI8Ptr[EnablePtr];
             if(TempSI16Ptr[ValuePtr] == PDefaultVal && TempEnable == _GlobalThresholdEnabled)
             {
             	ImageAngleActive[0][n] = 1;
             }
             if(TempEnable == _GlobalDefaultTrue)
             {
             	ImageAngleActive[0][n] = 1;
             }
             TempEnable = TempI8Ptr[EnablePtr+1];
             if(TempSI16Ptr[ValuePtr+1] == NDefaultVal && TempEnable == _GlobalThresholdEnabled)
             {
             	ImageAngleActive[1][n] = 1;
             }
             if(TempEnable == _GlobalDefaultTrue)
             {
             	ImageAngleActive[1][n] = 1;
             }
        }
        if(  TempSI16Ptr[IndexVal] == _Angle || TempSI16Ptr[IndexVal] == _NOTAngle )
        {
        	 ImageAngleThresholds[0][n] = ConvertXAngleToMouse(TempSI16Var[PDefaultVal]);
             ImageAngleThresholds[1][n] = ConvertXAngleToMouse(TempSI16Var[NDefaultVal]);
             ImageAngleActive[0][n] = 2;
             ImageAngleActive[1][n] = 2;
             TempEnable = TempI8Ptr[EnablePtr];
             if(TempSI16Ptr[ValuePtr] == PDefaultVal && TempEnable == _GlobalThresholdEnabled)
             {
             	ImageAngleActive[0][n] = 1;
             }
             if(TempEnable == _GlobalDefaultTrue)
             {
             	ImageAngleActive[0][n] = 1;
             }
             TempEnable = TempI8Ptr[EnablePtr+1];
             if(TempSI16Ptr[ValuePtr+1] == NDefaultVal && TempEnable == _GlobalThresholdEnabled)
             {
             	ImageAngleActive[1][n] = 1;
             }
             if(TempEnable == _GlobalDefaultTrue)
             {
             	ImageAngleActive[1][n] = 1;
             }
        }
        //Now force thresholds
        if( TempSI16Ptr[IndexVal] == _FTarget || TempSI16Ptr[IndexVal] == _MeasuredForce )
        {
             //Convert Variable to YPos
        	 ForceThresholdValues[0][n] = ConvertForceValueToYMouse(TempSI16Var[PDefaultVal]);
             ForceThresholdValues[1][n] = ConvertForceValueToYMouse(TempSI16Var[NDefaultVal]);

             ForceThresholdActive[0][n] = 2;
             ForceThresholdActive[1][n] = 2;
             TempEnable = TempI8Ptr[EnablePtr];
             if(TempSI16Ptr[ValuePtr] == PDefaultVal && TempEnable == _GlobalThresholdEnabled )
             {
             	ForceThresholdActive[0][n] = 1;
             }
             if(TempEnable == _GlobalDefaultTrue)
             {
             	ForceThresholdActive[0][n] = 1;
             }
             TempEnable = TempI8Ptr[EnablePtr+1];
             if(TempSI16Ptr[ValuePtr+1] == NDefaultVal && TempEnable == _GlobalThresholdEnabled)
             {
             	ForceThresholdActive[1][n] = 1;
             }
             if(TempEnable == _GlobalDefaultTrue)
             {
             	ForceThresholdActive[1][n] = 1;
             }
        }
        //Now Velocity thresholds
        if( TempSI16Ptr[IndexVal] == _AngleVelocity || TempSI16Ptr[IndexVal] == _NOTAngleVelocity )
        {
             //Convert Variable to YPos
        	 VelocityThresholdValues[0][n] = TempSI16Var[PDefaultVal]/8;
             VelocityThresholdValues[1][n] = TempSI16Var[NDefaultVal]/8;

             VelocityThresholdActive[0][n] = 2;
             VelocityThresholdActive[1][n] = 2;
             TempEnable = TempI8Ptr[EnablePtr];
             if(TempSI16Ptr[ValuePtr] == PDefaultVal && TempEnable == _GlobalThresholdEnabled )
             {
             	VelocityThresholdActive[0][n] = 1;
             }
             if(TempEnable == _GlobalDefaultTrue)
             {
             	VelocityThresholdActive[0][n] = 1;
             }
             TempEnable = TempI8Ptr[EnablePtr+1];
             if(TempSI16Ptr[ValuePtr+1] == NDefaultVal && TempEnable == _GlobalThresholdEnabled)
             {
             	VelocityThresholdActive[1][n] = 1;
             }
             if(TempEnable == _GlobalDefaultTrue)
             {
             	VelocityThresholdActive[1][n] = 1;
             }
        }


    	IndexVal++;
        PDefaultVal+=2;
        NDefaultVal+=2;
        ValuePtr+=2;
        EnablePtr+=2;

    }
}
//---------------------------------------------------------------------------



void __fastcall TProfileEditForm::Timer1Timer(TObject *Sender)
{
	//try using to refresh the images

    RedrawAndRefresh->Execute();	
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::Image1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	Timer1->Enabled = false;
    RedrawVelocityGraphics->Execute();
    RedrawAndRefresh->Execute();
    int PDefaultVal = _PT1Default;
 	int NDefaultVal = _NT1Default;
	for(int n = 0; n < 4; n++)
    {
    	if(ImageAngleActive[0][n] > 0)
        {
    		TempSI16Var[PDefaultVal] = ConvertXMouseToAngle(ImageAngleThresholds[0][n]);
        }
        if(ImageAngleActive[1][n] > 0)
        {
    		TempSI16Var[NDefaultVal] = ConvertXMouseToAngle(ImageAngleThresholds[1][n]);
        }
        if(ForceThresholdActive[0][n] > 0)
        {
    		TempSI16Var[PDefaultVal] = ConvertYMouseToForceValue(ForceThresholdValues[0][n]);
        }
        if(ForceThresholdActive[1][n] > 0)
        {
    		TempSI16Var[NDefaultVal] = ConvertYMouseToForceValue(ForceThresholdValues[1][n]);
        }
        PDefaultVal+=2;
        NDefaultVal+=2;
    }
    TempSI16Var[ _EQAngle ] = ConvertXMouseToAngle(EQImagePosition);


}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::DrawEQPExecute(TObject *Sender)
{
	//Draws a line for the EQPoint (Horizontal scaling origin)


    //EQImagePosition = ConvertXAngleToMouse(  TempSI16Var[ _EQAngle ] );
    Image1->Canvas->Pen->Color = clPurple;
    Image1->Canvas->Brush->Color = clPurple;
    Image1->Canvas->Pen->Width = 1;
    Image1->Canvas->Rectangle(EQImagePosition-55, VPStart-16, EQImagePosition+55, VPStart);
    //Update the box info for dragging
    //EQPXStart, EQPXEnd, EQPYStart, EQPYEnd;

    //update mouse drag area
    EQPXStart = EQImagePosition-55;
    EQPXEnd = EQImagePosition+55;
    EQPYStart = VPStart-16;
    EQPYEnd = VPStart;

    Image1->Canvas->MoveTo(EQImagePosition, VPStart-16);
    Image1->Canvas->LineTo(EQImagePosition, VPEnd-30);
    //Image1->Canvas->LineTo(EQImagePosition, VPEnd+8);



    AnsiString Caption = "H Scale Origin: ";
    Caption += ConvertXMouseToAngle(EQImagePosition);
    Image1->Canvas->Font->Color = clWhite;
    Image1->Canvas->Font->Name = "Arial";
    Image1->Canvas->Font->Size = 7;
    Image1->Canvas->TextOutA(EQImagePosition-46, VPStart-13, Caption);
}
//---------------------------------------------------------------------------

int  TProfileEditForm::DetermineImageDragItem(int X, int Y)
{
    //returns the item being dragged or -1 if none
    //offset is set to the difference between the mouse pos and the value being edited
    //Now the EQ Point
    //EQPXStart, EQPXEnd, EQPYStart, EQPYEnd;
    if( X > EQPXStart && X < EQPXEnd && Y > EQPYStart && Y < EQPYEnd )
    {
    	//StaticText1->Caption = "EQPEdit";
    	ThresholdDragOffset = X-EQImagePosition;
    	return 16;
    }
    
    int ReturnVal = 0;
    for(int n = 0; n < 4; n++)
    {
    	if(X > ThresholdDragStartX[0][n] && X < ThresholdDragEndX[0][n]
    			&& Y > ThresholdDragStartY[0][n] && Y < ThresholdDragEndY[0][n] )
    	{
    		//you are in threshold tab PATn
        	if( ImageAngleActive[0][n] )
        	{
            	ThresholdDragOffset = X - ThresholdDragStartX[0][n];
        		return ReturnVal;
        	}
        	return -1;
    	}
        if(X > ThresholdDragStartX[1][n] && X < ThresholdDragEndX[1][n]
    			&& Y > ThresholdDragStartY[1][n] && Y < ThresholdDragEndY[1][n] )
    	{
    		//you are in threshold tab NATn
        	if( ImageAngleActive[1][n] )
        	{
            	ThresholdDragOffset =  X - ThresholdDragEndX[1][n];
        		return ReturnVal+1;
        	}
        	return -1;
    	}
        ReturnVal+=2;
    }
    //Now check to see if you are dragging a force threshold
	for(int n = 0; n < 4; n++)
    {
    	if(X > ForceThresholdDragStartX[0][n] && X < ForceThresholdDragEndX[0][n]
    			&& Y > ForceThresholdDragStartY[0][n] && Y < ForceThresholdDragEndY[0][n] )
    	{
    		//you are in threshold tab PATn
        	if( ForceThresholdActive[0][n] )
        	{
            	ThresholdDragOffset = Y - ForceThresholdDragEndY[0][n];
        		return ReturnVal;
        	}
        	return -1;
    	}
        if(X > ForceThresholdDragStartX[1][n] && X < ForceThresholdDragEndX[1][n]
    			&& Y > ForceThresholdDragStartY[1][n] && Y < ForceThresholdDragEndY[1][n] )
    	{
    		//you are in threshold tab NATn
        	if( ForceThresholdActive[1][n] )
        	{
            	ThresholdDragOffset =  Y - ForceThresholdDragStartY[1][n];
        		return ReturnVal+1;
        	}
        	return -1;
    	}
        ReturnVal+=2;
    }

    return -1;
}
//---------------------------------------------------------------------------
void __fastcall TProfileEditForm::DrawForceThresholdsExecute(
      TObject *Sender)
{
	//Draws any thresholds that apply to the force axis
    int PT, NT;
    AnsiString Text;
    int DrawingOffset=0;
    int BoxWidth = 50;
    int BoxHeight = 14;
    int TextOffset = 6;
    Image1->Canvas->Font->Color = clWhite;
    Image1->Canvas->Font->Name = "Arial";
    Image1->Canvas->Font->Size = 7;
    	//Image1->Canvas->Brush->Color = clLtGray;
    	//Image1->Canvas->Font->Style = TFontStyles()<< fsBold;
     for(int n = 0; n < 4; n++)
     {
     	if(ForceThresholdActive[0][n] !=0 || ForceThresholdActive[1][n] !=0)
        {
        	//draw the positive threshold
            Image1->Canvas->Pen->Width = 3;

            //check to see if it should be greyed
            if( ForceThresholdActive[0][n] == 1 )
            {
            	Image1->Canvas->Pen->Color = clBlue;
            	Image1->Canvas->Brush->Color = clBlue;
            }
            if( ForceThresholdActive[0][n] == 2 )
            {
            	Image1->Canvas->Pen->Color = clDkGray	;
            	Image1->Canvas->Brush->Color = clDkGray	;
            }
            Image1->Canvas->MoveTo(HPStart-8, ForceThresholdValues[0][n]-50);
            Image1->Canvas->LineTo(HPStart-8, ForceThresholdValues[0][n]);
            Image1->Canvas->LineTo(HPEnd, ForceThresholdValues[0][n]);
            Image1->Canvas->Pen->Width = 1;
            Image1->Canvas->Pen->Color = clBlack ;

            Image1->Canvas->Rectangle(HPEnd, ForceThresholdValues[0][n]-BoxHeight
            						, HPEnd+BoxWidth, ForceThresholdValues[0][n]);
            //Copy the rectangle coords to the array for dragging later
            ForceThresholdDragStartX[0][n] =  HPEnd;
        	ForceThresholdDragStartY[0][n] = ForceThresholdValues[0][n]-BoxHeight;
        	ForceThresholdDragEndX[0][n] = HPEnd+BoxWidth;
        	ForceThresholdDragEndY[0][n] = ForceThresholdValues[0][n];

            Image1->Canvas->Pen->Color = clWhite;
            Text= "PT";
            Text += n+1;
            Text += " ";
            Text += ConvertYMouseToForceValue(ForceThresholdValues[0][n]);
            //StaticText2->Caption = ConvertYMouseToForceValue(ForceThresholdValues[0][n]);
            Image1->Canvas->TextOutA(HPEnd+4, ForceThresholdValues[0][n]-13, Text);


            //draw the negative threshold
            Image1->Canvas->Pen->Width = 3;
            //check to see if it should be greyed
            if( ForceThresholdActive[1][n] == 1 )
            {
            	Image1->Canvas->Pen->Color = clGreen;
            	Image1->Canvas->Brush->Color = clGreen;
            }
            if( ForceThresholdActive[1][n] == 2 )
            {
            	Image1->Canvas->Pen->Color = clDkGray	;
            	Image1->Canvas->Brush->Color = clDkGray	;
            }
            Image1->Canvas->MoveTo(HPStart-8, ForceThresholdValues[1][n]+50);
            Image1->Canvas->LineTo(HPStart-8, ForceThresholdValues[1][n]);
            Image1->Canvas->LineTo(HPEnd, ForceThresholdValues[1][n]);
            Image1->Canvas->Pen->Width = 1;
            Image1->Canvas->Pen->Color = clBlack ;

            Image1->Canvas->Rectangle(HPEnd, ForceThresholdValues[1][n]
            						, HPEnd+BoxWidth, ForceThresholdValues[1][n]+BoxHeight);
            //Copy the rectangle coords to the array for dragging later
            ForceThresholdDragStartX[1][n] =  HPEnd;
        	ForceThresholdDragStartY[1][n] = ForceThresholdValues[1][n];
        	ForceThresholdDragEndX[1][n] = HPEnd+BoxWidth;
        	ForceThresholdDragEndY[1][n] = ForceThresholdValues[1][n]+BoxHeight;

            Image1->Canvas->Pen->Color = clWhite;
            Text= "NT";
            Text += n+1;
            Text += " ";
            Text += ConvertYMouseToForceValue(ForceThresholdValues[1][n]);
            //StaticText2->Caption = ConvertYMouseToForceValue(ForceThresholdValues[0][n]);
            Image1->Canvas->TextOutA(HPEnd+4, ForceThresholdValues[1][n]+1, Text);


        }
        //DrawingOffset += 15;
        //TextOffset += 15;
     }
    	
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::DrawVelocityThresholdsExecute(
      TObject *Sender)
{
	//DrawVelocityBackground->Execute();
    int HalfHeight = Image2->Height/2;
    for(int n = 0; n < 4; n++)
     {
     	if(VelocityThresholdActive[0][n] !=0 || VelocityThresholdActive[1][n] !=0)
        {
        	//draw the positive threshold
            //check to see if it should be greyed
            if( VelocityThresholdActive[0][n] == 1 )
            {
            	Image2->Canvas->Pen->Color = clBlue;
            	Image2->Canvas->Brush->Color = clBlue;
            }
            if( VelocityThresholdActive[0][n] == 2 )
            {
            	Image2->Canvas->Pen->Color = clDkGray	;
            	Image2->Canvas->Brush->Color = clDkGray	;
            }
            Image2->Canvas->MoveTo(0, HalfHeight+VelocityThresholdValues[0][n]);
            Image2->Canvas->LineTo(Image2->Width, HalfHeight+VelocityThresholdValues[0][n]);

            //draw the negative threshold
            //check to see if it should be greyed
            if( VelocityThresholdActive[1][n] == 1 )
            {
            	Image2->Canvas->Pen->Color = clGreen;
            	Image2->Canvas->Brush->Color = clGreen;
            }
            if( VelocityThresholdActive[1][n] == 2 )
            {
            	Image2->Canvas->Pen->Color = clDkGray	;
            	Image2->Canvas->Brush->Color = clDkGray	;
            }
            Image2->Canvas->MoveTo(0, HalfHeight+VelocityThresholdValues[1][n]);
            Image2->Canvas->LineTo(Image2->Width, HalfHeight+VelocityThresholdValues[1][n]);
        }
     }
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::DrawVelocityBackgroundExecute(
      TObject *Sender)
{
	//now defunct
    VelocityImageVCentre = Image2->Height/1.5;
    VelocityImageHCentre = Image2->Width/2;

    Image2->Canvas->Brush->Color = clWhite;
    Image2->Canvas->Pen->Color = clBlack;
    Image2->Canvas->Rectangle(0, 0, Image2->Width, Image2->Height);


    Image2->Canvas->Brush->Color = clRed;
    Image2->Canvas->Ellipse(VelocityImageHCentre-30, VelocityImageVCentre-30,
    								VelocityImageHCentre+30, VelocityImageVCentre+30);

    Image2->Canvas->Pen->Color = clLtGray;
    Image2->Canvas->MoveTo(VelocityImageHCentre, VelocityImageVCentre);
    Image2->Canvas->LineTo(VelocityImageHCentre, VelocityImageVCentre-60);
    Image2->Canvas->MoveTo(VelocityImageHCentre-60, VelocityImageVCentre);
    Image2->Canvas->LineTo(VelocityImageHCentre+60, VelocityImageVCentre);

   	Image2->Canvas->Font->Color = clBlack;
    Image2->Canvas->Brush->Color = clWhite;
    Image2->Canvas->Font->Name = "Arial";
    Image2->Canvas->Font->Size = 12;
    
    Image2->Canvas->TextOutA(VelocityImageHCentre-110, VelocityImageVCentre-10, "-Max");
    Image2->Canvas->TextOutA(VelocityImageHCentre+80, VelocityImageVCentre-10, "+Max");
    Image2->Canvas->TextOutA(VelocityImageHCentre-17, VelocityImageVCentre-100, "Zero");
}
//---------------------------------------------------------------------------





void __fastcall TProfileEditForm::EditThresholdsExecute(TObject *Sender)
{
	//Opens the threshold editor window -
    //passing the appropriate threhsold to be edited to the window

    if(ThresholdGroupSettingsForm != NULL) return;
    ThresholdGroupSettingsForm = new TThresholdGroupSettingsForm(Application);
    ThresholdGroupSettingsForm->PageControl1->ActivePageIndex = ThresholdClickEdit;
    ThresholdGroupSettingsForm->ShowModal();
    delete ThresholdGroupSettingsForm;
    ThresholdGroupSettingsForm = NULL;
    ThresholdClickEdit = 0;
    CheckThresholdsForAngle->Execute();
    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::EditModulatorsExecute(TObject *Sender)
{
	//open the scale and bias editor
    if(ModulatorsEditForm != NULL) return;
    ModulatorsEditForm = new TModulatorsEditForm(Application);
    ModulatorsEditForm->PageControl1->ActivePageIndex = ModulatorClickEdit;
    ModulatorsEditForm->ShowModal();
    delete ModulatorsEditForm;
    ModulatorsEditForm = NULL;
    ModulatorClickEdit = 0;
    EQImagePosition = ConvertXAngleToMouse(  TempSI16Var[ _EQAngle ] );
    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TProfileEditForm::EditProfileInteractionsExecute(
      TObject *Sender)
{
	//Edit the profile switcher system
    if(ProfileInteractionEditForm != NULL) return;
    ProfileInteractionEditForm = new TProfileInteractionEditForm(Application);
    ProfileInteractionEditForm->PageControl1->ActivePageIndex = InteractionsClickEdit;
    ProfileInteractionEditForm->ShowModal();
    delete ProfileInteractionEditForm;
    ProfileInteractionEditForm = NULL;
    InteractionsClickEdit = 0;
    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::EditOutputsExecute(TObject *Sender)
{
 	//Open the digital I/O Editor

    if(InputOutputForm != NULL) return;
    InputOutputForm = new TInputOutputForm(Application);
    InputOutputForm->PageControl1->ActivePageIndex = OutputsClickEdit;
    InputOutputForm->ShowModal();

    delete InputOutputForm;
    OutputsClickEdit = 0;
    InputOutputForm = NULL;
    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::EditGroupTriggerExecute(TObject *Sender)
{
	//Open the summed flag editor
    if(GroupTriggerForm != NULL) return;
    GroupTriggerForm = new TGroupTriggerForm(Application);
    GroupTriggerForm->ShowModal();
    delete GroupTriggerForm;
    GroupTriggerForm = NULL;
    RedrawAndRefresh->Execute();	
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::EditMotorEnableExecute(TObject *Sender)
{
    //Open the motor and force enable settings

    if(MotorEnableForm != NULL) return;
    MotorEnableForm = new TMotorEnableForm(Application);
    MotorEnableForm->ShowModal();
    delete MotorEnableForm;
    MotorEnableForm = NULL;
    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::Group11Click(TObject *Sender)
{
	//
    ThresholdClickEdit = 0;
    EditThresholds->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::Group21Click(TObject *Sender)
{
	//
    ThresholdClickEdit = 1;
    EditThresholds->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::Group31Click(TObject *Sender)
{
	//
    ThresholdClickEdit = 2;
    EditThresholds->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::Group41Click(TObject *Sender)
{
	//
    ThresholdClickEdit = 3;
    EditThresholds->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::ProfileSwitching1Click(TObject *Sender)
{
	//
    InteractionsClickEdit  = 0;
    EditProfileInteractions->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::InterprofileCommunications1Click(
      TObject *Sender)
{
    InteractionsClickEdit  = 1;
    EditProfileInteractions->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::ScaleAndBias1Click(TObject *Sender)
{
	ModulatorClickEdit = 0;
    EditModulators->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::InternalOscillator1Click(TObject *Sender)
{
    ModulatorClickEdit = 1;
    EditModulators->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::RS232SerialOutput1Click(TObject *Sender)
{
	OutputsClickEdit = 0;
    EditOutputs->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::CANBUSOutput1Click(TObject *Sender)
{
	OutputsClickEdit = 1;
    EditOutputs->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::DiscreteAnalogandDigitalOutputs1Click(
      TObject *Sender)
{
	OutputsClickEdit = 2;
    EditOutputs->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::OpenProfileGeneratorExecute(
      TObject *Sender)
{
	//opens the profile generator form
    
    if(ProfileGeneratorForm != NULL) return;
    ProfileGeneratorForm = new TProfileGeneratorForm(Application);
    ProfileGeneratorForm->ShowModal();
    delete ProfileGeneratorForm;
    ProfileGeneratorForm = NULL;
    RedrawVelocityGraphics->Execute();
    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TProfileEditForm::FlipProfileVerticalExecute(
      TObject *Sender)
{
	//Invert the profile
    for(int n = 0; n < 64; n++)
    {
    	TempFPro[n] = -TempFPro[n];
    }
    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::FlipProfileHorizontalExecute(
      TObject *Sender)
{
	int TempData[64];
    for(int n = 0; n < 64; n++)
    {
        TempData[n] = TempFPro[n];

    }
    for(int n = 0; n < 64; n++)
    {
         TempFPro[n] = TempData[63-n];
    }
   RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::FormHide(TObject *Sender)
{
	 REMOTE->EditingProfileNo = CurrentEditingProfile;
     REMOTE->RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::FormShow(TObject *Sender)
{
	//
    CurrentEditingProfile = REMOTE->EditingProfileNo;
        Title = "Editing Profile No: ";
        Title += CurrentEditingProfile;
        ProfileEditForm->Caption = Title;
        SelectProfileBox->ItemIndex = CurrentEditingProfile;
    for(int n = 0; n < 4; n++)
        {
        	ImageAngleThresholds[0][n] = 1024; //[PAT, NAT][1-4];
            ImageAngleThresholds[1][n] = -1;
            ImageAngleActive[0][n] = 0;
            ImageAngleActive[01][n] = 0;
            ForceThresholdValues[0][n] = ProfileZero-128; //[PAT, NAT][1-4];
            ForceThresholdValues[1][n] = ProfileZero+128;
            ForceThresholdActive[0][n] = 0;
            ForceThresholdActive[1][n] = 0;
        }

        CopyToLocalArrays->Execute();
        SetupComboBoxes->Execute();
        CheckThresholdsForAngle->Execute();
        EQImagePosition = ConvertXAngleToMouse(  TempSI16Var[ _EQAngle ] );
        DrawProfile->Execute();
        RedrawAndRefresh->Execute();

        ThresholdClickEdit = 0;
        ModulatorClickEdit = 0;
        OutputsClickEdit = 0;
        InteractionsClickEdit = 0;
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::OpenSurfacePlotWindowExecute(
      TObject *Sender)
{
    	//
    //Edit the actuator settings
     if(ForceSurfacePlotForm != NULL) return;
    ForceSurfacePlotForm = new TForceSurfacePlotForm(Application);
    ForceSurfacePlotForm->ShowModal();
    delete ForceSurfacePlotForm;
    ForceSurfacePlotForm = NULL;
}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::DrawForceMapExecute(TObject *Sender)
{
	//Draw a force map on Image2
    //Draw a contour map with colour as force
    int XStart = 100;
    int YStart = 20;
    int XPos, YPos;
    int Size = 2;
    //centre the image on the drawing area
    XStart = Image2->Width/2;
    XStart -= Size*64;
    YStart = Image2->Height/2;
    YStart -= Size*65;
    double ProfileForce = 0;
    Image2->Canvas->Brush->Color = clWhite;
    Image2->Canvas->Pen->Color = clWhite;
    Image2->Canvas->Rectangle(0, 0, Image2->Width, Image2->Height);

    //Image2->Canvas->Pen->Color = GetColour(0,0,0);
    //Image2->Canvas->Pen->Width = 1;

    XPos = XStart;
    YPos = YStart;
    for(int v = 32; v > -32; v--)
    {
    	for(int x = 0; x < 64; x++)
    	{
        	Image2->Canvas->Brush->Color = GetFinalForceColor(x, v);
            Image2->Canvas->Pen->Color =  Image2->Canvas->Brush->Color;
            Image2->Canvas->Rectangle(XPos-Size, YPos-Size, XPos+Size, YPos+Size);
            XPos += Size*2;
        }
        XPos = XStart;
        YPos += Size*2;
    }


}
//---------------------------------------------------------------------------
TColor TProfileEditForm::GetFinalForceColor(int Angle, int Velocity)
{
	double FinalForce;
    double ProfileForce;
    double PDamping;
    double NDamping;
    int TempInt;
    double RealV;
    int RedX = 0, GreenX = 0, BlueX = 0;
    TColor ReturnVal;

    int Index = 0;
    Index = Angle;
    if(Index > 63)  Index = 63;
    if(Index < 0) Index = 0;
    ProfileForce = (double)TempFPro[Index];
    ProfileForce /= 2048;
    PDamping = (double)TempPDamp[Index];
    PDamping /= 64;
    NDamping = (double)TempNDamp[Index];
    NDamping /= 64;
    RealV = ((double)Velocity) / 32;
    if(Velocity < 0)
    {
    	FinalForce = ProfileForce - ( RealV * NDamping );
    }
    else if(Velocity > 0)
    {
    	FinalForce = ProfileForce - ( RealV * PDamping );
    }
    else FinalForce = ProfileForce;
    //FinalForce += VBias;
    //if(FinalForce > 1.0) FinalForce = 1.0;
    //if(FinalForce < -1.0) FinalForce = -1.0;

    if(FinalForce > 0) BlueX = (int)(FinalForce*255);
    if(FinalForce < 0) RedX = (int)(FinalForce*255);
    return GetColour(-RedX, GreenX, BlueX);
}
    
//---------------------------------------------------------------------------

TColor TProfileEditForm::GetColour(int RedComponent, int GreenComponent, int BlueComponent)
{
	if(RedComponent > 255) RedComponent = 255;
    if(GreenComponent > 255) GreenComponent = 255;
    if(BlueComponent > 255) BlueComponent = 255;
    if(RedComponent < 0) RedComponent = 0;
    if(GreenComponent < 0) GreenComponent = 0;
    if(BlueComponent < 0) BlueComponent = 0;
	int rcol, gcol, bcol, col;
	rcol = RedComponent;
    gcol = GreenComponent;
    gcol <<= 8;
    bcol = BlueComponent;
    bcol <<= 16;
    col = rcol;
    col  = col|gcol;
    col = col|bcol;
    return (TColor)col;
}
//---------------------------------------------------------------------------


void __fastcall TProfileEditForm::RedrawVelocityGraphicsExecute(
      TObject *Sender)
{
	//
    DrawForceMap->Execute();

    if( ShowVThresholdsBox->Checked == true)DrawVelocityThresholds->Execute();
    RefreshImage->Execute();

}
//---------------------------------------------------------------------------

void __fastcall TProfileEditForm::DefaultTimerButtonClick(TObject *Sender)
{
	//
    TimerThresholdEdit->Text = TIMERSATURATION+1;	
}
//---------------------------------------------------------------------------

