// a multifunction GA

//#include "general.h"
#include "ProfileDefines.h"

using namespace std;

class ProObj
{
public:
    	ProObj();
        ~ProObj();
        void SetFValue(int Value, int Position);
        void SetPDampValue(int Value, int Position);
        void SetNDampValue(int Value, int Position);
        int GetFValue(int Position);
        double GetNormalisedFValue(int Position);
        double GetNormalisedPDamp(int Position);
        double GetNormalisedNDamp(int Position);
        double GetNormalisedFinalForce(int Angle, int Velocity);
        byte GetFVauleByte(int Index, bool Offset);
        byte GetPDampVauleByte(int Index);
        byte GetNDampVauleByte(int Index);
        byte GetSInt16VariableByte(int Index, bool Offset);
        byte GetInt8VariableByte(int Index);
        byte GetSInt16PointerByte(int Index);
        byte GetInt8PointerByte(int Index);

        void DrawForceGraph();
        void DrawForceSurface(int ColorDrawingMode);
        TColor GetForceVelocityColor(int AAngle, int AVelocity, int ColorMode);
        int GetGraphXFromAngle(int Angle);
        int GetSurfaceXFromAngle(int Angle);
        int GetSurfaceYFromVelocity(int Velocity);

        void SetAngleTraceValue(int Value, int Position);
        void SetAngleVelTraceValue(int Value, int Position);
        int GetAngleTraceValue(int Position);
        int GetAngleVelTraceValue(int Position);

        int ForceTable[64];
        int PDamptable[64];
        int NDamptable[64];

        int SInt16Variables[32];
        int Int8Variables[32];
        int SInt16Pointers[64];
        int Int8Pointers[64];

        int MutatedProfileNumber;
        int RecvProfileNumber;
        int RecvProfileCopyId;
        int *AngleTrace;
        int *AngleVelTrace;
        int MaxTraceIndex, MaxRecTraceIndex;
        int *ForceMutation, *PdampMutation, *NdampMutation;
        int zone0Cnt, zone1Cnt, zone2Cnt, zone3Cnt, profileScore, actuatorIterationCnt, mutationRange, avgTVZtransitionDist;

        Graphics::TBitmap *ProfileGraph;
        Graphics::TBitmap *ForceSurface;
private:
        TColor GetColour(int RedComponent, int GreenComponent, int BlueComponent);
        int MaxForceValue;
        int MaxDampVal;

        double XStart, XEnd, YStart, YEnd;
        double XScaling, YScaling;
        double XCentre, YCentre;
        double GraphAngleScale, SurfaceAngleScale;
        double VelocityScale;
};


// function declarations

ProObj::ProObj()
{
      MaxForceValue = 4096;
      MaxDampVal = 127;
      MutatedProfileNumber = 0;
      MaxTraceIndex = 100;
      MaxRecTraceIndex = 0;
      AngleTrace = new int[MaxTraceIndex];
      AngleVelTrace = new int[MaxTraceIndex];
      ForceMutation = new int[64];
      PdampMutation = new int[64];
      NdampMutation = new int[64];

      for(int n = 0; n < 64; n++)
      {
          ForceTable[n] = 0;
          PDamptable[n] = 0;
          NDamptable[n] = 0;
          SInt16Pointers[n] = 0;
        	Int8Pointers[n] = 0;
      }

      for(int n = 0; n < 32; n++)
      {
         SInt16Variables[n] = 0;
        Int8Variables[n] = 0;

      }
      ProfileGraph = new Graphics::TBitmap();
      ProfileGraph->Height = 600;
      ProfileGraph->Width = 800;
      ForceSurface = new Graphics::TBitmap();
      ForceSurface->Height = 600;
      ForceSurface->Width = 800;
}


ProObj::~ProObj()
{
    delete ProfileGraph;
    delete ForceSurface;

}

void ProObj::SetAngleTraceValue(int Value, int Position)
{
        if( Position < 0 || Position > (MaxTraceIndex-1) )
          return;

        AngleTrace[Position] = Value;
}

void ProObj::SetAngleVelTraceValue(int Value, int Position)
{
        if( Position < 0 || Position > (MaxTraceIndex-1) )
          return;

        AngleVelTrace[Position] = Value;
}

void ProObj::SetFValue(int Value, int Position)
{
        if( Position < 0 || Position > 63 ) return;

        if(Value > MaxForceValue)
                ForceTable[Position] = MaxForceValue;

        else if (Value < -MaxForceValue) ForceTable[Position] = -MaxForceValue;

        else  ForceTable[Position] = Value;
}

