//---------------------------------------------------------------------------

#ifndef ProfileGeneratorUnitH
#define ProfileGeneratorUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TProfileGeneratorForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TAction *SetupForm;
	TAction *GenerateSin;
	TLabeledEdit *SineFreqEdit;
	TLabeledEdit *SinHeightEdit;
	TLabeledEdit *SinStartEdit;
	TAction *UpdateMainImage;
	TButton *StartLeft1;
	TButton *StartLeft10;
	TButton *StartRight10;
	TButton *StartRight1;
	TAction *RegenerateFunction;
	TButton *CancelButton;
	TAction *CancelAndClose;
	TEdit *VBiasEdit;
	TLabel *Label1;
	TButton *VBisUp;
	TButton *VBiasDown;
	TRadioButton *SinButton;
	TAction *GenerateTanh;
	TRadioButton *TanhButton;
	TCheckBox *FlipHorizontalBox;
	TCheckBox *HorizontalMirrorMode;
	TAction *GenerateExponential;
	TRadioButton *ExponentialButton;
	TEdit *DeadBandEdit;
	TAction *TanhClick;
	TButton *VBiasUp16Button;
	TButton *VBiasDown16Button;
	TAction *SinClick;
	TButton *FreqUpButton;
	TButton *FreqDownButton;
	TButton *FreqUp1Button;
	TButton *FreqDown1Button;
	TLabel *Label2;
	TButton *HeightUp16Button;
	TButton *HeightUp1Button;
	TButton *HeightDown1Button;
	TButton *HeightDown16Button;
	TButton *OKButton;
	TAction *SaveAndClose;
	TBevel *Bevel1;
	TBevel *Bevel2;
	TBevel *Bevel3;
	TBevel *Bevel4;
	TBevel *Bevel5;
	TBevel *Bevel6;
	TLabel *Label3;
	TCheckBox *ApplyToNDampBox;
	TCheckBox *ApplyToPDampBox;
	TCheckBox *ApplyToForceBox;
	TBevel *Bevel7;
	TBevel *Bevel8;
	TBevel *Bevel9;
	void __fastcall SaveAndCloseExecute(TObject *Sender);
	void __fastcall UpdateMainImageExecute(TObject *Sender);
	void __fastcall StartLeft10Click(TObject *Sender);
	void __fastcall StartLeft1Click(TObject *Sender);
	void __fastcall StartRight1Click(TObject *Sender);
	void __fastcall StartRight10Click(TObject *Sender);
	void __fastcall RegenerateFunctionExecute(TObject *Sender);
	void __fastcall SetupFormExecute(TObject *Sender);
	void __fastcall SinStartEditExit(TObject *Sender);
	void __fastcall SineFreqEditExit(TObject *Sender);
	void __fastcall SinHeightEditExit(TObject *Sender);
	void __fastcall CancelAndCloseExecute(TObject *Sender);
	void __fastcall VBiasEditExit(TObject *Sender);
	void __fastcall VBisUpClick(TObject *Sender);
	void __fastcall VBiasDownClick(TObject *Sender);
    void __fastcall GenerateSinExecute(TObject *Sender);
	void __fastcall GenerateTanhExecute(TObject *Sender);
	void __fastcall GenerateExponentialExecute(TObject *Sender);
	void __fastcall TanhClickExecute(TObject *Sender);
	void __fastcall VBiasUp16ButtonClick(TObject *Sender);
	void __fastcall VBiasDown16ButtonClick(TObject *Sender);
	void __fastcall SinClickExecute(TObject *Sender);
	void __fastcall FreqDown1ButtonClick(TObject *Sender);
	void __fastcall FreqDownButtonClick(TObject *Sender);
	void __fastcall FreqUpButtonClick(TObject *Sender);
	void __fastcall FreqUp1ButtonClick(TObject *Sender);
	void __fastcall HeightUp16ButtonClick(TObject *Sender);
	void __fastcall HeightUp1ButtonClick(TObject *Sender);
	void __fastcall HeightDown1ButtonClick(TObject *Sender);
	void __fastcall HeightDown16ButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TProfileGeneratorForm(TComponent* Owner);

    int ForceProfile[64];
    int PDampProfile[64];
    int NDampProfile[64];
    int OLDForceProfile[64];
    int OLDPDampProfile[64];
    int OLDNDampProfile[64];

    double ExpandedProfile[1024];
    double SinFreq;
    double SinHeight;
    double Start;
    double SinVBias;
    double SinHBias;
    int SinDB;

    double TanhFreq, TanhHeight, TanhHBias, TanhVBias;
    int TanDB;
};
//---------------------------------------------------------------------------
extern PACKAGE TProfileGeneratorForm *ProfileGeneratorForm;
//---------------------------------------------------------------------------
#endif
