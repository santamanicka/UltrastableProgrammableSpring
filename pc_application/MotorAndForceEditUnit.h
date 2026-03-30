//---------------------------------------------------------------------------

#ifndef MotorAndForceEditUnitH
#define MotorAndForceEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMotorEnableForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Title;
	TLabel *Label2;
	TComboBox *MotorEnableBox;
	TButton *DefaultButton;
	TButton *Button1;
	TButton *Button2;
	TActionList *ActionList1;
	TAction *SetupForm;
	TAction *SaveForm;
	TLabel *Label3;
	TComboBox *ForceEnableBox;
	TLabel *Label4;
	TLabel *Label5;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TAction *SaveAndExit;
	TAction *CancelAndExit;
	TAction *SetDefaults;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveFormExecute(TObject *Sender);
	void __fastcall SaveAndExitExecute(TObject *Sender);
	void __fastcall CancelAndExitExecute(TObject *Sender);
	void __fastcall SetDefaultsExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMotorEnableForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMotorEnableForm *MotorEnableForm;
//---------------------------------------------------------------------------
#endif
