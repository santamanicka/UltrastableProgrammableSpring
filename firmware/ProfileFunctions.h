//#include "D:\PIC_C_Projects\PROGRAMMABLE SPRING\NewAngleControl\Multipliers.h"
//#include "D:\PIC_C_Projects\PROGRAMMABLE SPRING\NewAngleControl\SerialFunctions.h"
void IterateProfile(void);

signed int16 ModifyAngle(int8 ProfileToModify);
signed int16 GetSummedProfileForce();
signed int8 LookUpInterpolatedDampingValue(signed int8 LowerIndexVal, signed int8 UpperIndexVal
                                            , signed int16 FractionVal);
                                            
signed int16 CalculateProfileForce(int8 ProfileToUse, signed int16 SAngle);
void CheckThresholds(int8 CurrentPro);
void CheckExIn(int8 CurrentPro);
void SetSummedFlags(int8 CurrentPro);
void SetExOut(int8 CurrentPro);
void UpdateInterComms(int8 CurrentPro);
void SendSerialDataA(int8 CurrentPro);
void SendSerialDataB(int8 CurrentPro);
int8 GetCurrentProfile(int8 CurrentPro);

void SetupProfileOscillator(int8 CurrentPro, int8 UpdateStepSize, int8 Prescaler
                                    , signed int16 Maxval, signed int16 MinVal
                                    , signed int16 StartVal, int1 StartDirection);
                                    
void IterateOscillator(int8 CurrentPro);
void CreateDefaultProfile(int8 ProfileToUse);
void CreateDefaultProfile2(int8 ProfileToUse);

signed int16 ReadAD(int8 Port);
void ReadSensors();
void ApplyVelocityCompensation();
void CyclicTestFunction();
void PrintTestData();

//==============================================================================
/*
Make some major changes:
Each profile contains its own angle variables?
each profile can 'see' others angle variables so you can, for example, take the bias for one profile 
from the velocity that another was in when it exited.

Give each profile a global input variable set.  This has a pointer that can point to any other
variable in the whole system and collects those variables with each iteration, ready for the profile to use.
Still need a way of saving the angle?
The current profile can 'collect' the current angle (or modAngle) into its own global buffer
Other profiles can point to this buffer so when you are in a different profile it can get the
previous profiles angle from when it last iterated 

Use this:
signed int16 GlobalVar[PROFILES];//one for each profile
signed int16* GlobalVar_ptr[PROFILES];
All profiles can point to any of the above variables
The pointers for each profile above can point to any system var or any of its own variables
The system only updates the variables for the CURRENT profile
For example Profile1 has its global var pointing to the angle
When profile1 updates it refreshes its global var with the current angle
The system switches to profile2 which has its bias pointing at the global var for profile1
Profile2 updates and refreshes its own global var but takes its bias from profile1's global var which still
contains the old angle as last read by profile1!!!
Now do the same thing with flags

GlobalVar1,2,3,4[PROFILES};
GlobalFlag1,2,3,4[PROFILES};


Changes to the update system

Work out force and apply first then at the end decide if the profile has changed so you load a new profile at the start of the next iteration


*/
//==============================================================================
void IterateProfile(void)
{
    ReadSensors();
    //ModifiedAngle = Angle;
    //ActualAngle = Angle;

    CheckExIn(CurrentProfile );
    //First scale and bias the angle along the horizontal axis
    //shift the angle by a value based on the angle velocity to 'look ahead' to where you ought to be when the force is applied
    //ApplyVelocityCompensation();
/*
first check to see if the current profile is a summed profile
if it is then modify its angle and the profile above
then get a force value for the first profile and the second and sum them
Set the digital and analog outputs for the first profile only - it can take their state from the second if nessacary
if(Summed[CurrentPro] !=0)
{
    ModifiedAngle = ModifyAngle(CurrentPro)
    ModifiedAngle1 = ModifyAngle(CurrentPro+1);
    FinalForce = GetForceValue(ModifiedAngle, CurrentPro) + GetForceValue(ModifiedAngle1, CurrentPro+1);
}

*/
    if( SummedProfile[CurrentProfile] > 0 )
    {
        FTarget = GetSummedProfileForce();
    }
    else
    {
        ModifiedAngle = ModifyAngle(CurrentProfile);
        NOTModifiedAngle = -ModifiedAngle;
          ModifiedAngle_B = ModifiedAngle;
        NOTModifiedAngle_B = -NOTModifiedAngle;
        //work out the force target for the SEA
        FTarget = CalculateProfileForce(CurrentProfile, ModifiedAngle);
        
    }

    


    // Check the status of the motor enable flag and the forcezeroforce flag to see if the motor and SEA need surpression
    if(*MotorEnable_ptr[CurrentProfile] == 0) DisableMotor();
    else EnableMotor();
    if(*ForceControlEnable_ptr[CurrentProfile] == 0) DisableForce();
    else EnableForce();
    

    SetForce(-FTarget);
    //check the thresholds
    CheckThresholds(CurrentProfile);
    //now work out the summed flags
    SetSummedFlags(CurrentProfile);
    
    //Set all the outputs
    SetExOut(CurrentProfile);
    SetDAC(ADOUT1CHANEL, *ADOut1_ptr[ CurrentProfile ] * ADOut1Scaling[ CurrentProfile ]);
    SetDAC(ADOUT2CHANEL, *ADOut2_ptr[ CurrentProfile ] * ADOut2Scaling[ CurrentProfile ]);
    UpdateInterComms(CurrentProfile);
    SendSerialDataA(CurrentProfile);
    SendSerialDataB(CurrentProfile);
    IterateOscillator(CurrentProfile);
    
    //check to see if the current angle causes a profile change
    CurrentProfile = GetCurrentProfile(CurrentProfile);
    //PrintTestData();
}
//==============================================================================
signed int16 ModifyAngle(int8 ProfileToModify)
{
    //first apply the scaling relative to the scaling origin
    //check that the scaling is not zero
    signed int16 HScaling;
    signed int16 AngleOffset;
    signed int16 ModAng;
    /*
    work out a modifying value to add to the angle and all switchpoints
    The scaling can never be zero
    Just hack it - scale the angle so that a small scaling value (eg 0.01) effectively stretches the profile
    */
    HScaling = *HScale_ptr[ ProfileToModify ];
    if(HScaling == 0) HScaling = 1;

    AngleOffset = Angle - EQAngle[ ProfileToModify ];
    
    ModAng = SMul2(AngleOffset, HScaling);
    
    //CANVarIn[ 0 ] = ModAng; 
    //CANVarIn[ 1 ] = SMul2(100, 10);
    //printf("ModAng1 %ld Offset %ld  ", SMul2(AngleOffset, HScaling), AngleOffset );
    //now apply the bias
    ModAng += *HBias_ptr[ ProfileToModify ];

    //ModifiedAngle = Angle + *HBias_ptr[ CurrentProfile ];

    ModAng += EQAngle[ ProfileToModify ];
    //now apply the limits
    if(ModAng > 511)
    {
        ModAng = 511;
    }
    else if(ModAng < -512)
    {
        ModAng = -512;
    }
    return ModAng;
}
//==============================================================================
signed int16 GetSummedProfileForce()
{
    //Make sure the working profile is EVEN
    int8 MasterPro, SlavePro;

    if( ( CurrentProfile & 1 ) > 0)
    {
        SlavePro = CurrentProfile;
        MasterPro = SlavePro-1;
    }
    else
    {
        Masterpro = CurrentProfile;
        SlavePro = SlavePro+1;
    }
    ModifiedAngle = ModifyAngle(Masterpro);
    ModifiedAngle_B = ModifyAngle(SlavePro);
    NOTModifiedAngle = -ModifiedAngle;  
    NOTModifiedAngle_B = -ModifiedAngle_B;
    
    return CalculateProfileForce(Masterpro, ModifiedAngle) 
                + CalculateProfileForce(SlavePro, ModifiedAngle);
}

