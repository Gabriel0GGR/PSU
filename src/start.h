#pragma once
extern unsigned int SetV1, SetV2, SetI1, SetI2, I1, I2, V1_50V, V2_50V, V1_15V, V2_15V;
extern float voltage_pwm_coefficients[63][1][1];
unsigned int x0=0, x1=0, y0=0, y1=0;

void start()
{
    for(int8_t i=0; i<63; i++)
    {
        OCR1A=(65*i);
        y0=y1;
        y1=65*i;
        delayMicroseconds(9000);
        x0=x1;
        if(V1_15V<1023)
            x1=V1_15V;
        else
            x1=V1_50V;
        delayMicroseconds(1);
        voltage_pwm_coefficients[i][0][0]=(static_cast<float>(y1-y0)/static_cast<float>(x1-x0)); //Coeficiente angular
        voltage_pwm_coefficients[i][1][0]=(y0-(voltage_pwm_coefficients[i][0][0]*x0)); //Coeficiente linear
    }
}