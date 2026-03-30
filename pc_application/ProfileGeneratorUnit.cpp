//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProfileGeneratorUnit.h"
#include "ProfileEditUnit.h"
#include <Math.h>
#include <Math.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProfileGeneratorForm *ProfileGeneratorForm;
//---------------------------------------------------------------------------
__fastcall TProfileGeneratorForm::TProfileGeneratorForm(TComponent* Owner)
	: TForm(Owner)
{
    SetupForm->Execute();
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::SaveAndCloseExecute(TObject *Sender)
{
     ProfileGeneratorForm->Close();
}

//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::UpdateMainImageExecute(
      TObject *Sender)
{
	//
    int TempVar;
    if( ApplyToForceBox->Checked == true)
    {
    	for(int n = 0; n < 64; n++)
    	{
    		ProfileEditForm->TempFPro[n] = ForceProfile[n];
    	}
    }
    else
    {
    	for(int n = 0; n < 64; n++)
    	{
    		ProfileEditForm->TempFPro[n] = OLDForceProfile[n];
    	}
    }
    if( ApplyToPDampBox->Checked == true)
    {
    	for(int n = 0; n < 64; n++)
    	{
        	TempVar = ForceProfile[n]/16;
            if(TempVar > 127) TempVar = 127;
            if(TempVar < -128) TempVar = -128;
    		ProfileEditForm->TempPDamp[n] = TempVar;
    	}
    }
    else
    {
    	for(int n = 0; n < 64; n++)
    	{
    		ProfileEditForm->TempPDamp[n] = OLDPDampProfile[n];
    	}
    }
    if( ApplyToNDampBox->Checked == true)
    {
    	for(int n = 0; n < 64; n++)
    	{
        	TempVar = ForceProfile[n]/16;
            if(TempVar > 127) TempVar = 127;
            if(TempVar < -128) TempVar = -128;
    		ProfileEditForm->TempNDamp[n] = TempVar;
    	}
    }
    else
    {
    	for(int n = 0; n < 64; n++)
    	{
    		ProfileEditForm->TempNDamp[n] = OLDNDampProfile[n];
    	}
    }
    ProfileEditForm->RedrawVelocityGraphics->Execute();
    ProfileEditForm->RedrawAndRefresh->Execute();

}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::StartLeft10Click(TObject *Sender)
{
	int Val = SinStartEdit->Text.ToInt();
	Val += 8;
    SinStartEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::StartLeft1Click(TObject *Sender)
{
     int Val = SinStartEdit->Text.ToInt();
	Val += 1;
    SinStartEdit->Text = Val;
     RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::StartRight1Click(TObject *Sender)
{
     int Val = SinStartEdit->Text.ToInt();
	Val -= 1;
    SinStartEdit->Text = Val;
     RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::StartRight10Click(TObject *Sender)
{
     int Val = SinStartEdit->Text.ToInt();
	Val -= 8;
    SinStartEdit->Text = Val;
     RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::RegenerateFunctionExecute(
      TObject *Sender)
{
	//Redraws everything when a change occurs
    if(SinButton->Checked == true) GenerateSin->Execute();
    else if(TanhButton->Checked == true) GenerateTanh->Execute();
    else if(ExponentialButton->Checked == true) GenerateExponential->Execute();

    UpdateMainImage->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::SetupFormExecute(TObject *Sender)
{
	SinFreq = 0.1;
    SinHeight = 1024;
    Start = 1;
    SinVBias = 0;
    SinHBias = 480;
    SinDB = 0;
    TanhFreq = 0.1;
    TanhHeight = 1024;
    TanhHBias = 480;
    TanhVBias = 0;
    TanDB = 0;
    for(int n = 0; n < 64; n++)
    {
    	OLDForceProfile[n] = ProfileEditForm->TempFPro[n];
    	OLDPDampProfile[n] = ProfileEditForm->TempPDamp[n];
    	OLDNDampProfile[n] = ProfileEditForm->TempNDamp[n];
    }
    SinStartEdit->Text = SinHBias;
    SinHeightEdit->Text = SinHeight;
    SineFreqEdit->Text = TanhFreq;
    VBiasEdit->Text = SinVBias;
    DeadBandEdit->Text = SinDB;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::SinStartEditExit(TObject *Sender)
{

    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::SineFreqEditExit(TObject *Sender)
{

    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::SinHeightEditExit(TObject *Sender)
{

    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::CancelAndCloseExecute(
      TObject *Sender)
{
	for(int n = 0; n < 64; n++)
    {
    	ProfileEditForm->TempFPro[n] = OLDForceProfile[n];
    	ProfileEditForm->TempPDamp[n] = OLDPDampProfile[n];
        ProfileEditForm->TempNDamp[n] = OLDNDampProfile[n];
    }
    ProfileGeneratorForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::VBiasEditExit(TObject *Sender)
{

    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::VBisUpClick(TObject *Sender)
{
	int Val = VBiasEdit->Text.ToInt();
    Val ++;
    VBiasEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::VBiasDownClick(TObject *Sender)
{
	int Val = VBiasEdit->Text.ToInt();
    Val --;
    VBiasEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::GenerateSinExecute(TObject *Sender)
{
    double Val = 0;
    double V2 = 0;
    //double TanhFreq, TanhHeight, TanhHBias, TanhVBias;
    SinFreq = SineFreqEdit->Text.ToDouble();
    SinHeight = SinHeightEdit->Text.ToDouble();
    SinVBias = VBiasEdit->Text.ToDouble();
    SinHBias = 480+SinStartEdit->Text.ToDouble();
    SinDB = DeadBandEdit->Text.ToIntDef(0);
    for(int n = 0; n < 1024; n++)
    {
    	Val = sin(V2);
        V2 += SinFreq;
    	ExpandedProfile[n] = Val;
    }
	int i = 0;
    i = SinHBias;
    if(i < 0) i = 0;
    if(i > 1024-64) i = 1024-64;
    if( FlipHorizontalBox->Checked == true )
    {
    	for(int n = 63; n > -1; n--)
    	{
        	ForceProfile[n] = (int)((ExpandedProfile[i]*SinHeight)+SinVBias);
        	i++;
    	}
    }
    else
    {
    	for(int n = 0; n < 64; n++)
    	{
        	ForceProfile[n] = (int)((ExpandedProfile[i]*SinHeight)+SinVBias);
        	i++;
    	}
    }

    /*
	double Val = 0;
    double V2 = Start;
    if( HorizontalMirrorMode->Checked == true )
    {
     	for(int n = 0; n < 32; n++)
    	{
        	Val = sin(V2);
        	V2 += Freq;
			if(FlipHorizontalBox->Checked == true) ForceProfile[63-n] = (int)((Val*Height)+VerticalBias);
        	else ForceProfile[n] = (int)((Val*Height)+VerticalBias);
    	}
        int x = 31;
        for(int n = 32; n < 64; n++)
    	{
        	ForceProfile[n] = ForceProfile[x];
            x--;
    	}
    }
    else
    {
		for(int n = 0; n < 64; n++)
    	{
        	Val = sin(V2);
        	V2 += Freq;
			if(FlipHorizontalBox->Checked == true) ForceProfile[63-n] = (int)((Val*Height)+VerticalBias);
        	else ForceProfile[n] = (int)((Val*Height)+VerticalBias);
    	}
    }*/
    //DrawProfile->Execute();
}

//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::GenerateTanhExecute(TObject *Sender)
{
//Generate a Cosine??
    double Val = 0;
    //double V2 = -28;
    double V2 = 0;

    //double TanhFreq, TanhHeight, TanhHBias, TanhVBias;
    TanhFreq = SineFreqEdit->Text.ToDouble();
    TanhHeight = SinHeightEdit->Text.ToDouble();
    TanhVBias = VBiasEdit->Text.ToDouble();
    TanhHBias = 480+SinStartEdit->Text.ToDouble();
    TanDB = DeadBandEdit->Text.ToIntDef(0);
    int x = 0;
    int n = 0;
    for(n = 512+TanDB; n < 1024; n++)
    {
    	Val = tanh(V2);
        V2 += TanhFreq;
    	ExpandedProfile[n] = Val;
    }
    x = 512 + TanDB;
    for(n = 512-TanDB; n >-1; n--)
    {
    	ExpandedProfile[n] = -ExpandedProfile[x];
        x++;
        if(x > 1023) x = 1023;
    }
    for(n = 512-TanDB; n < 513+TanDB; n++)
    {
        ExpandedProfile[n] = 0;
    }
	int i = 0;
    i = TanhHBias;
    if(i < 0) i = 0;
    if(i > 1024-64) i = 1024-64;
    if( FlipHorizontalBox->Checked == true )
    {
    	for(n = 63; n > -1; n--)
    	{
        	ForceProfile[n] = (int)((ExpandedProfile[i]*TanhHeight)+TanhVBias);
        	i++;
    	}
    }
    else
    {
    	for(n = 0; n < 64; n++)
    	{
        	ForceProfile[n] = (int)((ExpandedProfile[i]*TanhHeight)+TanhVBias);
        	i++;
    	}
    }
    /*
    if( HorizontalMirrorMode->Checked == true )
    {
     	for(int n = 0; n < 32; n++)
    	{
        	Val = tanh(V2);
        	V2 += Freq;
			if(FlipHorizontalBox->Checked == true) ForceProfile[63-n] = (int)((Val*Height)+VerticalBias);
        	else ForceProfile[n] = (int)((Val*Height)+VerticalBias);
    	}
        int x = 31;
        for(int n = 32; n < 64; n++)
    	{
        	ForceProfile[n] = ForceProfile[x];
            x--;
    	}
    }
    else
    {
		for(int n = 0; n < 64; n++)
    	{
        	Val = tanh(V2);
        	V2 += Freq;
			if(FlipHorizontalBox->Checked == true) ForceProfile[63-n] = (int)((Val*Height)+VerticalBias);
        	else ForceProfile[n] = (int)((Val*Height)+VerticalBias);
    	}
    } */
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::GenerateExponentialExecute(
      TObject *Sender)
{
    double Val = 0;
    double V2 = Start;
    /*
    if( HorizontalMirrorMode->Checked == true )
    {
     	for(int n = 0; n < 32; n++)
    	{

			if(FlipHorizontalBox->Checked == true)
            {
            	ForceProfile[63-n] = (int)((Val*Height)+VerticalBias);
            }
        	else ForceProfile[n] = (int)((Val*Height)+VerticalBias);
            Val++;
        	Val = Val*Freq;
    	}
        int x = 31;
        for(int n = 32; n < 64; n++)
    	{
        	ForceProfile[n] = ForceProfile[x];
            x--;
    	}
    }
    else
    {
		for(int n = 0; n < 64; n++)
    	{

			if(FlipHorizontalBox->Checked == true) ForceProfile[63-n] = (int)((Val*Height)+VerticalBias);
        	else ForceProfile[n] = (int)((Val*Height)+VerticalBias);
            Val++;
            Val = Val*Freq;
    	}
    } */
}
//---------------------------------------------------------------------------
void __fastcall TProfileGeneratorForm::TanhClickExecute(TObject *Sender)
{
	SineFreqEdit->Text = TanhFreq;
    SinHeightEdit->Text = TanhHeight;
    VBiasEdit->Text = TanhVBias;
    SinStartEdit->Text = TanhHBias-480;
    DeadBandEdit->Text = TanDB;
    RegenerateFunction->Execute();

}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::VBiasUp16ButtonClick(
      TObject *Sender)
{

    int Val = VBiasEdit->Text.ToInt();
    Val += 16;
    VBiasEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::VBiasDown16ButtonClick(
      TObject *Sender)
{
	int Val = VBiasEdit->Text.ToInt();
    Val -= 16;
    VBiasEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::SinClickExecute(TObject *Sender)
{
    SineFreqEdit->Text = SinFreq;
    SinHeightEdit->Text = SinHeight;
    VBiasEdit->Text = SinVBias;
    SinStartEdit->Text = SinHBias-480;
    DeadBandEdit->Text = SinDB;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::FreqDown1ButtonClick(
      TObject *Sender)
{
    double Val = SineFreqEdit->Text.ToDouble();
    Val -= 0.1;
    SineFreqEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::FreqDownButtonClick(TObject *Sender)
{
	double Val = SineFreqEdit->Text.ToDouble();
    Val -= 0.01;
    SineFreqEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::FreqUpButtonClick(TObject *Sender)
{

	double Val = SineFreqEdit->Text.ToDouble();
    Val += 0.01;
    SineFreqEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::FreqUp1ButtonClick(TObject *Sender)
{
	double Val = SineFreqEdit->Text.ToDouble();
    Val += 0.1;
    SineFreqEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::HeightUp16ButtonClick(
      TObject *Sender)
{
	double Val = SinHeightEdit->Text.ToDouble();
    Val += 16;
    SinHeightEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::HeightUp1ButtonClick(
      TObject *Sender)
{
	double Val = SinHeightEdit->Text.ToDouble();
    Val += 1;
    SinHeightEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::HeightDown1ButtonClick(
      TObject *Sender)
{
	double Val = SinHeightEdit->Text.ToDouble();
    Val -=1;
    SinHeightEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TProfileGeneratorForm::HeightDown16ButtonClick(
      TObject *Sender)
{
	double Val = SinHeightEdit->Text.ToDouble();
    Val -=16;
    SinHeightEdit->Text = Val;
    RegenerateFunction->Execute();
}
//---------------------------------------------------------------------------

