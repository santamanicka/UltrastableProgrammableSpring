//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DownloadProgressUnit.h"
#include "bcb_pgm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDownloadProgressForm *DownloadProgressForm;
//---------------------------------------------------------------------------
__fastcall TDownloadProgressForm::TDownloadProgressForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDownloadProgressForm::ClearLabelsExecute(TObject *Sender)
{
	Label1->Caption = "";

}
//---------------------------------------------------------------------------
