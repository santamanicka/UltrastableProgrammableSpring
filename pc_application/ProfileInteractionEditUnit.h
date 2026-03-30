//---------------------------------------------------------------------------

#ifndef ProfileInteractionEditUnitH
#define ProfileInteractionEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TProfileInteractionEditForm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TButton *Button2;
	TActionList *ActionList1;
	TAction *SetupProfileSwitchTab;
	TAction *SaveAndClose;
	TButton *Button3;
	TAction *TriggerListWarning;
	TPageControl *PageControl1;
	TTabSheet *ProfileSwitchingTab;
	TTabSheet *InterProfileCommTab;
	TBevel *Bevel3;
	TBevel *Bevel5;
	TBevel *Bevel4;
	TBevel *Bevel2;
	TBevel *Bevel1;
	TLabel *SwitcherTitle;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label52;
	TLabel *Label53;
	TLabel *Label56;
	TLabel *Label59;
	TLabel *Label68;
	TLabel *Label62;
	TLabel *Label63;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label9;
	TLabel *Label8;
	TLabel *Label10;
	TBevel *Bevel6;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label11;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TBevel *Bevel7;
	TComboBox *AltproTriggerlist1;
	TComboBox *AltProTargetlist1;
	TComboBox *AltProTargetlist2;
	TComboBox *AltproTriggerlist2;
	TComboBox *AltProTargetlist3;
	TComboBox *AltproTriggerlist3;
	TComboBox *AltProTargetlist4;
	TComboBox *AltproTriggerlist4;
	TComboBox *IncrimentTriggerBox;
	TComboBox *DeincrimentTriggerBox;
	TAction *SetupInterProfileCommTab;
	TAction *SaveProfileSwitchTab;
	TAction *SaveInterProfileCommTab;
	TAction *CancelAndClose;
	TAction *SetDefaults;
	TAction *SetSwitcherDefaults;
	TAction *SetInterCommDefaults;
	TLabel *CommTitle;
	TComboBox *VariableSourceBox1;
	TLabel *Label17;
	TLabel *Label18;
	TComboBox *VariableSourceBox2;
	TComboBox *FlagSourceBox2;
	TComboBox *FlagSourceBox1;
	TLabel *Label19;
	TLabel *Label20;
	TBevel *Bevel9;
	TLabel *Label21;
	TBevel *Bevel10;
	TLabel *Label22;
	TLabel *Label23;
	TBevel *Bevel8;
	TLabel *Label24;
	TLabel *WarningLabel;
	TLabel *WarningLabel2;
	void __fastcall SetupProfileSwitchTabExecute(TObject *Sender);
	void __fastcall SaveAndCloseExecute(TObject *Sender);
	void __fastcall TriggerListWarningExecute(TObject *Sender);
	void __fastcall SetupInterProfileCommTabExecute(TObject *Sender);
	void __fastcall SaveProfileSwitchTabExecute(TObject *Sender);
	void __fastcall SaveInterProfileCommTabExecute(TObject *Sender);
	void __fastcall CancelAndCloseExecute(TObject *Sender);
	void __fastcall SetDefaultsExecute(TObject *Sender);
	void __fastcall SetSwitcherDefaultsExecute(TObject *Sender);
	void __fastcall SetInterCommDefaultsExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TProfileInteractionEditForm(TComponent* Owner);

    int CurrentProfile;

    TStringList* TempVarList;
    int VariableListOffset;
    int OwnComVariableIndex1;
    int OwnComVariableIndex2;
    int OwnComFlagIndex1;
    int OwnComFlagIndex2;
};
//---------------------------------------------------------------------------
extern PACKAGE TProfileInteractionEditForm *ProfileInteractionEditForm;
//---------------------------------------------------------------------------
#endif
