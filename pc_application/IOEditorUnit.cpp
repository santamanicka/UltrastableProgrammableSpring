//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Bcb_pgm.h"
#include "IOEditorUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TInputOutputForm *InputOutputForm;
//---------------------------------------------------------------------------
__fastcall TInputOutputForm::TInputOutputForm(TComponent* Owner)
	: TForm(Owner)
{

	SetupSerialTab->Execute();
    SetupCANTab->Execute();
    SetupDiscreteTab->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::SetupSerialTabExecute(TObject *Sender)
{
	//
    AnsiString Title = "RS232 Serial Outputs for Profile Group ";
    Title += (int)ProfileEditForm->CurrentEditingProfile;
    SerialTabTitle->Caption = Title;

    VarOutBoxA1->Items = ProfileEditForm->VariableList16;
    VarOutBoxA1->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out1_ptr];
    TrigOutBoxA1->Items = ProfileEditForm->VariableList8;
    TrigOutBoxA1->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut1_ptr];

    VarOutBoxA2->Items = ProfileEditForm->VariableList16;
    VarOutBoxA2->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out2_ptr];
    TrigOutBoxA2->Items = ProfileEditForm->VariableList8;
    TrigOutBoxA2->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut2_ptr];

    VarOutBoxA3->Items = ProfileEditForm->VariableList16;
    VarOutBoxA3->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out3_ptr];
    TrigOutBoxA3->Items = ProfileEditForm->VariableList8;
    TrigOutBoxA3->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut3_ptr];

    VarOutBoxA4->Items = ProfileEditForm->VariableList16;
    VarOutBoxA4->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out4_ptr];
    TrigOutBoxA4->Items = ProfileEditForm->VariableList8;
    TrigOutBoxA4->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut4_ptr];

    AutoTXTriggerA->Items = ProfileEditForm->VariableList8;
    AutoTXTriggerA->ItemIndex = ProfileEditForm->TempI8Ptr[_SerialOutEnableA_ptr];

    VarOutBoxB1->Items = ProfileEditForm->VariableList16;
    VarOutBoxB1->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out5_ptr];
    TrigOutBoxB1->Items = ProfileEditForm->VariableList8;
    TrigOutBoxB1->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut5_ptr];

    VarOutBoxB2->Items = ProfileEditForm->VariableList16;
    VarOutBoxB2->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out6_ptr];
    TrigOutBoxB2->Items = ProfileEditForm->VariableList8;
    TrigOutBoxB2->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut6_ptr];

    VarOutBoxB3->Items = ProfileEditForm->VariableList16;
    VarOutBoxB3->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out7_ptr];
    TrigOutBoxB3->Items = ProfileEditForm->VariableList8;
    TrigOutBoxB3->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut7_ptr];

    VarOutBoxB4->Items = ProfileEditForm->VariableList16;
    VarOutBoxB4->ItemIndex = ProfileEditForm->TempSI16Ptr[_RS232Out8_ptr];
    TrigOutBoxB4->Items = ProfileEditForm->VariableList8;
    TrigOutBoxB4->ItemIndex = ProfileEditForm->TempI8Ptr[_RS232FlagsOut8_ptr];

    AutoTXTriggerB->Items = ProfileEditForm->VariableList8;
    AutoTXTriggerB->ItemIndex = ProfileEditForm->TempI8Ptr[_SerialOutEnableB_ptr];

    for(int n = 0; n < 255; n++)
    {
    	TargetNodeBoxA->Items->Add(n);
        TargetNodeBoxB->Items->Add(n);
        TxDelayBoxA->Items->Add(n);
        TxDelayBoxB->Items->Add(n);
	}

    TargetNodeBoxA->ItemIndex = ProfileEditForm->TempI8Var[_RS232OutTargetNodeA];
	TargetNodeBoxB->ItemIndex = ProfileEditForm->TempI8Var[_RS232OutTargetNodeB];
	TxDelayBoxA->ItemIndex = ProfileEditForm->TempI8Var[_RS232CommRateGroupA];
	TxDelayBoxB->ItemIndex = ProfileEditForm->TempI8Var[_RS232CommRateGroupB];

    if( ProfileEditForm->TempI8Var[_RS232RequestReplyA] > 0) GetReplyBoxA->Checked = true;
    if( ProfileEditForm->TempI8Var[_RS232RequestReplyB] > 0) GetReplyBoxB->Checked = true;

    SerialPortBoxA->Items->Add("0 - Primary");
    SerialPortBoxA->Items->Add("1 - Secondary");
    SerialPortBoxA->ItemIndex = ProfileEditForm->TempI8Var[_RS232TransmitStreamA];
    SerialPortBoxB->Items->Add("0 - Primary");
    SerialPortBoxB->Items->Add("1 - Secondary");
    SerialPortBoxB->ItemIndex = ProfileEditForm->TempI8Var[_RS232TransmitStreamB];

}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::SetupCANTabExecute(TObject *Sender)
{
	AnsiString Title = "CAN BUS Outputs for Profile Group ";
    Title += (int)ProfileEditForm->CurrentEditingProfile;
    CanTabTitle->Caption = Title;

    CANVarOutBoxA1->Items = ProfileEditForm->VariableList16;
    CANVarOutBoxA1->ItemIndex = ProfileEditForm->TempSI16Ptr[_CANVarOut1_ptr];
    CANTrigOutBoxA1->Items = ProfileEditForm->VariableList8;
    CANTrigOutBoxA1->ItemIndex = ProfileEditForm->TempI8Ptr[_CANFlagsOut1_ptr];

    CANVarOutBoxA2->Items = ProfileEditForm->VariableList16;
    CANVarOutBoxA2->ItemIndex = ProfileEditForm->TempSI16Ptr[_CANVarOut2_ptr];
    CANTrigOutBoxA2->Items = ProfileEditForm->VariableList8;
    CANTrigOutBoxA2->ItemIndex = ProfileEditForm->TempI8Ptr[_CANFlagsOut2_ptr];

    CANAutoTxTriggerA->Items = ProfileEditForm->VariableList8;

    CANAutoTxTriggerA->ItemIndex = ProfileEditForm->TempI8Ptr[_CANOutEnableA_ptr];

    CANVarOutBoxB1->Items = ProfileEditForm->VariableList16;
    CANVarOutBoxB1->ItemIndex = ProfileEditForm->TempSI16Ptr[_CANVarOut3_ptr];
    CANTrigOutBoxB1->Items = ProfileEditForm->VariableList8;
    CANTrigOutBoxB1->ItemIndex = ProfileEditForm->TempI8Ptr[_CANFlagsOut3_ptr];

    CANVarOutBoxB2->Items = ProfileEditForm->VariableList16;
    CANVarOutBoxB2->ItemIndex = ProfileEditForm->TempSI16Ptr[_CANVarOut4_ptr];
    CANTrigOutBoxB2->Items = ProfileEditForm->VariableList8;
    CANTrigOutBoxB2->ItemIndex = ProfileEditForm->TempI8Ptr[_CANFlagsOut4_ptr];

    CANAutoTxTriggerB->Items = ProfileEditForm->VariableList8;
    CANAutoTxTriggerB->ItemIndex = ProfileEditForm->TempI8Ptr[_CANOutEnableB_ptr];

    for(int n = 0; n < 255; n++)
    {
    	CANTargetNodeBoxA->Items->Add(n);
        CANTargetNodeBoxB->Items->Add(n);
        CANTxDelayBoxA->Items->Add(n);
        CANTxDelayBoxB->Items->Add(n);
	}

	CANTargetNodeBoxA->ItemIndex = ProfileEditForm->TempI8Var[_CANOutTargetNodeA];
	CANTargetNodeBoxB->ItemIndex = ProfileEditForm->TempI8Var[_CANOutTargetNodeB];
	CANTxDelayBoxA->ItemIndex = ProfileEditForm->TempI8Var[_CANCommRateGroupA];
	CANTxDelayBoxB->ItemIndex = ProfileEditForm->TempI8Var[_CANCommRateGroupB];

}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::SetupDiscreteTabExecute(TObject *Sender)
{
	//
    AnsiString Title = "Digital Outputs for Profile Group ";
    Title += (int)ProfileEditForm->CurrentEditingProfile;
    DiscreteTabTitle1->Caption = Title;

    Title = "Analog Outputs for Profile Group ";
    Title += (int)ProfileEditForm->CurrentEditingProfile;
    DiscreteTabTitle2->Caption = Title;

    ExOutBox1->Items = ProfileEditForm->VariableList8;
    ExOutBox1->ItemIndex = ProfileEditForm->TempI8Ptr[_ExOut1_ptr];

    ExOutBox2->Items = ProfileEditForm->VariableList8;
    ExOutBox2->ItemIndex = ProfileEditForm->TempI8Ptr[_ExOut2_ptr];

    AnOutBox1->Items = ProfileEditForm->VariableList16;
    AnOutBox1->ItemIndex = ProfileEditForm->TempSI16Ptr[_ADOut1_ptr];

    AnOutBox2->Items = ProfileEditForm->VariableList16;
    AnOutBox2->ItemIndex = ProfileEditForm->TempSI16Ptr[_ADOut2_ptr];


    //This will be changes to a double value
    //at the moment the only valid gains are 0-10 (int)
    //Double GainVar;
    //int TempInt;
    GainEdit1->Text = ProfileEditForm->TempI8Var[_ADOut1Scaling];
    GainEdit2->Text = ProfileEditForm->TempI8Var[_ADOut2Scaling];	
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::DefaultSerialTabExecute(TObject *Sender)
{
	//defaults
    VarOutBoxA1->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxA1->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxA2->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxA2->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxA3->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxA3->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxA4->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxA4->ItemIndex = _GlobalDefaultFalse;

    AutoTXTriggerA->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxB1->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxB1->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxB2->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxB2->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxB3->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxB3->ItemIndex = _GlobalDefaultFalse;

    VarOutBoxB4->ItemIndex = _GlobalDefaultZeroModulator;
    TrigOutBoxB4->ItemIndex = _GlobalDefaultFalse;

    AutoTXTriggerB->ItemIndex = _GlobalDefaultFalse;

    TargetNodeBoxA->ItemIndex = 0;
    TargetNodeBoxB->ItemIndex = 0;
    TxDelayBoxA->ItemIndex = 10;
    TxDelayBoxB->ItemIndex = 10;

    GetReplyBoxA->Checked = false;
    GetReplyBoxB->Checked = false;

    SerialPortBoxA->ItemIndex = 0;
    SerialPortBoxB->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::DefaultCANTabExecute(TObject *Sender)
{
	//
    CANVarOutBoxA1->ItemIndex = _GlobalDefaultZeroModulator;
    CANTrigOutBoxA1->ItemIndex = _GlobalDefaultFalse;

    CANVarOutBoxA2->ItemIndex = _GlobalDefaultZeroModulator;
    CANTrigOutBoxA2->ItemIndex = _GlobalDefaultFalse;

    CANAutoTxTriggerA->ItemIndex = _GlobalDefaultFalse;


    CANVarOutBoxB1->ItemIndex = _GlobalDefaultZeroModulator;
    CANTrigOutBoxB1->ItemIndex = _GlobalDefaultFalse;

    CANVarOutBoxB2->ItemIndex = _GlobalDefaultZeroModulator;
    CANTrigOutBoxB2->ItemIndex = _GlobalDefaultFalse;

    CANAutoTxTriggerB->ItemIndex = _GlobalDefaultFalse;

    CANTargetNodeBoxA->ItemIndex = 0;
    CANTargetNodeBoxB->ItemIndex = 0;
	CANTxDelayBoxA->ItemIndex = 10;
	CANTxDelayBoxB->ItemIndex = 10;
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::DefaultDiscreteTabExecute(
      TObject *Sender)
{
	//Set Defaults
    ExOutBox1->ItemIndex = _GlobalDefaultFalse;
   	ExOutBox2->ItemIndex = _GlobalDefaultFalse;

    AnOutBox1->ItemIndex = _GlobalDefaultZeroModulator;
    AnOutBox2->ItemIndex = _GlobalDefaultZeroModulator;

    GainEdit1->Text = 1;
    GainEdit2->Text = 1;
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::SetDefaultsExecute(TObject *Sender)
{
	switch( PageControl1->ActivePageIndex )
    {
    case 0:
        //Serial
        DefaultSerialTab->Execute();
    	break;
    case 1:
        //CAN
        DefaultCANTab->Execute();
    	break;

    case 2:
        //Discrete
        DefaultDiscreteTab->Execute();
    	break;
    default:
    	break;
    }
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::SaveSerialTabExecute(TObject *Sender)
{
	ProfileEditForm->TempSI16Ptr[_RS232Out1_ptr] = VarOutBoxA1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut1_ptr] = TrigOutBoxA1->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out2_ptr] = VarOutBoxA2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut2_ptr] = TrigOutBoxA2->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out3_ptr] = VarOutBoxA3->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut3_ptr] = TrigOutBoxA3->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out4_ptr] = VarOutBoxA4->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut4_ptr] = TrigOutBoxA4->ItemIndex;

    ProfileEditForm->TempI8Ptr[_SerialOutEnableA_ptr] = AutoTXTriggerA->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out5_ptr] = VarOutBoxB1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut5_ptr] = TrigOutBoxB1->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out6_ptr] = VarOutBoxB2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut6_ptr] = TrigOutBoxB2->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out7_ptr] = VarOutBoxB3->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut7_ptr] = TrigOutBoxB3->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_RS232Out8_ptr] = VarOutBoxB4->ItemIndex;
    ProfileEditForm->TempI8Ptr[_RS232FlagsOut8_ptr] = TrigOutBoxB4->ItemIndex;

    ProfileEditForm->TempI8Ptr[_SerialOutEnableB_ptr] = AutoTXTriggerB->ItemIndex;

    ProfileEditForm->TempI8Var[_RS232OutTargetNodeA] = TargetNodeBoxA->ItemIndex;
    ProfileEditForm->TempI8Var[_RS232OutTargetNodeB] = TargetNodeBoxB->ItemIndex;

    ProfileEditForm->TempI8Var[_RS232CommRateGroupA] = TxDelayBoxA->ItemIndex;
    ProfileEditForm->TempI8Var[_RS232CommRateGroupB] = TxDelayBoxB->ItemIndex;

    if( GetReplyBoxA->Checked == true) ProfileEditForm->TempI8Var[_RS232RequestReplyA] = 1;
    else ProfileEditForm->TempI8Var[_RS232RequestReplyA] = 0;
    if( GetReplyBoxB->Checked == true) ProfileEditForm->TempI8Var[_RS232RequestReplyB] = 1;
    else ProfileEditForm->TempI8Var[_RS232RequestReplyB] = 0;

    ProfileEditForm->TempI8Var[_RS232TransmitStreamA] = SerialPortBoxA->ItemIndex;
    ProfileEditForm->TempI8Var[_RS232TransmitStreamB] = SerialPortBoxB->ItemIndex;
    //Now check to see if the copy to all box is checked
    //- if it is then copy the settings to all the other profile objects
    //This will override the cancel button on the editor form
    if(CopySettingsToAllBox->Checked == true)
    {
    	for(int n = 0; n < 8; n++)
        {
             REMOTE->ArrayOfProfileData[n]->SInt16Pointers[_RS232Out1_ptr] = ProfileEditForm->TempSI16Ptr[_RS232Out1_ptr];
             REMOTE->ArrayOfProfileData[n]->SInt16Pointers[_RS232Out2_ptr] = ProfileEditForm->TempSI16Ptr[_RS232Out2_ptr];
             REMOTE->ArrayOfProfileData[n]->SInt16Pointers[_RS232Out3_ptr] = ProfileEditForm->TempSI16Ptr[_RS232Out3_ptr];
             REMOTE->ArrayOfProfileData[n]->SInt16Pointers[_RS232Out4_ptr] = ProfileEditForm->TempSI16Ptr[_RS232Out4_ptr];
             REMOTE->ArrayOfProfileData[n]->SInt16Pointers[_RS232Out5_ptr] = ProfileEditForm->TempSI16Ptr[_RS232Out5_ptr];
             REMOTE->ArrayOfProfileData[n]->SInt16Pointers[_RS232Out6_ptr] = ProfileEditForm->TempSI16Ptr[_RS232Out6_ptr];
             REMOTE->ArrayOfProfileData[n]->SInt16Pointers[_RS232Out7_ptr] = ProfileEditForm->TempSI16Ptr[_RS232Out7_ptr];
             REMOTE->ArrayOfProfileData[n]->SInt16Pointers[_RS232Out8_ptr] = ProfileEditForm->TempSI16Ptr[_RS232Out8_ptr];

             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_RS232FlagsOut1_ptr] = ProfileEditForm->TempI8Ptr[_RS232FlagsOut1_ptr];
             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_RS232FlagsOut2_ptr] = ProfileEditForm->TempI8Ptr[_RS232FlagsOut2_ptr];
             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_RS232FlagsOut3_ptr] = ProfileEditForm->TempI8Ptr[_RS232FlagsOut3_ptr];
             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_RS232FlagsOut4_ptr] = ProfileEditForm->TempI8Ptr[_RS232FlagsOut4_ptr];
             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_RS232FlagsOut5_ptr] = ProfileEditForm->TempI8Ptr[_RS232FlagsOut5_ptr];
             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_RS232FlagsOut6_ptr] = ProfileEditForm->TempI8Ptr[_RS232FlagsOut6_ptr];
             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_RS232FlagsOut7_ptr] = ProfileEditForm->TempI8Ptr[_RS232FlagsOut7_ptr];
             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_RS232FlagsOut8_ptr] = ProfileEditForm->TempI8Ptr[_RS232FlagsOut8_ptr];

             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_SerialOutEnableA_ptr] = ProfileEditForm->TempI8Ptr[_SerialOutEnableA_ptr];
             REMOTE->ArrayOfProfileData[n]->Int8Pointers[_SerialOutEnableB_ptr] = ProfileEditForm->TempI8Ptr[_SerialOutEnableB_ptr];

             REMOTE->ArrayOfProfileData[n]->Int8Variables[_RS232OutTargetNodeA] = ProfileEditForm->TempI8Var[_RS232OutTargetNodeA];
             REMOTE->ArrayOfProfileData[n]->Int8Variables[_RS232OutTargetNodeB] = ProfileEditForm->TempI8Var[_RS232OutTargetNodeB];

             REMOTE->ArrayOfProfileData[n]->Int8Variables[_RS232CommRateGroupA] = ProfileEditForm->TempI8Var[_RS232CommRateGroupA];
             REMOTE->ArrayOfProfileData[n]->Int8Variables[_RS232CommRateGroupB] = ProfileEditForm->TempI8Var[_RS232CommRateGroupB];


             REMOTE->ArrayOfProfileData[n]->Int8Variables[_RS232RequestReplyA] = ProfileEditForm->TempI8Var[_RS232RequestReplyA];
             REMOTE->ArrayOfProfileData[n]->Int8Variables[_RS232RequestReplyB] = ProfileEditForm->TempI8Var[_RS232RequestReplyB];

             REMOTE->ArrayOfProfileData[n]->Int8Variables[_RS232TransmitStreamA] = ProfileEditForm->TempI8Var[_RS232TransmitStreamA];
             REMOTE->ArrayOfProfileData[n]->Int8Variables[_RS232TransmitStreamB] = ProfileEditForm->TempI8Var[_RS232TransmitStreamB];
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::SaveCANTabExecute(TObject *Sender)
{
	ProfileEditForm->TempSI16Ptr[_CANVarOut1_ptr] = CANVarOutBoxA1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_CANFlagsOut1_ptr] = CANTrigOutBoxA1->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_CANVarOut2_ptr] = CANVarOutBoxA2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_CANFlagsOut2_ptr] = CANTrigOutBoxA2->ItemIndex;

    ProfileEditForm->TempI8Ptr[_CANOutEnableA_ptr] = CANAutoTxTriggerA->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_CANVarOut3_ptr] = CANVarOutBoxB1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_CANFlagsOut3_ptr] = CANTrigOutBoxB1->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_CANVarOut4_ptr] = CANVarOutBoxB2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_CANFlagsOut4_ptr] = CANTrigOutBoxB2->ItemIndex;

    ProfileEditForm->TempI8Ptr[_CANOutEnableB_ptr] = CANAutoTxTriggerB->ItemIndex;

    ProfileEditForm->TempI8Var[_CANOutTargetNodeA] = CANTargetNodeBoxA->ItemIndex;
    ProfileEditForm->TempI8Var[_CANOutTargetNodeB] = CANTargetNodeBoxB->ItemIndex;

    ProfileEditForm->TempI8Var[_CANCommRateGroupA] = CANTxDelayBoxA->ItemIndex;
    ProfileEditForm->TempI8Var[_CANCommRateGroupB] = CANTxDelayBoxB->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::SaveDiscreteTabExecute(TObject *Sender)
{
	ProfileEditForm->TempI8Ptr[_ExOut1_ptr] = ExOutBox1->ItemIndex;

    ProfileEditForm->TempI8Ptr[_ExOut2_ptr] = ExOutBox2->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_ADOut1_ptr] = AnOutBox1->ItemIndex;
    ProfileEditForm->TempSI16Ptr[_ADOut2_ptr] = AnOutBox2->ItemIndex;

    //This will be changes to a double value
    //at the moment the only valid gains are 0-10 (int)
    //Double GainVar;
    //int TempInt;
    ProfileEditForm->TempI8Var[_ADOut1Scaling] = GainEdit1->Text.ToInt();
    if( ProfileEditForm->TempI8Var[_ADOut1Scaling] < 0)  ProfileEditForm->TempI8Var[_ADOut1Scaling] = 0;
    else if( ProfileEditForm->TempI8Var[_ADOut1Scaling] > 10 )  ProfileEditForm->TempI8Var[_ADOut1Scaling] = 10;

    ProfileEditForm->TempI8Var[_ADOut2Scaling] = GainEdit2->Text.ToInt();
    if( ProfileEditForm->TempI8Var[_ADOut2Scaling] < 0)  ProfileEditForm->TempI8Var[_ADOut2Scaling] = 0;
    else if( ProfileEditForm->TempI8Var[_ADOut2Scaling] > 10 )  ProfileEditForm->TempI8Var[_ADOut2Scaling] = 10;
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::SaveAndCloseExecute(TObject *Sender)
{
	SaveSerialTab->Execute();
    SaveCANTab->Execute();
    SaveDiscreteTab->Execute();
    InputOutputForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TInputOutputForm::CancelAndCloseExecute(TObject *Sender)
{
	InputOutputForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TInputOutputForm::CANAutoTxTriggerAChange(TObject *Sender)
{
 //	
}
//---------------------------------------------------------------------------


