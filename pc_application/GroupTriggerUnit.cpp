//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GroupTriggerUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGroupTriggerForm *GroupTriggerForm;
//---------------------------------------------------------------------------
__fastcall TGroupTriggerForm::TGroupTriggerForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TGroupTriggerForm::SetupFormExecute(TObject *Sender)
{
	//
    AnsiString Title;
    Title = "Group Triggers for Profile Group ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Label1->Caption = Title;

    SourceBox1->Items = ProfileEditForm->VariableList8;
    SourceBox1->ItemIndex = ProfileEditForm->TempI8Ptr[_SummedFlag1_ptr];

    SourceBox2->Items = ProfileEditForm->VariableList8;
    SourceBox2->ItemIndex = ProfileEditForm->TempI8Ptr[_SummedFlag2_ptr];

    SourceBox3->Items = ProfileEditForm->VariableList8;
    SourceBox3->ItemIndex = ProfileEditForm->TempI8Ptr[_SummedFlag3_ptr];

    SourceBox4->Items = ProfileEditForm->VariableList8;
    SourceBox4->ItemIndex = ProfileEditForm->TempI8Ptr[_SummedFlag4_ptr];

    
}
//---------------------------------------------------------------------------

void __fastcall TGroupTriggerForm::SaveFormExecute(TObject *Sender)
{
	//
    ProfileEditForm->TempI8Ptr[_SummedFlag1_ptr] = SourceBox1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_SummedFlag2_ptr] = SourceBox2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_SummedFlag3_ptr] = SourceBox3->ItemIndex;
    ProfileEditForm->TempI8Ptr[_SummedFlag4_ptr] = SourceBox4->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TGroupTriggerForm::Button2Click(TObject *Sender)
{
	//Cancel
    GroupTriggerForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TGroupTriggerForm::Button1Click(TObject *Sender)
{
	//Save
    SaveForm->Execute();
    GroupTriggerForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TGroupTriggerForm::DefaultButtonClick(TObject *Sender)
{
	//Defaults

    SourceBox1->ItemIndex = _GlobalDefaultFalse;
    SourceBox2->ItemIndex = _GlobalDefaultFalse;
    SourceBox3->ItemIndex = _GlobalDefaultFalse;
    SourceBox4->ItemIndex = _GlobalDefaultFalse;
}
//---------------------------------------------------------------------------