//==============================================================================
signed int8 LookUpInterpolatedDampingValue(signed int8 LowerIndexVal, signed int8 UpperIndexVal, signed int16 FractionVal)
{
    signed int16 DDifference = 0;
    signed int16 FractionalD = 0;
    signed int8 Fract;
    signed int16 ReturnValue = 0;
    //if they are both the same then use the lower one
    if(UpperIndexVal == LowerIndexVal)
    {
        return LowerIndexVal;
    }
    //work out the absolute difference between the two force values
    DDifference = (signed int16)abs( UpperIndexVal - LowerIndexVal );
    //now work out the force value to add to the lowest indexed value
    //multiply the force difference by the fractional value then divide by sixteen (Bit shift right by four)
    FractionalD = DDifference * FractionVal;
    FractionalD >>= 4;
    Fract = (signed int8)FractionalD;
    //check which index is lowest, if upper is lowest then subtract fraction from lower, otherwise add fraction to lower
    //what happens with negative numbers?
    if(LowerIndexVal > UpperIndexVal)
    {
        Return ( LowerIndexVal - Fract );
    }
    //this is returned if the above is not (if else)
    Return ( ReturnValue = LowerIndexVal + Fract );
}

//==============================================================================
signed int16 CalculateProfileForce(int8 ProfileToUse, signed int16 SAngle)
{
   //ForceTable[??];
    //use interpolation to get the real value
    // if the index is directly in place then use the real value
    //if not then take the lower and uper index values and work out your position between them
    //Pro[CurrentPro].ForceTable[Index]
    signed int16 FinalForceValue = 0;
    signed int16 FinalDampVal;
    int16 Mod;
    int16 ABSAngle;
    signed int16 fraction;
    int16 Index = 0, Index1 = 1;
    signed int16 ForceDifference = 0;
    signed int16 FractionalForce = 0;
    signed int16 DampingSum = 0;
    
    int16 FlashIndex = 0;
    signed int16 IndexdValue, IndexdValue1;
    int16 TempDamp;
    signed int8 DampVal, DampVal1;
    //work out the scale and bias that affect the angle
    //(Do this in the calling function once the system limits SP's etc have been checked)

    //need to move the angle up to the range 0-1023 and make unsigned
    //(the mod angle is capped to min -512 and max 511
    ABSAngle = (int16)(SAngle+512);
    Index = ABSAngle>>4;
    Mod = Index<<4;
    Index1 = Index+1;



    //first check that the indexes are in bounds
    //Index is unsigned so will never be less than zero
    if(Index > 63)
    {
        printf("Index out of bounds error Index = %lu\n", Index);
        Index = 63;
    }

    //work out the fractional part of the index - angle will always be higher??
    Fraction = ABSAngle - Mod;

    //copy the two indexed values to temp variables to make this work faster (no indexing the arrays)
    //copy these from flash
    FlashIndex = FlashProfileStart[ProfileToUse];
    FlashIndex += Index*2;
    IndexdValue = read_program_eeprom(FlashIndex);
    if(Index == 63) IndexdValue1 = IndexdValue;
    else IndexdValue1 = read_program_eeprom(FlashIndex+2);
    
    //IndexdValue = ForceTable[ProfileToUse][Index];
    //IndexdValue1 = ForceTable[ProfileToUse][Index1];

    if(ModifiedAngle != Mod || Index != 63 || IndexdValue1 != IndexdValue)
    {
        //work out the absolute difference between the two force values
        ForceDifference = abs( IndexdValue1 - IndexdValue );
        //now work out the force value to add to the lowest indexed value
        //multiply the force difference by the fractional value then divide by sixteen (Bit shift right by four)
        FractionalForce = ForceDifference * Fraction;
        FractionalForce /= 16;
    }

    //now work out which force calculation to use
    //check which index is lowest, if upper is lowest then subtract fraction from lower, otherwise add fraction to lower
    //what happens with negative numbers?
    if(IndexdValue > IndexdValue1)
    {
        FinalForceValue = IndexdValue - FractionalForce;
    }
    else if(IndexdValue < IndexdValue1)
    {
        FinalForceValue = IndexdValue + FractionalForce;
    }
    else FinalForceValue = IndexdValue;

    //DEBUG - skip damping for now
    //return FinalForceValue;
    
    //Now do the damping
    if(AngleVelocity > 1)
    {
        FlashIndex = (FlashProfileStart[ProfileToUse]+128)+Index;
        TempDamp = read_program_eeprom(FlashIndex);
        
        DampVal = make8(TempDamp, 0);
        if(Index == 63) DampVal1 = DampVal;
        if(Index < 63) DampVal1 = make8(TempDamp, 1);
        FinalDampVal = LookUpInterpolatedDampingValue(DampVal, DampVal1, Fraction);

        DampingSum = FinalDampVal + *UniformDamping_ptr[ ProfileToUse ];
        FinalForceValue = FinalForceValue - SMul1Sat(AngleVelocity, DampingSum, 2047 );
        //printf("FDV1 %ld ", FinalDampval);
    }
    if(AngleVelocity < -1)
    {
        FlashIndex = (FlashProfileStart[ProfileToUse]+192)+Index;
        TempDamp = read_program_eeprom(FlashIndex);
        
        DampVal = make8(TempDamp, 0);
        if(Index == 63) DampVal1 = DampVal;
        if(Index < 63) DampVal1 = make8(TempDamp, 1);
        FinalDampVal = LookUpInterpolatedDampingValue(DampVal, DampVal1, Fraction);
        DampingSum = FinalDampVal + *UniformDamping_ptr[ ProfileToUse ];
        FinalForceValue = FinalForceValue - SMul1Sat(AngleVelocity, DampingSum, 2047 );
        //printf("FDV2 %ld ", FinalDampval);
    }
    
    //Now apply the vertical scaling and biasing
    //Scale first
    FinalForceValue = SMul2(FinalForceValue, *VScale_ptr[ ProfileToUse ]);
    //then bias
    FinalForceValue += *VBias_ptr[ ProfileToUse ];

    return FinalForceValue;
    //no velocity so no damping

}

