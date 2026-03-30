//---------------------------------------------------------------------------

#ifndef ActuatorCommandUnitH
#define ActuatorCommandUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TCommandForm : public TForm
{
__published:	// IDE-managed Components
	TTrackBar *VarBar1;
	TBevel *Bevel1;
	TButton *ZeroButton1;
	TLabel *ValueText1;
	TTrackBar *VarBar2;
	TBevel *Bevel2;
	TButton *ZeroButton2;
	TLabel *ValueText2;
	TTrackBar *VarBar3;
	TBevel *Bevel3;
	TButton *ZeroButton3;
	TLabel *ValueText3;
	TTrackBar *VarBar4;
	TBevel *Bevel4;
	TButton *ZeroButton4;
	TLabel *ValueText4;
	TCheckBox *FlagBox1;
	TCheckBox *FlagBox2;
	TCheckBox *FlagBox3;
	TCheckBox *FlagBox4;
	TBevel *Bevel5;
	TActionList *ActionList1;
	TAction *SetupForm;
	TAction *Zero1;
	TAction *Zero2;
	TAction *Zero3;
	TAction *Zero4;
	TAction *ChangeVar1;
	TAction *ChangeVar2;
	TAction *ChangeVar3;
	TAction *ChangeVar4;
	TAction *ChangeFlag1;
	TAction *ChangeFlag2;
	TAction *ChangeFlag3;
	TAction *ChangeFlag4;
	TAction *TransmitCommands;
	TButton *SendButton;
	TRadioButton *AutoTXButton;
	TRadioButton *OnChangeTXButton;
	TRadioButton *ManualTXButton;
	TBevel *Bevel6;
	TTimer *Timer1;
	TEdit *TxRateEdit;
	TCheckBox *RequestReplyBox;
	TBevel *Bevel7;
	TButton *StartStopTxButton;
	TAction *StartStopAutoTx;
	TEdit *ScaleEdit1;
	TLabel *Label1;
	TEdit *ScaleEdit2;
	TLabel *Label2;
	TEdit *ScaleEdit3;
	TLabel *Label3;
	TEdit *ScaleEdit4;
	TLabel *Label4;
	TButton *ResetActuatorButton;
	TButton *HaltActuatorButton;
	TButton *StartActuatorButton;
	TButton *PrintProfileButton;
	TButton *SwitchProfileButton;
	TComboBox *SwitchProfileBox;
	TBevel *Bevel8;
	TStaticText *StaticText1;
    TComboBox *PacketTypeBox;
    TLabel *Label5;
    TBevel *Bevel9;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall Zero1Execute(TObject *Sender);
	void __fastcall Zero2Execute(TObject *Sender);
	void __fastcall Zero3Execute(TObject *Sender);
	void __fastcall Zero4Execute(TObject *Sender);
	void __fastcall ChangeVar1Execute(TObject *Sender);
	void __fastcall ChangeVar2Execute(TObject *Sender);
	void __fastcall ChangeVar3Execute(TObject *Sender);
	void __fastcall ChangeVar4Execute(TObject *Sender);
	void __fastcall ChangeFlag1Execute(TObject *Sender);
	void __fastcall ChangeFlag2Execute(TObject *Sender);
	void __fastcall ChangeFlag3Execute(TObject *Sender);
	void __fastcall ChangeFlag4Execute(TObject *Sender);
	void __fastcall TransmitCommandsExecute(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall StartStopAutoTxExecute(TObject *Sender);
	void __fastcall ResetActuatorButtonClick(TObject *Sender);
	void __fastcall HaltActuatorButtonClick(TObject *Sender);
	void __fastcall StartActuatorButtonClick(TObject *Sender);
	void __fastcall PrintProfileButtonClick(TObject *Sender);
	void __fastcall SwitchProfileButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCommandForm(TComponent* Owner);
    byte GetVarByte(int Var, int Offset);

    int Var1, Var2, Var3, Var4;
    byte Flag1, Flag2, Flag3, Flag4;


};
//---------------------------------------------------------------------------
extern PACKAGE TCommandForm *CommandForm;
//---------------------------------------------------------------------------
#endif
