//---------------------------------------------------------------------------

#ifndef ActuatorSettingsUnitH
#define ActuatorSettingsUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TActuatorSettingsForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TAction *SetupForm;
	TComboBox *StartProfileBox;
	TComboBox *StartModeBox;
	TComboBox *RS232NodeBox;
	TComboBox *CANBUSNodeBox;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TButton *OKButton;
	TButton *CancelButton;
	TButton *DefaultButton;
	TAction *SaveAndClose;
	TAction *CancelAndClose;
	TAction *SetDefaults;
    TCheckBox *PassAlongCommandsBox;
        TLabel *Label5;
        TEdit *DelayValueBox;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall CancelAndCloseExecute(TObject *Sender);
	void __fastcall SaveAndCloseExecute(TObject *Sender);
	void __fastcall SetDefaultsExecute(TObject *Sender);
    void __fastcall PassAlongCommandsBoxClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TActuatorSettingsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TActuatorSettingsForm *ActuatorSettingsForm;
//---------------------------------------------------------------------------
#endif
