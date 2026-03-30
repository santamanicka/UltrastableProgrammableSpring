//---------------------------------------------------------------------------

#ifndef ThresholdGroupSettingsUnitH
#define ThresholdGroupSettingsUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TThresholdGroupSettingsForm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *ThresholdGroup1;
	TTabSheet *ThresholdGroup2;
	TTabSheet *ThresholdGroup3;
	TTabSheet *ThresholdGroup4;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TLabel *Label10;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label13;
	TLabel *Label20;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Tab1Title;
	TEdit *PT1DefaultEdit1;
	TComboBox *PT1SourceList1;
	TComboBox *PT1LevelList1;
	TComboBox *PT1EnableList1;
	TEdit *NT1DefaultEdit1;
	TComboBox *NT1LevelList1;
	TComboBox *NT1EnableList1;
	TActionList *ActionList;
	TAction *SetupForm;
	TAction *SaveAndExit;
	TAction *CancelAndExit;
	TButton *OKButton;
	TButton *CancelButton;
	TButton *SetDefaultButton;
	TAction *ChangeTab;
	TLabel *Tab2Title;
	TLabel *Label3;
	TComboBox *PT1SourceList2;
	TLabel *Label4;
	TBevel *Bevel3;
	TComboBox *PT1LevelList2;
	TLabel *Label5;
	TLabel *Label6;
	TComboBox *PT1EnableList2;
	TEdit *PT1DefaultEdit2;
	TLabel *Label7;
	TBevel *Bevel4;
	TLabel *Label8;
	TLabel *Label9;
	TComboBox *NT1LevelList2;
	TComboBox *NT1EnableList2;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *NT1DefaultEdit2;
	TLabel *Tab3Title;
	TLabel *Label17;
	TComboBox *PT1SourceList3;
	TLabel *Label18;
	TBevel *Bevel5;
	TComboBox *PT1LevelList3;
	TLabel *Label19;
	TLabel *Label21;
	TComboBox *PT1EnableList3;
	TEdit *PT1DefaultEdit3;
	TLabel *Label26;
	TBevel *Bevel6;
	TLabel *Label27;
	TLabel *Label28;
	TComboBox *NT1LevelList3;
	TComboBox *NT1EnableList3;
	TLabel *Label29;
	TLabel *Label30;
	TEdit *NT1DefaultEdit3;
	TLabel *Tab4Title;
	TLabel *Label32;
	TComboBox *PT1SourceList4;
	TLabel *Label33;
	TBevel *Bevel7;
	TComboBox *PT1LevelList4;
	TLabel *Label34;
	TLabel *Label35;
	TComboBox *PT1EnableList4;
	TEdit *PT1DefaultEdit4;
	TLabel *Label36;
	TBevel *Bevel8;
	TLabel *Label37;
	TLabel *Label38;
	TComboBox *NT1LevelList4;
	TComboBox *NT1EnableList4;
	TLabel *Label39;
	TLabel *Label40;
	TEdit *NT1DefaultEdit4;
	TAction *SetupTab1;
	TAction *SetupTab2;
	TAction *SetupTab3;
	TAction *SetupTab4;
	TAction *SetDefaults;
	TAction *DefaultTab1;
	TAction *DefaultTab2;
	TAction *DefaultTab3;
	TAction *DefaultTab4;
	TAction *SaveTab1;
	TAction *SaveTab2;
	TAction *SaveTab3;
	TAction *SaveTab4;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveAndExitExecute(TObject *Sender);
	void __fastcall CancelAndExitExecute(TObject *Sender);
	void __fastcall SetupTab1Execute(TObject *Sender);
	void __fastcall SetupTab2Execute(TObject *Sender);
	void __fastcall SetupTab3Execute(TObject *Sender);
	void __fastcall SetupTab4Execute(TObject *Sender);
	void __fastcall SetDefaultsExecute(TObject *Sender);
	void __fastcall DefaultTab1Execute(TObject *Sender);
	void __fastcall DefaultTab2Execute(TObject *Sender);
	void __fastcall DefaultTab3Execute(TObject *Sender);
	void __fastcall DefaultTab4Execute(TObject *Sender);
	void __fastcall SaveTab1Execute(TObject *Sender);
	void __fastcall SaveTab2Execute(TObject *Sender);
	void __fastcall SaveTab3Execute(TObject *Sender);
	void __fastcall SaveTab4Execute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TThresholdGroupSettingsForm(TComponent* Owner);


};
//---------------------------------------------------------------------------
extern PACKAGE TThresholdGroupSettingsForm *ThresholdGroupSettingsForm;
//---------------------------------------------------------------------------
#endif
