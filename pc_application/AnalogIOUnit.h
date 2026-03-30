//---------------------------------------------------------------------------

#ifndef AnalogIOUnitH
#define AnalogIOUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TAnalogIOForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TComboBox *AnOutBox1;
	TComboBox *AnOutBox2;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *GainEdit1;
	TLabel *Label4;
	TEdit *GainEdit2;
	TLabel *Label5;
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
	__fastcall TAnalogIOForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAnalogIOForm *AnalogIOForm;
//---------------------------------------------------------------------------
#endif