//=======================================================================
void CheckThresholds(int8 CurrentPro)
{
//Check the thresholds to see if they have been exceeded


    if(*PT1Enabled_ptr[ CurrentPro ] == 1)
    {
        if(*Threshold1Input_ptr[ CurrentPro ] > *PT1Value_ptr[ CurrentPro ])
        {
            PT1State[ CurrentPro ] = 1;
        }
        else PT1State[ CurrentPro ] = 0;
    }

    if(*NT1Enabled_ptr[ CurrentPro ] == 1)
    {
        if(*Threshold1Input_ptr[ CurrentPro ] < *NT1Value_ptr[ CurrentPro ])
        {
            NT1State[ CurrentPro ] = 1;
        }
        else NT1State[ CurrentPro ] = 0;
    }
    PTAndNT1State[ CurrentPro ] = PT1State[ CurrentPro ]+NT1State[ CurrentPro ];
    

    if(*PT2Enabled_ptr[ CurrentPro ] == 1)
    {
        if(*Threshold2Input_ptr[ CurrentPro ] > *PT2Value_ptr[ CurrentPro ])
        {
            PT2State[ CurrentPro ] = 1;
        }
        else PT2State[ CurrentPro ] = 0;
    }

    if(*NT2Enabled_ptr[ CurrentPro ] == 1)
    {
        if(*Threshold2Input_ptr[ CurrentPro ] < *NT2Value_ptr[ CurrentPro ])
        {
            NT2State[ CurrentPro ] = 1;
        }
        else NT2State[ CurrentPro ] = 0;
    }
    PTAndNT2State[ CurrentPro ] = PT2State[ CurrentPro ]+NT2State[ CurrentPro ];

    if(*PT3Enabled_ptr[ CurrentPro ] == 1)
    {
        if(*Threshold3Input_ptr[ CurrentPro ] > *PT3Value_ptr[ CurrentPro ])
        {
            PT3State[ CurrentPro ] = 1;
        }
        else PT3State[ CurrentPro ] = 0;
    }

    if(*NT3Enabled_ptr[ CurrentPro ] == 1)
    {
        if(*Threshold3Input_ptr[ CurrentPro ] < *NT3Value_ptr[ CurrentPro ])
        {
            NT3State[ CurrentPro ] = 1;
        }
        else NT3State[ CurrentPro ] = 0;
    }
    PTAndNT3State[ CurrentPro ] = PT3State[ CurrentPro ]+NT3State[ CurrentPro ];

    if(*PT4Enabled_ptr[ CurrentPro ] == 1)
    {
        if(*Threshold4Input_ptr[ CurrentPro ] > *PT4Value_ptr[ CurrentPro ])
        {
            PT4State[ CurrentPro ] = 1;
        }
        else PT4State[ CurrentPro ] = 0;
    }

    if(*NT4Enabled_ptr[ CurrentPro ] == 1)
    {
        if(*Threshold4Input_ptr[ CurrentPro ] < *NT4Value_ptr[ CurrentPro ])
        {
            NT4State[ CurrentPro ] = 1;
        }
        else NT4State[ CurrentPro ] = 0;
    }
    PTAndNT4State[ CurrentPro ] = PT4State[ CurrentPro ]+NT4State[ CurrentPro ];

}

