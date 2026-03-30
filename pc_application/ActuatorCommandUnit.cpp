//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ActuatorCommandUnit.h"
#include "bcb_pgm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCommandForm *CommandForm;
//---------------------------------------------------------------------------
__fastcall TCommandForm::TCommandForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::SetupFormExecute(TObject *Sender)
{
	//
    Var1 = 0;
    Var2 = 0;
    Var3 = 0;
    Var4 = 0;
    Flag1 = 0;
    Flag2 = 0;
    Flag3 = 0;
    Flag4 = 0;
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::Zero1Execute(TObject *Sender)
{
	VarBar1->Position = 0;	
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::Zero2Execute(TObject *Sender)
{
	VarBar2->Position = 0;	
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::Zero3Execute(TObject *Sender)
{
	VarBar3->Position = 0;	
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::Zero4Execute(TObject *Sender)
{
	VarBar4->Position = 0;
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::ChangeVar1Execute(TObject *Sender)
{
	//
    double Temp = (double)VarBar1->Position;
    Var1 = (int)( Temp * ScaleEdit1->Text.ToDouble() );
    ValueText1->Caption = Var1;
    if(OnChangeTXButton->Checked == true) TransmitCommands->Execute();

}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::ChangeVar2Execute(TObject *Sender)
{
	//
    double Temp = (double)VarBar2->Position;
    Var2 = (int)( Temp * ScaleEdit2->Text.ToDouble() );
    ValueText2->Caption = Var2;
    if(OnChangeTXButton->Checked == true) TransmitCommands->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::ChangeVar3Execute(TObject *Sender)
{
	//
    double Temp = (double)VarBar3->Position;
    Var3 = (int)( Temp * ScaleEdit3->Text.ToDouble() );
    ValueText3->Caption = Var3;
    if(OnChangeTXButton->Checked == true) TransmitCommands->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::ChangeVar4Execute(TObject *Sender)
{
	//
    double Temp = (double)VarBar4->Position;
    Var4 = (int)( Temp * ScaleEdit4->Text.ToDouble() );
    ValueText4->Caption = Var4;
    if(OnChangeTXButton->Checked == true) TransmitCommands->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::ChangeFlag1Execute(TObject *Sender)
{
	if(FlagBox1->Checked == true) Flag1 = 1;
    else Flag1 = 0;
    if(OnChangeTXButton->Checked == true) TransmitCommands->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::ChangeFlag2Execute(TObject *Sender)
{
	if(FlagBox2->Checked == true) Flag2 = 1;
    else Flag2 = 0;
    if(OnChangeTXButton->Checked == true) TransmitCommands->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::ChangeFlag3Execute(TObject *Sender)
{
	if(FlagBox3->Checked == true) Flag3 = 1;
    else Flag3 = 0;
    if(OnChangeTXButton->Checked == true) TransmitCommands->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::ChangeFlag4Execute(TObject *Sender)
{
	if(FlagBox4->Checked == true) Flag4 = 1;
    else Flag4 = 0;
    if(OnChangeTXButton->Checked == true) TransmitCommands->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TCommandForm::TransmitCommandsExecute(TObject *Sender)
{
	//Pack up the commands and send
    	if(!REMOTE->ConnectionStatus)
     {
     	REMOTE->PrintMessage("Error - Not Connected");
        StartStopAutoTx->Execute();
        return;
     }

     byte PacketSize;

     //place the preamble in the DataBlock array
     REMOTE->ControlOutBuffer[0] = 'P';
     REMOTE->ControlOutBuffer[1] = 'G';
     REMOTE->ControlOutBuffer[2] = 'S';
     REMOTE->ControlOutBuffer[3] = '#';
     REMOTE->ControlOutBuffer[4] = REMOTE->TargetNode;
     if(PacketTypeBox->ItemIndex == 0) REMOTE->ControlOutBuffer[5] = 'A';
     else REMOTE->ControlOutBuffer[5] = 'B';
     if(RequestReplyBox->Checked == true)
     {
     	REMOTE->ControlOutBuffer[6] = 'A';
     }
     else REMOTE->ControlOutBuffer[6] = 'X';


     PacketSize = 15;
     REMOTE->ControlOutBuffer[7] = PacketSize;

     REMOTE->ControlOutBuffer[8] = GetVarByte( Var1, 1);
     REMOTE->ControlOutBuffer[9] = GetVarByte( Var1, 0);

     REMOTE->ControlOutBuffer[10] = GetVarByte( Var2, 1);
     REMOTE->ControlOutBuffer[11] = GetVarByte( Var2, 0);

     REMOTE->ControlOutBuffer[12] = GetVarByte( Var3, 1);
     REMOTE->ControlOutBuffer[13] = GetVarByte( Var3, 0);

     REMOTE->ControlOutBuffer[14] = GetVarByte( Var4, 1);
     REMOTE->ControlOutBuffer[15] = GetVarByte( Var4, 0);

     REMOTE->ControlOutBuffer[16] = Flag1;
     REMOTE->ControlOutBuffer[17] = Flag2;
     REMOTE->ControlOutBuffer[18] = Flag3;
     REMOTE->ControlOutBuffer[19] = Flag4;

     REMOTE->ControlOutBuffer[20] = 0;//Node
     REMOTE->ControlOutBuffer[21] = 0;//Mode
     REMOTE->ControlOutBuffer[22] = 0;//Profile

     REMOTE->SendCommandPacket->Execute();

}
//---------------------------------------------------------------------------
byte TCommandForm::GetVarByte(int Var, int Offset)
{
    int BitMask;
        int TempVal;
        byte ReturnVal;
        TempVal = Var;

        if(TempVal < -32767) TempVal = -32767;
        if(TempVal > 32768) TempVal = 32768;
        TempVal += 32767;
        BitMask =  0xFF00;
        //mask out the lower 8 bits
        if(Offset == 1)
        {
               TempVal >>=8; //shift out the lower bits
               ReturnVal = (byte)TempVal;
               return ReturnVal;
        }


        else if(Offset == 0)
        {      //mask out the upper 8 bits
                BitMask =  0x00FF;
               TempVal = TempVal & BitMask; //Bitwise AND to remove upper 8 bits
               ReturnVal = (byte)TempVal;
               return ReturnVal;
        }
        return 0;
}

//---------------------------------------------------------------------------
void __fastcall TCommandForm::Timer1Timer(TObject *Sender)
{
     TransmitCommands->Execute();
     unsigned int URate;
     double DRate;
     DRate = (double)TxRateEdit->Text.ToIntDef(10);
     if(DRate > 40)
     {
     	DRate = 40;
        TxRateEdit->Text = DRate;
     }
     else if(DRate < 1)
     {
     	DRate = 1;
        TxRateEdit->Text = DRate;
     }
     else TxRateEdit->Text = DRate;

     DRate = (1/DRate)*1000;
     URate = (unsigned int)DRate;
     if(URate < 20) URate = 20;
     if(URate > 1000) URate = 1000;

     Timer1->Interval = URate;
     StaticText1->Caption = URate;

}
//---------------------------------------------------------------------------

void __fastcall TCommandForm::StartStopAutoTxExecute(TObject *Sender)
{

	if(Timer1->Enabled == true)
    {
    	Timer1->Enabled = false;
        StartStopTxButton->Caption = "Start";
        return;
    }

    StartStopTxButton->Caption = "Stop";
	double DRate = TxRateEdit->Text.ToIntDef(10);
     if(DRate > 40)
     {
        TxRateEdit->Text = DRate;
     	DRate = 40;
     }
     if(DRate < 1)
     {
        TxRateEdit->Text = DRate;
     	DRate = 1;
     }
     DRate = 1/DRate;
     DRate *=1000;
     unsigned int URate = (unsigned int)DRate;
     if(DRate < 20) DRate = 20;
     if(DRate > 1000) DRate = 1000;

     Timer1->Interval = DRate;
     Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TCommandForm::ResetActuatorButtonClick(TObject *Sender)
{
	//Reset
    REMOTE->SendRestartCommand->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TCommandForm::HaltActuatorButtonClick(TObject *Sender)
{
	REMOTE->SendStopActuatorCommand->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TCommandForm::StartActuatorButtonClick(TObject *Sender)
{
	REMOTE->SendStartActuatorCommand->Execute();	
}
//---------------------------------------------------------------------------

void __fastcall TCommandForm::PrintProfileButtonClick(TObject *Sender)
{
	REMOTE->NewActuatorProfile = (byte)SwitchProfileBox->ItemIndex;
	REMOTE->SendPrintProfileDataCommand->Execute();	
}
//---------------------------------------------------------------------------

void __fastcall TCommandForm::SwitchProfileButtonClick(TObject *Sender)
{
	//Sends a command to jump to the profile in the combobox
    REMOTE->NewActuatorProfile = (byte)SwitchProfileBox->ItemIndex;
    REMOTE->SendSwitchProfileCommand->Execute();
}
//---------------------------------------------------------------------------

