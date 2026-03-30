//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ForceSurfaceUnit.h"
#include "ProfileEditUnit.h"
#include "bcb_pgm.h"

#define ImageRect1  Rect( 0, 0, Image1->Width, Image1->Height)
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForceSurfacePlotForm *ForceSurfacePlotForm;
//---------------------------------------------------------------------------
__fastcall TForceSurfacePlotForm::TForceSurfacePlotForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForceSurfacePlotForm::UpdateImageExecute(TObject *Sender)
{
	PaintBox1->Canvas->CopyMode = cmSrcCopy;
    PaintBox1->Canvas->CopyRect(ImageRect1, Image1->Canvas, ImageRect1);
}
//---------------------------------------------------------------------------
void __fastcall TForceSurfacePlotForm::DrawSurfaceExecute(TObject *Sender)
{
	//Draws a surface with filled polygons
     TPoint points[4];
    //Draw the 3D Surface
    double HalfHeight = Image1->Height/2;
    double StartX = 276+ViewAngleOffset;
    double GraphHeight = 100;
    double StartY = (HalfHeight + GraphHeight)-300;
    double BottomY = StartY+80;
    double TopY = StartY-80;
    double Step = 8.0;//*HScale;
    double YVStep = 4.0;
    double XVStep = 4.0*ViewAngleTweak;
    double XVal, YVal, NextXVal, NextYVal;
    double ProfileForce;
    double VScale = 80.0;
    double X1, X2, X3, X4, Y1, Y2, Y3, Y4;
    double ColorVal;
    int Angle = 0;
    ClearImage->Execute();

    Image1->Canvas->Pen->Color = GetColour(0,0,0);
    Image1->Canvas->Pen->Width = 1;
    //ProfileForce = FinalForceValues[0][64];
    //YVal = StartY-(ProfileForce*VScale);
    XVal = StartX;
    for(int v = 64; v > 0; v--)
    {
    	XVal = StartX;
    	for(double x = HBias; x < HBias+63; x++) //x+= HScale
    	{

        	Angle = (int)x;
            if(Angle < 0) Angle = 0;
            if(Angle > 62) Angle = 62;
        	ProfileForce = FinalForceValues[Angle][v];
            ColorVal = ProfileForce;
        	Y1 = StartY-(ProfileForce*VScale);
            X1 = XVal;
            points[0] = Point(X1,Y1);

        	ProfileForce = FinalForceValues[Angle+1][v];
        	Y2 = StartY-(ProfileForce*VScale);
        	X2 = X1 + Step;
  			points[1] = Point(X2,Y2);

        	ProfileForce = FinalForceValues[Angle+1][v-1];
        	Y3 = (StartY-(ProfileForce*VScale) )+YVStep;
            X3 = X2 - XVStep;
  			points[2] = Point(X3,Y3);

            ProfileForce = FinalForceValues[Angle][v-1];
            Y4 = (StartY-(ProfileForce*VScale) )+YVStep;
            X4 = XVal-XVStep;
            points[3] = Point(X4,Y4);

            if(ColorVal > 0) Image1->Canvas->Pen->Color = GetColour(0,0,(int)(ColorVal*255) );
        	else if(ColorVal < 0) Image1->Canvas->Pen->Color = GetColour((int)(-ColorVal*255),0,0);
        	else   Image1->Canvas->Pen->Color = GetColour(0,0,0);
            if(FilledBox->Checked == true) Image1->Canvas->Brush->Color = Image1->Canvas->Pen->Color;
            else Image1->Canvas->Brush->Color = clWhite;
    		Image1->Canvas->Polygon(points, 3);
            XVal += Step;
        }
        StartY += YVStep;
        StartX -= XVStep;
        //Step -= PerspectiveScale;

    }


}
//---------------------------------------------------------------------------

double TForceSurfacePlotForm::GetFinalForceValue(int Angle, int Velocity)
{
	double FinalForce;
    double ProfileForce;
    double PDamping;
    double NDamping;
    int TempInt;
    double RealV;
    double SubForce, NextForce;
    int Index = 0;
    AnsiString DataLine;

    Index = Angle;
    if(Index > 63)  Index = 63;
    if(Index < 0) Index = 0;
    ProfileForce = (double)ProfileEditForm->TempFPro[Index];
    ProfileForce /= 2048;
    PDamping = (double)ProfileEditForm->TempPDamp[Index];
    PDamping /= 64;
    NDamping = (double)ProfileEditForm->TempNDamp[Index];
    NDamping /= 64;
    RealV = ((double)Velocity) / 512;
    if(Velocity < 0)
    {
    	FinalForce = ProfileForce - ( RealV * NDamping );
    }
    else if(Velocity > 0)
    {
    	FinalForce = ProfileForce - ( RealV * PDamping );
    }
    else FinalForce = ProfileForce;
    FinalForce += VBias;
    if(FinalForce > 1.0) FinalForce = 1.0;
    if(FinalForce < -1.0) FinalForce = -1.0;
    return FinalForce;
}

