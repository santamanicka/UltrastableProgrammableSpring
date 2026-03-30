//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProfileSwitchEditUnit.h"
#include "ProfileEditUnit.h"
#include "ProfileDefines.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProfileSwitchEditForm *ProfileSwitchEditForm;
//---------------------------------------------------------------------------
__fastcall TProfileSwitchEditForm::TProfileSwitchEditForm(TComponent* Owner)
	: TForm(Owner)
{

	SetupForm->Execute();
    TriggerListWarning->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileSwitchEditForm::SetupFormExecute(TObject *Sender)
{
    CurrentProfile = ProfileEditForm->CurrentEditingProfile;
    AnsiString Title;
    //TempVarList = new TStringList;
    int ListIndex = 0;
    //The first 11 variables in the lists of options are invalid so remove them
    //use this variable to add to the item index to get the real value
    VariableListOffset = 11;


    Title = "Conditional Profile Switchers for Profile No ";
    Title += CurrentProfile;
    Label49->Caption = Title;
    for(int n = 0; n < 8; n++)
    {
              AltProTargetlist1->Items->Add(n);
              AltProTargetlist2->Items->Add(n);
              AltProTargetlist3->Items->Add(n);
              AltProTargetlist4->Items->Add(n);
    }
    //TempVarList = ProfileEditForm->VariableList8;


	AltproTriggerlist1->Items = ProfileEditForm->VariableList8;
    AltproTriggerlist2->Items = ProfileEditForm->VariableList8;
    AltproTriggerlist3->Items = ProfileEditForm->VariableList8;
    AltproTriggerlist4->Items = ProfileEditForm->VariableList8;
    IncrimentTriggerBox->Items = ProfileEditForm->VariableList8;
    DeincrimentTriggerBox->Items = ProfileEditForm->VariableList8;

    /*for(int n = 0; n < VariableListOffset; n++)
    {
    	AltproTriggerlist1->Items->Delete(0);
        AltproTriggerlist2->Items->Delete(0);
        AltproTriggerlist3->Items->Delete(0);
        AltproTriggerlist4->Items->Delete(0);

        IncrimentTriggerBox->Items->Delete(0);
        DeincrimentTriggerBox->Items->Delete(0);
    }*/

    ListIndex =  ProfileEditForm->TempI8Ptr[_AltPro1_ptr];
    //if(ListIndex < VariableListOffset)ListIndex = 0;
    //else ListIndex-=VariableListOffset;
    AltproTriggerlist1->ItemIndex = ListIndex; //Subtact the offset
    AltProTargetlist1->ItemIndex = ProfileEditForm->TempI8Var[_AltPro1];


    ListIndex =  ProfileEditForm->TempI8Ptr[_AltPro2_ptr];
    //if(ListIndex < VariableListOffset)ListIndex = 0;
    //else ListIndex-=VariableListOffset;
    AltproTriggerlist2->ItemIndex = ListIndex;
    AltProTargetlist2->ItemIndex = ProfileEditForm->TempI8Var[_AltPro2];


    ListIndex =  ProfileEditForm->TempI8Ptr[_AltPro3_ptr];
    //if(ListIndex < VariableListOffset)ListIndex = 0;
    //else ListIndex-=VariableListOffset;
    AltproTriggerlist3->ItemIndex = ListIndex;
    AltProTargetlist3->ItemIndex = ProfileEditForm->TempI8Var[_AltPro3];


    ListIndex =  ProfileEditForm->TempI8Ptr[_AltPro4_ptr];
    //if(ListIndex < VariableListOffset)ListIndex = 0;
    //else ListIndex-=VariableListOffset;
    AltproTriggerlist4->ItemIndex = ListIndex;
    AltProTargetlist4->ItemIndex = ProfileEditForm->TempI8Var[_AltPro4];


    ListIndex =  ProfileEditForm->TempI8Ptr[_IncrimentProfile_ptr];
    //if(ListIndex < VariableListOffset)ListIndex = 0;
    //else ListIndex-=VariableListOffset;
    IncrimentTriggerBox->ItemIndex = ListIndex;


    ListIndex =  ProfileEditForm->TempI8Ptr[_DeIncrimentProfile_ptr];
    //if(ListIndex < VariableListOffset)ListIndex = 0;
    //else ListIndex-=VariableListOffset;
    DeincrimentTriggerBox->ItemIndex = ListIndex;

    AnsiString Capt;
    Capt = "New Profile Will Be: ";
    if(CurrentProfile == 7) Capt += 0;
    else Capt += (CurrentProfile+1);
    Label15->Caption = Capt;

    Capt = "New Profile Will Be: ";
    if(CurrentProfile == 0) Capt += 7;
    else Capt += (CurrentProfile-1);
    Label16->Caption = Capt;
}
//---------------------------------------------------------------------------
void __fastcall TProfileSwitchEditForm::SaveAndCloseExecute(
      TObject *Sender)
{
	//Save the settings back to the parent form
    int ListIndex =0;
    
    ListIndex =  AltproTriggerlist1->ItemIndex;
    ProfileEditForm->TempI8Ptr[_AltPro1_ptr] = ListIndex;
    ProfileEditForm->TempI8Var[_AltPro1] = AltProTargetlist1->ItemIndex;

    ListIndex =  AltproTriggerlist2->ItemIndex;
    ProfileEditForm->TempI8Ptr[_AltPro2_ptr] = ListIndex;
    ProfileEditForm->TempI8Var[_AltPro2] = AltProTargetlist2->ItemIndex;

    ListIndex =  AltproTriggerlist3->ItemIndex;
    ProfileEditForm->TempI8Ptr[_AltPro3_ptr] = ListIndex;
    ProfileEditForm->TempI8Var[_AltPro3] = AltProTargetlist3->ItemIndex;

    ListIndex =  AltproTriggerlist4->ItemIndex;
    ProfileEditForm->TempI8Ptr[_AltPro4_ptr] = ListIndex;
    ProfileEditForm->TempI8Var[_AltPro4] = AltProTargetlist4->ItemIndex;

    ListIndex = IncrimentTriggerBox->ItemIndex;
    ProfileEditForm->TempI8Ptr[_IncrimentProfile_ptr] = ListIndex;

    ListIndex = DeincrimentTriggerBox->ItemIndex;
    ProfileEditForm->TempI8Ptr[_DeIncrimentProfile_ptr] = ListIndex;


}
//---------------------------------------------------------------------------

void __fastcall TProfileSwitchEditForm::Button2Click(TObject *Sender)
{
    SaveAndClose->Execute();
    ProfileSwitchEditForm->Close();
}
//---------------------------------------------------------------------------


void __fastcall TProfileSwitchEditForm::Button3Click(TObject *Sender)
{
	//Set default values

    AltproTriggerlist1->ItemIndex = _GlobalDefaultFalse;
    AltProTargetlist1->ItemIndex = CurrentProfile;

    AltproTriggerlist2->ItemIndex = _GlobalDefaultFalse;
    AltProTargetlist2->ItemIndex = CurrentProfile;

    AltproTriggerlist3->ItemIndex = _GlobalDefaultFalse;
    AltProTargetlist3->ItemIndex = CurrentProfile;

    AltproTriggerlist4->ItemIndex = _GlobalDefaultFalse;
    AltProTargetlist4->ItemIndex = CurrentProfile;

    IncrimentTriggerBox->ItemIndex = _GlobalDefaultFalse;

    DeincrimentTriggerBox->ItemIndex = _GlobalDefaultFalse;

    TriggerListWarning->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileSwitchEditForm::TriggerListWarningExecute(
      TObject *Sender)
{
	//Issues a warning if you choose something from a list that is not supposed
    //to be a conditional trigger
    //search all the lists for an error
    int ErrorCount = 0;
    int ErrorCount1 = 0;
    AnsiString Message;
    AnsiString Message1;
    AnsiString InvalidEntry = "<Not In Use>";



    if(AltproTriggerlist1->ItemIndex < VariableListOffset)
    {
    	Message = "Warning - Selected Trigger Source is not meant to be a trigger!";
        ErrorCount++;
    }
    if(AltproTriggerlist1->Items->Strings[AltproTriggerlist1->ItemIndex] == InvalidEntry)
    {
    	Message1 = "Warning - Selected Source is not used - reverting to default";
        AltproTriggerlist1->ItemIndex = _GlobalDefaultFalse;
        ErrorCount1++;
    }

    if(AltproTriggerlist2->ItemIndex < VariableListOffset)
    {
    	Message = "Warning - Selected Trigger Source is not meant to be a trigger!";
        ErrorCount++;
    }
    if(AltproTriggerlist2->Items->Strings[AltproTriggerlist2->ItemIndex] == InvalidEntry)
    {
    	Message1 = "Warning - Selected Source is not used - reverting to default"; 
        AltproTriggerlist2->ItemIndex = _GlobalDefaultFalse;
        ErrorCount1++;
    }

    if(AltproTriggerlist3->ItemIndex < VariableListOffset)
    {
    	Message = "Warning - Selected Trigger Source is not meant to be a trigger!";
        ErrorCount++;
    }
    if(AltproTriggerlist3->Items->Strings[AltproTriggerlist3->ItemIndex] == InvalidEntry)
    {
    	Message1 = "Warning - Selected Source is not used - reverting to default";
        AltproTriggerlist3->ItemIndex = _GlobalDefaultFalse;
        ErrorCount1++;
    }

    if(AltproTriggerlist4->ItemIndex < VariableListOffset)
    {
    	Message = "Warning - Selected Trigger Source is not meant to be a trigger!";
        ErrorCount++;
    }
    if(AltproTriggerlist4->Items->Strings[AltproTriggerlist4->ItemIndex] == InvalidEntry)
    {
    	Message1 = "Warning - Selected Source is not used - reverting to default";
        AltproTriggerlist4->ItemIndex = _GlobalDefaultFalse;
        ErrorCount1++;
    }

    if(IncrimentTriggerBox->ItemIndex < VariableListOffset)
    {
    	Message = "Warning - Selected Trigger Source is not meant to be a trigger!";
        ErrorCount++;
    }
    if(IncrimentTriggerBox->Items->Strings[IncrimentTriggerBox->ItemIndex] == InvalidEntry)
    {
    	Message1 = "Warning - Selected Source is not used - reverting to default";
        IncrimentTriggerBox->ItemIndex = _GlobalDefaultFalse;
        ErrorCount1++;
    }

    if(DeincrimentTriggerBox->ItemIndex < VariableListOffset)
    {
    	Message = "Warning - Selected Trigger Source is not meant to be a trigger!";
        ErrorCount++;
    }
    if(DeincrimentTriggerBox->Items->Strings[DeincrimentTriggerBox->ItemIndex] == InvalidEntry)
    {
    	Message1 = "Warning - Selected Source is not used - reverting to default";
        DeincrimentTriggerBox->ItemIndex = _GlobalDefaultFalse;
        ErrorCount1++;
    }

    if( ErrorCount > 1 ) Message = "Warning - Some selected trigger sources are not valid!";
    if( ErrorCount1 > 1 ) Message1 = "Warning - Some Selected sources were reset to their defaults";
	StaticText1->Caption = Message;
    StaticText2->Caption = Message1;//AltproTriggerlist1->Items->Strings[AltproTriggerlist1->ItemIndex];//Message1;
}
//---------------------------------------------------------------------------

void __fastcall TProfileSwitchEditForm::Button1Click(TObject *Sender)
{
	//
    ProfileSwitchEditForm->Close();
}
//---------------------------------------------------------------------------

