#include "D:\PIC_C_Projects\PROGRAMMABLE SPRING\NewAngleControl\AngleController.h"
//#include <9366.C>

#define DAC1_CS 			PIN_C0
#define DAC2_CS 			PIN_D4
#define DAC3_CS				PIN_D5

#define DAC_DATA			PIN_D2
#define DAC_CLOCK			PIN_D1

#define EEPROM_CLOCK		PIN_D1
#define EEPROM_DATA_IN		PIN_D2
#define EEPROM_DATA_OUT		PIN_D3
#define EEPROM1_CS			PIN_D0
#define EEPROM2_CS			PIN_C1


#define MOTOR_ENABLE		PIN_E2
#define ZERO_FORCE_OVERRIDE	PIN_E1

#define SPI_CLK 			PIN_C2
#define SPI_DTA 			PIN_C3
//#define SPI_SS pin_c2

#define TXDELAY 			20

#define ZERO_FORCE 			0


#define EXIN1				PIN_B1
#define EXIN2				PIN_B0
#define LIMIT1				PIN_B5
#define LIMIT2				PIN_B4
#define EXOUT1				PIN_D7
#define EXOUT2				PIN_D6

#define AIN1				1
#define AIN2				0

#define ANGLEIN				3
#define ANGLEDTIN			2

#define MAX_ANGLE			400
#define MIN_ANGLE			-300

#define  PROFILES 			6

//Profile Structure
struct ProfileStruct
{
    signed int16 ForceTable[64];
    int8 PDampTable[64];
    int8 NDampTable[64];
    int16 SwitchPointA;
    int16 SwitchPointB;
    int8 AltProA;
    int8 AltProB;
    signed int16* HBias;
    signed int16* VBias;
    signed int16* HScale;
    signed int16* VScale;
    signed int16 EQAngle;

    int8 Flags; //Bits = {SPDir, SPenabled, InvertForce, InvertAngle, ?, ?, ?, ?}
    int1 SPEnabled;
    signed int16 UniformDamping;
    int1 UniformDampingEnabled;
    int1 ForceInversion;
    int1 SPScaled;    //Determines if the switchpoints are scaled along with the force profile
    int1 SPBiased;    //Determines if the switchpoints are Biased along with the force profile

};
//Functions ---------------------------------------
#int_RDA
void RDA_isr();

#int_RTCC
void RTCC_isr();

void SetForce(signed int16 ForceValue);

void SPITransmit(int16 SPIForceValue);

void EnableMotor();

void DisableMotor();

void EnableForce();

void DisableForce();

signed int16 readAD(int8 Chanel);

void ReadInputs();

void PrintfInputs();

void ApplyHardLimits();

//a signed multiplication with one decimal place
//returns the computed integer value (No decimal places)
signed int16 SMul(signed int16 Value, signed int16 Multiplier);

//Profile Functions

/*
procedure for getting the force value from the profile structure
Read the angle
apply the horizontal scale to the angle (relative to the scaling origin)
Apply the horizontal bias to the angle
Store the resulting modified angle for other operations like switchpoints and damping
look up the force and damping values
***Interpolate from 1024 angles to 64 stage LUT:
first bit shift right the TempAngle Value by 4 (Divide by 4) this gives you the index for the look up table
this index is the lowest possible interpolated value so the actual value may be the index plus up to 15
next work out the

*/
void UpateProfileSystem();
void ModifyAngle();
signed int16 CalculateForce();
signed int8 LookUpInterpolatedDampingValue(signed int8 LowerIndexVal, signed int8 UpperIndexVal, signed int16 FractionVal);

//peripheral functions

void SetDAC(int8 Chanel, signed int16 Value);
void ClockOutDACValue(int16 Value);


//Globals ---------------------------------------


struct ProfileStruct FProfiles[PROFILES]; // a global array of profiles


signed int16 ForceTarget = 0;

int1 Exit = 0;
int1 MotorEnabled = 1;
int1 ForceEnabled = 1;
int8 SerialInByte = 0;
int1 SerialNewData = 0;

