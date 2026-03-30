//---------------------------------------------------------------------------

#ifndef configunitH
#define configunitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Mask.hpp>

//---------------------------------------------------------------------------
class TConfigureForm : public TForm
{
__published:	// IDE-managed Components
        TButton *OKButton;
        TLabel *Label1;
        TLabel *Label2;
        TBevel *Bevel1;
        TComboBox *BaudSelectorBox;
        TComboBox *CommPortSelectorBox;
        TActionList *ActionList1;
        TAction *ChangeCOMMPort;
        TAction *ChangeBAUDRate;
        TMemo *Memo1;
        TMaskEdit *RobotScaleEdit;
        TLabel *Label3;
        TStaticText *StaticText1;
        void __fastcall ChangeBAUDRateExecute(TObject *Sender);
        void __fastcall ChangeCOMMPortExecute(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TConfigureForm(TComponent* Owner);
        void PrintMessage(AnsiString Line);
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigureForm *ConfigureForm;
//---------------------------------------------------------------------------
#endif