void ProObj::SetPDampValue(int Value, int Position)
{
        if( Position < 0 || Position > 63 ) return;

        if(Value > MaxDampVal) PDamptable[Position] = MaxDampVal;

        else if (Value < -(MaxDampVal+1)) PDamptable[Position] = -(MaxDampVal+1);

        else  PDamptable[Position] = Value;
}

 void ProObj::SetNDampValue(int Value, int Position)
{
        if( Position < 0 || Position > 63 ) return;

        if(Value > MaxDampVal) NDamptable[Position] = MaxDampVal;

        else if (Value < -(MaxDampVal+1)) NDamptable[Position] = -(MaxDampVal+1);

        else  NDamptable[Position] = Value;
}

int ProObj::GetAngleTraceValue(int Position)
{
        if(Position < 0 || Position > (MaxTraceIndex-1)) return 0;
        return AngleTrace[Position];
}

int ProObj::GetAngleVelTraceValue(int Position)
{
        if(Position < 0 || Position > (MaxTraceIndex-1)) return 0;
        return AngleVelTrace[Position];
}

int ProObj::GetFValue(int Position)
{
        if(Position < 0 || Position > 63) return 0;
        return ForceTable[Position];
}

double ProObj::GetNormalisedFValue(int Position)
{
        if(Position < 0 || Position > 63) return 0;
        return (double)ForceTable[Position]/2048;
}

double ProObj::GetNormalisedPDamp(int Position)
{
	if(Position < 0 || Position > 63) return 0;
	return (double)PDamptable[Position]/64;
}

double ProObj::GetNormalisedNDamp(int Position)
{
   if(Position < 0 || Position > 63) return 0;
   return (double)NDamptable[Position]/64;

}

double ProObj::GetNormalisedFinalForce(int Angle, int Velocity)
{
	double FinalForce;
    double ProfileForce;
    double PDamping;
    double NDamping;
    double RealV;
    int Index = 0;

    Index = Angle;
    if(Index > 63)  Index = 63;
    if(Index < 0) Index = 0;
    ProfileForce = GetNormalisedFValue(Index);
    PDamping = GetNormalisedPDamp(Index);
    NDamping = GetNormalisedNDamp(Index);
    RealV = ((double)Velocity) / 512;
    if(Velocity < 0)
    {
    	FinalForce = ProfileForce - ( RealV * NDamping );
    }
    else if(Velocity > 0)
    {
    	FinalForce = ProfileForce - ( RealV * PDamping );
    }
    else FinalForce = ProfileForce;
    //FinalForce += VBias;
    if(FinalForce > 1.0) FinalForce = 1.0;
    if(FinalForce < -1.0) FinalForce = -1.0;
    return FinalForce;
}

byte ProObj::GetFVauleByte(int Index, bool Offset)
{
        //returns the byte value of the force from the selected index
        //offset determines the byte - 0 = LSb, 1 = MSb
        //numbers are transmitted as unsigned 16bit numbers
        //the zero value is 32767
        int BitMask;
        int TempVal;
        byte ReturnVal;
        if(Index < 0 || Index > 63) return 0;
        TempVal = ForceTable[Index];

        if(TempVal < -32767) TempVal = -32767;
        if(TempVal > 32768) TempVal = 32768;
        TempVal += 32767;
        BitMask =  0xFF00;
        //mask out the lower 8 bits
        if(Offset == 1)
        {
               TempVal >>=8; //shift out the lower bits
               ReturnVal = (byte)TempVal;
               return ReturnVal;
        }


        else if(Offset == 0)
        {      //mask out the upper 8 bits
                BitMask =  0x00FF;
               TempVal = TempVal & BitMask; //Bitwise AND to remove upper 8 bits
               ReturnVal = (byte)TempVal;
               return ReturnVal;
        }
        return 0;
}

byte ProObj::GetPDampVauleByte(int Index)
{
        //returns the byte value of the force from the selected index
        int TempVal;
        byte ReturnVal;
        if(Index < 0 || Index > 63) return 0;

        TempVal = PDamptable[Index];
        if(TempVal < -128) TempVal = -128;
        if(TempVal > 127) TempVal = 127;

        //TempVal += 128;
        ReturnVal = (byte)TempVal;
        return ReturnVal;

}