signed int16 Angle;
signed int16 AngleDt;
signed int16 AnalogueInputs[6];
int8 DigitalInputs;
signed int16 ModifiedAngle;
int8 CurrentProfile;
void main()
{
	int16 TTest1 = 0;
	int16 Counter1 = 0;
	setup_adc_ports(AN0_TO_AN5|VSS_VDD);
    setup_adc(ADC_CLOCK_INTERNAL|ADC_TAD_MUL_0);
    setup_psp(PSP_DISABLED);
    setup_spi(FALSE);
    setup_wdt(WDT_OFF);
    setup_timer_0(RTCC_DIV_64|RTCC_INTERNAL);
    setup_timer_1(T1_DISABLED);
    setup_timer_2(T2_DISABLED|T2_DIV_BY_4,255,1);
    setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
    setup_oscillator(False);

    output_low(SPI_DTA);
	output_low(SPI_CLK);

    DisableMotor();
    DisableForce();

    SetForce(0);
    SetForce(0);

	printf("PGS 2.0 Starting . . .\n");
	delay_ms(10);
	EnableMotor();
	EnableForce();
      //output_low( SPI_SS );

 	//output_high( MOTOR_ENABLE );
    //output_low( ZERO_FORCE_OVERRIDE );
   //init_ext_eeprom();
   //enable_interrupts(INT_TIMER2);
   enable_interrupts(INT_RDA);
   enable_interrupts(INT_RTCC);
   enable_interrupts(GLOBAL);

   // TODO: USER CODE!!
   ForceTarget = ZERO_FORCE;
   SetForce(ForceTarget);

   delay_ms(100);
   while(!Exit)
   {


		UpateProfileSystem();

		if(SerialNewData == 1)
		{
			//ForceTarget = (signed int16) SerialInByte;
			//ForceTarget -=128;
			//ForceTarget*=4;
			//SetForce(ForceTarget);
			SerialNewData = 0;
		}
   }
}

//Functions ---------------------------------------

//==============================================================================
#int_RDA
void RDA_isr()
{
	SerialInByte = getc();
	SerialNewData = 1;

}


//==============================================================================
#int_RTCC
void RTCC_isr()
{

	ReadInputs();
	ApplyHardLimits();
	PrintfInputs();
	SetForce(ForceTarget);
	//ForceTarget+=16;
	//if(ForceTarget > 2047) ForceTarget = -2048;
	return;
}


//==============================================================================
void SetForce(signed int16 ForceValue)
{
	//convert a signed int16 to an int16 around the value 2047
	//int16 RawForce;
	signed int16 TempForce;

	TempForce = 2047 + ForceValue;
	if(TempForce < 0) TempForce = 0;
	if(TempForce > 4095) TempForce = 4095;

	//RawForce = (int16)TempForce;
	SPITransmit((int16)TempForce)  ;
	//printf("Txing %ld\n", TempForce);


}

//==============================================================================
void SPITransmit(int16 SPIForceValue)
{
	int16 OutVal = 0;
	int8 n;
	OutVal = SPIForceValue;

	OutVal <<=4;

	for(n = 0; n < 12; n++)
	{
		output_bit( SPI_DTA, shift_left(OutVal, 1, 0) );
		output_high(SPI_CLK);
		delay_us(TXDELAY);
		output_low(SPI_CLK);
	}
	//skip this if you are sending the same value as last time
	//if(SPIForceValue == OldVal)
	//{
		//OldVal = SPIForceValue;
		//return;
	//}
	/*
	OutVal = SPIForceValue;
	//printf("OldVal = %ld\n", OldVal);
	if(bit_test(OutVal, 11)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 10)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 9)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 8)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 7)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 6)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 5)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 4)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 3)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 2)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 1)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);

	if(bit_test(OutVal, 0)  == 1)    output_high(SPI_DTA);
	else output_low(SPI_DTA);
	output_high(PIN_C5);
	output_high(SPI_CLK);
	delay_us(TXDELAY);
	output_low(SPI_CLK);
	output_low(PIN_C5);
*/

}

//==============================================================================
void EnableMotor()
{
    output_low( MOTOR_ENABLE );
}

//==============================================================================
void DisableMotor()
{
	output_high( MOTOR_ENABLE );
}

//==============================================================================
void EnableForce()
{
	output_high( ZERO_FORCE_OVERRIDE );
}

//==============================================================================
void DisableForce()
{
	output_low( ZERO_FORCE_OVERRIDE );
}

