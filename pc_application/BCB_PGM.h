//---------------------------------------------------------------------------
#ifndef BCB_PGMH
#define BCB_PGMH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Menus.hpp>
#include <vcl\ExtCtrls.hpp>
#include <Mask.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <mmsystem.h>
#include <math.h>
#include <stdio.h>
#include <Dialogs.hpp>

#include "Prof.hpp"


//---------------------------------------------------------------------------
class TREMOTE : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer;
	TActionList *ActionList1;
	TAction *AttemptConnection;
	TAction *Disconnect;
	TAction *ConnectDisconnect;
	TAction *ProcessIncoming;
	TTimer *Timer1;
        TAction *OpenConfigWindow;
        TAction *OpenProfileEditForm;
        TAction *ChangeToSelectedProfile;
        TAction *UnpackProfileFileIntoDataObject;
        TAction *PrintDataObject;
        TAction *SendCurrentProfileToActuator;
        TAction *SendPrintProfileCommand;
        TOpenDialog *OpenProfileGroupDialog;
        TSaveDialog *SaveProfileGroupDialog;
        TAction *PackUpProfileData;
	TOpenDialog *OpenActuatorDialog;
	TSaveDialog *SaveActuatorDialog;
	TAction *UnpackActuatorFile;
	TAction *PackUpActuatorFile;
	TAction *SendFProfile;
	TAction *SendPDampProfile;
	TAction *SendNDampProfile;
	TAction *SendInt8Vars;
	TAction *SendInt8Pointers;
	TAction *SendInt16Vars;
	TAction *SendInt16Pointers;
	TAction *SendDownloadCompleteCommand;
	TAction *RedrawAndRefresh;
    TAction *SendStartActuatorCommand;
    TAction *SendStopActuatorCommand;
	TAction *Test1;
	TAction *OpenEditActuatorWindow;
	TMainMenu *MainMenu1;
	TMenuItem *Save1;
	TMenuItem *Edit1;
	TMenuItem *OpenProfileGroup1;
	TMenuItem *SaveProfileGroup1;
	TMenuItem *OpenActuator1;
	TMenuItem *SaveActuator1;
	TMenuItem *EditCurrentprofileGroup1;
	TMenuItem *EditActuatorSettings1;
	TAction *LoadProfileGroupFromFile;
	TAction *SaveProfileGroupToFile;
	TAction *LoadActuatorFromFile;
	TAction *SaveActuatorToFile;
	TMenuItem *Communication1;
	TMenuItem *Connect1;
	TMenuItem *Settings1;
	TMenuItem *Connect2;
	TMenuItem *Disconnect1;
	TMenuItem *DownloadCurrentProfile1;
	TMenuItem *DownloadWholeActuator1;
	TMenuItem *StartActuator1;
	TMenuItem *StopActuator1;
	TAction *SendActuatorSettings;
	TAction *ExtractIncomingData;
	TAction *ExtractCommandAorB;
	TAction *ExtractErrorMsg;
	TAction *ExtractAckMsg;
	TPanel *Panel1;
	TSplitter *Splitter1;
	TMemo *Messages;
	TPanel *Panel2;
	TStaticText *StatusText;
	TStaticText *CommRateText;
	TButton *SendProfileToActuatorButton;
	TComboBox *SelectprofileBox;
	TCheckBox *PrintLogCheckBox;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label1;
	TImage *Image1;
	TButton *EditProfileButton;
	TButton *EditActuatorButton;
	TButton *DownloadWholeActuatorButton;
	TButton *ConnectButton;
	TStaticText *CommText;
	TMemo *GroupBMemo;
	TBevel *Bevel2;
	TBevel *Bevel1;
	TStaticText *BaudText;
	TAction *OpenSerialPortMonitor;
	TAction *CheckPortMonotorIsVisible;
	TAction *ActivateForm;
	TMemo *GroupAMemo;
	TButton *ClearAButton;
	TButton *ClearBButton;
	TAction *ClearGroupAMemo;
	TAction *ClearGroupBMemo;
	TLabel *GroupAHeaderLabel;
	TLabel *GroupBHeaderLabel;
	TAction *TemporaryStorageOfCode;
	TAction *SendRestartCommand;
	TButton *ShowControlButton;
	TAction *ShowControls;
	TAction *SendCommandPacket;
	TMenuItem *OpenPortMonitor1;
	TMenuItem *OpenCommandWindow1;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N3;
	TMenuItem *N4;
	TBevel *Bevel4;
    TRadioGroup *DrawingOptionPanel;
    TCheckBox *ColorDrawingBox;
    TBevel *Bevel5;
    TCheckBox *DrawAngleDataBox;
    TCheckBox *TraceOnForceMapBox;
	TPanel *Panel3;
	TAction *RedrawProfileBitmaps;
	TAction *SendPrintProfileDataCommand;
	TAction *SendSwitchProfileCommand;
    TButton *ClearTraceButton;
    TAction *ClearTraceImage;
    TButton *StartStopLogButton;
    TEdit *LogFilenameEdit;
    TLabel *Label4;
    TStaticText *LogText;
    TAction *StartStopLog;
        TAction *ExtractDebugMsg;
        TButton *DLActuatorOnly;
        TAction *ExtractCommandC;
        TLabel *ProfileNumber;
        TLabel *Label5;
        TAction *ExtractCommandZ;
        TCheckBox *CollectStatisticsBox;
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall AttemptConnectionExecute(TObject *Sender);
	void __fastcall DisconnectExecute(TObject *Sender);
	void __fastcall ConnectDisconnectExecute(TObject *Sender);
	void __fastcall ProcessIncomingExecute(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ClearImageExecute(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall OpenConfigWindowExecute(TObject *Sender);
    void __fastcall OpenProfileEditFormExecute(TObject *Sender);
    void __fastcall ChangeToSelectedProfileExecute(TObject *Sender);
    void __fastcall UnpackProfileFileIntoDataObjectExecute(
          TObject *Sender);
    void __fastcall PrintDataObjectExecute(TObject *Sender);
    void __fastcall GetBytesTestButtonClick(TObject *Sender);
    void __fastcall SendCurrentProfileToActuatorExecute(
          TObject *Sender);
    void __fastcall SendPrintProfileCommandExecute(TObject *Sender);
    void __fastcall PackUpProfileDataExecute(TObject *Sender);
	void __fastcall UnpackActuatorFileExecute(TObject *Sender);
	void __fastcall PackUpActuatorFileExecute(TObject *Sender);
	void __fastcall SendFProfileExecute(TObject *Sender);
	void __fastcall SendPDampProfileExecute(TObject *Sender);
	void __fastcall SendNDampProfileExecute(TObject *Sender);
	void __fastcall SendInt8VarsExecute(TObject *Sender);
	void __fastcall SendInt8PointersExecute(TObject *Sender);
	void __fastcall SendInt16VarsExecute(TObject *Sender);
	void __fastcall SendInt16PointersExecute(TObject *Sender);
	void __fastcall SendDownloadCompleteCommandExecute(TObject *Sender);
	void __fastcall DownloadWholeActuatorButtonClick(TObject *Sender);
	void __fastcall RedrawAndRefreshExecute(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
    void __fastcall SendStartActuatorCommandExecute(TObject *Sender);
    void __fastcall SendStopActuatorCommandExecute(TObject *Sender);
	void __fastcall Test1Execute(TObject *Sender);
	void __fastcall OpenEditActuatorWindowExecute(TObject *Sender);
	void __fastcall LoadProfileGroupFromFileExecute(TObject *Sender);
	void __fastcall SaveProfileGroupToFileExecute(TObject *Sender);
	void __fastcall LoadActuatorFromFileExecute(TObject *Sender);
	void __fastcall SaveActuatorToFileExecute(TObject *Sender);
	void __fastcall SendActuatorSettingsExecute(TObject *Sender);
	void __fastcall ExtractIncomingDataExecute(TObject *Sender);
	void __fastcall ExtractCommandAorBExecute(TObject *Sender);
	void __fastcall ExtractAckMsgExecute(TObject *Sender);
	void __fastcall ExtractErrorMsgExecute(TObject *Sender);
	void __fastcall OpenSerialPortMonitorExecute(TObject *Sender);
	void __fastcall CheckPortMonotorIsVisibleExecute(TObject *Sender);
	void __fastcall ActivateFormExecute(TObject *Sender);
	void __fastcall ClearGroupAMemoExecute(TObject *Sender);
	void __fastcall ClearGroupBMemoExecute(TObject *Sender);
	void __fastcall SendRestartCommandExecute(TObject *Sender);
	void __fastcall ShowControlsExecute(TObject *Sender);
	void __fastcall SendCommandPacketExecute(TObject *Sender);
	void __fastcall RedrawProfileBitmapsExecute(TObject *Sender);
	void __fastcall SendPrintProfileDataCommandExecute(TObject *Sender);
	void __fastcall SendSwitchProfileCommandExecute(TObject *Sender);
    void __fastcall ClearTraceImageExecute(TObject *Sender);
    void __fastcall StartStopLogExecute(TObject *Sender);
        void __fastcall ExtractDebugMsgExecute(TObject *Sender);
        void __fastcall ExtractCommandCExecute(TObject *Sender);
        void __fastcall ExtractCommandZExecute(TObject *Sender);




	
private:	// User declarations
public:		// User declarations
	__fastcall TREMOTE(TComponent* Owner);
    void PrintMessage(AnsiString Line);
    void SendProfileRcvdAck();
    void processMutatedDamprofile();
    void processMutatedForceProfile();
    void processAngleTrace();
    void processAngleVelTrace();
    void plotMutatedData();
    void processPDMutationData();
    void processNDMutationData();
    void processForceMutationData();
    void collectMutationStatistics();
    void transferProfileData();
    void processProfileEvaluationData();
    
    void JoyAnim(int XX, int YY);
    void CalculateMotors(int XVal, int YVal);
    void CalculateEndpoint(double Range, double Angle, TPoint PointArray[]);
    TColor GetColour(int RedComponent, int GreenComponent, int BlueComponent);
    int ApplyToPacketFilter(int DataByte);
    int DecodeSerialVariable(int Upper, int Lower);
    void RedrawProfileBitmapX(int ProfileToRedraw);
    int flag1;
    byte bytesin[9];
    int buff;
    bool sending;
    bool stopall;

    int XValue, YValue;
    int ImageCentreX, ImageCentreY;
    double RRange;
    bool TypingFlag;
    //bool connected;
    int buttonstate;
    int ThePort;
    int TheBaud;
    int ConnectionStatus;
    double BodyScale;
    bool ChangedBodyScale;
    int SingleSerialVal;
    AnsiString PacketPreamble;
    char* Char_ptr1;
    char* Char_ptr2;
    char PreambleChars[8];
    int PreambleLength;
    char DataChars[16];
    int DataLength;
    char PacketMemory[24][10];
    AnsiString Names[10];
    char ForceTarget;

    int PacketOK;
    int PacketComplete;
    int IncomingDataBuffer[256];
    int IncomingDataCount;
    int IncomingPacketLength;
    int IncomingPreamble[8];
    int IncomingCommand1;
    int IncomingCommand2;

    int TimeSinceLastpacket;
    int OldTime;

    //Storage for the profiles

    TStringList *DefaultProfileSettings;
    TStringList *ProfileSettings0;
    TStringList *ProfileSettings1;
    TStringList *ProfileSettings2;
    TStringList *ProfileSettings3;
    TStringList *ProfileSettings4;
    TStringList *ProfileSettings5;
    TStringList *ProfileSettings6;
    TStringList *ProfileSettings7;
    TStringList *ActuatorSettings;
    TStringList *ArrayOfProSettings[8];

    TStringList *ForceSurfaceData;


     
    ProObj* ProfileData0;
    ProObj* ProfileData1;
    ProObj* ProfileData2;
    ProObj* ProfileData3;
    ProObj* ProfileData4;
    ProObj* ProfileData5;
    ProObj* ProfileData6;
    ProObj* ProfileData7;
    ProObj* ArrayOfProfileData[8];
    ProObj* MutatedProfile;
    ActObj* Actuator;
    int EditingProfileNo;
    int FProfileTXNo;
    int Timer1Counts;
    int FullDownload;
    int DownloadInProgress;
    int CurrentOldProfile;
    //int ImageXScalarValue;
    byte TargetNode;
    AnsiString GroupMemoHeader;
    bool SerialPortMonitorVisible;

    byte ControlOutBuffer[32];

    int Startup;

    Graphics::TBitmap *TraceImage1;
    TRect   ImageRectangle;

    byte NewActuatorProfile;
    AnsiString LogFileName;
    int LogNumber;
    bool LogRunning;
    int LogFileHandle;

    int ConnectedActuatorsCurrentProfile;

    int netQue;
    //Graphics stuff
    //Graphics::TBitmap *Graph1;

    TStringList *MutationData;
    FILE *pdampfile;
    FILE *ndampfile;
    FILE *forcefile;
    FILE *mutatedAnglesFile, *notMutatedAnglesFile, *numMutationsFile, *mutationsMagnitudeFile;
    FILE *profileEvaluationFile;
    FILE *trajectoryFile;

    int mutationCnt, totalAngle, totalAngleVelocity, iterations;
    int totalAngle0, totalAngleVelocity0, iterations0;
    int totalAngle1, totalAngleVelocity1, iterations1;
    int totalAngle2, totalAngleVelocity2, iterations2;
    int totalAngle3, totalAngleVelocity3, iterations3;
    /*
    TFileStream *pdampfile;
    TFileStream *ndampfile;
    TFileStream *forcefile;
    */
};
//---------------------------------------------------------------------------
extern TREMOTE *REMOTE;
//---------------------------------------------------------------------------
#endif