//========================================================
void CheckExIn(int8 CurrentPro)
{

    //Checks and sets flags for the external digital inputs
    /*
    this really needs to work so that you can specify exactly how the flag responds to inputs
    Examples are:
    Flag directly corresponds to the current state of the input (as is currently the case)
    Flag is set on when input detected but off again if input is still high next time (Pulse in)
    flag is toggled when an incoming pulse is recieved

    Two seperate actions - how to respond to the input
    what to do with the flag - set or toggle


    */
    if(input(EXIN1))
    {
        ExIn1Flag = 1;
        NotExIn1Flag = 0;
    }
    else
    {
        ExIn1Flag = 0;
        NotExIn1Flag = 1;
    }
    if(input(EXIN2))
    {
        ExIn2Flag = 1;
        NotExIn2Flag = 0;
    }
    else
    {
        ExIn2Flag = 0;
        NotExIn2Flag = 1;
    }


    if(input(LIMIT1)) LimitIn1Flag = 1;
    else  LimitIn1Flag = 0;

    if(input(LIMIT2)) LimitIn2Flag = 1;
    else  LimitIn2Flag = 0;

}
//========================================================
void SetSummedFlags(int8 CurrentPro)
{
    //sets the summed flag which indicates if any of a collection of flags is active
    if( *SummedFlag1_ptr[CurrentPro] != 0 )
    {
        SummedFlag[CurrentPro] = 1;
        NotSummedFlag[CurrentPro] = 0;
        return;
    }
    else if( *SummedFlag2_ptr[CurrentPro] != 0 )
    {
        SummedFlag[CurrentPro] = 1;
        NotSummedFlag[CurrentPro] = 0;
        return;
    }
    else if( *SummedFlag3_ptr[CurrentPro] != 0 )
    {
        SummedFlag[CurrentPro] = 1;
        NotSummedFlag[CurrentPro] = 0;
        return;
    }
    else if( *SummedFlag4_ptr[CurrentPro] != 0 )
    {
        SummedFlag[CurrentPro] = 1;
        NotSummedFlag[CurrentPro] = 0;
        return;
    }
    else
    {
        SummedFlag[CurrentPro] = 0;
        NotSummedFlag[CurrentPro] = 1;
    }
    return;

}
//========================================================
void SetExOut(int8 CurrentPro)
{

    //Checks and sets external digital outputs


    if(*ExOut1_ptr[CurrentPro]   == 1)    output_high(EXOUT1);
    else output_low(EXOUT1);

    if(*ExOut2_ptr[CurrentPro]   == 1)    output_high(EXOUT2);
    else output_low(EXOUT2);



}

//==============================================================================
void UpdateInterComms(int8 CurrentPro)
{
    //update the inter-profile communications
    GlobalVariable1[CurrentPro] = *GlobalVariable1_ptr[CurrentPro];
    GlobalVariable2[CurrentPro] = *GlobalVariable2_ptr[CurrentPro];
    
    GlobalFlag1[CurrentPro] = *GlobalFlag1_ptr[CurrentPro];
    GlobalFlag2[CurrentPro] = *GlobalFlag2_ptr[CurrentPro];
}

//==============================================================================
void SendSerialDataA(int8 CurrentPro)
{
    //checks to see if block A or B needs sending during a profile iteration

    if(*SerialOutEnableA_ptr[CurrentProfile] == 0)
    {
        SerialTXTicksA = 0;
        return;
    }
    if(SerialTXTicksA >= RS232CommRateGroupA[CurrentProfile])
    {
        //send group A
        SerialTXTicksA = 0;
        RS232TransmitBlockA();
    }
    else SerialTXTicksA++;

}
//==============================================================================


void SendSerialDataB(int8 CurrentPro)
{
    if(*SerialOutEnableB_ptr[CurrentProfile] == 0)
    {
        SerialTXTicksB = 0;
        return;
    }
    if(SerialTXTicksB >= RS232CommRateGroupB[CurrentProfile])
    {
        //send group A
        SerialTXTicksB = 0;
        RS232TransmitBlockB();
    }
    else SerialTXTicksB++;
}
//==============================================================================
int8 GetCurrentProfile(int8 CurrentPro)
//checks the angle against the switchpoint and returns a new profile if nessacary
{

    // Check each Switchpoint Flag and if true check the switchpoint
    /*
    First check all the thresholds to see if they are exceeded and set the appropriate flags
    check the AltPro1[  ]_ptr[  ] pointers - these will point to the relevant threshold trigger
    For example AltPro1[  ]_ptr[  ] can point to PAT1State[  ]
    If the value pointed to is nonzero then select the alt profile
    otherwise work through the next ones
    */


    //  now work through each of the profile change actions to determine which profile to use
    //Reset the serial TX timers if the profile has changed
    if( *AltPro1_ptr[ CurrentPro ] == 1 )
    {
        SerialTXTicksA = 0;
        SerialTXTicksB = 0;
        return AltPro1[CurrentPro];
    }
    else if( *AltPro2_ptr[ CurrentPro ] == 1 )
    {
        SerialTXTicksA = 0;
        SerialTXTicksB = 0;
        return AltPro2[CurrentPro];
    }
    else if( *AltPro3_ptr[ CurrentPro ] == 1 )
    {
        SerialTXTicksA = 0;
        SerialTXTicksB = 0;
        return AltPro3[CurrentPro];
    }
    else if( *AltPro4_ptr[ CurrentPro ] == 1 )
    {
        SerialTXTicksA = 0;
        SerialTXTicksB = 0;
        return AltPro4[CurrentPro];
    }


    else return CurrentPro;
}
//==============================================================================================