byte ProObj::GetNDampVauleByte(int Index)
{
        //returns the byte value of the force from the selected index
        int TempVal;
        byte ReturnVal;
        if(Index < 0 || Index > 63) return 0;

        TempVal = NDamptable[Index];
        if(TempVal < -128) TempVal = -128;
        if(TempVal > 127) TempVal = 127;

        //TempVal += 128;
        ReturnVal = (byte)TempVal;
        return ReturnVal;

}

byte ProObj::GetSInt16VariableByte(int Index, bool Offset)
{
        //returns the byte value of the force from the selected index
        //offset determines the byte - 0 = LSb, 1 = MSb
        //numbers are transmitted as unsigned 16bit numbers
        //the zero value is 32767
        int BitMask;
        int TempVal;
        byte ReturnVal;
        if(Index < 0 || Index > 31) return 0;
        TempVal = SInt16Variables[Index];

        if(TempVal < -32767) TempVal = -32767;
        if(TempVal > 32768) TempVal = 32768;
        TempVal += 32767;
        BitMask =  0xFF00;
        //mask out the lower 8 bits
        if(Offset == 1)
        {
               TempVal >>=8; //shift out the lower bits
               ReturnVal = (byte)TempVal;
               return ReturnVal;
        }


        else if(Offset == 0)
        {      //mask out the upper 8 bits
                BitMask =  0x00FF;
               TempVal = TempVal & BitMask; //Bitwise AND to remove upper 8 bits
               ReturnVal = (byte)TempVal;
               return ReturnVal;
        }
        return 0;
}

byte ProObj::GetInt8VariableByte(int Index)
{
        //returns the byte value of the force from the selected index
        int TempVal;
        byte ReturnVal;
        if(Index < 0 || Index > 31) return 0;

        TempVal = Int8Variables[Index];
        if(TempVal < -0) TempVal = -0;
        if(TempVal > 255) TempVal = 255;
        ReturnVal = (byte)TempVal;
        return ReturnVal;

}


byte ProObj::GetSInt16PointerByte(int Index)
{

        int TempVal;
        byte ReturnVal;
        if(Index < 0 || Index > 63) return 0;

        TempVal = SInt16Pointers[Index];
        if(TempVal < 0) TempVal = 0;
        if(TempVal > 255) TempVal = 255;

        ReturnVal = (byte)TempVal;
        return ReturnVal;
}

byte ProObj::GetInt8PointerByte(int Index)
{
        int TempVal;
        byte ReturnVal;
        if(Index < 0 || Index > 63) return 0;

        TempVal = Int8Pointers[Index];
        if(TempVal < 0) TempVal = 0;
        if(TempVal > 255) TempVal = 255;
        ReturnVal = (byte)TempVal;
        return ReturnVal;

}


