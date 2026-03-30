signed int16 SMul1(signed int16 Value, signed int16 Multiplier);

//performs fixed point multiplication with two decimal places
//Sending 50, 123,will multiply 50 by 1.23
signed int16 SMul2(signed int16 Value, signed int16 Multiplier);

//performs fixed point multiplication with one decimal place
//Sending 50, 123,will multiply 50 by 12.3
signed int16 SMul1Sat(signed int16 Value, signed int16 Multiplier, signed int16 Saturation);

//performs fixed point multiplication with two decimal places
//Sending 50, 123,will multiply 50 by 1.23
signed int16 SMul2Sat(signed int16 Value, signed int16 Multiplier, signed int16 Saturation);




//==============================================================================
//performs fixed point multiplication with one decimal place
//Sending 50, 123,will multiply 50 by 12.3
signed int16 SMul1(signed int16 Value, signed int16 Multiplier)
{
    signed int16 buff;

    //Multiply the Value by the Multiplier unles 10 (1.0)
    if(Multiplier == 10) return Value;
    buff = Value * Multiplier;

    buff /= 10;

    return buff;
}

//==============================================================================
//performs fixed point multiplication with two decimal places
//Sending 50, 123,will multiply 50 by 1.23
signed int16 SMul2(signed int16 Value, signed int16 Multiplier)
{
    signed int32 buff;

    //Multiply the Value by the Multiplier if not 100 (1.0)
    if(Multiplier == 100) return Value;
    buff = (signed int32)Value * (signed int32)Multiplier;

    buff /= 100;

    return (signed int16)buff;
}

//==============================================================================
//performs fixed point multiplication with one decimal place
//Sending 50, 123,will multiply 50 by 12.3
signed int16 SMul1Sat(signed int16 Value, signed int16 Multiplier, signed int16 Saturation)
{
    signed int32 buff;

    //Multiply the Value by the Multiplier
    buff = (signed int32)Value * (signed int32)Multiplier;

    buff /= 10;
    //check the saturation level
    if(buff > Saturation) return Saturation;
    else if(buff < -Saturation) return -Saturation;
    else return (signed int16)buff;
}

//==============================================================================
//performs fixed point multiplication with two decimal places
//Sending 50, 123,will multiply 50 by 12.3
signed int16 SMul2Sat(signed int16 Value, signed int16 Multiplier, signed int16 Saturation)
{
    signed int32 buff;

    //Multiply the Value by the Multiplier
    buff = (signed int32)Value * (signed int32)Multiplier;

    buff /= 100;
    //check the saturation level
    if(buff > Saturation) return Saturation;
    else if(buff < -Saturation) return -Saturation;
    else return (signed int16)buff;
}


