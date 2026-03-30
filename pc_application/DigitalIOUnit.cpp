//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DigitalIOUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDigitalIOForm *DigitalIOForm;
//---------------------------------------------------------------------------
__fastcall TDigitalIOForm::TDigitalIOForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TDigitalIOForm::SetupFormExecute(TObject *Sender)
{
	//
    AnsiString Title;
    Title = "Digital I/O for Profile No ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Label1->Caption = Title;

    ExOutBox1->Items = ProfileEditForm->VariableList8;
    ExOutBox1->ItemIndex = ProfileEditForm->TempI8Ptr[_ExOut1_ptr];

    ExOutBox2->Items = ProfileEditForm->VariableList8;
    ExOutBox2->ItemIndex = ProfileEditForm->TempI8Ptr[_ExOut2_ptr];
}
//---------------------------------------------------------------------------
void __fastcall TDigitalIOForm::SaveFormExecute(TObject *Sender)
{
    ProfileEditForm->TempI8Ptr[_ExOut1_ptr] = ExOutBox1->ItemIndex;

    ProfileEditForm->TempI8Ptr[_ExOut2_ptr] = ExOutBox2->ItemIndex;
    //DigitalIOForm->Close();
    
}
//---------------------------------------------------------------------------

void __fastcall TDigitalIOForm::Button2Click(TObject *Sender)
{
    DigitalIOForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TDigitalIOForm::Button1Click(TObject *Sender)
{
     SaveForm->Execute();
     DigitalIOForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TDigitalIOForm::DefaultButtonClick(TObject *Sender)
{
	//Set Defaults
    ExOutBox1->ItemIndex = _GlobalDefaultFalse;

   	ExOutBox2->ItemIndex = _GlobalDefaultFalse;
}
//---------------------------------------------------------------------------

