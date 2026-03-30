//---------------------------------------------------------------------------

#ifndef ThresholdGroupEditFormH
#define ThresholdGroupEditFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TThresholdGroupEditorForm : public TForm
{
__published:	// IDE-managed Components
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
	TEdit *PT1DefaultEdit;
	TComboBox *PT1SourceList;
	TComboBox *PT1LevelList;
	TComboBox *PT1EnableList;
	TEdit *NT1DefaultEdit;
	TComboBox *NT1LevelList;
	TComboBox *NT1EnableList;
	TBevel *Bevel1;
	TButton *OKButton;
	TButton *CancelButton;
	TActionList *ActionList1;
	TAction *SetupForm;
	TAction *SaveAndExit;
	TAction *CancelAndExit;
	TStaticText *StaticText1;
	TLabel *Label1;
	TButton *Button1;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveAndExitExecute(TObject *Sender);
	void __fastcall OKButtonClick(TObject *Sender);
	void __fastcall CancelButtonClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TThresholdGroupEditorForm(TComponent* Owner);

    int ThresholdGroupToEdit;
    int VariableOffset, GroupToEditMinus1;
};
//---------------------------------------------------------------------------
extern PACKAGE TThresholdGroupEditorForm *ThresholdGroupEditorForm;
//---------------------------------------------------------------------------
#endif
