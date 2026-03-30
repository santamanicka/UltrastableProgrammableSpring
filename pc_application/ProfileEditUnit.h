//---------------------------------------------------------------------------

#ifndef ProfileEditUnitH
#define ProfileEditUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TProfileEditForm : public TForm
{
__published:	// IDE-managed Components
        TImage *Image1;
        TActionList *ActionList1;
        TAction *RefreshImage;
        TAction *SetupComboBoxes;
        TAction *DrawProfile;
	TButton *EditThresholdGroupButton;
        TAction *CopyToLocalArrays;
        TRadioButton *EditForceProfileRadio;
        TRadioButton *EditPDampProfileRadio;
        TRadioButton *EditNDampProfileRadio;
        TLabel *Label65;
        TAction *UpdateMainProfileData;
        TCheckBox *DrawForceCheckBox;
        TLabel *Label66;
        TCheckBox *DrawPDampCheckBox;
        TCheckBox *DrawNDampCheckBox;
        TAction *RedrawAndRefresh;
	TComboBox *SelectProfileBox;
	TLabel *Label67;
	TStaticText *AngleText;
	TStaticText *ValueText;
	TBevel *Bevel7;
	TBevel *Bevel8;
	TBevel *Bevel14;
	TLabel *Label64;
	TLabel *Label69;
	TAction *DrawProfileText;
	TBevel *Bevel15;
	TImage *Image2;
	TPaintBox *PaintBox2;
	TButton *ProfileInteractionEditButton;
	TButton *ModulatorsEditButton;
	TButton *OKButton;
	TButton *CancelButton;
	TButton *EditOutputsButton;
	TButton *SummedFlagButton;
	TBevel *Bevel3;
	TBevel *Bevel5;
	TLabel *Label1;
	TComboBox *UniDampSourceBox;
	TEdit *UniDampDefaultEdit;
	TLabel *Label2;
	TLabel *Label3;
	TAction *DrawAngleThresholds;
	TAction *DrawProfileBackground;
	TAction *DrawProfileGraphAndText;
	TAction *CheckThresholdsForAngle;
	TTimer *Timer1;
	TAction *DrawEQP;
	TAction *DrawForceThresholds;
	TAction *DrawVelocityBackground;
	TAction *DrawVelocityThresholds;
	TButton *MotorEnableButton;
	TAction *TabbedTest;
	TLabel *Label5;
	TCheckBox *ProfileSummationBox;
	TBevel *Bevel2;
	TMainMenu *MainMenu1;
	TMenuItem *Edit1;
	TMenuItem *ProfileGenerators1;
	TMenuItem *ThresholdGroups1;
	TMenuItem *Group11;
	TMenuItem *Group21;
	TMenuItem *Group31;
	TMenuItem *Group41;
	TMenuItem *ProfileGroupInteraction1;
	TMenuItem *ProfileSwitching1;
	TMenuItem *InterprofileCommunications1;
	TMenuItem *GroupTrigger1;
	TMenuItem *Modulators1;
	TMenuItem *ScaleAndBias1;
	TMenuItem *InternalOscillator1;
	TMenuItem *ExternalOutputs1;
	TMenuItem *RS232SerialOutput1;
	TMenuItem *CANBUSOutput1;
	TMenuItem *DiscreteAnalogandDigitalOutputs1;
	TMenuItem *MotorandForceenable1;
	TMenuItem *GenerateAutoProfile1;
	TAction *EditThresholds;
	TAction *EditModulators;
	TAction *EditProfileInteractions;
	TAction *EditOutputs;
	TAction *EditGroupTrigger;
	TAction *EditMotorEnable;
	TAction *OpenProfileGenerator;
	TMenuItem *Modify;
	TMenuItem *FlipHorizontal1;
	TMenuItem *FlipVertical1;
	TAction *FlipProfileVertical;
	TAction *FlipProfileHorizontal;
	TButton *GenerateSurfaceButton;
	TAction *OpenSurfacePlotWindow;
	TAction *DrawForceMap;
	TCheckBox *ShowVThresholdsBox;
	TAction *RedrawVelocityGraphics;
	TPanel *Panel1;
	TEdit *TimerThresholdEdit;
	TLabel *Label4;
	TButton *DefaultTimerButton;

        void __fastcall RefreshImageExecute(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SetupComboBoxesExecute(TObject *Sender);
        void __fastcall DrawProfileExecute(TObject *Sender);
        void __fastcall CopyToLocalArraysExecute(TObject *Sender);
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall UpdateMainProfileDataExecute(TObject *Sender);
        void __fastcall RedrawAndRefreshExecute(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
	void __fastcall SelectProfileBoxChange(TObject *Sender);
	void __fastcall OKButtonClick(TObject *Sender);
	void __fastcall CancelButtonClick(TObject *Sender);
	void __fastcall DrawAngleThresholdsExecute(TObject *Sender);
	void __fastcall DrawProfileBackgroundExecute(TObject *Sender);
	void __fastcall DrawProfileGraphAndTextExecute(TObject *Sender);
	void __fastcall CheckThresholdsForAngleExecute(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall DrawEQPExecute(TObject *Sender);
	void __fastcall DrawForceThresholdsExecute(TObject *Sender);
	void __fastcall DrawVelocityThresholdsExecute(TObject *Sender);
	void __fastcall DrawVelocityBackgroundExecute(TObject *Sender);
	void __fastcall EditThresholdsExecute(TObject *Sender);
	void __fastcall EditModulatorsExecute(TObject *Sender);
	void __fastcall EditProfileInteractionsExecute(TObject *Sender);
	void __fastcall EditOutputsExecute(TObject *Sender);
	void __fastcall EditGroupTriggerExecute(TObject *Sender);
	void __fastcall EditMotorEnableExecute(TObject *Sender);
	void __fastcall Group11Click(TObject *Sender);
	void __fastcall Group21Click(TObject *Sender);
	void __fastcall Group31Click(TObject *Sender);
	void __fastcall Group41Click(TObject *Sender);
	void __fastcall ProfileSwitching1Click(TObject *Sender);
	void __fastcall InterprofileCommunications1Click(TObject *Sender);
	void __fastcall ScaleAndBias1Click(TObject *Sender);
	void __fastcall InternalOscillator1Click(TObject *Sender);
	void __fastcall RS232SerialOutput1Click(TObject *Sender);
	void __fastcall CANBUSOutput1Click(TObject *Sender);
	void __fastcall DiscreteAnalogandDigitalOutputs1Click(TObject *Sender);
	void __fastcall OpenProfileGeneratorExecute(TObject *Sender);
	void __fastcall FlipProfileVerticalExecute(TObject *Sender);
	void __fastcall FlipProfileHorizontalExecute(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall OpenSurfacePlotWindowExecute(TObject *Sender);
	void __fastcall DrawForceMapExecute(TObject *Sender);
	void __fastcall RedrawVelocityGraphicsExecute(TObject *Sender);
	void __fastcall DefaultTimerButtonClick(TObject *Sender);


private:	// User declarations
public:		// User declarations
        __fastcall TProfileEditForm(TComponent* Owner);
        void DragAngleThresholds(int X, int Y);
        void DragForceThresholds(int X, int Y);
        int ConvertXMouseToProfile(int XMouse);
        int ConvertForceValueToYMouse(int ForceVal);
        int ConvertYMouseToForceValue(int YMouse);
        double ConvertXAngleToMouse(int XAngle);
        int ConvertXMouseToAngle(double XMouse);

        int DetermineImageDragItem(int X, int Y);
        TColor GetFinalForceColor(int Angle, int Velocity);
        TColor GetColour(int RedComponent, int GreenComponent, int BlueComponent);
        TStringList *VariableList16;
        TStringList *VariableList8;
        TStringList *PointerList16;
        TStringList *PointerList8;
        int CurrentEditingProfile;

        int TempFPro[64];
        int TempPDamp[64];
        int TempNDamp[64];

        int TempSI16Var[32];
        int TempSI16Ptr[64];
        int TempI8Var[32];
        int TempI8Ptr[64];

        int GlobalMouseYPos;
        int GlobalMouseXPos;
        int DrawStart;
        int ShiftStartState;

        double ImageXScalarValue;
        double ScaleToAngleConstant;
        double ScaleToImageXConstant;
        AnsiString Title;
        int ThresholdToEdit;

        //Drawing Variables
        int ProfileHeight;
        int HPStart, HPEnd, VPStart, VPEnd, VPMax, VPMin;
        int ProfileZero;
        int VPBorder;
        int ImageWidth, ImageHeight;
        double ImageAngleThresholds[2][4]; //[PAT, NAT][angle 1-4];
        int ImageAngleActive[2][4];    //[Pat, Nat] [non angle, angle not enables, angle enabled]
        int AngleThresholdDragHeight;
        int EQPXStart, EQPXEnd, EQPYStart, EQPYEnd;
        int ThresholdDragStartX[2][4]; //[PAT, NAT][X]
        int ThresholdDragStartY[2][4]; //[PAT, NAT][X]
        int ThresholdDragEndX[2][4]; //[PAT, NAT][X]
        int ThresholdDragEndY[2][4]; //[PAT, NAT][X]
        int ThresholdDragOffset;
        int ThresholdBeingDragged;
        double EQImagePosition;

        int ForceThresholdValues[2][4];
        int ForceThresholdActive[2][4];

        int VelocityThresholdValues[2][4];
        int VelocityThresholdActive[2][4];

        int ForceThresholdDragStartX[2][4]; //[PAT, NAT][X]
        int ForceThresholdDragStartY[2][4]; //[PAT, NAT][Y]
        int ForceThresholdDragEndX[2][4]; //[PAT, NAT][X]
        int ForceThresholdDragEndY[2][4]; //[PAT, NAT][Y]
        int ForceThresholdDragOffset;


        int VelocityImageVCentre;
        int VelocityImageHCentre;
        int ThresholdClickEdit;
        int ModulatorClickEdit;
        int OutputsClickEdit;
        int InteractionsClickEdit;
};
//---------------------------------------------------------------------------
extern PACKAGE TProfileEditForm *ProfileEditForm;
//---------------------------------------------------------------------------
#endif