void SetupProfileOscillator(int8 CurrentPro, int8 UpdateStepSize, int8 Prescaler,
                                    signed int16 Maxval, signed int16 MinVal, signed int16 StartVal, int1 StartDirection)
{
    OSC1Out[CurrentPro] = StartVal;

    StepSize[CurrentPro] = UpdateStepSize;

    if(StartDirection == 0)
    {
        Iterator[CurrentPro] = -( (signed int16)UpdateStepSize);
    }
    else Iterator[CurrentPro] = UpdateStepSize;
    OSC1Min[CurrentPro] = MinVal;

    OSC1Max[CurrentPro] = Maxval;

    SkipRate[CurrentPro] = Prescaler;


}

//==============================================================================
void IterateOscillator(int8 CurrentPro)
{
    //iterates the simple oscillator for the profile
    //The output from the oscillator
    ///OSC1Out[ProfileToUse] = 0;
    //The step size for iterating
    //StepSize[ProfileToUse] = 0;
    //the iterator value (the actual value that is added to the output to update it)
    //Iterator[ProfileToUse] = 0;
    //the Minimum value that it can reach
    //OSC1Min[ProfileToUse] = -100;
    //the maximum value it can reach
    //OSC1Max[ProfileToUse] = 100;
    //A prescaler to allow the iteration rate for the oscillator to be less than that of the profile
    //SkipRate[ProfileToUse] = 0;
    static int8 SkipCounter = 0;
    if(SkipCounter == SkipRate[CurrentPro])
    {
        SkipCounter = 0;
        //update
        //check the upper and lower limits and if exceededd change the sign of the iterator value
        OSC1Out[CurrentPro] += Iterator[CurrentPro];
        if( OSC1Out[CurrentPro] > OSC1Max[CurrentPro] )
        {
            OSC1Out[CurrentPro] = OSC1Max[CurrentPro];
            Iterator[ CurrentPro ] = -( (signed int16)StepSize[ CurrentPro ] );
        }
        if( OSC1Out[CurrentPro] < OSC1Min[CurrentPro] )
        {
            OSC1Out[CurrentPro] = OSC1Min[CurrentPro];
            Iterator[ CurrentPro ] = ( (signed int16)StepSize[ CurrentPro ] );
        }
        return;
    }
    SkipCounter++;
}

