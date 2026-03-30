//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Bcb_pgm.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
#include "ThresholdGroupEditForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TThresholdGroupEditorForm *ThresholdGroupEditorForm;
//---------------------------------------------------------------------------
__fastcall TThresholdGroupEditorForm::TThresholdGroupEditorForm(TComponent* Owner)
	: TForm(Owner)
{

	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupEditorForm::SetupFormExecute(
      TObject *Sender)
{
	AnsiString Captions;
	ThresholdGroupToEdit = ProfileEditForm->ThresholdToEdit;
    GroupToEditMinus1 = ThresholdGroupToEdit-1;
    VariableOffset = (ThresholdGroupToEdit-1)*2;
    int TempInt;
    //Setup the combo boxes

    Captions = "Threshold Group ";
    Captions += ThresholdGroupToEdit;
    Label1->Caption = Captions;

    Captions = "Positive Threshold (PT) ";
    Captions += ThresholdGroupToEdit;
    Label10->Caption = Captions;

    Captions = "Negative Threshold (NT) ";
    Captions += ThresholdGroupToEdit;
    Label20->Caption = Captions;

    //Positive and Negative Threshold 1
    PT1SourceList->Items = ProfileEditForm->VariableList16;
    PT1SourceList->ItemIndex = ProfileEditForm->TempSI16Ptr[_Threshold1Input_ptr + GroupToEditMinus1];

    
    PT1LevelList->Items = ProfileEditForm->VariableList16;
    PT1LevelList->ItemIndex = ProfileEditForm->TempSI16Ptr[_PT1Value_ptr + VariableOffset];

    PT1EnableList->Items = ProfileEditForm->VariableList8;
    PT1EnableList->ItemIndex = ProfileEditForm->TempI8Ptr[_PT1Enabled_ptr + VariableOffset];




    NT1LevelList->Items = ProfileEditForm->VariableList16;
    NT1LevelList->ItemIndex = ProfileEditForm->TempSI16Ptr[_NT1Value_ptr + VariableOffset];

    NT1EnableList->Items = ProfileEditForm->VariableList8;
    NT1EnableList->ItemIndex = ProfileEditForm->TempI8Ptr[_NT1Enabled_ptr + VariableOffset];


    PT1DefaultEdit->Text = ProfileEditForm->TempSI16Var[_PT1Default+VariableOffset];
    NT1DefaultEdit->Text = ProfileEditForm->TempSI16Var[_NT1Default+VariableOffset];



}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupEditorForm::SaveAndExitExecute(
      TObject *Sender)
{


    ProfileEditForm->TempSI16Var[_NT1Default+VariableOffset] = NT1DefaultEdit->Text.ToIntDef(-513);
    ProfileEditForm->TempSI16Var[_PT1Default+VariableOffset] = PT1DefaultEdit->Text.ToIntDef(512);

    
	ProfileEditForm->TempSI16Ptr[_Threshold1Input_ptr + GroupToEditMinus1] = PT1SourceList->ItemIndex;
    ProfileEditForm->TempSI16Ptr[_PT1Value_ptr + VariableOffset] = PT1LevelList->ItemIndex;
    ProfileEditForm->TempI8Ptr[_PT1Enabled_ptr + VariableOffset] = PT1EnableList->ItemIndex;

    ProfileEditForm->TempSI16Ptr[_NT1Value_ptr + VariableOffset] = NT1LevelList->ItemIndex;
    ProfileEditForm->TempI8Ptr[_NT1Enabled_ptr + VariableOffset] = NT1EnableList->ItemIndex;

}
//---------------------------------------------------------------------------
void __fastcall TThresholdGroupEditorForm::OKButtonClick(TObject *Sender)
{
     SaveAndExit->Execute();
     ThresholdGroupEditorForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TThresholdGroupEditorForm::CancelButtonClick(
      TObject *Sender)
{
    ThresholdGroupEditorForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TThresholdGroupEditorForm::Button1Click(TObject *Sender)
{
	//Setup some defaults

    PT1SourceList->ItemIndex = _GlobalDefaultZeroModulator;

    PT1LevelList->ItemIndex = _PT1Default + VariableOffset;

    PT1EnableList->ItemIndex = _GlobalThresholdDisabled;

    PT1DefaultEdit->Text = 512;

    NT1LevelList->ItemIndex = _NT1Default + VariableOffset;

    NT1EnableList->ItemIndex = _GlobalThresholdDisabled;

    NT1DefaultEdit->Text = -513;
}
//---------------------------------------------------------------------------