void ProObj::DrawForceGraph()
{
    //Draws a graph representing the profile system with thresholds and damping
    /*
    int XStart, XEnd, YStart, YEnd;
    int XScaling, YScaling;
    int XCentre, YCentre
    */
    double FVal, DVal;
    double YFscale;
    double YDscale;

    double XPos = 0;

    double XBorderOverlap;
    double YBorderOverlap;
    XCentre = ProfileGraph->Width/2;
    YCentre = ProfileGraph->Height/2;
    XScaling = ProfileGraph->Width/72;
    YScaling = ProfileGraph->Height/96;
    XStart = XCentre-(XScaling*32);
    XEnd = XCentre+(XScaling*32);
    YStart = YCentre-(YScaling*32);
    YEnd = YCentre+(YScaling*32);

    XBorderOverlap = XScaling*3;
    YBorderOverlap = YScaling*3;

    YFscale = (YEnd-YStart)/4096;
    YDscale = (YEnd-YStart)/256;
    GraphAngleScale = (XEnd-XStart)/1024;
    ProfileGraph->Canvas->Pen->Width = 1;
    //clear the image with light grey
    ProfileGraph->Canvas->Brush->Color = clWhite;
    ProfileGraph->Canvas->Pen->Color = clBlack;
    ProfileGraph->Canvas->Rectangle(0,0,ProfileGraph->Width, ProfileGraph->Height);
    //Now fill the graph area with white
    //ProfileGraph->Canvas->Brush->Color = clWhite;
    //ProfileGraph->Canvas->Pen->Color = clWhite;
    //ProfileGraph->Canvas->Rectangle(XStart, YStart ,XEnd-XScaling, YEnd);


    //Draw some graph lines
    ProfileGraph->Canvas->Pen->Color = clSilver;
    ProfileGraph->Canvas->MoveTo(XStart-XBorderOverlap, YCentre);
    ProfileGraph->Canvas->LineTo(XEnd+XBorderOverlap, YCentre);

    ProfileGraph->Canvas->MoveTo(XStart-XBorderOverlap, YStart);
    ProfileGraph->Canvas->LineTo(XEnd+XBorderOverlap, YStart);

    ProfileGraph->Canvas->MoveTo(XStart-XBorderOverlap, YEnd);
    ProfileGraph->Canvas->LineTo(XEnd+XBorderOverlap, YEnd);

    ProfileGraph->Canvas->MoveTo(XStart, YStart-XBorderOverlap);
    ProfileGraph->Canvas->LineTo(XStart, YEnd+XBorderOverlap);

    ProfileGraph->Canvas->MoveTo(XEnd-XScaling, YStart-XBorderOverlap);
    ProfileGraph->Canvas->LineTo(XEnd-XScaling, YEnd+XBorderOverlap);
    //--------------------
    //Draw the PDamping Profile
    ProfileGraph->Canvas->Pen->Color = clOlive;
    XPos = XStart;
    DVal = YCentre-((double)PDamptable[0] * YDscale);
    ProfileGraph->Canvas->MoveTo(XPos, DVal);
    for(int n = 1; n < 64; n++)
    {
        //draw the PDamp graph
        XPos += XScaling;
        DVal = YCentre-((double)PDamptable[n]*YDscale);
        ProfileGraph->Canvas->LineTo(XPos, DVal);

    }

     //--------------------
    //Draw the Force Profile
    ProfileGraph->Canvas->Pen->Color = clRed;
    XPos = XStart;
    FVal = YCentre-((double)ForceTable[0] * YFscale);
    ProfileGraph->Canvas->MoveTo(XPos, FVal);
    for(int n = 1; n < 64; n++)
    {
        //draw the force graph
        XPos += XScaling;
        FVal = YCentre-((double)ForceTable[n]*YFscale);
        ProfileGraph->Canvas->LineTo(XPos, FVal);

    }

    //--------------------
    //Draw the NDamping Profile
    ProfileGraph->Canvas->Pen->Color = clBlue;
    XPos = XStart;
    DVal = YCentre-((double)NDamptable[0] * YDscale);
    ProfileGraph->Canvas->MoveTo(XPos, DVal);
    for(int n = 1; n < 64; n++)
    {
        //draw the PDamp graph
        XPos += XScaling;
        DVal = YCentre-((double)NDamptable[n]*YDscale);
        ProfileGraph->Canvas->LineTo(XPos, DVal);

    }

    //Now draw the EQP
    double EQPoint;
    ProfileGraph->Canvas->Pen->Color = clPurple;
    EQPoint =  XCentre + ((double)SInt16Variables[_EQAngle]*GraphAngleScale);

    ProfileGraph->Canvas->MoveTo(EQPoint, YStart);
    ProfileGraph->Canvas->LineTo(EQPoint, YEnd);
    //Now draw a triangle
    ProfileGraph->Canvas->LineTo(EQPoint+4, YEnd+10);
    ProfileGraph->Canvas->LineTo(EQPoint-4, YEnd+10);
    ProfileGraph->Canvas->LineTo(EQPoint, YEnd);

    //-------------------------------
    //Now draw some thresholds

    int IndexVal = _Threshold1Input_ptr;
    int PDefaultVal = _PT1Default;
    int NDefaultVal = _NT1Default;
    int ValuePtr = _PT1Value_ptr;
    int EnablePtr = _PT1Enabled_ptr;

    int PT1, NT1;
    TColor PT1Col, NT1Col;


    for(int n = 0; n < 4; n++)
    {
            //pick the colors for the threshold enable states
        if(Int8Pointers[EnablePtr] == _GlobalThresholdEnabled || Int8Pointers[EnablePtr] == _GlobalDefaultTrue) PT1Col = clBlue;
        else PT1Col = clDkGray;
        if(Int8Pointers[EnablePtr+1] == _GlobalThresholdEnabled || Int8Pointers[EnablePtr+1] == _GlobalDefaultTrue) NT1Col = clGreen;
        else NT1Col = clDkGray;

        if( SInt16Pointers[IndexVal] == _Angle || SInt16Pointers[IndexVal] == _NOTAngle )
        {
            PT1 = XCentre + ( SInt16Variables[PDefaultVal] * GraphAngleScale );
            NT1 = XCentre + (SInt16Variables[NDefaultVal] * GraphAngleScale );

            ProfileGraph->Canvas->Pen->Width = 2;

            ProfileGraph->Canvas->Pen->Color = PT1Col;
            ProfileGraph->Canvas->MoveTo(PT1, YStart);
            ProfileGraph->Canvas->LineTo(PT1, YEnd+10);
            ProfileGraph->Canvas->LineTo(PT1+10, YEnd+10);
            ProfileGraph->Canvas->LineTo(PT1, YEnd);

            ProfileGraph->Canvas->Pen->Color = NT1Col;
            ProfileGraph->Canvas->MoveTo(NT1, YStart);
            ProfileGraph->Canvas->LineTo(NT1, YEnd+10);
            ProfileGraph->Canvas->LineTo(NT1-10, YEnd+10);
            ProfileGraph->Canvas->LineTo(NT1, YEnd);
        }

        //Now velocity thresholds

        if(  SInt16Pointers[IndexVal] == _FTarget || SInt16Pointers[IndexVal] == _MeasuredForce )
        {
            PT1 = YCentre - ( SInt16Variables[PDefaultVal] * YFscale );
            NT1 = YCentre - (SInt16Variables[NDefaultVal] * YFscale );
            ProfileGraph->Canvas->Pen->Width = 2;

            ProfileGraph->Canvas->Pen->Color = PT1Col;
            ProfileGraph->Canvas->MoveTo(XStart, PT1);
            ProfileGraph->Canvas->LineTo(XEnd+20, PT1);
            ProfileGraph->Canvas->LineTo(XEnd+20, PT1-10);
            ProfileGraph->Canvas->LineTo(XEnd, PT1);
            ProfileGraph->Canvas->Pen->Color = NT1Col;
            ProfileGraph->Canvas->MoveTo(XStart, NT1);
            ProfileGraph->Canvas->LineTo(XEnd+20, NT1);
            ProfileGraph->Canvas->LineTo(XEnd+20, NT1+10);
            ProfileGraph->Canvas->LineTo(XEnd, NT1);

        }
        IndexVal++;
        PDefaultVal+=2;
        NDefaultVal+=2;
        ValuePtr+=2;
        EnablePtr+=2;
    }
}


 //-------------------------------------------
