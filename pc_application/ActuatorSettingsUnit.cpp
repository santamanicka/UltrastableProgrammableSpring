//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ActuatorSettingsUnit.h"
#include "bcb_pgm.h"
#include "ProfileDefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TActuatorSettingsForm *ActuatorSettingsForm;
//---------------------------------------------------------------------------
__fastcall TActuatorSettingsForm::TActuatorSettingsForm(TComponent* Owner)
	: TForm(Owner)
{
	SetupForm->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TActuatorSettingsForm::SetupFormExecute(TObject *Sender)
{
	//Edit the profile switcher system

    //Setup the boxes
    for(int n = 0; n < 8; n++)
    {
    	StartProfileBox->Items->Add(n);
    }
    for(int n = 0; n < 4; n++)
    {
    	StartModeBox->Items->Add(n);
    }
    for(int n = 0; n < 256; n++)
    {
    	RS232NodeBox->Items->Add(n);
    }
    for(int n = 0; n < 128; n++)
    {
    	CANBUSNodeBox->Items->Add(n);
    }

    //Now set the items
    StartProfileBox->ItemIndex = (int)REMOTE->Actuator->GetStartingProfile();
    StartModeBox->ItemIndex = (int)REMOTE->Actuator->GetStartingMode();
    RS232NodeBox->ItemIndex = (int)REMOTE->Actuator->GetRS232NodeNumberByte();
    CANBUSNodeBox->ItemIndex = (int) REMOTE->Actuator->GetCANNodeNumberByte();
    DelayValueBox->Text = REMOTE->Actuator->GetDelayPeriod();

    if( (int)REMOTE->Actuator->GetPassAlongStatus() == 0) PassAlongCommandsBox->Checked = false;
    else PassAlongCommandsBox->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TActuatorSettingsForm::CancelAndCloseExecute(
      TObject *Sender)
{
    ActuatorSettingsForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TActuatorSettingsForm::SaveAndCloseExecute(TObject *Sender)
{
	//Save the settings and close

    REMOTE->Actuator->SetStartingProfile(StartProfileBox->ItemIndex);
    REMOTE->Actuator->SetStartingMode(StartModeBox->ItemIndex);
    REMOTE->Actuator->SetRS232NodeNumber(RS232NodeBox->ItemIndex);
    REMOTE->Actuator->SetCANNodeNumber(CANBUSNodeBox->ItemIndex);
    REMOTE->Actuator->SetDelayPeriod((unsigned int)DelayValueBox->Text.ToInt());
    ActuatorSettingsForm->Close();
}
//---------------------------------------------------------------------------

void __fastcall TActuatorSettingsForm::SetDefaultsExecute(TObject *Sender)
{
    StartProfileBox->ItemIndex = 0;
    StartModeBox->ItemIndex = 0;
    RS232NodeBox->ItemIndex = 1;
    CANBUSNodeBox->ItemIndex = 1;
}
//---------------------------------------------------------------------------

void __fastcall TActuatorSettingsForm::PassAlongCommandsBoxClick(
      TObject *Sender)
{
    if(PassAlongCommandsBox->Checked == true) REMOTE->Actuator->SetPassAlongStatus(1);
    else REMOTE->Actuator->SetPassAlongStatus(0);
}
//---------------------------------------------------------------------------






