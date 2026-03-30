//---------------------------------------------------------------------------

#ifndef GroupTriggerUnitH
#define GroupTriggerUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TGroupTriggerForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TComboBox *SourceBox1;
	TComboBox *SourceBox2;
	TComboBox *SourceBox3;
	TComboBox *SourceBox4;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TButton *DefaultButton;
	TAction *SetupForm;
	TAction *SaveForm;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveFormExecute(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall DefaultButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TGroupTriggerForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGroupTriggerForm *GroupTriggerForm;
//---------------------------------------------------------------------------
#endif