void ProObj::DrawForceSurface(int ColorDrawingMode)
{
    //Draws a graph representing the profile system with thresholds and damping
    /*
    int XStart, XEnd, YStart, YEnd;
    int XScaling, YScaling;
    int XCentre, YCentre
    */
    double FVal, DVal;
    double YFscale;
    double YDscale;

    double XPos = 0;
    double YPos = 0;

    double XBorderOverlap;
    double YBorderOverlap;

    double HalfXStep, HalfYStep;

    XCentre = ForceSurface->Width/2;
    YCentre = ForceSurface->Height/2;
    if( ForceSurface->Height <= ForceSurface->Width )
    {
        YScaling = ForceSurface->Height/70;
        XScaling = YScaling;
    }
    else
    {
        XScaling = ForceSurface->Width/70;
        YScaling = XScaling;
    }
    XStart = XCentre-(XScaling*32);
    XEnd = XCentre+(XScaling*32);
    YStart = YCentre-(YScaling*32);
    YEnd = YCentre+(YScaling*32);

    HalfXStep = XScaling/2;
    HalfYStep = YScaling/2;

    XBorderOverlap = XScaling*3;
    YBorderOverlap = YScaling*3;

    YFscale = (YEnd-YStart)/4096;
    YDscale = (YEnd-YStart)/256;
    SurfaceAngleScale = (XEnd-XStart)/1024;
    VelocityScale = (YEnd-YStart)/1024;
    ForceSurface->Canvas->Pen->Width = 1;
    //clear the image with light grey
    ForceSurface->Canvas->Brush->Color = clWhite;
    ForceSurface->Canvas->Pen->Color = clBlack;
    ForceSurface->Canvas->Rectangle(0,0,ForceSurface->Width, ForceSurface->Height);
    //Now fill the graph area with white
    //ProfileGraph->Canvas->Brush->Color = clWhite;
    //ProfileGraph->Canvas->Pen->Color = clWhite;
    //ProfileGraph->Canvas->Rectangle(XStart, YStart ,XEnd-XScaling, YEnd);


    //--------------------
    TColor SurfaceColor;
    XPos = XStart;
    YPos = YEnd;
    for(int vel = 0; vel < 65; vel++)
    {
        for(int ang = 0; ang < 64; ang++)
        {
            SurfaceColor = GetForceVelocityColor(ang, vel-32, ColorDrawingMode);
            ForceSurface->Canvas->Brush->Color = SurfaceColor;
            ForceSurface->Canvas->Pen->Color = SurfaceColor;
            ForceSurface->Canvas->Rectangle(XPos-HalfXStep, YPos+HalfYStep, XPos+HalfXStep, YPos-HalfYStep);
            XPos += XScaling;
        }
        XPos = XStart;
        YPos -= YScaling;
    }

    //Draw some graph lines on top of the surface

    ForceSurface->Canvas->Pen->Color = clSilver;
    ForceSurface->Canvas->MoveTo(XStart-XBorderOverlap, YCentre);
    ForceSurface->Canvas->LineTo(XEnd+XBorderOverlap, YCentre);

    ForceSurface->Canvas->MoveTo(XStart-XBorderOverlap, YStart-HalfYStep);
    ForceSurface->Canvas->LineTo(XEnd+XBorderOverlap, YStart-HalfYStep);

    ForceSurface->Canvas->MoveTo(XStart-XBorderOverlap, YEnd+HalfYStep);
    ForceSurface->Canvas->LineTo(XEnd+XBorderOverlap, YEnd+HalfYStep);

    ForceSurface->Canvas->MoveTo(XStart-HalfXStep, YStart-XBorderOverlap);
    ForceSurface->Canvas->LineTo(XStart-HalfXStep, YEnd+XBorderOverlap);

    ForceSurface->Canvas->MoveTo(XEnd-HalfXStep, YStart-XBorderOverlap);
    ForceSurface->Canvas->LineTo(XEnd-HalfXStep, YEnd+XBorderOverlap);


    //Now draw the EQP
    double EQPoint;
    ForceSurface->Canvas->Pen->Color = clPurple;
    EQPoint =  XCentre + ((double)SInt16Variables[_EQAngle]*SurfaceAngleScale);

    ForceSurface->Canvas->MoveTo(EQPoint, YStart);
    ForceSurface->Canvas->LineTo(EQPoint, YEnd);
    //Now draw a triangle
    ForceSurface->Canvas->LineTo(EQPoint+4, YEnd+10);
    ForceSurface->Canvas->LineTo(EQPoint-4, YEnd+10);
    ForceSurface->Canvas->LineTo(EQPoint, YEnd);

    //-------------------------------
    //Now draw some thresholds

    int IndexVal = _Threshold1Input_ptr;
    int PDefaultVal = _PT1Default;
    int NDefaultVal = _NT1Default;
    int ValuePtr = _PT1Value_ptr;
    int EnablePtr = _PT1Enabled_ptr;

    int PT1, NT1;
    TColor PT1Col, NT1Col;


    for(int n = 0; n < 4; n++)
    {
            //pick the colors for the threshold enable states
        if(Int8Pointers[EnablePtr] == _GlobalThresholdEnabled || Int8Pointers[EnablePtr] == _GlobalDefaultTrue) PT1Col = clBlue;
        else PT1Col = clDkGray;
        if(Int8Pointers[EnablePtr+1] == _GlobalThresholdEnabled || Int8Pointers[EnablePtr+1] == _GlobalDefaultTrue) NT1Col = clGreen;
        else NT1Col = clDkGray;

        //First Angle Thresholds
        if( SInt16Pointers[IndexVal] == _Angle || SInt16Pointers[IndexVal] == _NOTAngle )
        {
            PT1 = XCentre + ( SInt16Variables[PDefaultVal] * SurfaceAngleScale );
            NT1 = XCentre + (SInt16Variables[NDefaultVal] * SurfaceAngleScale );

            ForceSurface->Canvas->Pen->Width = 2;

            ForceSurface->Canvas->Pen->Color = PT1Col;
            ForceSurface->Canvas->MoveTo(PT1, YStart);
            ForceSurface->Canvas->LineTo(PT1, YEnd+10);
            ForceSurface->Canvas->LineTo(PT1+10, YEnd+10);
            ForceSurface->Canvas->LineTo(PT1, YEnd);

            ForceSurface->Canvas->Pen->Color = NT1Col;
            ForceSurface->Canvas->MoveTo(NT1, YStart);
            ForceSurface->Canvas->LineTo(NT1, YEnd+10);
            ForceSurface->Canvas->LineTo(NT1-10, YEnd+10);
            ForceSurface->Canvas->LineTo(NT1, YEnd);
        }

        //Now velocity thresholds
        if(  SInt16Pointers[IndexVal] == _AngleVelocity || SInt16Pointers[IndexVal] == _NOTAngleVelocity )
        {
            PT1 = YCentre - ( SInt16Variables[PDefaultVal] * VelocityScale );
            NT1 = YCentre - ( SInt16Variables[NDefaultVal] * VelocityScale );

            ForceSurface->Canvas->Pen->Color = PT1Col;
            ForceSurface->Canvas->MoveTo(XStart, PT1);
            ForceSurface->Canvas->LineTo(XEnd+20, PT1);
            ForceSurface->Canvas->LineTo(XEnd+20, PT1-10);
            ForceSurface->Canvas->LineTo(XEnd, PT1);
            ForceSurface->Canvas->Pen->Color = NT1Col;
            ForceSurface->Canvas->MoveTo(XStart, NT1);
            ForceSurface->Canvas->LineTo(XEnd+20, NT1);
            ForceSurface->Canvas->LineTo(XEnd+20, NT1+10);
            ForceSurface->Canvas->LineTo(XEnd, NT1);

        }
        IndexVal++;
        PDefaultVal+=2;
        NDefaultVal+=2;
        ValuePtr+=2;
        EnablePtr+=2;
    }
}

