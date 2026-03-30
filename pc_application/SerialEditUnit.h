//---------------------------------------------------------------------------

#ifndef SerialEditUnitH
#define SerialEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSerialEditForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TComboBox *VarOutBoxA1;
	TComboBox *VarOutBoxA2;
	TComboBox *VarOutBoxA3;
	TComboBox *VarOutBoxA4;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TComboBox *VarOutBoxB1;
	TComboBox *VarOutBoxB2;
	TComboBox *VarOutBoxB3;
	TComboBox *VarOutBoxB4;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TComboBox *TrigOutBoxA1;
	TComboBox *TrigOutBoxA2;
	TComboBox *TrigOutBoxA3;
	TComboBox *TrigOutBoxA4;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TComboBox *TrigOutBoxB1;
	TComboBox *TrigOutBoxB2;
	TComboBox *TrigOutBoxB3;
	TComboBox *TrigOutBoxB4;
	TButton *Button3;
	TAction *SetupForm;
	TAction *SaveForm;
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SaveFormExecute(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSerialEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSerialEditForm *SerialEditForm;
//---------------------------------------------------------------------------
#endif
