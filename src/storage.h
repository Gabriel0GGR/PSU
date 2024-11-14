#pragma once
unsigned int SetV1=0, SetV2=0, SetI1=0, SetI2=0;

void storage(unsigned char a, char b)
{
    char V1_0, V1_1, V1_2, V1_3, V2_0, V2_1, V2_2, V2_3, I1_0, I1_1, I1_2, I1_3, I2_0, I2_1, I2_2, I2_3;
    switch (a)
    {
        case 0:
            SetV1=(SetV1%1000);
            SetV1+=b*1000;
        break;
        case 1:
            SetV1=((SetV1/1000)*1000)+(SetV1%100);
            SetV1+=b*100;
        break;
        case 2:
            SetV1=((SetV1/100)*100)+(SetV1%10);
            SetV1+=b*10;
        break;
        case 3:
            SetV1=((SetV1/10)*10);
            SetV1+=b;
        break;
        case 4:
            SetV2=(SetV2%1000);
            SetV2+=b*1000;
        break;
        case 5:
            SetV2=((SetV2/1000)*1000)+(SetV2%100);
            SetV2+=b*100;
        break;
        case 6:
            SetV2=((SetV2/100)*100)+(SetV2%10);
            SetV2+=b*10;
        break;
        case 7:
            SetV2=((SetV2/10)*10);
            SetV2+=b;
        break;
        case 8:
            SetI1+=b*1000;
        break;
        case 9:
            SetI1+=b*100;
        break;
        case 10:
            SetI1+=b*10;
        break;
        case 11:
            SetI1+=b;
        break;
        case 12:
            SetI2+=b*1000;
        break;
        case 13:
            SetI2+=b*100;
        break;
        case 14:
            SetI2+=b*10;
        break;
        case 15:
            SetI2+=b;
        break;
        case 32:
            if(SetV1==0 & SetV2==0)
                SetV1=500, SetV2=500;
            else if(SetV2==0)
                SetV2=SetV1;
            else if(SetV1==0)
                SetV1=SetV2;
            if(SetI1==0 & SetI2==0)
                SetI1=3000, SetI2=3000;
            else if(SetI2==0)
                SetI2=SetI1;
            else if(SetI1==0)
                SetI1=SetI2;
            V1_3=(SetV1/1000)+48;
            V1_2=((SetV1/100)%10)+48;
            V1_1=((SetV1/10)%10)+48;
            V1_0=(SetV1%10)+48;
            V2_3=(SetV2/1000)+48;
            V2_2=((SetV2/100)%10)+48;
            V2_1=((SetV2/10)%10)+48;
            V2_0=(SetV2%10)+48;
            I1_3=(SetI1/1000)+48;
            I1_2=((SetI1/100)%10)+48;
            I1_1=((SetI1/10)%10)+48;
            I1_0=(SetI1%10)+48;
            I2_3=(SetI2/1000)+48;
            I2_2=((SetI2/100)%10)+48;
            I2_1=((SetI2/10)%10)+48;
            I2_0=(SetI2%10)+48;
            PORTD&=~(1 << PORTD5);
            display(0x08);
            display(0x01);
            delayMicroseconds(2000);
            display(0x0C);
            PORTD|=(1 << PORTD5);
            display(V1_3);
            display(V1_2);
            PORTD&=~(1 << PORTD5);
            display(0x14);
            PORTD|=(1 << PORTD5);
            display(V1_1);
            display(V1_0);
            PORTD&=~(1 << PORTD5);
            display(0x14);
            display(0x14);
            PORTD|=(1 << PORTD5);
            display(V2_3);
            display(V2_2);
            PORTD&=~(1 << PORTD5);
            display(0x14);
            PORTD|=(1 << PORTD5);
            display(V2_1);
            display(V2_0);
            PORTD&=~(1 << PORTD5);
            display(0xC0);
            display(0x14);
            display(0x14);
            display(0x14);
            PORTD|=(1 << PORTD5);
            display(I1_3);
            PORTD&=~(1 << PORTD5);
            display(0x14);
            PORTD|=(1 << PORTD5);
            display(I1_2);
            display(I1_1);
            display(I1_0);
            PORTD&=~(1 << PORTD5);
            display(0x14);
            display(0x14);
            PORTD|=(1 << PORTD5);
            display(I2_3);
            PORTD&=~(1 << PORTD5);
            display(0x14);
            PORTD|=(1 << PORTD5);
            display(I2_2);
            display(I2_1);
            display(I2_0);
            PORTD&=~(1 << PORTD5);
        break;
    }
}