//---------------------------------------------------------------------------
TColor ProObj::GetForceVelocityColor(int AAngle, int AVelocity, int ColorMode)
{

    //Takes angles from 0-63, velocity from -32 to 32
	double FinalForce;
    double ProfileForce;
    double PDamping;
    double NDamping;
    int TempInt;
    double RealV;

    int RedX = 0, GreenX = 0, BlueX = 0;
    int Positive, Negative;
    TColor ReturnVal;

    int Index = 0;
    Index = AAngle;
    if(Index > 63)  Index = 63;
    if(Index < 0) Index = 0;
    ProfileForce = (double)ForceTable[Index];
    ProfileForce /= 2048;
    PDamping = (double)PDamptable[Index];
    PDamping /= 64;
    NDamping = (double)NDamptable[Index];
    NDamping /= 64;
    RealV = ((double)AVelocity) / 32;

    //RealV /= 32;
    if(AVelocity < 0)
    {
    	FinalForce = ProfileForce - ( RealV * NDamping );
    }
    else if(AVelocity > 0)
    {
    	FinalForce = ProfileForce - ( RealV * PDamping );
    }
    else FinalForce = ProfileForce;
    //FinalForce += VBias;
    //if(FinalForce > 1.0) FinalForce = 1.0;
    //if(FinalForce < -1.0) FinalForce = -1.0;
    switch (ColorMode)
    {
    case 0:
        if(FinalForce > 0) BlueX = (int)(FinalForce*255);
        if(FinalForce < 0) RedX = (int)(FinalForce*255);
        return GetColour(-RedX, GreenX, BlueX);
        break;
    case 1:
        RedX = (int)((FinalForce+1.0)*128);
        return GetColour(RedX, RedX, RedX);
        break;
    default:
        if(FinalForce > 0) BlueX = (int)(FinalForce*255);
        if(FinalForce < 0) RedX = (int)(FinalForce*255);
        return GetColour(-RedX, GreenX, BlueX);
        break;
    }
}
//---------------------------------------------------------------------------

