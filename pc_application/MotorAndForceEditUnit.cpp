//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MotorAndForceEditUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMotorEnableForm *MotorEnableForm;
//---------------------------------------------------------------------------
__fastcall TMotorEnableForm::TMotorEnableForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TMotorEnableForm::SetupFormExecute(TObject *Sender)
{
	//
    AnsiString TitleCaption;
    TitleCaption = "Motor and Force Enable for Profile Group ";
    TitleCaption += ProfileEditForm->CurrentEditingProfile;
    Title->Caption = TitleCaption;

    MotorEnableBox->Items = ProfileEditForm->VariableList8;
    MotorEnableBox->ItemIndex = ProfileEditForm->TempI8Ptr[_MotorEnable_ptr];

    ForceEnableBox->Items = ProfileEditForm->VariableList8;
    ForceEnableBox->ItemIndex = ProfileEditForm->TempI8Ptr[_ForceControlEnable_ptr];
}
//---------------------------------------------------------------------------

void __fastcall TMotorEnableForm::SaveFormExecute(TObject *Sender)
{
	//
    ProfileEditForm->TempI8Ptr[_MotorEnable_ptr] = MotorEnableBox->ItemIndex;
    ProfileEditForm->TempI8Ptr[_ForceControlEnable_ptr] = ForceEnableBox->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TMotorEnableForm::SaveAndExitExecute(TObject *Sender)
{
	//
    SaveForm->Execute();
    MotorEnableForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMotorEnableForm::CancelAndExitExecute(TObject *Sender)
{
	//
    MotorEnableForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMotorEnableForm::SetDefaultsExecute(TObject *Sender)
{
	//
    MotorEnableBox->ItemIndex = _GlobalDefaultTrue;

    ForceEnableBox->ItemIndex = _GlobalDefaultTrue;
}
//---------------------------------------------------------------------------

