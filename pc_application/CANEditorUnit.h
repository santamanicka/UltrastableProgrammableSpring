//---------------------------------------------------------------------------

#ifndef CANEditorUnitH
#define CANEditorUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TCANEditForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TComboBox *ComboBox1;
	TComboBox *ComboBox2;
	TComboBox *ComboBox3;
	TComboBox *ComboBox4;
	TButton *Button1;
	TButton *Button2;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label4;
	TLabel *Label5;
	TComboBox *ComboBox5;
	TComboBox *ComboBox6;
	TComboBox *ComboBox7;
	TComboBox *ComboBox8;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label12;
	TLabel *Label10;
	TBevel *Bevel1;
	TBevel *Bevel2;
    TAction *SetupForm;
    void __fastcall SetupFormExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCANEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCANEditForm *CANEditForm;
//---------------------------------------------------------------------------
#endif
