//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CANEditorUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCANEditForm *CANEditForm;
//---------------------------------------------------------------------------
__fastcall TCANEditForm::TCANEditForm(TComponent* Owner)
	: TForm(Owner)
{
    SetupForm->Execute();

}
//---------------------------------------------------------------------------
void __fastcall TCANEditForm::SetupFormExecute(TObject *Sender)
{
    AnsiString Title = "CAN Bus I/O for Profile No ";
    Title += ProfileEditForm->CurrentEditingProfile;
    Label1->Caption = Title;
}
//---------------------------------------------------------------------------

