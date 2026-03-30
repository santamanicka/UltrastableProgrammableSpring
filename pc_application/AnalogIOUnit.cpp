//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AnalogIOUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAnalogIOForm *AnalogIOForm;
//---------------------------------------------------------------------------
__fastcall TAnalogIOForm::TAnalogIOForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TAnalogIOForm::SetupFormExecute(TObject *Sender)
{
	AnsiString Title;
    Title = "Analog I/O for Profile No ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Label1->Caption = Title;

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
void __fastcall TAnalogIOForm::SaveFormExecute(TObject *Sender)
{

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

void __fastcall TAnalogIOForm::Button2Click(TObject *Sender)
{
	//Cancel
    AnalogIOForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TAnalogIOForm::Button1Click(TObject *Sender)
{
	//Save and close
    SaveForm->Execute();
    AnalogIOForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TAnalogIOForm::DefaultButtonClick(TObject *Sender)
{
	AnOutBox1->ItemIndex = _GlobalDefaultZeroModulator;
    AnOutBox2->ItemIndex = _GlobalDefaultZeroModulator;

    GainEdit1->Text = 1;
    GainEdit2->Text = 1;
}
//---------------------------------------------------------------------------

