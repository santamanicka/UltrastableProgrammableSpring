//---------------------------------------------------------------------------

#ifndef DownloadProgressUnitH
#define DownloadProgressUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TDownloadProgressForm : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *ProgressBar1;
	TLabel *Label1;
	TActionList *ActionList1;
	TAction *ClearLabels;
	void __fastcall ClearLabelsExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDownloadProgressForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDownloadProgressForm *DownloadProgressForm;
//---------------------------------------------------------------------------
#endif
