//---------------------------------------------------------------------------

#ifndef ModulatorsEditUnitH
#define ModulatorsEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TModulatorsEditForm : public TForm
{
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TButton *Button1;
	TAction *SetupScaleAndBiasTab;
	TAction *SaveAndClose;
	TButton *Button2;
	TButton *SetDefaultsButton;
	TPageControl *PageControl1;
	TTabSheet *ScaleAndBiasTab;
	TTabSheet *InternalOscillatorTab;
	TBevel *Bevel5;
	TBevel *Bevel4;
	TBevel *Bevel3;
	TBevel *Bevel2;
	TBevel *Bevel1;
	TLabel *Label2;
	TLabel *Label3;
    TLabel *ScaleAndBiasTitle;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TComboBox *HScaleSourceBox;
	TEdit *HScaleEdit;
	TComboBox *VScaleSourceBox;
	TEdit *VScaleEdit;
	TComboBox *HBiasSourceBox;
	TEdit *HBiasEdit;
	TComboBox *VBiasSourceBox;
	TEdit *VBiasEdit;
	TEdit *EQEdit;
	TAction *CancelAndClose;
	TAction *SetupOscillatorTab;
	TAction *SaveScaleAndBiasTab;
	TAction *SaveOscillatorTab;
	TAction *SetDefaults;
	TAction *SetDefaultScaleAndBiasTab;
	TAction *SetDefaultOscillatorTab;
	TLabel *OscillatorTitle;
	TEdit *StepEdit;
	TLabel *Label15;
	TLabel *Label16;
	TEdit *PrescaleEdit;
	TEdit *MaxEdit;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *MinEdit;
	TEdit *VerticalReferenceEdit;
	TLabel *Label1;
	TBevel *Bevel6;
    TTabSheet *RandomiserTab;
    TAction *SetupRandomisersTab;
    TAction *SetDefaultRandomisersTab;
    TAction *SaveRandomisersTab;
    TLabel *RandomisersTitle;
    TLabel *Label20;
    TBevel *Bevel7;
    TComboBox *MutationBiasSourceBox;
    TLabel *Label22;
    TEdit *RangeEdit;
    TComboBox *ForceRandomiserTriggerList;
    TBevel *Bevel8;
    TEdit *MaxValEdit;
    TLabel *Label23;
    TLabel *Label24;
    TEdit *MinValEdit;
    TLabel *Label25;
    TEdit *DefaultMutateBiasBox;
    TLabel *Label26;
    TComboBox *PDampRandomiserTriggerList;
    TLabel *Label19;
    TComboBox *NDampRandomiserTriggerList;
    TLabel *Label21;
    TEdit *BiasScaleEdit;
    TLabel *Label27;
    TLabel *Label28;
        TTabSheet *ParametersTab;
        TEdit *PolygonSidesEdit;
        TEdit *TVZRadiusEdit;
        TEdit *ViabilityAngle;
        TLabel *PolygonSides;
        TLabel *TVZRadius;
        TLabel *Label29;
        TLabel *Label30;
        TEdit *TVZDropByEdit;
        TEdit *EvalTimeEdit;
        TLabel *Label31;
        TAction *SaveParametersTab;
        TAction *SetupParametersTab;
        TEdit *ViabilityVelocity;
        TEdit *MutationRangeEdit;
        TLabel *Label32;
        TAction *SetDefaultParametersTab;
        TEdit *dampingMutationEdit;
        TLabel *Label33;
        TEdit *AnalysisSamplesEdit;
        TLabel *Label34;
	void __fastcall SetupScaleAndBiasTabExecute(TObject *Sender);
	void __fastcall SaveAndCloseExecute(TObject *Sender);
	void __fastcall SaveScaleAndBiasTabExecute(TObject *Sender);
	void __fastcall CancelAndCloseExecute(TObject *Sender);
	void __fastcall SetDefaultsExecute(TObject *Sender);
	void __fastcall SetDefaultScaleAndBiasTabExecute(TObject *Sender);
	void __fastcall SetDefaultOscillatorTabExecute(TObject *Sender);
	void __fastcall SaveOscillatorTabExecute(TObject *Sender);
	void __fastcall SetupOscillatorTabExecute(TObject *Sender);
    void __fastcall SetupRandomisersTabExecute(TObject *Sender);
    void __fastcall SetDefaultRandomisersTabExecute(TObject *Sender);
    void __fastcall SaveRandomisersTabExecute(TObject *Sender);
        void __fastcall SaveParametersTabExecute(TObject *Sender);
        void __fastcall SetupParametersTabExecute(TObject *Sender);
        void __fastcall SetDefaultParametersTabExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TModulatorsEditForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TModulatorsEditForm *ModulatorsEditForm;
//---------------------------------------------------------------------------
#endif