//---------------------------------------------------------------------------
TColor TForceSurfacePlotForm::GetColour(int RedComponent, int GreenComponent, int BlueComponent)
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

void __fastcall TForceSurfacePlotForm::CreateGraphDataExecute(
      TObject *Sender)
{
	//copy and calculate final forces int the 2d array of final force values
    int VIndex = 0;
    for(int Vel = -512; Vel < 513; Vel+=16)
    {
    	for(int Ang = 0; Ang < 64; Ang++)
    	{
    		FinalForceValues[Ang][VIndex] = GetFinalForceValue(Ang, Vel);

        }
     	VIndex++;
    }

}
//---------------------------------------------------------------------------

void __fastcall TForceSurfacePlotForm::DrawContourExecute(TObject *Sender)
{
	//Draw a contour map with colour as force
    int XStart = 100;
    int YStart = 20;
    int XPos, YPos;
    int Size = 4;
    //centre the image on the drawing area
    XStart = Image1->Width/2;
    XStart -= Size*64;
    YStart = Image1->Height/2;
    YStart -= Size*65;
    double ProfileForce = 0;
    ClearImage->Execute();

    Image1->Canvas->Pen->Color = GetColour(0,0,0);
    Image1->Canvas->Pen->Width = 1;

    XPos = XStart;
    YPos = YStart;
    for(int v = 64; v > -1; v--)
    {
    	for(int x = 0; x < 64; x++)
    	{
        	ProfileForce = FinalForceValues[x][v];
            if(ProfileForce > 0) Image1->Canvas->Brush->Color = GetColour(0,0,(int)(ProfileForce*255) );
        	else if(ProfileForce < 0) Image1->Canvas->Brush->Color = GetColour((int)-(ProfileForce*255),0,0);
        	else   Image1->Canvas->Brush->Color = GetColour(0,0,0);
            Image1->Canvas->Pen->Color =  Image1->Canvas->Brush->Color;
            Image1->Canvas->Rectangle(XPos-Size, YPos-Size, XPos+Size, YPos+Size);
            XPos += Size*2;
        }
        XPos = XStart;
        YPos += Size*2;
    }
   /* TPoint points[4];
  	points[0] = Point(10,10);
  	points[1] = Point(30,10);
  	points[2] = Point(130,30);
  	points[3] = Point(240,120);

    Image1->Canvas->Polygon(points, 3); */
    	
}
//---------------------------------------------------------------------------

void __fastcall TForceSurfacePlotForm::DrawGraphsExecute(TObject *Sender)
{
    CreateGraphData->Execute();
	//Decide using checkboxes which graph to draw
    ViewAngleTweak = ((double)TrackBar1->Position)/50;
    ViewAngleOffset = ((double)TrackBar1->Position-50)*ViewAngleOffsetScale;
    HBias = HBiasBar->Position;
    StaticText1->Caption = HBias;

    HScale = ((float)HScaleBar->Position)/10;
    StaticText2->Caption = HScale;

    VBias = -(((float)VBiasBar->Position)/50);
    if(RadioButton1->Checked == true)
    {
    	DrawSurface->Execute();
    }
    else
    {
    	DrawContour->Execute();
    }
    UpdateImage->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TForceSurfacePlotForm::ClearImageExecute(TObject *Sender)
{
	//Clear the Image
    Image1->Canvas->Brush->Color = clWhite;
    Image1->Canvas->Pen->Color = clBlack;
    Image1->Canvas->Rectangle(0, 0, Image1->Width, Image1->Height);
    
}
//---------------------------------------------------------------------------

void __fastcall TForceSurfacePlotForm::FormActivate(TObject *Sender)
{
   // Setup the form and create the graph
   ViewAngleOffsetScale = 4.0;
   ViewAngleTweak = ((double)TrackBar1->Position)/50;
   ViewAngleOffset = ((double)TrackBar1->Position-50)*ViewAngleOffsetScale;

    DrawGraphs->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TForceSurfacePlotForm::SaveImageExecute(TObject *Sender)
{
    SavePictureDialog1->Options.Clear();
    if( SavePictureDialog1->Execute() )
    {
      	Image1->Picture->SaveToFile(SavePictureDialog1->FileName);
    }
    UpdateImage->Execute();

}
//---------------------------------------------------------------------------





