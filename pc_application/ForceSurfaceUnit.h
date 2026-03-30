//---------------------------------------------------------------------------

#ifndef ForceSurfaceUnitH
#define ForceSurfaceUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForceSurfacePlotForm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TActionList *ActionList1;
	TImage *Image1;
	TAction *DrawSurface;
	TAction *UpdateImage;
	TPaintBox *PaintBox1;
	TAction *CreateGraphData;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TAction *DrawGraphs;
	TAction *DrawContour;
	TAction *ClearImage;
	TAction *SaveImage;
	TSavePictureDialog *SavePictureDialog1;
	TButton *SaveButton;
	TCheckBox *FilledBox;
	TTrackBar *TrackBar1;
	TTrackBar *HBiasBar;
	TLabel *Label1;
	TLabel *Label2;
	TStaticText *StaticText1;
	TTrackBar *HScaleBar;
	TLabel *Label3;
	TStaticText *StaticText2;
	TTrackBar *VBiasBar;
	void __fastcall UpdateImageExecute(TObject *Sender);
	void __fastcall DrawSurfaceExecute(TObject *Sender);
	void __fastcall CreateGraphDataExecute(TObject *Sender);
	void __fastcall DrawContourExecute(TObject *Sender);
	void __fastcall DrawGraphsExecute(TObject *Sender);
	void __fastcall ClearImageExecute(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SaveImageExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForceSurfacePlotForm(TComponent* Owner);
    double GetFinalForceValue(int Angle, int Velocity);

    TColor GetColour(int RedComponent, int GreenComponent, int BlueComponent);

    double FinalForceValues[64][65];

    double ViewAngleTweak;
    double ViewAngleOffset;
    double ViewAngleOffsetScale;
    int HBias;
    float HScale;
    float VBias;
};
//---------------------------------------------------------------------------
extern PACKAGE TForceSurfacePlotForm *ForceSurfacePlotForm;
//---------------------------------------------------------------------------
#endif