//==============================================================================================
void CreateDefaultProfile(int8 ProfileToUse)
{
    //setup defaults

    int8 n;
    signed int16 Fiterator = 32;
    for(n = 0; n < 64; n++)
    {
         TempForceTable[n] = Fiterator;
        //ForceTable[ProfileToUse][n] = 0;
        TempPDampTable[n] = n;
        //PDampTable[ProfileToUse][n] = 0;
        TempNDampTable[n] = 63-n;
        //NDampTable[ProfileToUse][n] = 0;
        Fiterator--;
    }



    //pointers to variables to set the scale and bias values
    HBias_ptr[ProfileToUse] = &DefaultHBias[ProfileToUse];
    VBias_ptr[ProfileToUse] = &DefaultVBias[ProfileToUse];
    HScale_ptr[ProfileToUse] = &DefaultHScale[ProfileToUse];
    VScale_ptr[ProfileToUse] = &DefaultVScale[ProfileToUse];

    //default values for Bias and scale values (horizontal and vertical)
    DefaultHBias[ProfileToUse] = 0;
    DefaultVBias[ProfileToUse] = 0;
    DefaultHScale[ProfileToUse] = 100;    //a fixed point multiplier with two decimal places (100 == 1.0)
    DefaultVScale[ProfileToUse] = 100;    //a fixed point multiplier with two decimal places (100 == 1.0)

    EQAngle[ ProfileToUse ] = 0;
    //SPEnabled = 0;
    DefaultUniformDamping[ ProfileToUse ] = 0;
    UniformDamping_ptr[ ProfileToUse ] = &DefaultUniformDamping[ ProfileToUse ];

    //Pointers to conditional flags that determine if a profile switch should happen
    //These are in order of priority
    // - if the first is triggered then it is used, else the next is checked, then the next...
    AltPro1_ptr[ProfileToUse] = &GlobalDefaultFalse;
    AltPro2_ptr[ProfileToUse] = &GlobalDefaultFalse;
    AltPro3_ptr[ProfileToUse] = &GlobalDefaultFalse;
    AltPro4_ptr[ProfileToUse] = &GlobalDefaultFalse;

    //Alternative profiles to use if a switch is triggered (Defaults to the same profile)
    AltPro1[ProfileToUse] = ProfileToUse;
    AltPro2[ProfileToUse] = ProfileToUse;
    AltPro3[ProfileToUse] = ProfileToUse;
    AltPro4[ProfileToUse] = ProfileToUse;

    //Pointers to conditional flags to determine if a profile should be incrimented or de-incrimented
    IncrimentProfile_ptr[ProfileToUse] = &GlobalDefaultFalse;
    DeIncrimentProfile_ptr[ProfileToUse] = &GlobalDefaultFalse;

    //Setup all four threshold pairs
    //THRESHOLDS1
    Threshold1Input_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;   //Input to this threshold value is always zero
    //Pointers to thresholds values - by default these will point to their default values below
    PT1Value_ptr[ProfileToUse] = &PT1Default[ProfileToUse];
    NT1Value_ptr[ProfileToUse] = &NT1Default[ProfileToUse];
    //default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
    PT1Default[ProfileToUse] = 1024;
    NT1Default[ProfileToUse] = -1024;
    //The current state will be zero  (Not triggered)
    PT1State[ProfileToUse] = 0;
    NT1State[ProfileToUse] = 0;
    //pointers to the enable flags for these thresholds - these point to global default (fixed) values
    PT1Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;
    NT1Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;

    //THRESHOLDS2
    Threshold2Input_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;   //Input to this threshold value is always zero
    //Pointers to thresholds values - by default these will point to their default values below
    PT2Value_ptr[ProfileToUse] = &PT2Default[ProfileToUse];
    NT2Value_ptr[ProfileToUse] = &NT2Default[ProfileToUse];
    //default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
    PT2Default[ProfileToUse] = 1024;
    NT2Default[ProfileToUse] = -1024;
    //The current state will be zero  (Not triggered)
    PT2State[ProfileToUse] = 0;
    NT2State[ProfileToUse] = 0;
    //pointers to the enable flags for these thresholds - these point to global default (fixed) values
    PT2Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;
    NT2Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;

    //THRESHOLDS3
    Threshold3Input_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;   //Input to this threshold value is always zero
    //Pointers to thresholds values - by default these will point to their default values below
    PT3Value_ptr[ProfileToUse] = &PT3Default[ProfileToUse];
    NT3Value_ptr[ProfileToUse] = &NT3Default[ProfileToUse];
    //default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
    PT3Default[ProfileToUse] = 1024;
    NT3Default[ProfileToUse] = -1024;
    //The current state will be zero  (Not triggered)
    PT3State[ProfileToUse] = 0;
    NT3State[ProfileToUse] = 0;
    //pointers to the enable flags for these thresholds - these point to global default (fixed) values
    PT3Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;
    NT3Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;

    //THRESHOLDS4
    Threshold4Input_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;   //Input to this threshold value is always zero
    //Pointers to thresholds values - by default these will point to their default values below
    PT4Value_ptr[ProfileToUse] = &PT4Default[ProfileToUse];
    NT4Value_ptr[ProfileToUse] = &NT4Default[ProfileToUse];
    //default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
    PT4Default[ProfileToUse] = 1024;
    NT4Default[ProfileToUse] = -1024;
    //The current state will be zero  (Not triggered)
    PT4State[ProfileToUse] = 0;
    NT4State[ProfileToUse] = 0;
    //pointers to the enable flags for these thresholds - these point to global default (fixed) values
    PT4Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;
    NT4Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;


    //set up the oscllator variables
    //The output from the oscillator
    OSC1Out[ProfileToUse] = 0;
    //The step size for iterating
    StepSize[ProfileToUse] = 0;
    //the iterator value (the actual value that is added to the output to update it)
    Iterator[ProfileToUse] = 0;
    //the Minimum value that it can reach
    OSC1Min[ProfileToUse] = -100;
    //the maximum value it can reach
    OSC1Max[ProfileToUse] = 100;
    //A prescaler to allow the iteration rate for the oscillator to be less than that of the profile
    SkipRate[ProfileToUse] = 0;

    //ADOut pointers (Set to default zero)
    ADOut1_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;
    ADOut2_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;
    //Scale Values for the ADOut values
    ADOut1Scaling[ProfileToUse] = 1;
    ADOut2Scaling[ProfileToUse] = 1;

    SummedFlag[ProfileToUse] = 0;
    SummedFlag1_ptr[ProfileToUse] = &GlobalDefaultFalse;
    SummedFlag2_ptr[ProfileToUse] = &GlobalDefaultFalse;
    SummedFlag3_ptr[ProfileToUse] = &GlobalDefaultFalse;
    SummedFlag4_ptr[ProfileToUse] = &GlobalDefaultFalse;
    
    MotorEnable_ptr[ProfileToUse] = &GlobalDefaultTrue;
    ForceControlEnable_ptr[ProfileToUse] = &GlobalDefaultTrue;
    
    RS232Out1_ptr[ProfileToUse] = &RS232In[0];
    RS232Out2_ptr[ProfileToUse] = &RS232In[1];
    RS232Out3_ptr[ProfileToUse] = &RS232In[2];
    RS232Out4_ptr[ProfileToUse] = &RS232In[3];
    RS232Out5_ptr[ProfileToUse] = &RS232In[4];
    RS232Out6_ptr[ProfileToUse] = &RS232In[5];
    RS232Out7_ptr[ProfileToUse] = &RS232In[6];
    RS232Out8_ptr[ProfileToUse] = &RS232In[7];
    SummedProfile[ProfileToUse] = 0;
    RS232OutTargetNodeA[ProfileToUse]    = 0;
    RS232OutTargetNodeB[ProfileToUse]    = 0;

    CANOutTargetNodeA[ProfileToUse]    = 0;
    CANOutTargetNodeB[ProfileToUse]    = 0;

    RS232CommRateGroupA[ProfileToUse]    = 0;                             
    RS232CommRateGroupB[ProfileToUse]    = 0;
    CANCommRateGroupA[ProfileToUse]    = 0;
    CANCommRateGroupB[ProfileToUse]    = 0;

    RS232RequestReplyA[ProfileToUse]    = 0;
    RS232RequestReplyB[ProfileToUse]    = 0;
    
    SerialOutEnableA_ptr[ProfileToUse] = &GlobalDefaultFalse;
    SerialOutEnableB_ptr[ProfileToUse] = &GlobalDefaultFalse;

    CANOutEnableA_ptr[ProfileToUse] = &GlobalDefaultFalse; 
    CANOutEnableB_ptr[ProfileToUse] = &GlobalDefaultFalse;
    
    //Now save the profile

    CopyRAMProfileDataToBuffers(ProfileToUse);
    SaveAllBuffersToFlash(ProfileToUse);
}
//==============================================================================



