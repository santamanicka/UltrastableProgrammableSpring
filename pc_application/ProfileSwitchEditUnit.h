//---------------------------------------------------------------------------

#ifndef ProfileSwitchEditUnitH
#define ProfileSwitchEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TProfileSwitchEditForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label49;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label52;
	TLabel *Label53;
	TLabel *Label56;
	TLabel *Label59;
	TLabel *Label68;
	TLabel *Label62;
	TLabel *Label63;
	TComboBox *AltproTriggerlist1;
	TComboBox *AltProTargetlist1;
	TComboBox *AltProTargetlist2;
	TComboBox *AltproTriggerlist2;
	TComboBox *AltProTargetlist3;
	TComboBox *AltproTriggerlist3;
	TComboBox *AltProTargetlist4;
	TComboBox *AltproTriggerlist4;
	TLabel *Label3;
	TLabel *Label4;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TLabel *Label5;
	TLabel *Label6;
	TBevel *Bevel4;
	TBevel *Bevel5;
	TLabel *Label7;
	TLabel *Label9;
	TLabel *Label8;
	TLabel *Label10;
	TBevel *Bevel3;
	TBevel *Bevel6;
	TLabel *Label12;
	TLabel *Label13;
	TButton *Button1;
	TButton *Button2;
	TActionList *ActionList1;
	TAction *SetupForm;
	TAction *SaveAndClose;
	TLabel *Label11;
	TLabel *Label14;
	TComboBox *IncrimentTriggerBox;
	TComboBox *DeincrimentTriggerBox;
	TLabel *Label15;
	TLabel *Label16;
	TButton *Button3;
	TAction *TriggerListWarning;
	TStaticText *StaticText1;
	TBevel *Bevel7;
	TStaticText *StaticText2;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveAndCloseExecute(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall TriggerListWarningExecute(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TProfileSwitchEditForm(TComponent* Owner);

    int CurrentProfile;

    TStringList* TempVarList;
    int VariableListOffset;
};
//---------------------------------------------------------------------------
extern PACKAGE TProfileSwitchEditForm *ProfileSwitchEditForm;
//---------------------------------------------------------------------------
#endif