TColor ProObj::GetColour(int RedComponent, int GreenComponent, int BlueComponent)
{
	if(RedComponent > 255) RedComponent = 255;
    if(GreenComponent > 255) GreenComponent = 255;
    if(BlueComponent > 255) BlueComponent = 255;
    if(RedComponent < 0) RedComponent = 0;
    if(GreenComponent < 0) GreenComponent = 0;
    if(BlueComponent < 0) BlueComponent = 0;
	int rcol, gcol, bcol, col;
	rcol = RedComponent;
    gcol = GreenComponent;
    gcol <<= 8;
    bcol = BlueComponent;
    bcol <<= 16;
    col = rcol;
    col  = col|gcol;
    col = col|bcol;
    return (TColor)col;
}
int ProObj::GetGraphXFromAngle(int Angle)
{
    //returns the x pos on the image for an actuator angle on a profile graph
    return XCentre + (Angle*GraphAngleScale);

}
int ProObj::GetSurfaceXFromAngle(int Angle)
{
    //returns the x pos on the image for an actuator angle on a force surface
    return XCentre + (Angle*SurfaceAngleScale);


}

int ProObj::GetSurfaceYFromVelocity(int Velocity)
{
    //returns the Y pos on the image for an actuator velocity on a force surface
    return YCentre - (Velocity*VelocityScale);


}











