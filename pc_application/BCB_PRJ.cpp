//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USEFORM("BCB_PGM.CPP", REMOTE);
USEFORM("configunit.cpp", ConfigureForm);
USEFORM("ProfileEditUnit.cpp", ProfileEditForm);
USEFORM("ProfileInteractionEditUnit.cpp", ProfileInteractionEditForm);
USEFORM("ModulatorsEditUnit.cpp", ModulatorsEditForm);
USEFORM("GroupTriggerUnit.cpp", GroupTriggerForm);
USEFORM("MotorAndForceEditUnit.cpp", MotorEnableForm);
USEFORM("ThresholdGroupSettingsUnit.cpp", ThresholdGroupSettingsForm);
USEFORM("IOEditorUnit.cpp", InputOutputForm);
USEFORM("ActuatorSettingsUnit.cpp", ActuatorSettingsForm);
USEFORM("ProfileGeneratorUnit.cpp", ProfileGeneratorForm);
USEFORM("SerialPortMonitorUnit.cpp", SerialPortMonitorForm);
USEFORM("DownloadProgressUnit.cpp", DownloadProgressForm);
USEFORM("ActuatorCommandUnit.cpp", CommandForm);
USEFORM("ForceSurfaceUnit.cpp", ForceSurfacePlotForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TREMOTE), &REMOTE);
		Application->CreateForm(__classid(TSerialPortMonitorForm), &SerialPortMonitorForm);
		Application->CreateForm(__classid(TDownloadProgressForm), &DownloadProgressForm);
		Application->CreateForm(__classid(TCommandForm), &CommandForm);
		Application->CreateForm(__classid(TProfileEditForm), &ProfileEditForm);
		Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
