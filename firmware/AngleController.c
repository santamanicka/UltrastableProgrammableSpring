#include "AngleController.h"
#include "Defines.h"
#include "FlashDefineList.h"
#include "Variables.h"
#include "Multipliers.h"
#include "PeripheralFunctions.h"
#include "FlashFunctions.h"
#include "SerialFunctions.h"
#include "ProfileFunctions.h"



#zero_ram


//FUNCTION DEFS============================================================================
//Interrupts:
#int_timer1
void Timer1Interrupt();

#int_rda
void SerialInputInterrupt();

void SetupVariables();
//void SPISendByte(int16 Value)
void ClockOutDACValue(int16 Value);
void SetDAC(int8 Chanel, signed int16 Value);


//MAIN====================================================================================

void main()
{

   int8 n;
   int8 NewProfile;
   int8 SerialParserError = 0;
   int8 RefreshActuatorSettings = 0;
   int16 Timer0Value = 0;
   int16 MaxTime = 30000;
   int16 DelayTime = 0;

   setup_adc_ports(AN0_TO_AN5|VSS_VDD);
   setup_adc(ADC_CLOCK_INTERNAL|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_spi(FALSE);
   setup_wdt(WDT_OFF);
   //setup_timer_0(RTCC_DIV_64|RTCC_INTERNAL);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8);
   setup_timer_2(T2_DIV_BY_4,255,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   
   setup_ccp1(CCP_PWM);
   
   
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(False);
   enable_interrupts(int_rda);
   output_low(MOTOR_DIR1);
   output_low(MOTOR_DIR2);

    DisableMotor();
    DisableForce();

    SetForce(0);
    SetForce(0);

   //First check to see if any profiles reside in flash
   //Innitialise the profiles
   CurrentProfile = 0;
   for(n = 0; n < FLASH_PROFILES; n++)
      {
         //setup the array of memory addresses for the start of each flash profile
         FlashProfileStart[n] = FLASH_PROFILE_START + ( 1024 * n );
      }
    for(n = 0; n < PROFILES; n++)
      {
         if(CheckProfileIsInFlash(n) == 0)
         {
            CreateDefaultProfile(n);
            SetProfileLoadedFlag(n);
            printf("Create Default Pro %u\n", n);
            RefreshActuatorSettings = 1;
         }
         else
         {
            UnpackFlashProfileToRAM(n);     
            printf("Load Pro %u\n", n);
            
         }
      }
      
      //if profiles were not in RAM (i.e. the chip has just been re-flashed)
      //Update the actuator confing settings in flash
      if( RefreshActuatorSettings == 1)
      {
         CopyActuatorSettingsToBuffers();
         SaveActuatorSettingBuffersToFlash();
      }
      //if you already have profiles (and we assume settings as well!) then copy them to RAM
   else UnpackActuaotrConfiguration();
   
   CurrentProfile = StartingProfile;
   Mode = StartingMode;
   NewProfile = CurrentProfile;
   //CheckExIn(CurrentProfile );
   SetForce(0);

   //EnableMotor();
   //EnableForce();
   
   

    //fprintf(PRIMARY_STREAM, "\nProgrammable Spring V3.0\nInitialising\n");

   enable_interrupts(GLOBAL);
   /*
   for(n = 0; n < 20; n++)
   {
      for(MPow1 = 0; MPow1 < 2048; MPow1++)
      {
         SetMotor(MPow1);
         delay_ms(1);
      }
      for(MPow1 = 2047; MPow1 > -2048; MPow1--)
      {
         SetMotor(MPow1);
         delay_ms(1);
      }
      for(MPow1 = -2047; MPow1 < 1; MPow1++)
      {
         SetMotor(MPow1);
         delay_ms(1);
      }
   }
   */

    while(1)
    {
       set_timer0(0);
      SerialParserError = ParseSerialBuffer();
      //read the analog sensors
      if(Mode == 1)
      {                                                                        
         IterateProfile();
         Timer0Value = get_timer0();
         if(Timer0Value < MaxTime)
         {
            DelayTime = MaxTime - Timer0Value;
            delay_us (DelayTime);
         }

         //printf("\nT0=%ld\n", Timer0Value);
         delay_ms(100);
      }
      else if(Mode == 0)
      {
         delay_ms(50);
         //Angle = 519;
      }
   }

}
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#int_timer1
void Timer1Interrupt()
{
   //this is used as a serial input timeout tester
   SerialTimerTimeout = 1;

}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#int_rda
void SerialInputInterrupt()
{

   InBuffer[NextIn] = getc();
   #IFDEF SERIAL_RDA_DEBUG
   putc(InBuffer[NextIn]);

   #ENDIF
   NextIn++;
   if(NextIn == BUFFERSIZE) NextIn = 0;
   BufferInOutDifference++;
   if(BufferInOutDifference == BUFFERSIZE)
   {
      BufferInOutDifference = 0;
      BufferOverflowError = 1;
      PreambleOK = 0;
   }
}


//==============================================================================
void SetupVariables()
{


    GlobalThresholdDisabled = 0;
    GlobalThresholdEnabled = 1;
    GlobalDefaultZeroModulator = 0;
   GlobalDefaultFalse = 0;
   GlobalDefaultTrue = 1;
}


//==============================================================================
/*
void SPISendByte(int16 Value)
{
   //sends two bytes out over the SPI
   int8 HiByte, LowByte;
   HiByte = make8(Value, 1);
   LowByte = make8(Value, 0);

   //first the lower byte
   output_high(BYTESELECT);
   spi_write(HiByte);
   delay_us(50);
   output_low(BYTESELECT);
   //then the upper byte
   spi_write(LowByte);
}
*/


