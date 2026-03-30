//---------------------------------------------------------------------------

#ifndef OscillatorEditUnitH
#define OscillatorEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TOscillatorEditForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *Button2;
	TButton *Button1;
	TButton *Button3;
	TActionList *ActionList1;
	TAction *SetupForm;
	TAction *SaveAndClose;
	TAction *TriggerListWarning;
	TEdit *StepEdit;
	TEdit *PrescaleEdit;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *MaxEdit;
	TLabel *Label5;
	TEdit *MinEdit;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveAndCloseExecute(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TOscillatorEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOscillatorEditForm *OscillatorEditForm;
//---------------------------------------------------------------------------
#endif
