//---------------------------------------------------------------------------

#ifndef ScaleAndBiasUnitH
#define ScaleAndBiasUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TScaleAndBiasForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TButton *Button1;
	TComboBox *HScaleSourceBox;
	TEdit *HScaleEdit;
	TLabel *Label2;
	TLabel *Label3;
	TBevel *Bevel1;
	TLabel *Label1;
	TLabel *Label4;
	TComboBox *VScaleSourceBox;
	TEdit *VScaleEdit;
	TLabel *Label5;
	TLabel *Label6;
	TBevel *Bevel2;
	TLabel *Label7;
	TComboBox *HBiasSourceBox;
	TEdit *HBiasEdit;
	TLabel *Label8;
	TLabel *Label9;
	TBevel *Bevel3;
	TLabel *Label10;
	TComboBox *VBiasSourceBox;
	TEdit *VBiasEdit;
	TLabel *Label11;
	TLabel *Label12;
	TBevel *Bevel4;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TBevel *Bevel5;
	TAction *SetupForm;
	TEdit *EQEdit;
	TAction *SaveAndClose;
	TButton *Button2;
	TButton *SetDefaultsButton;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveAndCloseExecute(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall SetDefaultsButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TScaleAndBiasForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TScaleAndBiasForm *ScaleAndBiasForm;
//---------------------------------------------------------------------------
#endif