void CreateDefaultProfile2(int8 ProfileToUse)
{
    //setup defaults

    int8 n;
    signed int16 Fiterator = 1024;
    for(n = 0; n < 64; n++)
    {

            TempForceTable[n] = ProfileToUse+Fiterator;
            TempPDampTable[n] = n;
            TempNDampTable[n] = 64+n;

        //ForceTable[ProfileToUse][n] = ProfileToUse+Fiterator;
        //PDampTable[ProfileToUse][n] = n;
        //NDampTable[ProfileToUse][n] = 64+n;
            Fiterator -=32;
    }

    //pointers to variables to set the scale and bias values
    HBias_ptr[ProfileToUse] = &DefaultHBias[ProfileToUse];
    VBias_ptr[ProfileToUse] = &DefaultVBias[ProfileToUse];
    HScale_ptr[ProfileToUse] = &DefaultHScale[ProfileToUse];
    VScale_ptr[ProfileToUse] = &DefaultVScale[ProfileToUse];

    //default values for Bias and scale values (horizontal and vertical)
    DefaultHBias[ProfileToUse] = 0;
    DefaultVBias[ProfileToUse] = 0;
    DefaultHScale[ProfileToUse] = 100;    //a fixed point multiplier with two decimal places (100 == 1.0)
    DefaultVScale[ProfileToUse] = 100;    //a fixed point multiplier with two decimal places (100 == 1.0)

    EQAngle[ ProfileToUse ] = 0;
    //SPEnabled = 0;
    DefaultUniformDamping[ ProfileToUse ] = 0;
    UniformDamping_ptr[ ProfileToUse ] = &DefaultUniformDamping[ ProfileToUse ];


    //Pointers to conditional flags that determine if a profile switch should happen
    //These are in order of priority
    // - if the first is triggered then it is used, else the next is checked, then the next...
    AltPro1_ptr[ProfileToUse] = &GlobalDefaultFalse;
    AltPro2_ptr[ProfileToUse] = &GlobalDefaultFalse;
    AltPro3_ptr[ProfileToUse] = &GlobalDefaultFalse;
    AltPro4_ptr[ProfileToUse] = &GlobalDefaultFalse;

    //Alternative profiles to use if a switch is triggered (Defaults to the same profile)
    AltPro1[ProfileToUse] = ProfileToUse;
    AltPro2[ProfileToUse] = ProfileToUse;
    AltPro3[ProfileToUse] = ProfileToUse;
    AltPro4[ProfileToUse] = ProfileToUse;

    //Pointers to conditional flags to determine if a profile should be incrimented or de-incrimented
    IncrimentProfile_ptr[ProfileToUse] = &GlobalDefaultFalse;
    DeIncrimentProfile_ptr[ProfileToUse] = &GlobalDefaultFalse;

    //Setup all four threshold pairs
    //THRESHOLDS1
    Threshold1Input_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;   //Input to this threshold value is always zero
    //Pointers to thresholds values - by default these will point to their default values below
    PT1Value_ptr[ProfileToUse] = &PT1Default[ProfileToUse];
    NT1Value_ptr[ProfileToUse] = &NT1Default[ProfileToUse];
    //default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
    PT1Default[ProfileToUse] = 1024;
    NT1Default[ProfileToUse] = -1024;
    //The current state will be zero  (Not triggered)
    PT1State[ProfileToUse] = 0;
    NT1State[ProfileToUse] = 0;
    //pointers to the enable flags for these thresholds - these point to global default (fixed) values
    PT1Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;
    NT1Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;

    //THRESHOLDS2
    Threshold2Input_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;   //Input to this threshold value is always zero
    //Pointers to thresholds values - by default these will point to their default values below
    PT2Value_ptr[ProfileToUse] = &PT2Default[ProfileToUse];
    NT2Value_ptr[ProfileToUse] = &NT2Default[ProfileToUse];
    //default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
    PT2Default[ProfileToUse] = 1024;
    NT2Default[ProfileToUse] = -1024;
    //The current state will be zero  (Not triggered)
    PT2State[ProfileToUse] = 0;
    NT2State[ProfileToUse] = 0;
    //pointers to the enable flags for these thresholds - these point to global default (fixed) values
    PT2Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;
    NT2Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;

    //THRESHOLDS3
    Threshold3Input_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;   //Input to this threshold value is always zero
    //Pointers to thresholds values - by default these will point to their default values below
    PT3Value_ptr[ProfileToUse] = &PT3Default[ProfileToUse];
    NT3Value_ptr[ProfileToUse] = &NT3Default[ProfileToUse];
    //default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
    PT3Default[ProfileToUse] = 1024;
    NT3Default[ProfileToUse] = -1024;
    //The current state will be zero  (Not triggered)
    PT3State[ProfileToUse] = 0;
    NT3State[ProfileToUse] = 0;
    //pointers to the enable flags for these thresholds - these point to global default (fixed) values
    PT3Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;
    NT3Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;

    //THRESHOLDS4
    Threshold4Input_ptr[ProfileToUse] = &GlobalDefaultZeroModulator;   //Input to this threshold value is always zero
    //Pointers to thresholds values - by default these will point to their default values below
    PT4Value_ptr[ProfileToUse] = &PT4Default[ProfileToUse];
    NT4Value_ptr[ProfileToUse] = &NT4Default[ProfileToUse];
    //default (fixed) values for these thresholds - these are by default set to + and - 1024 (Outside normal limits)
    PT4Default[ProfileToUse] = 1024;
    NT4Default[ProfileToUse] = -1024;
    //The current state will be zero  (Not triggered)
    PT4State[ProfileToUse] = 0;
    NT4State[ProfileToUse] = 0;
    //pointers to the enable flags for these thresholds - these point to global default (fixed) values
    PT4Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;
    NT4Enabled_ptr[ProfileToUse] = &GlobalThresholdDisabled;


    //set up the oscllator variables
    //The output from the oscillator
    OSC1Out[ProfileToUse] = 0;
    //The step size for iterating
    StepSize[ProfileToUse] = 0;
    //the iterator value (the actual value that is added to the output to update it)
    Iterator[ProfileToUse] = 0;
    //the Minimum value that it can reach
    OSC1Min[ProfileToUse] = -100;
    //the maximum value it can reach
    OSC1Max[ProfileToUse] = 100;
    //A prescaler to allow the iteration rate for the oscillator to be less than that of the profile
    SkipRate[ProfileToUse] = 0;

    //ADOut pointers (Set to default zero)
    ADOut1_ptr[ProfileToUse] = &Angle;
    ADOut2_ptr[ProfileToUse] = &Angle;
    //Scale Values for the ADOut values
    ADOut1Scaling[ProfileToUse] = 1;
    ADOut2Scaling[ProfileToUse] = 1;

    SummedFlag[ProfileToUse] = 0;
    SummedFlag1_ptr[ProfileToUse] = &GlobalDefaultFalse;
    SummedFlag2_ptr[ProfileToUse] = &GlobalDefaultFalse;
    SummedFlag3_ptr[ProfileToUse] = &GlobalDefaultFalse;
    SummedFlag4_ptr[ProfileToUse] = &GlobalDefaultFalse;
    
    MotorEnable_ptr[ProfileToUse] = &GlobalDefaultTrue;
    ForceControlEnable_ptr[ProfileToUse] = &GlobalDefaultTrue;

    RS232Out1_ptr[ProfileToUse] = &RS232In[0];
    RS232Out2_ptr[ProfileToUse] = &RS232In[1];
    RS232Out3_ptr[ProfileToUse] = &RS232In[2];
    RS232Out4_ptr[ProfileToUse] = &RS232In[3];
    RS232Out5_ptr[ProfileToUse] = &RS232In[4];
    RS232Out6_ptr[ProfileToUse] = &RS232In[5];
    RS232Out7_ptr[ProfileToUse] = &RS232In[6];
    RS232Out8_ptr[ProfileToUse] = &RS232In[7];
    //Now save the profile

    CopyRAMProfileDataToBuffers(ProfileToUse);
    SaveAllBuffersToFlash(ProfileToUse);
}
//==============================================================================