//==============================================================================
signed int16 readAD(int8 Channel)
{
	signed int16 TempVal;
	if(Channel > 5) return 0;
	set_adc_channel(Channel);
	delay_us(10);
	TempVal = read_adc();
	TempVal -= 512;
	//TempVal *= 2;
	return TempVal;
}

//==============================================================================
void ReadInputs()
{
	AnalogueInputs[0] = readAD(0);
	AnalogueInputs[1] = readAD(1);
	AnalogueInputs[2] = readAD(2);
	AnalogueInputs[3] = readAD(3);
	AnalogueInputs[4] = readAD(4);
	AnalogueInputs[5] = readAD(5);
	DigitalInputs = 0;
	if( input(EXIN1) ) bit_set(DigitalInputs, 0);
	if( input(EXIN2) ) bit_set(DigitalInputs, 1);
	if( input(LIMIT1) ) bit_set(DigitalInputs, 2);
	if( input(LIMIT2) ) bit_set(DigitalInputs, 3);



}

//==============================================================================
void PrintfInputs()
{
	int8 n;

	for(n = 0; n < 6; n++)
	{
		printf("AD%u = %ld ", n,  AnalogueInputs[n]);
	}
	for(n = 0; n < 4; n++)
	{
		if( bit_test( DigitalInputs, n ) ) printf("1 ");
		else printf("0 ");
	}
	printf("\n");
}

//==============================================================================
void ApplyHardLimits()
{
	if( AnalogueInputs[ANGLEIN] > MAX_ANGLE || AnalogueInputs[ANGLEIN] < MIN_ANGLE ) DisableMotor();
	else EnableMotor();
}

//==============================================================================
signed int16 SMul(signed int16 Value, signed int16 Multiplier)
{
    signed int16 buff;

    //Multiply the Value by the Multiplier
    buff = Value * Multiplier;

	buff /= 10;
    return buff;
}

//==============================================================================
void UpateProfileSystem()
{
	//this is the main function for updating the force output using the profile system
	//all profile operations start here

	//1 Read all the inputs
	void ReadInputs();
	Angle = AnalogueInputs[ANGLEIN];//AnalogueInputs[6];
	//2 Modify the system angle
	ModifyAngle();
	//3 Work out which profile you should be in based on the inputs and conditionals

	//4 look up force values
	ForceTarget = CalculateForce();
	//5 transmit force values to SEA
}
//==============================================================================
void ModifyAngle()
{
	//first apply the scaling relative to the scaling origin

	ModifiedAngle = SMul(ModifiedAngle, FProfiles[CurrentProfile].HScale);

	//now apply the bias
	ModifiedAngle += FProfiles[CurrentProfile].HBias;
	//now apply the limits
    if(ModifiedAngle >511)
    {
        ModifiedAngle = 511;
    }
    else if(ModifiedAngle < -512)
    {
        ModifiedAngle = -512;
    }
}



