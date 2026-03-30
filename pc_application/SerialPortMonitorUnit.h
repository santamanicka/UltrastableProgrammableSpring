//---------------------------------------------------------------------------

#ifndef SerialPortMonitorUnitH
#define SerialPortMonitorUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TSerialPortMonitorForm : public TForm
{
__published:	// IDE-managed Components
	TMemo *RawListMemo;
	TLabel *Label10;
	TMemo *COMMMemo;
	TLabel *Label1;
	TActionList *ActionList1;
	TAction *CloseForm;
	TCheckBox *PrintRawDataBox;
	TButton *ClearButton;
	TAction *UpdateMemo;
    TCheckBox *ShowHiddenCharsBox;
	void __fastcall ClearButtonClick(TObject *Sender);
	void __fastcall UpdateMemoExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations


	__fastcall TSerialPortMonitorForm(TComponent* Owner);
    void PrintCommData(int ByteValue, int flag);

    AnsiString MessageLine;
    int CurrentLine;
    int LineLength;
};
//---------------------------------------------------------------------------
extern PACKAGE TSerialPortMonitorForm *SerialPortMonitorForm;
//---------------------------------------------------------------------------
#endif
