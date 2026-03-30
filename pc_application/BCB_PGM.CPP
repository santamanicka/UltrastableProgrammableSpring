//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <time.h>
#include <stdio.h>
#pragma hdrstop

#define WIN32
#include "bcb_pgm.h"
#include "wsc.h"
#include "keycode.h"
#include "configunit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
#include "ActuatorSettingsUnit.h"

#include "SerialPortMonitorUnit.h"
#include "DownloadProgressUnit.h"
#include "ActuatorCommandUnit.h"



#define PROFILE_HOR_DRAWING_BORDERS 10
#define UINT16ZERO 	32768

//---------------------------------------------------------------------------
//
//*** NOTES ***
//
// Compile with BCB_PRJ.MAK if running BCB version 1 through 3, and compile with
// BCB_PRJ.BPR if running BCB version 4 or above.
//
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

// set default port and baud rate

//---------------------------------------------------------------------------
 TREMOTE *REMOTE;
//---------------------------------------------------------------------------
__fastcall TREMOTE::TREMOTE(TComponent* Owner)
   : TForm(Owner)
{//TheDC = GetDeviceContext(&WindowHandle);
        SerialPortMonitorVisible = 0;
        DefaultProfileSettings = new TStringList;
        DefaultProfileSettings->LoadFromFile("DefaultProfileSettings.txt");

        ProfileSettings0 = new TStringList();
        ProfileSettings1 = new TStringList();
        ProfileSettings2 = new TStringList();
        ProfileSettings3 = new TStringList();
        ProfileSettings4 = new TStringList();
        ProfileSettings5 = new TStringList();
        ProfileSettings6 = new TStringList();
        ProfileSettings7 = new TStringList();
        ProfileSettings0->LoadFromFile("DefaultProfileSettings.txt");

        ArrayOfProSettings[0] = ProfileSettings0;
        ArrayOfProSettings[1] = ProfileSettings1;
        ArrayOfProSettings[2] = ProfileSettings2;
        ArrayOfProSettings[3] = ProfileSettings3;
        ArrayOfProSettings[4] = ProfileSettings4;
        ArrayOfProSettings[5] = ProfileSettings5;
        ArrayOfProSettings[6] = ProfileSettings6;
        ArrayOfProSettings[7] = ProfileSettings7;
        ActuatorSettings = new TStringList();


        ProfileData0 = new ProObj;
        ProfileData1 = new ProObj;
        ProfileData2 = new ProObj;
        ProfileData3 = new ProObj;
        ProfileData4 = new ProObj;
        ProfileData5 = new ProObj;
        ProfileData6 = new ProObj;
        ProfileData7 = new ProObj;
        MutatedProfile = new ProObj;

        MutationData = new TStringList();
        pdampfile = fopen("D:\\PSprings\\Analysis\\PDamp.txt","a+");
        ndampfile = fopen("D:\\PSprings\\Analysis\\NDamp.txt","a+");
        forcefile = fopen("D:\\PSprings\\Analysis\\Force.txt","a+");
        mutatedAnglesFile = fopen("D:\\PSprings\\Analysis\\MutatedAngles.txt","a+");
        notMutatedAnglesFile = fopen("D:\\PSprings\\Analysis\\NotMutatedAngles.txt","a+");
        numMutationsFile = fopen("D:\\PSprings\\Analysis\\NumMutations.txt","a+");
        mutationsMagnitudeFile = fopen("D:\\PSprings\\Analysis\\MutationsMagnitude.txt","a+");
        mutationCnt = 0;
        totalAngle = 0;
        totalAngleVelocity = 0;
        iterations = 0;
        totalAngle0 = 0;
        totalAngleVelocity0 = 0;
        iterations0 = 0;
        totalAngle1 = 0;
        totalAngleVelocity1 = 0;
        iterations1 = 0;
        totalAngle2 = 0;
        totalAngleVelocity2 = 0;
        iterations2 = 0;
        totalAngle3 = 0;
        totalAngleVelocity3 = 0;
        iterations3 = 0;

        //trajectoryFile = fopen("D:\\PSprings\\Trajectories\\Trajectory.txt","w+");
        /*
        pdampfile = new TFileStream("D:\\PSprings\\Analysis\\PDamp.txt",fmOpenReadWrite	);
        ndampfile = new TFileStream("D:\\PSprings\\Analysis\\NDamp.txt",fmOpenReadWrite	);
        forcefile = new TFileStream("D:\\PSprings\\Analysis\\Force.txt",fmOpenReadWrite	);
        */
        
        ArrayOfProfileData[0] = ProfileData0;
        ArrayOfProfileData[1] = ProfileData1;
        ArrayOfProfileData[2] = ProfileData2;
        ArrayOfProfileData[3] = ProfileData3;
        ArrayOfProfileData[4] = ProfileData4;
        ArrayOfProfileData[5] = ProfileData5;
        ArrayOfProfileData[6] = ProfileData6;
        ArrayOfProfileData[7] = ProfileData7;

        Actuator = new ActObj;
        TargetNode = 1;
        EditingProfileNo = 0;
        ConnectedActuatorsCurrentProfile = 0;
        Timer1Counts = 0;
        FProfileTXNo = 0;
        DownloadInProgress = 0;
        FullDownload = 0;

        PacketOK = 0;
        PacketComplete = 0;
        IncomingDataCount = 0;
		IncomingPacketLength = 0;
        IncomingPreamble[0] = 'P';
        IncomingPreamble[1] = 'G';
		IncomingPreamble[2] = 'S';
		IncomingPreamble[3] = '#';

        flag1 = 0;
        //connected = false;
    ThePort = COM4;
    TheBaud = WSC_Baud38400;
    //TheBaud = WSC_Baud19200;
    ConnectionStatus = 0;
    BodyScale = 3;
    BaudText->Caption = "38400";
    //BaudText->Caption = "19200";
    CommText->Caption = ThePort+1;
    StatusText->Caption = "Off Line";

    netQue = 0;


    for(int n = 0; n < 6; n++)
    {
    	bytesin[n] = 100;
    }
    bytesin[8] = 0;

    for(int n = 0; n < 10; n++)
    {
        Names[n] = "Blank";
    }
    sending = 0;
    TypingFlag = false;
    PreambleLength = 8;
    DataLength = 16;

    for(int n = 0; n < NUMBER_OF_PROFILE_GROUPS; n++)
    {
          SelectprofileBox->Items->Add(n);
    }
    SelectprofileBox->ItemIndex = EditingProfileNo;

    GroupMemoHeader = "  Var1  | Var2  | Var3  | Var4  |F1 |F2 |F3 |F4 |Node|Mode|Pro";
    GroupAHeaderLabel->Caption = GroupMemoHeader;
    GroupBHeaderLabel->Caption = GroupMemoHeader;
    TimeSinceLastpacket = 0;
    OldTime = 0;

    Disconnect1->Enabled = false;


    ActuatorSettings->LoadFromFile("DEFAULTACTUATOR.psa");
    UnpackActuatorFile->Execute();
    

    PrintMessage("Default Actuator Loaded!");

    //The image is on panel3 which is set to double buffered
    // - this prevents the image flickering when it redraws
    Panel3->DoubleBuffered = true;
    for(int n = 0; n < 8; n++)
    {
    	ArrayOfProfileData[n]->ProfileGraph->Height = Image1->Height;
    	ArrayOfProfileData[n]->ProfileGraph->Width = Image1->Width;
    	ArrayOfProfileData[n]->ForceSurface->Height = Image1->Height;
    	ArrayOfProfileData[n]->ForceSurface->Width = Image1->Width;
    }
    //Now draw all the profile images for the actuator ready for display
    RedrawProfileBitmaps->Execute();



   // GenerateAllActuatorImages->Execute();
    //RedrawAndRefresh->Execute();
    //Graph1 = new Graphics::TBitmap();
    //Graph1->Height = Image1->Height;
    //Graph1->Width = Image1->Width;
    TraceImage1 = new Graphics::TBitmap;
    TraceImage1->Width = Image1->Width;
    TraceImage1->Height = Image1->Height;
    //ImageRectangle = new TRect(0,0,Image1->Width,Image1->Height);
    ImageRectangle.Left = 0;
    ImageRectangle.Right = Image1->Width;
    ImageRectangle.Top = 0;
    ImageRectangle.Bottom = Image1->Height;

    LogFileName = "Logs\\Default_0.txt";
    LogRunning = 0;
    LogNumber = 0;
    LogText->Caption = LogNumber;
    Startup = 1;

    
    //GroupAMemo->Lines->Add(GroupMemoHeader);
    //GroupBMemo->Lines->Add(GroupMemoHeader);

        //RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void TREMOTE::PrintMessage(AnsiString Line)
{
     Messages->Lines->Add(Line);
}
//---------------------------------------------------------------------------
void __fastcall TREMOTE::TimerTimer(TObject *Sender)
{
        int marker;
        static double time1=0, time2=0;
        int RxQueCleared=0;
        
	if(Startup == 1)
    {
    //	//this bit is only used when the application starts to redraw the image for the first time
        Startup = 0;
        RedrawAndRefresh->Execute();
    }
	if(!ConnectionStatus)
    {
     	Timer->Enabled = false;
    	return;
    }
    //static AnsiString FormatedData;
    //AnsiString pending = "A:";
    int Que, crap;
    int Overflow, OverWrite, ParityError, FrameError, BreakDetect, TxqFull;
    static int byteCount = 0;
    static int startNextPkt = 1;
    
    Que = SioRxQue(ThePort);

    Overflow = SioStatus(ThePort, WSC_RXOVER);
    OverWrite = SioStatus(ThePort, WSC_OVERRUN);
    ParityError = SioStatus(ThePort, WSC_PARITY);
    FrameError = SioStatus(ThePort, WSC_FRAME);
    BreakDetect = SioStatus(ThePort, WSC_BREAK);
    TxqFull = SioStatus(ThePort, WSC_TXFULL);

    if( Overflow != 0 || OverWrite != 0 || ParityError != 0 || FrameError != 0 || BreakDetect != 0 || TxqFull != 0)
    {
    	AnsiString ErrMessage = "Error Overflow = ";
        ErrMessage += Overflow;
        ErrMessage += " OverWrite = ";
        ErrMessage += OverWrite;
        ErrMessage += " ParityError = ";
        ErrMessage += ParityError;
        ErrMessage += " FrameError = ";
        ErrMessage += FrameError;
        ErrMessage += " BreakDetect = ";
        ErrMessage += BreakDetect;
        ErrMessage += " TxqFull = ";
        ErrMessage += TxqFull;
        PrintMessage(ErrMessage);
    }

     //WSC_RXOVER   :  The receive queue overflowed.
     //WSC_OVERRUN    :  An incoming byte was overwritten.
    if( Que == 0)
    {
        /*
        if(startNextPkt == 0 && !RxQueCleared)
        {
            if(time1 == 0)
                time1 = clock()/CLK_TCK;
            time2 = clock()/CLK_TCK;
            if(time2-time1 >= 2)
            {
                SioRxClear(ThePort);
                time2 = 0;
                time1 = 0;
                PacketComplete = 1;
                IncomingDataCount = 0;
                PacketOK = 0;
                RxQueCleared = 1;
                AnsiString msg = "Que empty when pkt not complete yet. RXQ cleared...";
                PrintMessage(msg);
            }
        }
        */
        //StaticText1->Caption = "NoQue";
        /*
        if(startNextPkt == 0)
        {
                Disconnect->Execute();
                AttemptConnection->Execute();
                while(ConnectionStatus == 0)
                        AttemptConnection->Execute();
        }
        */
        /*
        if(startNextPkt == 0)
        {
          AnsiString msg = "Que is empty when prev pkt not complete yet!";
          PrintMessage(msg);
        }
        */
        byteCount = 0;
    	return;
    }

    //if(Que == 1)
        //crap =1;
        
    //PrintMessage(Que);
    //StaticText1->Caption = "Que";
    //pending += Que;
    //GroupAMemo->Lines->Add(pending);
	int InByte, InBuffLen;
    int n;
    for( n = 0; n < Que; n++ )
    {
        RxQueCleared = 0;
        if(n == 0)
        {
            //netQue += Que;
            //byteCount += Que;
            /*
            if(byteCount > 139)
            {
                AnsiString msg = "Net byte count is > 139!\n";
                PrintMessage(msg);
                crap = 1;
            }
            */
            /*
            AnsiString msg = "Current net Que length = ";
            msg += netQue;
            PrintMessage(msg);
            */
        }

    	 InByte = SioGetc(ThePort);

         if(InByte != 80 && startNextPkt == 1 && Que <= 5)
         {
                SioRxClear(ThePort);
                AnsiString msg = "RXQ cleared...";
                PrintMessage(msg);
                continue;
                /*
                if(InByte != 80)
                {
                  AnsiString msg = "Corrupted Byte replaced ";
                  msg += (char)InByte;
                  PrintMessage(msg);
                  InByte = 80;
                }
                */
                /*
                else
                {
                  AnsiString msg = "Byte skipped = ";
                  msg += (char)InByte;
                  PrintMessage(msg);
                  continue;
                }
                */
                /*
                Disconnect->Execute();
                AttemptConnection->Execute();
                while(ConnectionStatus == 0)
                        AttemptConnection->Execute();
                */
                //After this, I should probably clear the RXQ and exit the loop. This will
                //automatically trigger retransmission of profile and hopefully fix things.
         }
         
         if(InByte == 80 && startNextPkt == 1)
         {
                marker = (int)'#';
                SerialPortMonitorForm->PrintCommData(marker,0);
                marker = MutatedProfile->MutatedProfileNumber;
                SerialPortMonitorForm->PrintCommData(marker,1);
                marker = (int)'#';
                SerialPortMonitorForm->PrintCommData(marker,0);
         }
         startNextPkt = 0;

         /*
         if(InByte == 80 && PacketOK != 0 && IncomingDataCount == 0)
         {
                AnsiString msg = "Something is fishy!\n";
                PrintMessage(msg);
                crap=1;
         }
         */

         //Send to port monitor
         if(PrintLogCheckBox->Checked == true) SerialPortMonitorForm->PrintCommData(InByte,0);

    	if(PacketOK == 0)
        {
        	PacketOK = ApplyToPacketFilter(InByte);
                if(PacketOK == 0)
                {
                        /*
                        AnsiString msg = "Preamble not ok. ";
                        msg += "Byte = ";
                        msg += InByte;
                        msg += "Que size = ";
                        msg += Que;
                        PrintMessage(msg);
                        */
                }
        }
        else if(PacketOK == 1 && PacketComplete == 0)
        {
        	IncomingDataBuffer[IncomingDataCount] = InByte;
            IncomingDataCount++;
            //PrintMessage("Saving Pack data");
            if(IncomingDataCount >= IncomingPacketLength)
            {
            	PacketComplete = 1;

                //ExtractIncomingData->Execute();
        		//PacketComplete = 0;

                IncomingDataCount = 0;
                PacketOK = 0;

                //REMEMBER -- In debug mode, the byteCount can easily grow more than 138 coz data might get accumulated during the time of debugging
                //if(byteCount > 138)
                    //SioRxClear(ThePort);

                break;
                //PrintMessage("Pack Complete");

            }
        }

    }
    //if a good packes has been recieved then extract the data and print
    if(PacketComplete == 1)
    {
    	//Process the packet data
        //PrintMessage("Data Extraction");
        ExtractIncomingData->Execute();
        PacketComplete = 0;
        startNextPkt = 1;
    }
    //Update the memo line if required
    if(PrintLogCheckBox->Checked == true) SerialPortMonitorForm->UpdateMemo->Execute();
}



//---------------------------------------------------------------------------

void __fastcall TREMOTE::AttemptConnectionExecute(TObject *Sender)
{
	int Code;
 	// pass the key code
 	if(SioKeyCode(WSC_KEY_CODE)<0)
   	{
    	AnsiString line = "ERROR: Bad Key Code!";
        PrintMessage(line);
    	return;
   	}
 	// open the port
 	//Code = SioReset(ThePort,2048,1024);
        Code = SioReset(ThePort,2048,2048);
 	if(Code<0)
   	{
    	AnsiString line = "ERROR: S: ";
    	char Temp[80];
    	SioWinError((LPSTR)Temp,80);
        for(int n = 0; n < 80; n++)
        {
        	line+= Temp[n];
        }
    	PrintMessage(line);
    	return;
   	}
 	// set baud rate, DTR, and RTS

 	SioBaud(ThePort,TheBaud);
 	SioDTR(ThePort,'S');
 	SioRTS(ThePort,'S');
        SioTxClear(ThePort);
        SioRxClear(ThePort);
    ConnectionStatus = 1;
    Timer->Enabled = true;
    StatusText->Caption = "On Line";
    //connected = true;
   	AnsiString line = "Connection Established!";
   	PrintMessage(line);
    Settings1->Enabled = false;
    //ConfigureButton->Enabled = false;

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::DisconnectExecute(TObject *Sender)
{
    if(!ConnectionStatus) return;
	SioDone(ThePort);
    Timer->Enabled = false;
    ConnectionStatus = 0;
    StatusText->Caption = "Off Line";
    //connected = false;
    AnsiString line = "Disconnected!";
   	PrintMessage(line);
    Settings1->Enabled = true;
    //ConfigureButton->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ConnectDisconnectExecute(TObject *Sender)
{
	int f1 = 0;
	if(ConnectionStatus == 0)
    {
    	AttemptConnection->Execute();
        if(ConnectionStatus == 0) return;
        
    	ConnectButton->Caption = "DISCONNECT";
        Connect2->Enabled = false;
        Disconnect1->Enabled = true;
        f1 = 1;
    }
    if(f1 == 0)
    {
        Disconnect->Execute();
		ConnectButton->Caption = "Connect";
        Connect2->Enabled = true;
        Disconnect1->Enabled = false;
        f1 = 0;
    }

}

//---------------------------------------------------------------------------

void __fastcall TREMOTE::ProcessIncomingExecute(TObject *Sender)
{
	//process the contents of the serial buffers
}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::Timer1Timer(TObject *Sender)
{

    AnsiString Line;
    static int NumberOfDownloads = 0;
    static int AlreadyBeenHere = 0;
    static int Progress = 0;
    if(AlreadyBeenHere == 0)
    {
        DownloadProgressForm->ProgressBar1->Step = 1;
        DownloadProgressForm->ProgressBar1->Max = 8;
    	if(FullDownload == 1)
        {
			CurrentOldProfile = EditingProfileNo;
            EditingProfileNo = 0;
            DownloadProgressForm->ProgressBar1->Step = 1;
            DownloadProgressForm->ProgressBar1->Max = 72;
        }
    	DownloadInProgress = 1;
        AlreadyBeenHere = 1;
    }

    switch(Timer1Counts)
    {
    case 0:
        //Send FProfile
       // Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        Timer1->Enabled = false;
        
        Line = "Sending Profile: ";
    	Line += EditingProfileNo;
        DownloadProgressForm->Caption = Line;
    	//PrintMessage(Line);

        //SendPDampProfile->Execute();
        SendFProfile->Execute();
        Timer1->Enabled = true;
        Timer1Counts ++;
    	break;
    case 1:
        //Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        Timer1->Enabled = false;
        SendPDampProfile->Execute();

        Timer1->Enabled = true;
        Timer1Counts ++;
    	break;
    case 2:
        //Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        Timer1->Enabled = false;
        SendNDampProfile->Execute();

        Timer1->Enabled = true;
        Timer1Counts ++;
    	break;
    case 3:
        //Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        Timer1->Enabled = false;
        SendInt16Vars->Execute();

        Timer1->Enabled = true;
        Timer1Counts ++;
    	break;
    case 4:
        //Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        Timer1->Enabled = false;
        SendInt8Vars->Execute();

        Timer1->Enabled = true;
        Timer1Counts ++;
    	break;
    case 5:
        //Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        Timer1->Enabled = false;
        SendInt16Pointers->Execute();

        Timer1->Enabled = true;
        Timer1Counts ++;
    	break;
    case 6:
        //Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        Timer1->Enabled = false;
        SendInt8Pointers->Execute();

        Timer1->Enabled = true;
        Timer1Counts ++;
    	break;
    case 7:
    	//Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        //Send Finish
        Timer1->Enabled = false;
        SendDownloadCompleteCommand->Execute();

        Timer1->Enabled = true;
        Timer1Counts ++;
    	break;
    case 8:
    	//Line = "Timer1 Case ";
        //Line += Timer1Counts;
        //PrintMessage(Line);
        //Send Finish
        Timer1->Enabled = false;
        if(FullDownload == 1 && EditingProfileNo < 7 )
        {
        	//now do the next profile group
            EditingProfileNo++;
            Timer1Counts = 0;
            Timer1->Enabled = true;
        }
        else if(FullDownload == 1)
        {
        	SendActuatorSettings->Execute();
            EditingProfileNo = CurrentOldProfile;
        	AlreadyBeenHere = 0;
        	DownloadInProgress = 0;
        	Timer1Counts = 0;
        	FullDownload = 0;
            Progress = 0;
            SendProfileToActuatorButton->Enabled = true;
        	DownloadWholeActuatorButton->Enabled = true;
            DownloadProgressForm->ProgressBar1->Position = 0;
            DownloadProgressForm->Hide();
        }
        else
        {
        	AlreadyBeenHere = 0;
        	DownloadInProgress = 0;
        	Timer1Counts = 0;
        	FullDownload = 0;
            Progress = 0;
            SendProfileToActuatorButton->Enabled = true;
        	DownloadWholeActuatorButton->Enabled = true;
            DownloadProgressForm->ProgressBar1->Position = 0;
            DownloadProgressForm->Hide();
        }
    	break;
    default:
       //	Line = "Timer1 Default Case ";
       // Line += Timer1Counts;
       // PrintMessage(Line);
    	Timer1->Enabled = false;
        CurrentOldProfile = 0;
        EditingProfileNo = 0;
        AlreadyBeenHere = 0;
        DownloadInProgress = 0;
        Timer1Counts = 0;
        FullDownload = 0;
        Progress = 0;
        DownloadProgressForm->ProgressBar1->Position = 0;
        DownloadProgressForm->Hide();
    }

    if(AlreadyBeenHere == 1)
    {
    	DownloadProgressForm->ProgressBar1->StepIt();
    }
	//used for sending a profile to the actuator
    //To send a profile just enable this timer.
    //Every time it fires it calls the appropriate function and incriments its counter
    //when it is finished it sends the finish command, turns its self off and resets its counter
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ClearImageExecute(TObject *Sender)
{
	Image1->Canvas->Brush->Color = clWhite;
    Image1->Canvas->Pen->Color = clWhite;
    Image1->Canvas->Pen->Width = 2;
    Image1->Canvas->Rectangle(0,0,Image1->Width, Image1->Height);
}

//---------------------------------------------------------------------------
TColor TREMOTE::GetColour(int RedComponent, int GreenComponent, int BlueComponent)
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

void __fastcall TREMOTE::FormClose(TObject *Sender, TCloseAction &Action)
{
        Disconnect->Execute();
        SioDone(ThePort);
 	//Close();

}
//---------------------------------------------------------------------------



void __fastcall TREMOTE::OpenConfigWindowExecute(TObject *Sender)
{
        //opens the configure window
        /*
        if(SimEditForm != NULL) return;
    SimEditForm = new TSimEditForm(Application);
    SimEditForm->ShowModal();
    delete SimEditForm;
    SimEditForm = NULL;
    DrawImage->Execute();
    */

    if(ConfigureForm != NULL) return;
    ConfigureForm = new TConfigureForm(Application);
    ConfigureForm->ShowModal();
    delete ConfigureForm;
    ConfigureForm = NULL;

}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::OpenProfileEditFormExecute(TObject *Sender)
{
        //opens a profile editing window
	//if(ProfileEditForm != NULL) return;
    //ProfileEditForm = new TProfileEditForm(Application);
    //ProfileEditForm->ShowModal();
    //delete ProfileEditForm;
    //ProfileEditForm = NULL;
    ProfileEditForm->ShowModal();
    SelectprofileBox->ItemIndex = EditingProfileNo;

    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ChangeToSelectedProfileExecute(TObject *Sender)
{
        EditingProfileNo = SelectprofileBox->ItemIndex;
        ProfileEditForm->CurrentEditingProfile = EditingProfileNo;
        RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::UnpackProfileFileIntoDataObjectExecute(
      TObject *Sender)
{
        int TempInt = 0;
        int LineIndex = 0;
        AnsiString TempString;
        AnsiString LineID;
        //Unpacks the contents of the stringlist into the specified profile object
        LineID = "PGS#";
        TempString = ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].SubString(0, 4);
        if(TempString != LineID)
        {
        	PrintMessage("Invalid File Header");
            return;
        }
        LineIndex++;
        LineIndex++;
        for(int n = 0; n < 64; n++)
        {
                TempInt =  ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].ToInt();
                ArrayOfProfileData[EditingProfileNo]->SetFValue(TempInt, n);
                LineIndex++;
        }


        LineIndex++;
        for(int n = 0; n < 64; n++)
        {
                TempInt =  ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].ToInt();
                ArrayOfProfileData[EditingProfileNo]->SetPDampValue(TempInt, n);
                LineIndex++;
        }
        LineIndex++;
        for(int n = 0; n < 64; n++)
        {
                TempInt =  ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].ToInt();
                ArrayOfProfileData[EditingProfileNo]->SetNDampValue(TempInt, n);
                LineIndex++;
        }

        LineIndex++;
        for(int n = 0; n < 32; n++)
        {
                TempInt =  ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].ToInt();
                ArrayOfProfileData[EditingProfileNo]->SInt16Variables[n] = TempInt;
                LineIndex++;
        }

        LineIndex++;
        for(int n = 0; n < 64; n++)
        {
                TempInt =  ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].ToInt();
                ArrayOfProfileData[EditingProfileNo]->SInt16Pointers[n] = TempInt;
                LineIndex++;
        }

        LineIndex++;
        for(int n = 0; n < 32; n++)
        {
                TempInt =  ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].ToInt();
                ArrayOfProfileData[EditingProfileNo]->Int8Variables[n] = TempInt;
                LineIndex++;
        }

        LineIndex++;
        for(int n = 0; n < 64; n++)
        {
                TempInt =  ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].ToInt();
                ArrayOfProfileData[EditingProfileNo]->Int8Pointers[n] = TempInt;
                LineIndex++;
        }

        //Now redraw all the images in the object
        RedrawProfileBitmapX(EditingProfileNo);
        //Print the results
        //PrintDataObject->Execute();
        /*
        int Iteval = -127;
        for(int n = 0; n < 64; n++)
        {
                PrintMessage(Iteval);
                Iteval+=4;
        } */


}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::PrintDataObjectExecute(TObject *Sender)
{
		PackUpProfileData->Execute();
        Messages->Lines->AddStrings(ArrayOfProSettings[EditingProfileNo]);
        Messages->Lines->Add("------------------------------------------------");
        //Messages->F
        /*
        AnsiString TempMessage = "Force = ";
        for(int n = 0; n < 64; n++)
        {
            //TempMessage += ProfileData0->ForceTable[n];
            TempMessage += ArrayOfProfileData[EditingProfileNo]->ForceTable[n];
            TempMessage += " ";
        }
        PrintMessage(TempMessage);
        TempMessage = "PDamp = ";
        PrintMessage(TempMessage);
        TempMessage = "";
        for(int n = 0; n < 64; n++)
        {
            TempMessage += ArrayOfProfileData[EditingProfileNo]->PDamptable[n];
            TempMessage += " ";
        }
        PrintMessage(TempMessage);
        TempMessage = "NDamp = ";
        PrintMessage(TempMessage);
        TempMessage = "";
        for(int n = 0; n < 64; n++)
        {
            TempMessage += ArrayOfProfileData[EditingProfileNo]->NDamptable[n];
            TempMessage += " ";
        }
        PrintMessage(TempMessage);

        TempMessage = "I 16 = ";
        PrintMessage(TempMessage);
        TempMessage = "";
        for(int n = 0; n < 32; n++)
        {
            TempMessage += ArrayOfProfileData[EditingProfileNo]->SInt16Variables[n];
            TempMessage += " ";
        }
        PrintMessage(TempMessage);

        TempMessage = "I 16 PTR = ";
        PrintMessage(TempMessage);

        TempMessage = "";
        for(int n = 0; n < 32; n++)
        {
            TempMessage += ArrayOfProfileData[EditingProfileNo]->SInt16Pointers[n];
            TempMessage += " ";
        }
        PrintMessage(TempMessage);

        TempMessage = "I 8 = ";
        PrintMessage(TempMessage);
        TempMessage = "";
        for(int n = 0; n < 32; n++)
        {
            TempMessage += ArrayOfProfileData[EditingProfileNo]->Int8Variables[n];
            TempMessage += " ";
        }
        PrintMessage(TempMessage);

        TempMessage = "I 8 PTR = ";
        PrintMessage(TempMessage);
        TempMessage = "";
        for(int n = 0; n < 32; n++)
        {
            TempMessage += ArrayOfProfileData[EditingProfileNo]->Int8Pointers[n];
            TempMessage += " ";
        }
        PrintMessage(TempMessage); */
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::GetBytesTestButtonClick(TObject *Sender)
{
        //read the force profile as byte values
        byte LSB1, MSB1;
        AnsiString Line, Line2;
        int ReconstructedWord;


        Line = "Force Profile Bytes: ";
        Line2 = "Force Profile Values: ";
        for(int n = 0; n < 64; n++)
        {
               LSB1 = ArrayOfProfileData[EditingProfileNo]->GetFVauleByte(n, 0);
               MSB1 = ArrayOfProfileData[EditingProfileNo]->GetFVauleByte(n, 1);

               //Reconstruct the word
               ReconstructedWord = MSB1;
               ReconstructedWord <<=8;
               ReconstructedWord += LSB1;
               ReconstructedWord -= 32767;


               Line += (int)MSB1;
               Line += (int)LSB1;
               Line += " ";

               Line2 += ReconstructedWord;
               Line2 += " ";
        }
        PrintMessage(Line);
        PrintMessage(Line2);

        byte ByteValue;
        //Now the PDampTable
        Line = "PDamp Profile Bytes: ";
        Line2 = "PDamp Profile Values: ";
        for(int n = 0; n < 64; n++)
        {
               ByteValue = ArrayOfProfileData[EditingProfileNo]->GetPDampVauleByte(n);

               //Reconstruct the word
               ReconstructedWord = ByteValue;
               ReconstructedWord -= 128;


               Line += (int)ByteValue;
               Line += " ";

               Line2 += ReconstructedWord;
               Line2 += " ";
        }
        PrintMessage(Line);
        PrintMessage(Line2);

        //Now the NDampTable
        Line = "NDamp Profile Bytes: ";
        Line2 = "NDamp Profile Values: ";
        for(int n = 0; n < 64; n++)
        {
               ByteValue = ArrayOfProfileData[EditingProfileNo]->GetNDampVauleByte(n);

               //Reconstruct the word
               ReconstructedWord = ByteValue;
               ReconstructedWord -= 128;


               Line += (int)ByteValue;
               Line += " ";

               Line2 += ReconstructedWord;
               Line2 += " ";
        }
        PrintMessage(Line);
        PrintMessage(Line2);

        //Now the Variables

        Line = "SI16 Bytes: ";
        Line2 = "SI16 Values: ";
        for(int n = 0; n < 32; n++)
        {
               LSB1 = ArrayOfProfileData[EditingProfileNo]->GetSInt16VariableByte(n, 0);
               MSB1 = ArrayOfProfileData[EditingProfileNo]->GetSInt16VariableByte(n, 1);

               //Reconstruct the word
               ReconstructedWord = MSB1;
               ReconstructedWord <<=8;
               ReconstructedWord += LSB1;
               ReconstructedWord -= 32767;


               Line += (int)MSB1;
               Line += (int)LSB1;
               Line += " ";

               Line2 += ReconstructedWord;
               Line2 += " ";
        }
        PrintMessage(Line);
        PrintMessage(Line2);

        Line = "SI16Ptr Bytes: ";
        Line2 = "SI16Ptr Values: ";
        for(int n = 0; n < 64; n++)
        {
               ByteValue = ArrayOfProfileData[EditingProfileNo]->GetSInt16PointerByte(n);

               //Reconstruct the word
               ReconstructedWord = ByteValue;

               Line += (int)ByteValue;
               Line += " ";

               Line2 += ReconstructedWord;
               Line2 += " ";
        }
        PrintMessage(Line);
        PrintMessage(Line2);

        Line = "I8 Bytes: ";
        Line2 = "I8 Values: ";
        for(int n = 0; n < 32; n++)
        {
               ByteValue = ArrayOfProfileData[EditingProfileNo]->GetInt8VariableByte(n);

               //Reconstruct the word
               ReconstructedWord = ByteValue;

               Line += (int)ByteValue;
               Line += " ";

               Line2 += ReconstructedWord;
               Line2 += " ";
        }
        PrintMessage(Line);
        PrintMessage(Line2);

        Line = "I8Ptr Bytes: ";
        Line2 = "I8Ptr Values: ";
        for(int n = 0; n < 64; n++)
        {
               ByteValue = ArrayOfProfileData[EditingProfileNo]->GetInt8PointerByte(n);

               //Reconstruct the word
               ReconstructedWord = ByteValue;

               Line += (int)ByteValue;
               Line += " ";

               Line2 += ReconstructedWord;
               Line2 += " ";
        }
        PrintMessage(Line);
        PrintMessage(Line2);



}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendCurrentProfileToActuatorExecute(
      TObject *Sender)
{
        if(!ConnectionStatus)
        {
                PrintMessage("Error - Not Connected");
                return;
        }
        SendStopActuatorCommand->Execute();
        Timer1->Interval = 200;
        SendProfileToActuatorButton->Enabled = false;
        DownloadWholeActuatorButton->Enabled =false;
        DownloadProgressForm->Show();
        DownloadProgressForm->ClearLabels->Execute();
        
        Timer1->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendPrintProfileCommandExecute(TObject *Sender)
{
         if(!ConnectionStatus)
        {
                PrintMessage("Error - Not Connected");
                return;
        }
        //Sends the current profile object to the actuator
        byte DataBlock[255];
        int Index;
        byte PacketSize = 1;
        byte ProfileNo;
        ProfileNo = EditingProfileNo;
        ProfileNo += 48;
        //Unwrap and package the first block

        //place the preamble in the DataBlock array
        DataBlock[0] = 'P';
        DataBlock[1] = 'G';
        DataBlock[2] = 'S';
        DataBlock[3] = '#';
        DataBlock[4] = TargetNode;
        DataBlock[5] = 'P';
        DataBlock[6] = ProfileNo;
        DataBlock[7] = PacketSize;
        DataBlock[8] = 1;
        for(int n = 0; n < PacketSize+8; n++)
        {
             SioPutc(ThePort, DataBlock[n]);
        }
        PrintMessage("Print Request Sent");
}
//---------------------------------------------------------------------------



void __fastcall TREMOTE::PackUpProfileDataExecute(TObject *Sender)
{
        //Takes the profile data and places it in the strings object ready for saving
        int TempInt = 0;
        int LineIndex = 0;
        AnsiString TempString;
        AnsiString TempLine;
        AnsiString LineID;
        //Unpacks the contents of the stringlist into the specified profile object
        LineID = "PGS#";
        ArrayOfProSettings[EditingProfileNo]->Clear();
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        LineID = "Force Values:";
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        //TempString = ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].SubString(0, 13);
        for(int n = 0; n < 64; n++)
        {
                LineID = ArrayOfProfileData[EditingProfileNo]->GetFValue(n);
                ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        }


        LineID = "Positive Damping values:";
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);

        for(int n = 0; n < 64; n++)
        {
               LineID = ArrayOfProfileData[EditingProfileNo]->PDamptable[n];
                ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        }


        LineID = "Negative Damping values:";
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);

        for(int n = 0; n < 64; n++)
        {
                LineID = ArrayOfProfileData[EditingProfileNo]->NDamptable[n];
                ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        }

        LineID = "System Variables:";
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        for(int n = 0; n < 32; n++)
        {
                LineID = ArrayOfProfileData[EditingProfileNo]->SInt16Variables[n];
                ArrayOfProSettings[EditingProfileNo]->Add(LineID);

        }
        LineID = "System Pointers:";
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        for(int n = 0; n < 64; n++)
        {
                LineID = ArrayOfProfileData[EditingProfileNo]->SInt16Pointers[n];
                ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        }
        LineID = "Flag Variables:";
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        for(int n = 0; n < 32; n++)
        {
                LineID = ArrayOfProfileData[EditingProfileNo]->Int8Variables[n];
                ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        }
        LineID = "Flag Pointers:";
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        for(int n = 0; n < 64; n++)
        {
                LineID = ArrayOfProfileData[EditingProfileNo]->Int8Pointers[n];
                ArrayOfProSettings[EditingProfileNo]->Add(LineID);
        }

        LineID = "";
        ArrayOfProSettings[EditingProfileNo]->Add(LineID);


}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::UnpackActuatorFileExecute(TObject *Sender)
{
	//Unpacks the actuator stringlist into the profile objects
    int TempInt = 0;
        int LineIndex = 0;
        AnsiString TempString;
        AnsiString LineID;
        //Unpacks the contents of the stringlist into the specified profile object
        LineID = "ACTUATOR";
        TempString = ActuatorSettings->Strings[LineIndex].SubString(0, 8);
        if(TempString != LineID)
        {
        	PrintMessage("Invalid File Header");
            return;
        }
        LineIndex++;
        for(int Prof = 0; Prof < 8; Prof++)
        {
        	//Work your way through the string list

        	LineIndex++; //skip over "Profile No"
            LineIndex++; //Skip over "Force Data"
        	for(int n = 0; n < 64; n++)
        	{
        	 	TempInt =  ActuatorSettings->Strings[LineIndex].ToInt();
        	 	ArrayOfProfileData[Prof]->SetFValue(TempInt, n);
        	 	LineIndex++;
        	}


        	LineIndex++;
        	for(int n = 0; n < 64; n++)
        	{
        		TempInt =  ActuatorSettings->Strings[LineIndex].ToInt();
        		ArrayOfProfileData[Prof]->SetPDampValue(TempInt, n);
        		LineIndex++;
        	}
        	LineIndex++;
        	for(int n = 0; n < 64; n++)
        	{
        		TempInt =  ActuatorSettings->Strings[LineIndex].ToInt();
            	ArrayOfProfileData[Prof]->SetNDampValue(TempInt, n);
            	LineIndex++;
        	}

        	LineIndex++;
        	for(int n = 0; n < 32; n++)
        	{
            	TempInt =  ActuatorSettings->Strings[LineIndex].ToInt();
        	    ArrayOfProfileData[Prof]->SInt16Variables[n] = TempInt;
                LineIndex++;
        	}
        	LineIndex++;
        	for(int n = 0; n < 64; n++)
        	{
               	TempInt =  ActuatorSettings->Strings[LineIndex].ToInt();
                ArrayOfProfileData[Prof]->SInt16Pointers[n] = TempInt;
                LineIndex++;
        	}
        	LineIndex++;
        	for(int n = 0; n < 32; n++)
        	{
                TempInt =  ActuatorSettings->Strings[LineIndex].ToInt();
                ArrayOfProfileData[Prof]->Int8Variables[n] = TempInt;
                LineIndex++;
        	}
        	LineIndex++;
        	for(int n = 0; n < 64; n++)
        	{
                TempInt =  ActuatorSettings->Strings[LineIndex].ToInt();
                ArrayOfProfileData[Prof]->Int8Pointers[n] = TempInt;
                LineIndex++;
        	}
        }
        LineIndex++;
    	for(int n = 0; n < 32; n++)
    	{
        	TempInt =  ActuatorSettings->Strings[LineIndex].ToInt();
        	Actuator->SetSettings(TempInt , n);
    		LineIndex++;
    	}

        //Now redraw the images in the profile group objects
        RedrawProfileBitmaps->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::PackUpActuatorFileExecute(TObject *Sender)
{
	//Copies all the profile group objects into a stringlist
    //Takes the profile data and places it in the strings object ready for saving
        int TempInt = 0;
        int LineIndex = 0;
        AnsiString TempString;
        AnsiString TempLine;
        AnsiString LineID;
        //Unpacks the contents of the stringlist into the specified profile object
        LineID = "ACTUATOR";
        ActuatorSettings->Clear();
        ActuatorSettings->Add(LineID);

        for(int Pro = 0; Pro < 8; Pro++)
        {

            LineID = "PROFILE: ";
        	LineID += Pro;
        	ActuatorSettings->Add(LineID);
        	LineID = "Force Values:";
        	ActuatorSettings->Add(LineID);
        	//TempString = ArrayOfProSettings[EditingProfileNo]->Strings[LineIndex].SubString(0, 13);
        	for(int n = 0; n < 64; n++)
        	{
                LineID = ArrayOfProfileData[Pro]->GetFValue(n);
                ActuatorSettings->Add(LineID);
        	}


        	LineID = "Positive Damping values:";
        	ActuatorSettings->Add(LineID);

        	for(int n = 0; n < 64; n++)
        	{
               LineID = ArrayOfProfileData[Pro]->PDamptable[n];
                ActuatorSettings->Add(LineID);
        	}


        	LineID = "Negative Damping values:";
        	ActuatorSettings->Add(LineID);

        	for(int n = 0; n < 64; n++)
        	{
                LineID = ArrayOfProfileData[Pro]->NDamptable[n];
                ActuatorSettings->Add(LineID);
        	}

        	LineID = "System Variables:";
        	ActuatorSettings->Add(LineID);
        	for(int n = 0; n < 32; n++)
        	{
                LineID = ArrayOfProfileData[Pro]->SInt16Variables[n];
                ActuatorSettings->Add(LineID);

        	}
        	LineID = "System Pointers:";
        	ActuatorSettings->Add(LineID);
        	for(int n = 0; n < 64 ; n++)
        	{
                LineID = ArrayOfProfileData[Pro]->SInt16Pointers[n];
                ActuatorSettings->Add(LineID);
        	}
        	LineID = "Flag Variables:";
        	ActuatorSettings->Add(LineID);
        	for(int n = 0; n < 32; n++)
        	{
                LineID = ArrayOfProfileData[Pro]->Int8Variables[n];
                ActuatorSettings->Add(LineID);
       	 	}
       	 	LineID = "Flag Pointers:";
        	ActuatorSettings->Add(LineID);
        	for(int n = 0; n < 64; n++)
        	{
                LineID = ArrayOfProfileData[Pro]->Int8Pointers[n];
                ActuatorSettings->Add(LineID);
        	}
	}
    LineID = "Actuator Settings";
    ActuatorSettings->Add(LineID);
    for(int n = 0; n < 32; n++)
    {
    	LineID = (int)Actuator->GetSettingsByte(n);
    	ActuatorSettings->Add(LineID);
    }
    LineID = "END";
    ActuatorSettings->Add(LineID);
    LineID = "";
    ActuatorSettings->Add(LineID);

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendFProfileExecute(TObject *Sender)
{
	//Send the Force Profile to the actuator
     if(!ConnectionStatus)

     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //PrintMessage("Entered Function");
     //Sends the current profile object to the actuator
     byte Preamble[32];
     byte DataBlockA[128];
     byte DataBlockB[128];
     int Index;
     int PacketSize;
     byte ProfileNo;
     AnsiString Line;
     ProfileNo = EditingProfileNo;
     int ErrCode =0;
     ProfileNo += 48;
     //Unwrap and package the first block


     //place the preamble in the preamble array
     //PrintMessage("Filling Preamble Array");
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '0';

     //Now the packet size for block 1 (128)
     PacketSize = 128;
     Preamble[7] = (byte)PacketSize;

     //PrintMessage("Filling Data Block A");
     int BuffIndex = 0;
     for(int n = 0; n < 32; n++)
     {
     	DataBlockA[BuffIndex] = ArrayOfProfileData[EditingProfileNo]->GetFVauleByte(n, 1);
     	DataBlockA[BuffIndex+1] = ArrayOfProfileData[EditingProfileNo]->GetFVauleByte(n, 0);
        BuffIndex+=2;
     }

     //PrintMessage("Filling Data Block B");
     BuffIndex = 0;
     for(int n = 32; n < 64; n++)
     {
     	DataBlockB[BuffIndex] = ArrayOfProfileData[EditingProfileNo]->GetFVauleByte(n, 1);
     	DataBlockB[BuffIndex+1] = ArrayOfProfileData[EditingProfileNo]->GetFVauleByte(n, 0);
        BuffIndex+=2;
     }

     //Send the preamble
     //PrintMessage("Sending Preamble");

     ErrCode = SioPuts(ThePort, Preamble, 8);
     //Line = "Preamble Error Code = ";
     //Line += ErrCode;
     //PrintMessage(Line);
     //put the first 64 bytes

     //PrintMessage("Sending Block A");
     ErrCode = SioPuts(ThePort, DataBlockA, 64);
     //Line = "Preamble Error Code = ";
     //Line += ErrCode;
     //PrintMessage(Line);

     //PrintMessage("Sending Block B");


     ErrCode = SioPuts(ThePort, DataBlockB, 64);
     //Line = "Preamble Error Code = ";
     //Line += ErrCode;
     //PrintMessage(Line);

     //PrintMessage(Line);
     DownloadProgressForm->Label1->Caption = "Force Data Sent";



}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendPDampProfileExecute(TObject *Sender)
{
 	if(!ConnectionStatus)

     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //Sends the current PD profile object to the actuator
     byte Preamble[32];
     byte DataBlock[255];
     int Index;
     byte PacketSize;
     byte ProfileNo;
     ProfileNo = EditingProfileNo;
     ProfileNo += 48;
     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '1';

     //Now the packet size for block 1 (128)
     PacketSize = 64;
     Preamble[7] = PacketSize;

     for(int n = 0; n < PacketSize; n++)
     {
     	DataBlock[n] = ArrayOfProfileData[EditingProfileNo]->GetPDampVauleByte(n);
     }

     //Now send to the actuator
     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 8);
     ErrCode = SioPuts(ThePort, DataBlock, 64);
     DownloadProgressForm->Label1->Caption = "P Damp Data Sent";
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendNDampProfileExecute(TObject *Sender)
{
	if(!ConnectionStatus)

     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //Sends the current PD profile object to the actuator
     byte Preamble[32];
     byte DataBlock[255];
     int Index;
     byte PacketSize;
     byte ProfileNo;
     ProfileNo = EditingProfileNo;
     ProfileNo += 48;
     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '2';


     PacketSize = 64;
     Preamble[7] = PacketSize;

     for(int n = 0; n < PacketSize; n++)
     {
     	DataBlock[n] = ArrayOfProfileData[EditingProfileNo]->GetNDampVauleByte(n);
     }

     //Now send to the actuator
     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 8);
     ErrCode = SioPuts(ThePort, DataBlock, 64);
     DownloadProgressForm->Label1->Caption = "N Damp Data Sent";
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendInt8VarsExecute(TObject *Sender)
{
     if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //Sends the current int8vars
     byte Preamble[32];
     byte DataBlock[255];
     int Index;
     byte PacketSize;
     byte ProfileNo;
     ProfileNo = EditingProfileNo;
     ProfileNo += 48;
     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '4';

     PacketSize = 32;
     Preamble[7] = PacketSize;

     for(int n = 0; n < PacketSize; n++)
     {
     	DataBlock[n] = ArrayOfProfileData[EditingProfileNo]->GetInt8VariableByte(n);
     }

     //Now send to the actuator
     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 8);
     ErrCode = SioPuts(ThePort, DataBlock, 32);
     DownloadProgressForm->Label1->Caption = "8 Bit Variable Data Sent";
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendInt8PointersExecute(TObject *Sender)
{
	if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //Sends the current int8vars
     byte Preamble[32];
     byte DataBlock[255];
     int Index;
     byte PacketSize;
     byte ProfileNo;
     ProfileNo = EditingProfileNo;
     ProfileNo += 48;
     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '6';

     PacketSize = 64;
     Preamble[7] = PacketSize;

     for(int n = 0; n < PacketSize; n++)
     {
     	DataBlock[n] = ArrayOfProfileData[EditingProfileNo]->GetInt8PointerByte(n);
     }

     //Now send to the actuator
     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 8);
     ErrCode = SioPuts(ThePort, DataBlock, PacketSize);
     DownloadProgressForm->Label1->Caption = "8 Bit Pointer Data Sent";
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendInt16VarsExecute(TObject *Sender)
{
	if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //Sends the current int8vars
     byte Preamble[32];
     byte DataBlock[255];
     int Index;
     byte PacketSize;
     byte ProfileNo;
     ProfileNo = EditingProfileNo;
     ProfileNo += 48;
     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '3';

     PacketSize = 64;
     Preamble[7] = PacketSize;
     Index= 0;
     for(int n = 0; n < 64; n++)
     {
     	DataBlock[Index] = ArrayOfProfileData[EditingProfileNo]->GetSInt16VariableByte(n, 1);
     	DataBlock[Index+1] = ArrayOfProfileData[EditingProfileNo]->GetSInt16VariableByte(n, 0);
        Index+=2;
     }

     //Now send to the actuator
     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 8);
     ErrCode = SioPuts(ThePort, DataBlock, 64);
     DownloadProgressForm->Label1->Caption = "16 Bit Variable Data Sent";
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendInt16PointersExecute(TObject *Sender)
{
	if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //Sends the current int8vars
     byte Preamble[32];
     byte DataBlock[255];
     int Index;
     byte PacketSize;
     byte ProfileNo;
     ProfileNo = EditingProfileNo;
     ProfileNo += 48;
     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '5';

     //Now the packet size for block 1 (128)
     PacketSize = 64;
     Preamble[7] = PacketSize;

     for(int n = 0; n < PacketSize; n++)
     {
     	DataBlock[n] = ArrayOfProfileData[EditingProfileNo]->GetSInt16PointerByte(n);
     }

     //Now send to the actuator
     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 8);
     ErrCode = SioPuts(ThePort, DataBlock, PacketSize);
     DownloadProgressForm->Label1->Caption = "16 Bit Pointer Data Sent";
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendDownloadCompleteCommandExecute(
      TObject *Sender)
{
	//Send the profile download complete command to the actuator

    if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //Sends the current int8vars
     byte Preamble[32];
     int Index;
     byte PacketSize;
     byte ProfileNo;
     ProfileNo = EditingProfileNo;
     ProfileNo += 48;
     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '7';

     //Now the packet size for block 1 (128)
     PacketSize = 1;
     Preamble[7] = PacketSize;
     Preamble[8] = 1;

     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 9);

     DownloadProgressForm->Label1->Caption = "Completion Packet Sent";
}
//---------------------------------------------------------------------------



void __fastcall TREMOTE::DownloadWholeActuatorButtonClick(TObject *Sender)
{
	//Download each of the eight profile groups to the actuator

    AnsiString Line;
    //set the current profile to zero - remember where you were
    //so you can go back at the end of the function
    FullDownload = 1;

	if(!ConnectionStatus)
    {
    	PrintMessage("Error - Not Connected");
    	return;
    }
    PrintMessage("Sending All Profile Groups . . .");

    SendCurrentProfileToActuator->Execute();
    
}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::RedrawAndRefreshExecute(TObject *Sender)
{
    if(DrawingOptionPanel->ItemIndex == 0)
    {
        //ArrayOfProfileData[EditingProfileNo]->ProfileGraph->Height = Image1->Height;
        //ArrayOfProfileData[EditingProfileNo]->ProfileGraph->Width = Image1->Width;
        ArrayOfProfileData[EditingProfileNo]->DrawForceGraph();
        Image1->Canvas->Draw(0,0, ArrayOfProfileData[EditingProfileNo]->ProfileGraph);
    }
    if(DrawingOptionPanel->ItemIndex == 1)
    {
        //ArrayOfProfileData[EditingProfileNo]->ForceSurface->Height = Image1->Height;
        //ArrayOfProfileData[EditingProfileNo]->ForceSurface->Width = Image1->Width;
        if(ColorDrawingBox->Checked == true) ArrayOfProfileData[EditingProfileNo]->DrawForceSurface(0);
        if(ColorDrawingBox->Checked == false) ArrayOfProfileData[EditingProfileNo]->DrawForceSurface(1);
        Image1->Canvas->Draw(0,0, ArrayOfProfileData[EditingProfileNo]->ForceSurface);
    }

    //Image2->Canvas->CopyMode = cmSrcCopy;
    //Image2->Canvas->CopyRect(Rect( 0, 0, Image1->Width, Image1->Height)
    									//, Image1->Canvas
                                       // , Rect( 0, 0, Image1->Width, Image1->Height));
   // if(DrawingOptionPanel->ItemIndex == 0) DrawProfile->Execute();
   // if(DrawingOptionPanel->ItemIndex == 1) DrawForceSurface->Execute();
    //ProfileEditForm->CopyToLocalArrays->Execute();
    //ProfileEditForm->CheckThresholdsForAngle->Execute();
    //ProfileEditForm->EQImagePosition = ProfileEditForm->ConvertXAngleToMouse(  ProfileEditForm->TempSI16Var[ _EQAngle ] );
    //ProfileEditForm->DrawProfile->Execute();
    //Image1->Picture = ProfileEditForm->Image1->Picture;
    //RefreshImage->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::Button1Click(TObject *Sender)
{
	RedrawAndRefresh->Execute();	
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendStartActuatorCommandExecute(TObject *Sender)
{
    //Send a start command to the actuator - to begin executing code

    //The start stop command is X followed by A to start or B to stop
    if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     byte Preamble[32];
     int Index;
     byte PacketSize;


     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = 'X';
     Preamble[6] = 'A';

     //Now the packet size for block 1 (128)
     PacketSize = 1;
     Preamble[7] = PacketSize;
     Preamble[8] = 1;

     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, (LPSTR)Preamble, 9);

     PrintMessage("Start Command Sent");
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendStopActuatorCommandExecute(TObject *Sender)
{
    //send a stop command to the actuator - halts code execution and places the
    //force controller in power down mode
    if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     byte Preamble[32];
     int Index;
     byte PacketSize;

     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = 'X';
     Preamble[6] = 'B';

     //Now the packet size for block 1 (128)
     PacketSize = 1;
     Preamble[7] = PacketSize;
     Preamble[8] = 1;

     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 9);

     PrintMessage("Stop Command Sent");
}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::Test1Execute(TObject *Sender)
{

    //
    ArrayOfProfileData[0]->ProfileGraph->Height = Image1->Height;
    ArrayOfProfileData[0]->ProfileGraph->Width = Image1->Width;
    ArrayOfProfileData[0]->DrawForceGraph();
    Image1->Canvas->Draw(0,0, ArrayOfProfileData[0]->ProfileGraph);
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::OpenEditActuatorWindowExecute(TObject *Sender)
{
	//Edit the actuator settings
     if(ActuatorSettingsForm != NULL) return;
    ActuatorSettingsForm = new TActuatorSettingsForm(Application);
    ActuatorSettingsForm->ShowModal();
    delete ActuatorSettingsForm;
    ActuatorSettingsForm = NULL;

}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::LoadProfileGroupFromFileExecute(TObject *Sender)
{
	OpenProfileGroupDialog->Options.Clear();
  		//OpenProfileGroupDialog->Options << ofFileMustExist;
  		//OpenProfileGroupDialog->Filter = "Profile Group Files (*.pgf)|*.txt|All files (*.*)|*.*";
        SaveProfileGroupDialog->FilterIndex = 1;
        if( OpenProfileGroupDialog->Execute() )
        {
                ArrayOfProSettings[EditingProfileNo]->LoadFromFile(OpenProfileGroupDialog->FileName);
                UnpackProfileFileIntoDataObject->Execute();
                
        		PrintMessage("File Loaded into current profile group!");
        }
	    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SaveProfileGroupToFileExecute(TObject *Sender)
{
		SaveProfileGroupDialog->Options.Clear();
  		//SaveProfileGroupDialog->Options << ofFileMustExist;
  		//SaveProfileGroupDialog->Filter = "Profile Group Files (*.pgf)|*.txt|All files (*.*)|*.*";
        SaveProfileGroupDialog->FilterIndex = 1;

         if(SaveProfileGroupDialog->Execute() )
         {
                PackUpProfileData->Execute();
                ArrayOfProSettings[EditingProfileNo]->SaveToFile(SaveProfileGroupDialog->FileName);
                
                PrintMessage("Current profile group saved!");
         }

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::LoadActuatorFromFileExecute(TObject *Sender)
{
	//Opens an actuator file and unpacks it into all the profile data objects
    OpenActuatorDialog->Options.Clear();
    OpenActuatorDialog->FilterIndex = 1;
    if( OpenActuatorDialog->Execute() )
    {
      	ActuatorSettings->LoadFromFile(OpenActuatorDialog->FileName);

    	UnpackActuatorFile->Execute();

    	PrintMessage("Actuator Loaded!");
    }
    RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SaveActuatorToFileExecute(TObject *Sender)
{
	//Saves all the profiles as an .act file

    //First work through each profilegroup and load into the actuator string list
    //Opens an actuator file and unpacks it into all the profile data objects
    SaveActuatorDialog->Options.Clear();
    SaveActuatorDialog->FilterIndex = 1;
    if( SaveActuatorDialog->Execute() )
    {
        //PackUpProfileData->Execute();
        //ArrayOfProSettings[EditingProfileNo]->SaveToFile(SaveProfileGroupDialog->FileName);
        PackUpActuatorFile->Execute();
      	ActuatorSettings->SaveToFile(SaveActuatorDialog->FileName);


    	PrintMessage("Actuator Saved!");
        
    }

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendActuatorSettingsExecute(TObject *Sender)
{
	//Send the actuator settings to the actuator
	if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     //Sends the current int8vars
     byte Preamble[32];
     byte DataBlock[48];
     int Index;
     byte PacketSize;
     byte ProfileNo;
     ProfileNo = EditingProfileNo;
     ProfileNo += 48;
     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = ProfileNo;
     Preamble[6] = '8';

     //Now the packet size for block 1 (128)
     PacketSize = 32;
     Preamble[7] = PacketSize;

     for(int n = 0; n < PacketSize; n++)
     {
		DataBlock[n] = Actuator->GetSettingsByte(n);
     }

     //Now send to the actuator
     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 8);
     ErrCode = SioPuts(ThePort, DataBlock, PacketSize);
     DownloadProgressForm->Label1->Caption = "Actuator Settings Sent";
}
//---------------------------------------------------------------------------

int TREMOTE::ApplyToPacketFilter(int DataByte)
{

    int PacketAccepted = 0;
	int CurrentByte;
    //AnsiString Message;
	static int AcceptanceFlag = 0;

       //	Message = AcceptanceFlag;
		CurrentByte = DataByte;
		switch (AcceptanceFlag)
		{
		case 0:
			if(CurrentByte == IncomingPreamble[AcceptanceFlag])
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
          //  Message += " ";
          //  Message += CurrentByte;
          //  PrintMessage(Message);
			break;
		case 1:
			if(CurrentByte == IncomingPreamble[AcceptanceFlag])
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
           // Message += " ";
           // Message += CurrentByte;
          //  PrintMessage(Message);
			break;
		case 2:
			if(CurrentByte == IncomingPreamble[AcceptanceFlag])
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
           // Message += " ";
           // Message += CurrentByte;
           // PrintMessage(Message);
			break;
		case 3:
			if(CurrentByte == IncomingPreamble[AcceptanceFlag])
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
           // Message += " ";
           // Message += CurrentByte;
           // PrintMessage(Message);
			break;
		case 4: //check aagainst the node number - or to see if it is a broadcast
			if(CurrentByte < 255)
			{
				AcceptanceFlag++;
			}
			else AcceptanceFlag = 0;
           // Message += " ";
           // Message += CurrentByte;
           // PrintMessage(Message);
			break;
		case 5://check to see if this is a valid command (A keyboard character UPPER or Lower case)
			if(CurrentByte > 47 && CurrentByte < 123)
			{
				AcceptanceFlag++;
				IncomingCommand1 = CurrentByte;
			}
			else AcceptanceFlag = 0;
           // Message += " ";
           // Message += CurrentByte;
           // PrintMessage(Message);
			break;
		case 6://check to see if this is a valid command (A keyboard character UPPER or Lower case)
			//if(CurrentByte > 47 && CurrentByte < 123)
			//{
				AcceptanceFlag++;
				IncomingCommand2 = CurrentByte;
			//}
			//else AcceptanceFlag = 0;
           // Message += " ";
           // Message += CurrentByte;
           // PrintMessage(Message);
			break;
		case 7://This should be a packet length - if zero then this is just a command with no data
				//if greater than 128 then it is an invalid packet - the largest packet is 128 bytes
			if(CurrentByte < 255)
			{
				AcceptanceFlag = 0;
				IncomingPacketLength = CurrentByte;
                //AnsiString OKMsg = "PKT OK: ";
                //OKMsg += IncomingPacketLength;
                //PrintMessage(OKMsg);
				PacketAccepted = 1;
			}
			else AcceptanceFlag = 0;
            //PrintMessage(AcceptanceFlag);
			break;
		default:
                PacketAccepted = 0;
		  		AcceptanceFlag = 0;
                //PrintMessage("Default");
                //Message += " " + CurrentByte;
           		//PrintMessage(Message);
		  	break;
		}
		//each time you pass a byte through the case checker de-incriment the buffer in out diff counter
		//and incriment the buffer read index - checking the limits

		//if at any point the packet gets accepted then return
		/*if(PacketAccepted == 1)
		{
			//The buffer read index has been incrimented to look at the NEXT byte
			//which will be the first byte of the data in the packet
            
            AnsiString Message;
        	Message = "Recieved Packet: Command1 = ";
        	Message += IncomingCommand1;
        	Message += "Command2 = ";
        	Message += IncomingCommand2;
        	Message += "Packet Length = ";
        	Message += IncomingPacketLength;
        	PrintMessage(Message);

			return PacketAccepted;
		} */

	//if you get to here then you have reached the end of the buffer and there are no more pending bytes
	//and the packet filter has not been passed
	return PacketAccepted;

}

void __fastcall TREMOTE::ExtractIncomingDataExecute(TObject *Sender)
{
	//extracts the incoming data from a packet
    switch(  IncomingCommand1 )
    {
    case 'A':
    	ExtractCommandAorB->Execute();
    	break;
    case 'B':
    	ExtractCommandAorB->Execute();
    	break;
    case 'V':
         ExtractAckMsg->Execute();
         break;
    case 'E':
         ExtractErrorMsg->Execute();
         break;
    case 'D':
         ExtractDebugMsg->Execute();
         break;
    case 'C': //Mutated profile data, command2 includes trace and profile data
         ExtractCommandC->Execute();
         break;
    case 'Z': //empty packet -- to "push" the data in the RXQ buffer
         //ExtractCommandZ->Execute();
         //SendProfileRcvdAck();
         break;
    default:
    	break;
    }
}

//---------------------------------------------------------------------------
int TREMOTE::DecodeSerialVariable(int Upper, int Lower)
{
   //Converts two serial bytes to a signed int16
   int Result = 0;
   Result = Upper;
   Result<<=8;
   Result |= Lower;
   Result -= UINT16ZERO;
   return Result;
}

void __fastcall TREMOTE::ExtractCommandZExecute(TObject *Sender)
{
     if(!ConnectionStatus)
     {
                PrintMessage("Error - Not Connected");
                return;
     }
     AnsiString Line;
     //Sends an empty packet to the actuator in response to an empty pkt from the actuator
     byte DataBlock[32];
     int Index;
     byte PacketSize = 1;
     //Unwrap and package the first block

     //place the preamble in the DataBlock array
     DataBlock[0] = 'P';
     DataBlock[1] = 'G';
     DataBlock[2] = 'S';
     DataBlock[3] = '#';
     DataBlock[4] = TargetNode;
     DataBlock[5] = 'Z';
     DataBlock[6] = 'Z';
     DataBlock[7] = PacketSize;
     DataBlock[8] = 1;

     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, DataBlock, 9);
     if(ErrCode < 0)
     {
        Line = "Error in sending Ack. Errcode = ";
        Line += ErrCode;
     }
     else
     {
        Line = "Sending empty pkt to actuator";
     }
     PrintMessage(Line);
}

//---------------------------------------------------------------------------
void __fastcall TREMOTE::ExtractCommandCExecute(TObject *Sender)
{
    //PDamp mutation data
    if(IncomingCommand2 == 'A')
        processPDMutationData();
    //NDamp mutation data
    if(IncomingCommand2 == 'B')
        processNDMutationData();
    //Force mutation data
    if(IncomingCommand2 == 'C')
    {
        processForceMutationData();
        if(mutationCnt == 0)
            transferProfileData(); //transfer ArrayOfProfileData[0] to MutatedProfile
        collectMutationStatistics();
    }
    //Profile evaluation data - score and zone counts
    if(IncomingCommand2 == 'E')
        processProfileEvaluationData();

    if(IncomingCommand2 == 'D')
        processMutatedDamprofile();

    if(IncomingCommand2 == 'P')
    {
        processMutatedForceProfile();
        PackUpProfileData->Execute();
        AnsiString fileName = "D:\\PSprings\\Analysis\\Adapted";
        mutationCnt++;
        fileName += (AnsiString)mutationCnt;
        fileName += ".pgf";
        ArrayOfProSettings[EditingProfileNo]->SaveToFile(fileName);

        //plotMutatedData();
        //SendProfileRcvdAck();
    }
}

//---------------------------------------------------------------------------
void TREMOTE::processMutatedDamprofile()
{
    int PDampVal, NDampVal;
    int i,j;
    AnsiString profileMsg="";
    //MutatedProfile->MaxRecTraceIndex = (IncomingPacketLength/2);

    for(i=0; i<64; i++)
    {
        //PDampVal = DecodeSerialVariable(IncomingDataBuffer[2*i], IncomingDataBuffer[2*i+1]);
        PDampVal = IncomingDataBuffer[i];
        PDampVal -= 128;
        profileMsg += PDampVal;
        profileMsg += ",";
        MutatedProfile->SetPDampValue(PDampVal, i);
        ArrayOfProfileData[EditingProfileNo]->SetPDampValue(PDampVal, i);
    }
    profileMsg += "\n";
    for(j=i; j<128; j++)
    {
        //PDampVal = DecodeSerialVariable(IncomingDataBuffer[2*i], IncomingDataBuffer[2*i+1]);
        NDampVal = IncomingDataBuffer[j];
        NDampVal -= 128;
        profileMsg += NDampVal;
        profileMsg += ",";
        MutatedProfile->SetNDampValue(NDampVal, j-64);
        ArrayOfProfileData[EditingProfileNo]->SetNDampValue(NDampVal, j-64);
    }
    profileMsg += "\n";
    PrintMessage(profileMsg);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::processMutatedForceProfile()
{
    int forceVal;
    double time1, time2;
    int pnum, CopyId, n, i;
    char pnumString[10], pnumString2[10];
    AnsiString profileMsg="";

    for(i=0;i<64;i++)
    {
        forceVal = DecodeSerialVariable(IncomingDataBuffer[2*i], IncomingDataBuffer[2*i+1]);
        profileMsg += forceVal;
        profileMsg += ",";
        MutatedProfile->SetFValue(forceVal, i);
        ArrayOfProfileData[EditingProfileNo]->SetFValue(forceVal, i);
    }
    n=2*i;
    pnum = IncomingDataBuffer[n++];
    pnum = pnum<<8;
    pnum |= IncomingDataBuffer[n++];
    MutatedProfile->RecvProfileNumber = pnum;
    MutatedProfile->RecvProfileCopyId = IncomingDataBuffer[n++];

    profileMsg += "\n";
    PrintMessage(profileMsg);
    /*
    MutatedProfile->ProfileGraph->Height = Image1->Height;
    MutatedProfile->ProfileGraph->Width = Image1->Width;
    MutatedProfile->DrawForceGraph();
    Image1->Canvas->Draw(0,0, MutatedProfile->ProfileGraph);
    */

    pnum = MutatedProfile->MutatedProfileNumber += 1;
    itoa(pnum,pnumString,10);
    strcat(pnumString," ## ");

    itoa(MutatedProfile->RecvProfileNumber,pnumString2,10);
    strcat(pnumString, pnumString2);
    strcat(pnumString,"/");
    itoa(MutatedProfile->RecvProfileCopyId,pnumString2,10);
    strcat(pnumString, pnumString2);

    REMOTE->ProfileNumber->Caption=pnumString;

    ArrayOfProfileData[EditingProfileNo]->DrawForceSurface(0);
    REMOTE->ClearTraceImage->Execute();
    //REMOTE->RedrawAndRefresh->Execute();

    //SioTxClear(ThePort);
    /*
    time1 = clock()/CLK_TCK;
    while(SioTxQue(ThePort) != 0)
    {
        time2 = clock()/CLK_TCK;
        if(time2-time1 >= 4)
        {
            AnsiString Line = "Sending empty pkt to flush buffer...";
            PrintMessage(Line);
            ExtractCommandZ->Execute();
            break;
        }
    }
    */
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::processPDMutationData()
{
    int pdampVal;
    int i;
    //AnsiString Filename = "D:\\PSprings\\Analysis\\PDamp.txt";

    //MutationData->Clear();
    //MutationData->Append("\n");
    pdampfile = fopen("D:\\PSprings\\Analysis\\PDamp.txt","a+");
    fprintf(pdampfile,"\n");
    for(i=0;i<64;i++)
    {
        pdampVal = DecodeSerialVariable(IncomingDataBuffer[2*i], IncomingDataBuffer[2*i+1]);
        //MutationData->Add((AnsiString)pdampVal);
        //pdampVal = IncomingDataBuffer[2*i];
        //pdampVal = pdampVal<<8;
        //pdampVal |= IncomingDataBuffer[2*i+1];
        //pdampVal -=128;
        fprintf(pdampfile,"%d ",pdampVal);
        MutatedProfile->PdampMutation[i] = pdampVal;
    }
    fclose(pdampfile);
    //pdampfile = new TFileStream("D:\\PSprings\\Analysis\\PDamp.txt",fmShareDenyWrite);
    //MutationData->SaveToStream(pdampfile);
    //pdampfile->Free();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::processNDMutationData()
{
    int ndampVal;
    int i;
    //AnsiString Filename = "D:\\PSprings\\Analysis\\NDamp.txt";

    //MutationData->Clear();
    ndampfile = fopen("D:\\PSprings\\Analysis\\NDamp.txt","a+");
    fprintf(ndampfile,"\n");
    for(i=0;i<64;i++)
    {
        ndampVal = DecodeSerialVariable(IncomingDataBuffer[2*i], IncomingDataBuffer[2*i+1]);
        //MutationData->Add((AnsiString)ndampVal);
        //ndampVal = IncomingDataBuffer[2*i];
        //ndampVal = ndampVal<<8;
        //ndampVal |= IncomingDataBuffer[2*i+1];
        //ndampVal -=128;
        fprintf(ndampfile,"%d ",ndampVal);
        MutatedProfile->NdampMutation[i] = ndampVal;
    }
    fclose(ndampfile);
    //ndampfile = new TFileStream("D:\\PSprings\\Analysis\\NDamp.txt",fmShareDenyWrite);
    //MutationData->SaveToStream(ndampfile);
    //ndampfile->Free();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::processForceMutationData()
{
    int forceVal;
    int i;
    //AnsiString Filename = "D:\\PSprings\\Analysis\\Force.txt";

    //MutationData->Clear();
    forcefile = fopen("D:\\PSprings\\Analysis\\Force.txt","a+");
    fprintf(forcefile,"\n");
    for(i=0;i<64;i++)
    {
        forceVal = DecodeSerialVariable(IncomingDataBuffer[2*i], IncomingDataBuffer[2*i+1]);
        //MutationData->Add((AnsiString)forceVal);
        fprintf(forcefile,"%d ",forceVal);
        MutatedProfile->ForceMutation[i] = forceVal;
    }
    fclose(forcefile);
    //forcefile = new TFileStream("D:\\PSprings\\Analysis\\Force.txt",fmShareDenyWrite);
    //MutationData->SaveToStream(forcefile);
    //forcefile->Free();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::transferProfileData()
{
    for(int i=0;i<64;i++)
    {
        MutatedProfile->ForceTable[i] = ArrayOfProfileData[0]->ForceTable[i];
        MutatedProfile->PDamptable[i] = ArrayOfProfileData[0]->PDamptable[i];
        MutatedProfile->NDamptable[i] = ArrayOfProfileData[0]->NDamptable[i];
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::processProfileEvaluationData()
{
    int avgAngle0, avgAngle1, avgAngle2, avgAngle3, avgAngle;
    int avgAngleVelocity0, avgAngleVelocity1, avgAngleVelocity2, avgAngleVelocity3, avgAngleVelocity;
    profileEvaluationFile = fopen("D:\\PSprings\\Analysis\\ProfileEvaluation.txt","a+");
    fprintf(profileEvaluationFile,"\n");
    MutatedProfile->zone0Cnt =  IncomingDataBuffer[0]*256 + IncomingDataBuffer[1];
    fprintf(profileEvaluationFile,"%d ",MutatedProfile->zone0Cnt);
    MutatedProfile->zone1Cnt =  IncomingDataBuffer[2]*256 + IncomingDataBuffer[3];
    fprintf(profileEvaluationFile,"%d ",MutatedProfile->zone1Cnt);
    MutatedProfile->zone2Cnt =  IncomingDataBuffer[4]*256 + IncomingDataBuffer[5];
    fprintf(profileEvaluationFile,"%d ",MutatedProfile->zone2Cnt);
    MutatedProfile->zone3Cnt =  IncomingDataBuffer[6]*256 + IncomingDataBuffer[7];
    fprintf(profileEvaluationFile,"%d ",MutatedProfile->zone3Cnt);
    MutatedProfile->profileScore = IncomingDataBuffer[8]*256 + IncomingDataBuffer[9];
    fprintf(profileEvaluationFile,"%d ",MutatedProfile->profileScore);
    MutatedProfile->actuatorIterationCnt = IncomingDataBuffer[10]*256 + IncomingDataBuffer[11];
    fprintf(profileEvaluationFile,"%d ",MutatedProfile->actuatorIterationCnt);
    MutatedProfile->mutationRange = IncomingDataBuffer[12]*256 + IncomingDataBuffer[13];
    fprintf(profileEvaluationFile,"%d ",MutatedProfile->mutationRange);
    MutatedProfile->avgTVZtransitionDist = IncomingDataBuffer[14]*256 + IncomingDataBuffer[15];
    fprintf(profileEvaluationFile,"%d ",MutatedProfile->avgTVZtransitionDist);
    //Calculate avg angle and angle velocity during evaluation
    if(iterations0 != 0)
    {
        avgAngle0 = totalAngle0/iterations0;
        avgAngleVelocity0 = totalAngleVelocity0/iterations0;
    }
    else
    {
        avgAngle0 = -999;
        avgAngleVelocity0 = -999;
    }
    fprintf(profileEvaluationFile,"%d %d %d ",avgAngle0,avgAngleVelocity0,iterations0);
    if(iterations1 != 0)
    {
        avgAngle1 = totalAngle1/iterations1;
        avgAngleVelocity1 = totalAngleVelocity1/iterations1;
    }
    else
    {
        avgAngle1 = -999;
        avgAngleVelocity1 = -999;
    }
    fprintf(profileEvaluationFile,"%d %d %d ",avgAngle1,avgAngleVelocity1,iterations1);
    if(iterations2 != 0)
    {
        avgAngle2 = totalAngle2/iterations2;
        avgAngleVelocity2 = totalAngleVelocity2/iterations2;
    }
    else
    {
        avgAngle2 = -999;
        avgAngleVelocity2 = -999;
    }
    fprintf(profileEvaluationFile,"%d %d %d ",avgAngle2,avgAngleVelocity2,iterations2);
    if( iterations3 != 0)
    {
        avgAngle3 = totalAngle3/iterations3;
        avgAngleVelocity3 = totalAngleVelocity3/iterations3;
    }
    else
    {
        avgAngle3 = -999;
        avgAngleVelocity3 = -999;
    }
    fprintf(profileEvaluationFile,"%d %d %d ",avgAngle3,avgAngleVelocity3,iterations3);
    if(iterations != 0)
    {
        avgAngle = totalAngle/iterations;
        avgAngleVelocity = totalAngleVelocity/iterations;
    }
    else
    {
        avgAngle = -999;
        avgAngleVelocity = -999;
    }
    fprintf(profileEvaluationFile,"%d %d %d ",avgAngle,avgAngleVelocity,iterations);
    fprintf(profileEvaluationFile,"%d ",mutationCnt);
    totalAngle = 0;
    totalAngleVelocity = 0;
    iterations = 0;
    totalAngle0 = 0;
    totalAngleVelocity0 = 0;
    iterations0 = 0;
    totalAngle1 = 0;
    totalAngleVelocity1 = 0;
    iterations1 = 0;
    totalAngle2 = 0;
    totalAngleVelocity2 = 0;
    iterations2 = 0;
    totalAngle3 = 0;
    totalAngleVelocity3 = 0;
    iterations3 = 0;
    fclose(profileEvaluationFile);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::collectMutationStatistics()
{
    int tempForceVal, tempPDval, tempNDval;
    int numMutations=0;
    int numNOmutations=0;
    int angle;
    int totalFmutation = 0;
    int totalPDmutation = 0;
    int totalNDmutation = 0;
    mutatedAnglesFile = fopen("D:\\PSprings\\Analysis\\MutatedAngles.txt","a+");
    notMutatedAnglesFile = fopen("D:\\PSprings\\Analysis\\NotMutatedAngles.txt","a+");
    numMutationsFile = fopen("D:\\PSprings\\Analysis\\NumMutations.txt","a+");
    mutationsMagnitudeFile = fopen("D:\\PSprings\\Analysis\\MutationsMagnitude.txt","a+");
    fprintf(mutatedAnglesFile,"\n");
    fprintf(notMutatedAnglesFile,"\n");
    fprintf(numMutationsFile,"\n");
    fprintf(mutationsMagnitudeFile,"\n");
    for(int i=0;i<64;i++)
    {
        tempForceVal = MutatedProfile->ForceMutation[i];
        if(tempForceVal != -9999 && tempForceVal != -9998)
        {
            numMutations++;
            angle = (i-32)*16;
            fprintf(mutatedAnglesFile,"%d ",angle);
            totalFmutation += abs(tempForceVal - MutatedProfile->ForceTable[i]);
        }
        else if(tempForceVal == -9998)
        {
            numNOmutations++;
            angle = (i-32)*16;
            fprintf(notMutatedAnglesFile,"%d ",angle);
        }
        tempPDval = MutatedProfile->PdampMutation[i];
        if(tempPDval != -9999 && tempPDval != -9998)
            totalPDmutation += abs(tempPDval - MutatedProfile->PDamptable[i]);
        tempNDval = MutatedProfile->NdampMutation[i];
        if(tempNDval != -9999 && tempNDval != -9998)
            totalNDmutation += abs(tempNDval - MutatedProfile->NDamptable[i]);
    }
    fprintf(numMutationsFile,"%d %d",numMutations,numNOmutations);
    fprintf(mutationsMagnitudeFile,"%d %d %d",totalFmutation,totalPDmutation,totalNDmutation);
    fclose(mutatedAnglesFile);
    fclose(notMutatedAnglesFile);
    fclose(numMutationsFile);
    fclose(mutationsMagnitudeFile);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::plotMutatedData()
{
    int NewDraw = 1;
    int XPos, YPos;
    MutatedProfile->ForceSurface->Height = Image1->Height;
    MutatedProfile->ForceSurface->Width = Image1->Width;
    MutatedProfile->DrawForceSurface(0);
    
    for(int i=0; i<MutatedProfile->MaxRecTraceIndex; i++)
    {
        XPos = MutatedProfile->GetSurfaceXFromAngle(MutatedProfile->GetAngleTraceValue(i));
        YPos = MutatedProfile->GetSurfaceYFromVelocity(MutatedProfile->GetAngleVelTraceValue(i));
        if(NewDraw == 1)
        {
            TraceImage1->Canvas->Draw(0,0, MutatedProfile->ForceSurface);
            TraceImage1->Canvas->MoveTo(XPos, YPos);
        }
        TraceImage1->Canvas->Pen->Color=clWhite;
        TraceImage1->Canvas->LineTo(XPos, YPos);
        Image1->Canvas->Draw(0,0, TraceImage1);
        NewDraw = 0;
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TREMOTE::SendProfileRcvdAck()
{
     if(!ConnectionStatus)
     {
                PrintMessage("Error - Not Connected");
                return;
     }
     AnsiString Line;
     //Sends a msg acklowledging the receipt of a mutated profile
     byte DataBlock[32];
     int Index;
     byte pnum = 0;
     byte PacketSize = 3; //2 bytes for the profile number and 1 byte for CopyId
     //Unwrap and package the first block

     //place the preamble in the DataBlock array
     DataBlock[0] = 'P';
     DataBlock[1] = 'G';
     DataBlock[2] = 'S';
     DataBlock[3] = '#';
     DataBlock[4] = TargetNode;
     DataBlock[5] = 'K';
     DataBlock[6] = 'Y';
     DataBlock[7] = PacketSize;

     pnum = (byte) (MutatedProfile->RecvProfileNumber >> 8);
     DataBlock[8] = pnum;
     pnum = (byte) MutatedProfile->RecvProfileNumber;
     DataBlock[9] = pnum;
     DataBlock[10] = MutatedProfile->RecvProfileCopyId;

     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, DataBlock, 11);
     if(ErrCode < 0)
     {
        Line = "Error in sending Ack. Errcode = ";
        Line += ErrCode;
     }
     else
     {
        Line = "Received profile #";
        Line += MutatedProfile->RecvProfileNumber;
     }
     PrintMessage(Line);
}


//---------------------------------------------------------------------------
void __fastcall TREMOTE::ExtractCommandAorBExecute(TObject *Sender)
{
    int Var1, Var2, Var3, Var4, Flag1, Flag2, Flag3, Flag4;
    int Node, Mode, WorkingPro;
    AnsiString Line;

    if(IncomingCommand1 == 'A' || IncomingCommand1 == 'B')
    {

     	Var1 = DecodeSerialVariable(IncomingDataBuffer[0], IncomingDataBuffer[1]);
        Var2 = DecodeSerialVariable(IncomingDataBuffer[2], IncomingDataBuffer[3]);
        Var3 = DecodeSerialVariable(IncomingDataBuffer[4], IncomingDataBuffer[5]);
        Var4 = DecodeSerialVariable(IncomingDataBuffer[6], IncomingDataBuffer[7]);
        Flag1 = IncomingDataBuffer[8];
        Flag2 = IncomingDataBuffer[9];
        Flag3 = IncomingDataBuffer[10];
        Flag4 = IncomingDataBuffer[11];
        Node = IncomingDataBuffer[12];
        Mode = IncomingDataBuffer[13];
        WorkingPro = IncomingDataBuffer[14];
    }
    Line.cat_printf("%7d ", Var1);
    Line.cat_printf("%7d ", Var2);
    Line.cat_printf("%7d ", Var3);
    Line.cat_printf("%7d ", Var4);


    Line.cat_printf("%3d ", Flag1);
    Line.cat_printf("%3d ", Flag2);
    Line.cat_printf("%3d ", Flag3);
    Line.cat_printf("%3d ", Flag4);

    Line.cat_printf("%3d   ", Node);
    Line.cat_printf(" %d  ", Mode);
    Line.cat_printf("  %d ", WorkingPro);

    if(IncomingCommand1 == 'A') GroupAMemo->Lines->Add(Line);
    else GroupBMemo->Lines->Add(Line);
    int Time1 = SioTimer();
    TimeSinceLastpacket =Time1 - OldTime;
    OldTime = Time1;
    AnsiString TimeMessage = "COMM Rate (ms): ";
    TimeMessage += TimeSinceLastpacket;
    CommRateText->Caption = TimeMessage;

    int XPos, YPos;
    static int NewDraw = 1;
    ConnectedActuatorsCurrentProfile = WorkingPro;
    //Now Draw on the image if required
    //return if this is a 'B' packet
    if(IncomingCommand1 == 'B')   return;

    //For profile analysis---------------
    if(CollectStatisticsBox->Checked == true)
    {
        //fprintf(trajectoryFile,"%d %d\n",Var1,Var2);
        if(Var1 >=0 && Var2>=0)
        {
            totalAngle0 += Var1;
            totalAngleVelocity0 += Var2;
            iterations0++;
        }
        if(Var1 >=0 && Var2 <= 0)
        {
            totalAngle1 += Var1;
            totalAngleVelocity1 += Var2;
            iterations1++;
        }
        if(Var1 <=0 && Var2 <= 0)
        {
            totalAngle2 += Var1;
            totalAngleVelocity2 += Var2;
            iterations2++;
        }
        if(Var1 <=0 && Var2 >= 0)
        {
            totalAngle3 += Var1;
            totalAngleVelocity3 += Var2;
            iterations3++;
        }
        totalAngle += Var1;
        totalAngleVelocity += Var2;
        iterations++;
    }
    //------------------------------------

    if(DrawAngleDataBox->Checked == true)
    {
        if(DrawingOptionPanel->ItemIndex == 0)
        {
            Image1->Canvas->Draw(0, 0, ArrayOfProfileData[WorkingPro]->ProfileGraph);
            XPos = ArrayOfProfileData[WorkingPro]->GetGraphXFromAngle(Var1);
            Image1->Canvas->Pen->Color=clBlack;
            Image1->Canvas->MoveTo(XPos, 0);
            Image1->Canvas->LineTo(XPos, Image1->Height);
            NewDraw = 1;
        }
        if(DrawingOptionPanel->ItemIndex == 1)
        {
        	//TraceImage1->Transparent = true;
        	//TraceImage1->TransparentMode = tmFixed;
            //TraceImage1->TransparentColor = clBlack;
            if(TraceOnForceMapBox->Checked == false)
            {
            	//Image1->Canvas->CopyMode = cmSrcCopy;
                TraceImage1->Canvas->Draw(0,0, ArrayOfProfileData[WorkingPro]->ForceSurface);
                XPos = ArrayOfProfileData[WorkingPro]->GetSurfaceXFromAngle(Var1);
                YPos = ArrayOfProfileData[WorkingPro]->GetSurfaceYFromVelocity(Var2);

                TraceImage1->Canvas->Pen->Color=clWhite;
                TraceImage1->Canvas->MoveTo(XPos, 0);
                TraceImage1->Canvas->LineTo(XPos, Image1->Height);
                TraceImage1->Canvas->MoveTo(0, YPos);
                TraceImage1->Canvas->LineTo(Image1->Width, YPos);
                //Image1->Canvas->CopyMode = cmSrcInvert;
                Image1->Canvas->Draw(0,0, TraceImage1);
                //Image1->Canvas->CopyMode = cmSrcCopy;
                /*
                Image1->Canvas->Pen->Color=clSilver;
                Image1->Canvas->MoveTo(XPos, 0);
                Image1->Canvas->LineTo(XPos, Image1->Height);
                Image1->Canvas->MoveTo(0, YPos);
                Image1->Canvas->LineTo(Image1->Width, YPos);
                 */
                NewDraw = 1;
            }
            if(TraceOnForceMapBox->Checked == true)
            {
                AnsiString msg = "Angle = ";
                msg += Var1;
                PrintMessage(msg);
                XPos = ArrayOfProfileData[WorkingPro]->GetSurfaceXFromAngle(Var1);
                YPos = ArrayOfProfileData[WorkingPro]->GetSurfaceYFromVelocity(Var2);
                if(NewDraw == 1)
                {
                    if(ColorDrawingBox->Checked == true) ArrayOfProfileData[WorkingPro]->DrawForceSurface(0);
                    if(ColorDrawingBox->Checked == false) ArrayOfProfileData[WorkingPro]->DrawForceSurface(1);
                	//TraceImage1->Canvas->Draw(0,0, ArrayOfProfileData[WorkingPro]->ForceSurface);
                    TraceImage1->Canvas->MoveTo(XPos, YPos);
                    //Image1->Canvas->MoveTo(XPos, YPos);
                }
                TraceImage1->Canvas->Pen->Color=clWhite;
                TraceImage1->Canvas->LineTo(XPos, YPos);
                Image1->Canvas->Draw(0,0, TraceImage1);
                //Image1->Canvas->Pen->Color=clSilver;
                //Image1->Canvas->LineTo(XPos, YPos);
                NewDraw = 0;
            }
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ExtractDebugMsgExecute(TObject *Sender)
{
    AnsiString Line ="Debug Message: ";

    for(int n = 0; n < IncomingPacketLength; n++)
    {
        Line += (char)IncomingDataBuffer[n];
    }
    PrintMessage(Line);
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ExtractAckMsgExecute(TObject *Sender)
{
	AnsiString Line ="ACTUATOR ACK: ";

    for(int n = 0; n < IncomingPacketLength; n++)
    {
        Line += (char)IncomingDataBuffer[n];
    }
    PrintMessage(Line);
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ExtractErrorMsgExecute(TObject *Sender)
{
     AnsiString Line ="ACTUATOR ERROR: ";

    for(int n = 0; n < IncomingPacketLength; n++)
    {
        Line += (char)IncomingDataBuffer[n];
    }
    PrintMessage(Line);
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::OpenSerialPortMonitorExecute(TObject *Sender)
{
	//Opens the serial port monitor window
    //Edit the actuator settings
    if( SerialPortMonitorForm->Visible == true ) SerialPortMonitorForm->BringToFront();
    else SerialPortMonitorForm->Show();
    SerialPortMonitorVisible = 1;
    //StaticText1->Caption = "Open";
    

}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::CheckPortMonotorIsVisibleExecute(TObject *Sender)
{
	//Checks to see if the serial port monitor is visibel when the main form gets focus
    if(SerialPortMonitorForm->Visible == false)
    {
    	SerialPortMonitorVisible = 0;
    	//StaticText1->Caption = "Closed";
    }
    else
    {
    	SerialPortMonitorVisible = 1;
    	//StaticText1->Caption = "Open";
    }

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ActivateFormExecute(TObject *Sender)
{
	//called whenever this form gets focus
    CheckPortMonotorIsVisible->Execute();
    //RedrawAndRefresh->Execute();
}
//---------------------------------------------------------------------------



void __fastcall TREMOTE::ClearGroupAMemoExecute(TObject *Sender)
{
	//
    GroupAMemo->Clear();
    //GroupAMemo->Lines->Add(GroupMemoHeader);
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ClearGroupBMemoExecute(TObject *Sender)
{
	//
    GroupBMemo->Clear();
    //GroupBMemo->Lines->Add(GroupMemoHeader);
}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::SendRestartCommandExecute(TObject *Sender)
{
	//Send a restart command to the actuator
    if(!ConnectionStatus)
     {
     	PrintMessage("Error - Not Connected");
        return;
     }
     byte Preamble[32];
     int Index;
     byte PacketSize;

     //place the preamble in the DataBlock array
     Preamble[0] = 'P';
     Preamble[1] = 'G';
     Preamble[2] = 'S';
     Preamble[3] = '#';
     Preamble[4] = TargetNode;
     Preamble[5] = 'X';
     Preamble[6] = 'X';

     //Now the packet size for block 1 (128)
     PacketSize = 1;
     Preamble[7] = PacketSize;
     Preamble[8] = 1;

     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, Preamble, 9);

     PrintMessage("Restart Command Sent");
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ShowControlsExecute(TObject *Sender)
{
	if(CommandForm->Visible == false) CommandForm->Show();
    else CommandForm->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendCommandPacketExecute(TObject *Sender)
{
    int ErrCode = 0;
    ErrCode = SioPuts(ThePort, ControlOutBuffer, 23);

	//PrintMessage("Command Sent");
}
//---------------------------------------------------------------------------



void __fastcall TREMOTE::RedrawProfileBitmapsExecute(TObject *Sender)
{
	//Redraws all the images in the profile objects
    //Call when ever a profile or actuator file is loaded
	for(int n = 0; n < 8; n++)
    {
        //ArrayOfProfileData[n]->ProfileGraph->Height = Image1->Height;
        //ArrayOfProfileData[n]->ProfileGraph->Width = Image1->Width;
        ArrayOfProfileData[n]->DrawForceGraph();

        //ArrayOfProfileData[n]->ForceSurface->Height = Image1->Height;
        //ArrayOfProfileData[n]->ForceSurface->Width = Image1->Width;
        ArrayOfProfileData[n]->DrawForceSurface(0);
    }
}
//---------------------------------------------------------------------------

void TREMOTE::RedrawProfileBitmapX(int ProfileToRedraw)
{
    //Redraws all the images in the profile objects
    //Call when ever a profile or actuator file is loaded
	//ArrayOfProfileData[ProfileToRedraw]->ProfileGraph->Height = Image1->Height;
    //ArrayOfProfileData[ProfileToRedraw]->ProfileGraph->Width = Image1->Width;
    ArrayOfProfileData[ProfileToRedraw]->DrawForceGraph();

    //ArrayOfProfileData[ProfileToRedraw]->ForceSurface->Height = Image1->Height;
    //ArrayOfProfileData[ProfileToRedraw]->ForceSurface->Width = Image1->Width;
    ArrayOfProfileData[ProfileToRedraw]->DrawForceSurface(0);

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::SendPrintProfileDataCommandExecute(
      TObject *Sender)
{
	//Sends a print command for just the force and damping profile of the current active profile group
     if(!ConnectionStatus)
     {
                PrintMessage("Error - Not Connected");
                return;
     }
     AnsiString Line;
     //Sends the current profile object to the actuator
     byte DataBlock[32];
     int Index;
     byte PacketSize = 1;
     byte ProfileNo;
     ProfileNo = NewActuatorProfile;
     ProfileNo += 48;
     //Unwrap and package the first block

     //place the preamble in the DataBlock array
     DataBlock[0] = 'P';
     DataBlock[1] = 'G';
     DataBlock[2] = 'S';
     DataBlock[3] = '#';
     DataBlock[4] = TargetNode;
     DataBlock[5] = 'p';
     DataBlock[6] = ProfileNo;
     DataBlock[7] = PacketSize;
     DataBlock[8] = 1;

     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, DataBlock, 9);

     Line = "Print Force and Damping Request for Profile Group ";
     Line += NewActuatorProfile;
     Line += " Sent";
     PrintMessage(Line);

}
//---------------------------------------------------------------------------


void __fastcall TREMOTE::SendSwitchProfileCommandExecute(TObject *Sender)
{
	//Sends a command to switch to a new profile
    
    //Sends a print command for just the force and damping profile of the current active profile group
     if(!ConnectionStatus)
     {
                PrintMessage("Error - Not Connected");
                return;
     }
     AnsiString Line;
     //Sends the current profile object to the actuator
     byte DataBlock[32];
     int Index;
     byte PacketSize = 1;
     byte ProfileNo;
     ProfileNo = NewActuatorProfile;
     ProfileNo += 48;
     //Unwrap and package the first block

     //place the preamble in the DataBlock array
     DataBlock[0] = 'P';
     DataBlock[1] = 'G';
     DataBlock[2] = 'S';
     DataBlock[3] = '#';
     DataBlock[4] = TargetNode;
     DataBlock[5] = 'J';
     DataBlock[6] = ProfileNo;
     DataBlock[7] = PacketSize;
     DataBlock[8] = 1;

     int ErrCode = 0;
     ErrCode = SioPuts(ThePort, DataBlock, 9);

     Line = "Switch Profile to ";
     Line += NewActuatorProfile;
     Line += " Request Sent";
     PrintMessage(Line);

}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::ClearTraceImageExecute(TObject *Sender)
{
    //Clear the image with the force surface trace
    TraceImage1->Canvas->Draw(0,0, ArrayOfProfileData[ConnectedActuatorsCurrentProfile]->ForceSurface);
    Image1->Canvas->Draw(0,0,TraceImage1);
}
//---------------------------------------------------------------------------

void __fastcall TREMOTE::StartStopLogExecute(TObject *Sender)
{
    //starts or stops logging data to a file
    if(LogRunning == false)
    {
        //open a new file

        LogText->Caption = LogNumber;
        LogFileName = "Logs\\";
        LogFileName += LogFilenameEdit->Text;
        LogFileName += "_";
        LogFileName += LogNumber;
        LogFileName += ".txt";
        
        LogRunning = true;
     }
     else if(LogRunning == true)
     {
        //close the file

        LogNumber++;
        LogRunning = false;
     }

}
//---------------------------------------------------------------------------