//==============================================================================
signed int16 CalculateProfileForce(int8 ProfileToUse);
{
   //ForceTable[??];
    //use interpolation to get the real value
    // if the index is directly in place then use the real value
    //if not then take the lower and uper index values and work out your position between them
    //Pro[CurrentPro].ForceTable[Index]
    signed int16 FinalForceValue = 0;
	signed int16 FinalDampVal;
    int16 Mod;
	signed int16 fraction;
    int16 Index = 0, Index1 = 1;
    signed int16 ForceDifference = 0;
    signed int16 FractionalForce = 0;
	signed int16 DampingSum;
	//work out the scale and bias that affect the angle
	//(Do this in the calling function once the system limits SP's etc have been checked)

    Index = ModifiedAngle>>4;
    Mod = Index<<4;
    Index1 = Index+1;



	//first check that the indexes are in bounds
 	if(Index < 0)
	{
		printf("Index out of bounds error Index = %lu\n", Index);
		Index = 0;
	}
	else if(Index > 63)
	{
		printf("Index out of bounds error Index = %lu\n", Index);
		Index = 63;
	}

	//work out the fractional part of the index - angle will always be higher??
	Fraction = ModifiedAngle - Mod;
    //work out the absolute difference between the two force values
    ForceDifference = abs( FProfiles[ProfileToUse].ForceTable[Index1] - FProfiles[ProfileToUse].ForceTable[Index] );
    //now work out the force value to add to the lowest indexed value
    //multiply the force difference by the fractional value then divide by sixteen (Bit shift right by four)
    FractionalForce = ForceDifference * Fraction;
    FractionalForce >>= 4;

	//now work out which force calculation to use
	//first check to see if the angle is dead on the index
    if(ModifiedAngle == Mod || Index == 63)
    {
        FinalForceValue = FProfiles[ProfileToUse].ForceTable[Index];
    }

	else if(FProfiles[ProfileToUse].ForceTable[Index1] == FProfiles[ProfileToUse].ForceTable[Index])
    {
        FinalForceValue = FProfiles[ProfileToUse].ForceTable[Index];
    }


    //check which index is lowest, if upper is lowest then subtract fraction from lower, otherwise add fraction to lower
    //what happens with negative numbers?
    else if(FProfiles[ProfileToUse].ForceTable[Index] > FProfiles[ProfileToUse].ForceTable[Index1])
    {
        FinalForceValue = FProfiles[ProfileToUse].ForceTable[Index] - FractionalForce;
    }
    else FinalForceValue = FProfiles[ProfileToUse].ForceTable[Index] + FractionalForce;

	//Now do the damping
	if(AngleDt > 0)
	{
		FinalDampVal = LookUpInterpolatedDampingValue(FProfiles[ProfileToUse].PDampTable[Index]
													, FProfiles[ProfileToUse].PDampTable[Index1], Fraction);
	}
	else if(AngleDt < 0)
	{
		FinalDampVal = LookUpInterpolatedDampingValue(FProfiles[ProfileToUse].NDampTable[Index]
													, FProfiles[ProfileToUse].NDampTable[Index1], Fraction);
	}
	else FinalDampVal = 0;
	//if(FProfiles[CurrentPro].ForceInversion) return -FinalForceValue;


	DampingSum = FinalDampVal;
	DampingSum += FProfiles[ProfileToUse].UniformDamping;
	return ( FinalForceValue - SMul(AngleDt, DampingSum) );

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
void SetDAC(int8 Chanel, signed int16 Value)
{
	//Sets the force target DAC - takes a signed int16 between -2048 and 2047
	//first make into an int16
	signed int16 TempVal;
    int16 DACVal;
	int8 BitIndex = 0;

	if(Value < -2048) DACVal = 0;
	else if(Value > 2047) DACVal = 4095;
	else DACVal = (int16)(Value+2048);

    //Bit values are
    //Higher Byte = (dnt care)    (dnt care)    (mode1)        (mode0)        (Bit 11 MSB)    (Bit 10)    (Bit 9)        (Bit 8)
    //Lower Byte =     (Bit 7)        (Bit 6)        (Bit 5)        (Bit 4)        (Bit 3)            (Bit 2)        (Bit 1)        (Bit 0 LSB)
    //mode bits are(Mode 1 and Mode 0) 00 Normal, 01 1K to gnd, 10 100k to gnd, 11 Tri State.

	if(Chanel == 1)
	{
		output_low(DAC1_CS);
		ClockOutDACValue(DACVal);
		output_high(DAC1_CS);
	}
	else if(Chanel == 2)
	{
		output_low(DAC2_CS);
		ClockOutDACValue(DACVal);
		output_high(DAC2_CS);
	}
	else if(Chanel == 3)
	{
		output_low(DAC3_CS);
		ClockOutDACValue(DACVal);
		output_high(DAC3_CS);
	}
	else return;

}

//==============================================================================
void ClockOutDACValue(int16 Value)
{
	//clocks out the value to the DAC's (CS for the appropriate chanel is set by the calling function)
	//output highest bytes first
	//do this manually rather than in a loop for higher speed
	output_high(DAC_CLOCK);
	//output_bit( DAC_DATA, bit_test(Value, 15) );
	output_bit( DAC_DATA, 0 );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	//output_bit( DAC_DATA, bit_test(Value, 14) );
	output_bit( DAC_DATA, 0 );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	//output_bit( DAC_DATA, bit_test(Value, 13) );
	output_bit( DAC_DATA, 0 );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	//output_bit( DAC_DATA, bit_test(Value, 12) );
	output_bit( DAC_DATA, 0 );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 11) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 10) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 9) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 8) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 7) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 6) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 5) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 4) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 3) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 2) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 1) );
	output_low(DAC_CLOCK);

	output_high(DAC_CLOCK);
	output_bit( DAC_DATA, bit_test(Value, 0) );
	output_low(DAC_CLOCK);
}

