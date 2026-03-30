void SetForce(signed int16 ForceValue);
void SetMotor(signed int16 ForceValue);

void SPITransmit(int16 SPIForceValue);
void ClockOutDACValue(int16 Value);
void SetDAC(int8 Chanel, signed int16 Value);

void HaltActuator();
void ResumeActuator();

void EnableMotor();
void DisableMotor();
void EnableForce();
void DisableForce();



//==============================================================================
void SetForce(signed int16 ForceValue)
{
   //convert a signed int16 to an int16 around the value 2047
   //int16 RawForce;
   SetMotor(ForceValue);
   /*
   signed int16 TempForce;

   TempForce = 2047 + ForceValue;
   if(TempForce < 0) TempForce = 0;
   if(TempForce > 4095) TempForce = 4095;

   //RawForce = (int16)TempForce;
   SPITransmit((int16)TempForce)  ;
   //printf("Txing %ld\n", TempForce);
*/

}


void SetMotor(signed int16 ForceValue)
{
   int16 ABSForce = 0;

   ABSForce = (int16)abs(ForceValue);
   ABSForce /=2;
   if(ABSForce > 1023) ABSForce = 1023;
   if(ForceValue > 0)
   {
      output_high(MOTOR_DIR1);
      output_low(MOTOR_DIR2);
      set_pwm1_duty(ABSForce);
   }
   else if(ForceValue < 0) 
   {
      output_low(MOTOR_DIR1);
      output_high(MOTOR_DIR2);
      set_pwm1_duty(ABSForce);
   }
   else
   {
      set_pwm1_duty(0);
      output_low(MOTOR_DIR1);
      output_low(MOTOR_DIR2);
      
   }
}
//==============================================================================
void SPITransmit(int16 SPIForceValue)
{
   int16 OutVal = 0;
   //int8 n;
   OutVal = SPIForceValue;

   //OutVal <<=4;

   //for(n = 0; n < 12; n++)
   //{
   //   output_bit( SPI_DTA, shift_left(OutVal, 1, 0) );
   //   output_high(SPI_CLK);
   //   delay_us(TXDELAY);
   //   output_low(SPI_CLK);
   //}

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


//==============================================================================
void SetDAC(int8 Chanel, signed int16 Value)
{
   //Sets the force target DAC - takes a signed int16 between -2048 and 2047
   //first make into an int16
   signed int16 TempVal;

   TempVal = 2047 + Value;
   if(TempVal < 0) TempVal = 0;
   if(TempVal > 4095) TempVal = 4095;

    //Bit values are
    //Higher Byte = (dnt care)    (dnt care)    (mode1)        (mode0)        (Bit 11 MSB)    (Bit 10)    (Bit 9)        (Bit 8)
    //Lower Byte =     (Bit 7)        (Bit 6)        (Bit 5)        (Bit 4)        (Bit 3)            (Bit 2)        (Bit 1)        (Bit 0 LSB)
    //mode bits are(Mode 1 and Mode 0) 00 Normal, 01 1K to gnd, 10 100k to gnd, 11 Tri State.

   if(Chanel == 1)
   {
      output_low(DAC1_CS);
      ClockOutDACValue( (int16)TempVal );
      output_high(DAC1_CS);
   }
   else if(Chanel == 2)
   {
      output_low(DAC2_CS);
      ClockOutDACValue( (int16)TempVal );
      output_high(DAC2_CS);
   }
   else if(Chanel == 3)
   {
      output_low(DAC3_CS);
      ClockOutDACValue( (int16)TempVal );
      output_high(DAC3_CS);
   }
   else return;

}

void HaltActuator()
{
   //Halts the actuator
   Mode = 0;
   
   DisableMotor();
   DisableForce();
   //Pause the motors
}
//==============================================================================
void ResumeActuator()
{
   Mode = 1;
   //Resume Motors
}

//==============================================================================
void EnableMotor()
{
    //output_low( MOTOR_ENABLE );
}

//==============================================================================
void DisableMotor()
{
   //output_high( MOTOR_ENABLE );
   SetMotor(0);
}

//==============================================================================
void EnableForce()
{
   //output_high( ZERO_FORCE_OVERRIDE );
}

//==============================================================================
void DisableForce()
{
   //output_low( ZERO_FORCE_OVERRIDE );
   SetMotor(0);
}