//==================================================================================================

//==================================================================================================

//==================================================================================================

//==================================================================================================

//Actuator Object - contains all the settings that apply to the whole actuator (Node No etc)
class ActObj
{
public:
	ActObj();
	~ActObj();

	byte GetRS232NodeNumberByte();
    void SetRS232NodeNumber(int Node);
    byte GetCANNodeNumberByte();
    void SetCANNodeNumber(int Node);
    byte GetStartingProfile();
    void SetStartingProfile(int Profile);
    byte GetStartingMode();
    void SetStartingMode(int Mode);
    byte GetPassAlongStatus();
    void SetPassAlongStatus(int PassStatus);
    byte GetSettingsByte(int Index);
    void SetSettings(int Value, int Index);
    int GetDelayPeriod();
    void SetDelayPeriod(unsigned int Delay);
private:
     int RS232Node;
     int CANNode;
     int StartingProfile;
     int StartingMode;
     int PassAlongCommands;
     int DelayValue;
};

ActObj::ActObj()
{
	RS232Node = 1;
    CANNode = 1;
    StartingProfile = 0;
    StartingMode = 0;
    PassAlongCommands = 0;
    DelayValue=0;
}


ActObj::~ActObj()
{

}

byte ActObj::GetRS232NodeNumberByte()
{
	return (byte)RS232Node;
}

void ActObj::SetRS232NodeNumber(int Node)
{
	RS232Node = Node;
    if(RS232Node == 0) RS232Node = 1;
    if(RS232Node >255 ) RS232Node = 255;
}

byte ActObj::GetCANNodeNumberByte()
{
    return (byte)CANNode;
}

void ActObj::SetCANNodeNumber(int Node)
{
	CANNode = Node;
	if(CANNode == 0) CANNode = 1;
    if(CANNode >255 ) CANNode = 255;
}

byte ActObj::GetStartingProfile()
{
     return (byte)StartingProfile;
}

void ActObj::SetStartingProfile(int Profile)
{
	StartingProfile = Profile;
	if(StartingProfile < 0) StartingProfile = 0;
    if(StartingProfile >7 ) StartingProfile = 7;
}

byte ActObj::GetStartingMode()
{
    return (byte)StartingMode;
}

void ActObj::SetStartingMode(int Mode)
{
    StartingMode = Mode;
	if(StartingMode < 0) StartingMode = 0;
    if(StartingMode > 3 ) StartingMode = 1;
}

byte ActObj::GetPassAlongStatus()
{
    return (Byte)PassAlongCommands;
}

void ActObj::SetPassAlongStatus(int PassStatus)
{
    if(PassStatus == 0) PassAlongCommands = 0;
    else  PassAlongCommands = 1;
}


void ActObj::SetDelayPeriod(unsigned int Delay)
{
        if(Delay>=0)
                DelayValue=Delay;
}

int ActObj::GetDelayPeriod()
{
        return DelayValue;
}

byte ActObj::GetSettingsByte(int Index)
{

	switch (Index)
    {
    case 0:
    	return (Byte)RS232Node;
    case 1:
    	return (Byte)CANNode;
    case 2:
    	return (Byte)StartingProfile;
    case 3:
    	return (Byte)StartingMode;
    case 4:
    	return (Byte)PassAlongCommands;
    case 5:
        return (Byte)DelayValue;
    case 6:
        return (Byte)(DelayValue>>8);
    default:
    	return (Byte)0;
    }
}

void ActObj::SetSettings(int Value, int Index)
{

	switch (Index)
    {
    case 0:
    	RS232Node = Value;
        break;
    case 1:
    	CANNode = Value;
        break;
    case 2:
    	StartingProfile = Value;
        break;
    case 3:
    	StartingMode = Value;
        break;
    case 4:
    	PassAlongCommands = Value;
        break;
    default:
    	return;
    }
}