//======================================
========================================




//==============================================================================
void CreateAutoProfile(int8 Type, int8 ProfileNo)
{
    //automatically generate a variety of profiles
    signed int16 AForce = 0;
	signed int8 Damp;
    int8 n = 0;
    switch(Type)
    {
        case 0:
            //plain zero force profile
            for(n = 0; n < 64; n++)
            {
                ForceTable[ProfileNo][n] = 0;
				//NDampTable[ProfileNo][n] = -20;
            }
            PAT1Enabled[ ProfileNo ] = 0;
			NAT1Enabled[ ProfileNo ] = 0;
            break;
        case 1:
            	//plain linear profile
            	AForce = 2047;
            	for(n = 0; n < 64; n++)
            	{
                	ForceTable[ProfileNo][n] = AForce;
                	NDampTable[ProfileNo][n] = 0;
                	PDampTable[ProfileNo][n] = 0;
                	AForce -= 64;
            	}
            	PAT1Enabled[ ProfileNo ] = 0;
				NAT1Enabled[ ProfileNo ] = 0;
			    DefaultHBias[ ProfileNo ] = 0;
    			DefaultVBias[ ProfileNo ] = 0;

				HBias_ptr[ ProfileNo ] = &DefaultHBias[ ProfileNo ];
    			VBias_ptr[ ProfileNo ] = &DefaultVBias[ ProfileNo ];
	
    			DefaultHScale[ ProfileNo ] = 1;
    			DefaultVScale[ ProfileNo ] = 1;
	
				HScale_ptr[ ProfileNo ] = &DefaultHScale[ ProfileNo ]; 
    			VScale_ptr[ ProfileNo ] = &DefaultVScale[ ProfileNo ];
            break;
        case 2:
            //plain linear sprung end stop zero force profile
            AForce = 2047;
            for(n = 0; n < 16; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                AForce -= 128;
            }
            AForce = 0;
            for(n = 16; n < 48; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
            }
            for(n = 48; n < 64; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                AForce -= 128;
            }
            PAT1Enabled[ ProfileNo ] = 0;
			NAT1Enabled[ ProfileNo ] = 0;
            break;
		case 3:
            //plain linear sprung end stop zero force profile with negative uniform damping
            AForce = 2047;
			DefaultUniformDamping[ ProfileNo ] = -3;
            for(n = 0; n < 16; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                AForce -= 128;
            }
            AForce = 0;
            for(n = 16; n < 48; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
            }
            for(n = 48; n < 64; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                AForce -= 128;
            }
            PAT1Enabled[ ProfileNo ] = 0;
			NAT1Enabled[ ProfileNo ] = 0;
            break;
		case 4:
            //plain linear sprung end stop zero force profile with profile damping
            AForce = 2047;
			//UniformDamping[ ProfileNo ] = -3;
            for(n = 0; n < 16; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
				NDampTable[ProfileNo][n] = 10;
                AForce -= 128;
            }
            AForce = 0;
            for(n = 16; n < 48; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
            }
            for(n = 48; n < 64; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
				PDampTable[ProfileNo][n] = 10;
                AForce -= 128;
            }
            PAT1Enabled[ ProfileNo ] = 0;
			NAT1Enabled[ ProfileNo ] = 0;
            break;
        case 5:
            //Centred equilibrium point with identical linear springs and uniform damping
			DefaultUniformDamping[ ProfileNo ] = 6;
            AForce = 2047;
            for(n = 0; n < 16; n++)
            {
                ForceTable[ProfileNo][n] = AForce;

            }
            for(n = 16; n < 32; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                AForce -= 128;
            }
            AForce = 0;
            ForceTable[ProfileNo][32] = AForce;
            AForce -= 128;
            for(n = 33; n < 49; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                AForce -= 128;
            }
            AForce = -2048;
            for(n = 49; n < 64; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
            }
            EQAngle[ ProfileNo ] = 32;
            EQAngle[ ProfileNo ] = EQAngle[ ProfileNo ] << 4;
            PAT1Enabled[ ProfileNo ] = 0;
			NAT1Enabled[ ProfileNo ] = 0;
            break;
        case 6:
            //A hysteresis system using profile ProfileNo and ProfileNo+1
            AForce = 1023;
            for(n = 0; n < 64; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                AForce -=16;

            }
            DefaultNegativeAngleThreshold1[ ProfileNo ] = 300;     //switches below 200
            DefaultPositiveAngleThreshold1[ ProfileNo ] = 1023;    //switches above 1023 (The max is 1023 so this is effectively disabled
            AltPro1[ ProfileNo ] = ProfileNo+1;    //Profile to use if N egativeSwitchPoint1 is passed
            AltPro2[ ProfileNo ] = ProfileNo+1;    //Profile to use of SwitchpointB is passed
            PAT1Enabled[ ProfileNo ] = 1;
			NAT1Enabled[ ProfileNo ] = 1;            //Enables the use of switching points
            AForce = 0;
            for(n = 0; n < 64; n++)
            {
                ForceTable[ProfileNo+1][n] = AForce;
                AForce -=16;

            }
			//AngleThresholdP1; AltProPAT1;
            DefaultPositiveAngleThreshold1[ ProfileNo+1 ] = 700;
            DefaultNegativeAngleThreshold1[ ProfileNo+1 ] = 0;
            AltPro1[ ProfileNo+1 ] = ProfileNo;
            AltPro2[ ProfileNo+1 ] = ProfileNo;
            PAT1Enabled[ ProfileNo+1 ] = 1;
			NAT1Enabled[ ProfileNo+1 ] = 1;
            break;
        case 7:
            //An Pinball flipper or oscillator
            //The first profile is the limp (Return) spring
            //The second is the power jump one
            AForce = 255;
            for(n = 0; n < 16; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                //AForce -=32;

            }
			for(n = 16; n < 30; n++)
            {
                ForceTable[ProfileNo][n] = AForce;
                AForce -=16;

            }
			ForceTable[ProfileNo][30] = 0;
			ForceTable[ProfileNo][31] = 0;
            for(n = 32; n < 64; n++)
            {
                ForceTable[ProfileNo][n] = -128;

            }
			Damp = 24;
			for(n = 32; n < 48; n++)
            {
                NDampTable[ProfileNo][n] = Damp;
			    Damp--;
            }

            DefaultNegativeAngleThreshold1[ ProfileNo ] = 390;
            DefaultPositiveAngleThreshold1[ ProfileNo ] = 1023;
            AltPro1[ ProfileNo ] = ProfileNo+1;
            AltPro2[ ProfileNo ] = ProfileNo+1;
            PAT1Enabled[ ProfileNo ] = 1;
			NAT1Enabled[ ProfileNo ] = 1;

            AForce = 2047;
            for(n = 0; n < 16; n++)
            {
                ForceTable[ProfileNo+1][n] = AForce;

            }
			Damp = 0;
            for(n = 16; n < 48; n++)
            {
                ForceTable[ProfileNo+1][n] = AForce;
				if(n > 40) PDampTable[ProfileNo+1][n] = Damp;
                AForce -= 64;
				Damp ++;

            }
            for(n = 48; n < 64; n++)
            {
                ForceTable[ProfileNo+1][n] = 0;
            }
			//AngleThresholdP1; AltProPAT1;
            DefaultPositiveAngleThreshold1[ ProfileNo+1 ] = 700;
            DefaultNegativeAngleThreshold1[ ProfileNo+1 ] = 0;
            AltPro1[ ProfileNo+1 ] = ProfileNo;
            AltPro2[ ProfileNo+1 ] = ProfileNo;
            PAT1Enabled[ ProfileNo+1 ] = 1;
			NAT1Enabled[ ProfileNo+1 ] = 0;
            break;

        default:
            for(n = 0; n < 64; n++)
            {
                ForceTable[ProfileNo][n] = 0;
            }
            PAT1Enabled[ ProfileNo ] = 0;
			NAT1Enabled[ ProfileNo ] = 0;
    }
}
