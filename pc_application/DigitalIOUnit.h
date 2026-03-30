//---------------------------------------------------------------------------

#ifndef DigitalIOUnitH
#define DigitalIOUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TDigitalIOForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TComboBox *ExOutBox1;
	TComboBox *ExOutBox2;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label12;
	TLabel *Label2;
	TBevel *Bevel1;
	TAction *SetupForm;
	TAction *SaveForm;
	TButton *DefaultButton;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveFormExecute(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DefaultButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDigitalIOForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDigitalIOForm *DigitalIOForm;
//---------------------------------------------------------------------------
#endif