//==============================================================================
signed int16 ReadAD(int8 Port)
{
    set_adc_channel(Port);
    delay_us(10);
    return (signed int16)read_adc();
}

//==============================================================================
void ReadSensors()
{
    //static int8 CalcPeriod = 1;
    int8 n;
    /*
//a single pass sensor collection
    Angle = readAD(ANGLEIN)-512;
    AngleVelocity = 504-ReadAD(ANGLEDTIN);
    ADIn1 = readAD(AIN1)-512;
    ADIn2 = readAD(AIN2)-512;

    //A four pass average
    //First clear the variables
    Angle = 0;
    AngleVelocity = 0;
    ADIn1 = 0;
    ADIn2 = 0;
    */
    

    

    Angle         = readAD(ANGLEIN);
    AngleVelocity     = ReadAD(ANGLEDTIN);
    ADIn1         = readAD(AIN1);
    ADIn2         = readAD(AIN2);
    //Now collect the data three times
    for(n = 0; n < 3; n++)
    {
        Angle         += readAD(ANGLEIN);
        AngleVelocity     += ReadAD(ANGLEDTIN);
        ADIn1         += readAD(AIN1);
        ADIn2         += readAD(AIN2);
    }
    Angle /= 4;
    Angle -= 512;


    AngleVelocity /= 4;
    AngleVelocity = AngleVelocity-VELOCITYTUNING_ACTUATOR2;
    AngleVelocity = -AngleVelocity;
    AngleAcceleration = AngleVelocity - OldAngleVelocity;

    OldAngleVelocity = AngleVelocity;
    ADIn1 /= 4;
    ADIn1 -= 512;
    ADIn2 /= 4;
    ADIn2 -= 512;

    //CyclicTestFunction();
    //Angle = 0;
    //AngleVelocity = 100;
    //AngleAcceleration = -100;
    //Now do all the inverted variables
    NOTAngle = -Angle;
    NOTAngleVelocity = -AngleVelocity;
    NOTAngleAcceleration  = -AngleAcceleration;
    NOTADIn1 = -ADIn1;
    NOTADIn2 = -ADIN2;
}


//==============================================================================
void ApplyVelocityCompensation()
{
    //looks ahead of the measured angle using the angle velocity to work out where you ought to be at the end of this iteration
    //this should help the system compensate for the lag between input and output
    //and for slow update rates

    Angle += SMul1Sat(AngleVelocity, VelocityMultiplier, 50);
}

void CyclicTestFunction()
{
    static signed int16 OldAng = 0;
    static signed int16 AIterator = -8;

    
    Angle+= AIterator;

    if(Angle < -512)
    {
        AIterator = 8;
        Angle = -512;
    }
    if(Angle > 512)
    {
        AIterator = -8;
        Angle = 512;
    }
    AngleVelocity = Angle-OldAng;
    OldAng = Angle;
}

void PrintTestData()
{
    //printf("Ang %5ld FT %5ld Pro %u \n", Angle, FTarget, CurrentProfile);
    printf("Ang %5ld FT %5ld PT1 %u NT1 %u\n", Angle, FTarget
                                                , PT1State[CurrentProfile], NT1State[CurrentProfile]);
}
