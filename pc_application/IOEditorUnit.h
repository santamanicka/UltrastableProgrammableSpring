//---------------------------------------------------------------------------

#ifndef IOEditorUnitH
#define IOEditorUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TInputOutputForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *RS232Tab;
	TTabSheet *CANBUSTab;
	TTabSheet *DiscreteIOTab;
	TActionList *ActionList1;
	TBevel *Bevel2;
	TLabel *SerialTabTitle;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TComboBox *VarOutBoxA1;
	TComboBox *VarOutBoxA2;
	TComboBox *VarOutBoxA3;
	TComboBox *VarOutBoxA4;
	TComboBox *VarOutBoxB1;
	TComboBox *VarOutBoxB2;
	TComboBox *VarOutBoxB3;
	TComboBox *VarOutBoxB4;
	TComboBox *TrigOutBoxA1;
	TComboBox *TrigOutBoxA2;
	TComboBox *TrigOutBoxA3;
	TComboBox *TrigOutBoxA4;
	TComboBox *TrigOutBoxB1;
	TComboBox *TrigOutBoxB2;
	TComboBox *TrigOutBoxB3;
	TComboBox *TrigOutBoxB4;
	TButton *Button3;
	TButton *Button1;
	TButton *Button2;
	TBevel *Bevel4;
	TLabel *CanTabTitle;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TComboBox *CANVarOutBoxA1;
	TComboBox *CANVarOutBoxA2;
	TComboBox *CANTrigOutBoxA1;
	TComboBox *CANTrigOutBoxA2;
	TComboBox *CANVarOutBoxB1;
	TComboBox *CANVarOutBoxB2;
	TComboBox *CANTrigOutBoxB1;
	TComboBox *CANTrigOutBoxB2;
	TBevel *Bevel5;
	TLabel *DiscreteTabTitle1;
	TLabel *Label32;
	TLabel *Label33;
	TComboBox *ExOutBox1;
	TComboBox *ExOutBox2;
	TLabel *DiscreteTabTitle2;
	TLabel *Label35;
	TLabel *Label36;
	TLabel *Label37;
	TLabel *Label38;
	TComboBox *AnOutBox1;
	TComboBox *AnOutBox2;
	TEdit *GainEdit1;
	TEdit *GainEdit2;
	TBevel *Bevel6;
	TAction *SetupSerialTab;
	TAction *SetupCANTab;
	TAction *SetupDiscreteTab;
	TAction *DefaultSerialTab;
	TAction *DefaultCANTab;
	TAction *DefaultDiscreteTab;
	TAction *SetDefaults;
	TAction *SaveSerialTab;
	TAction *SaveCANTab;
	TAction *SaveDiscreteTab;
	TAction *SaveAndClose;
	TAction *CancelAndClose;
	TComboBox *AutoTXTriggerB;
	TLabel *Label39;
	TBevel *Bevel7;
	TComboBox *AutoTXTriggerA;
	TLabel *Label40;
	TLabel *Label41;
	TComboBox *CANAutoTxTriggerB;
	TBevel *Bevel1;
	TLabel *Label42;
	TComboBox *CANAutoTxTriggerA;
	TLabel *Label1;
	TLabel *Label20;
	TLabel *Label31;
	TLabel *Label34;
	TComboBox *TargetNodeBoxA;
	TComboBox *TargetNodeBoxB;
	TLabel *Label8;
	TLabel *Label9;
	TComboBox *TxDelayBoxB;
	TComboBox *TxDelayBoxA;
	TLabel *Label43;
	TLabel *Label44;
	TComboBox *CANTargetNodeBoxA;
	TComboBox *CANTxDelayBoxA;
	TLabel *Label45;
	TLabel *Label46;
	TLabel *Label47;
	TComboBox *CANTargetNodeBoxB;
	TLabel *Label48;
	TComboBox *CANTxDelayBoxB;
	TCheckBox *GetReplyBoxA;
	TCheckBox *GetReplyBoxB;
	TCheckBox *CopySettingsToAllBox;
    TComboBox *SerialPortBoxB;
    TLabel *Label6;
    TLabel *Label7;
    TComboBox *SerialPortBoxA;
	void __fastcall SetupSerialTabExecute(TObject *Sender);
	void __fastcall SetupCANTabExecute(TObject *Sender);
	void __fastcall SetupDiscreteTabExecute(TObject *Sender);
	void __fastcall DefaultSerialTabExecute(TObject *Sender);
	void __fastcall DefaultCANTabExecute(TObject *Sender);
	void __fastcall DefaultDiscreteTabExecute(TObject *Sender);
	void __fastcall SetDefaultsExecute(TObject *Sender);
	void __fastcall SaveSerialTabExecute(TObject *Sender);
	void __fastcall SaveCANTabExecute(TObject *Sender);
	void __fastcall SaveDiscreteTabExecute(TObject *Sender);
	void __fastcall SaveAndCloseExecute(TObject *Sender);
	void __fastcall CancelAndCloseExecute(TObject *Sender);
	void __fastcall CANAutoTxTriggerAChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TInputOutputForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInputOutputForm *InputOutputForm;
//---------------------------------------------------------------------------
#endif
