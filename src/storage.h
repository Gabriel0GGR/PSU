#pragma once
unsigned int SetV1=0, SetV2=0, SetI1=0, SetI2=0, I1=0, I2=0, V1_50V=0, V2_50V=0, V1_15V=0, V2_15V=0;
bool c=0;

void storage(unsigned char a, int b)
{
    char V1_0, V1_1, V1_2, V1_3, V2_0, V2_1, V2_2, V2_3, I1_0, I1_1, I1_2, I1_3, I2_0, I2_1, I2_2, I2_3;
    switch (a)
    {
        case 0:
            if(c==1)
                SetV1=(SetV1%1000);
            SetV1+=b*1000;
        break;
        case 1:
            if(c==1)
                SetV1=((SetV1/1000)*1000)+(SetV1%100);
            SetV1+=b*100;
        break;
        case 2:
            if(c==1)
                SetV1=((SetV1/100)*100)+(SetV1%10);
            SetV1+=b*10;
        break;
        case 3:
            if(c==1)
                SetV1=((SetV1/10)*10);
            SetV1+=b;
        break;
        case 4:
            if(c==1)
                SetV2=(SetV2%1000);
            SetV2+=b*1000;
        break;
        case 5:
            if(c==1)
                SetV2=((SetV2/1000)*1000)+(SetV2%100);
            SetV2+=b*100;
        break;
        case 6:
            if(c==1)
                SetV2=((SetV2/100)*100)+(SetV2%10);
            SetV2+=b*10;
        break;
        case 7:
            if(c==1)
                SetV2=((SetV2/10)*10);
            SetV2+=b;
        break;
        case 8:
            if(c==1)
                SetI1=(SetI1%1000);
            SetI1+=b*1000;
        break;
        case 9:
            if(c==1)
                SetI1=((SetI1/1000)*1000)+(SetI1%100);
            SetI1+=b*100;
        break;
        case 10:
            if(c==1)
                SetI1=((SetI1/100)*100)+(SetI1%10);
            SetI1+=b*10;
        break;
        case 11:
            if(c==1)
                SetI1=((SetI1/10)*10);
            SetI1+=b;
        break;
        case 12:
            if(c==1)
                SetI2=(SetI2%1000);
            SetI2+=b*1000;
        break;
        case 13:
            if(c==1)
                SetI2=((SetI2/1000)*1000)+(SetI2%100);
            SetI2+=b*100;
        break;
        case 14:
            if(c==1)
                SetI2=((SetI2/100)*100)+(SetI2%10);
            SetI2+=b*10;
        break;
        case 15:
            if(c==1)
                SetI2=((SetI2/10)*10);
            SetI2+=b;
        break;
        case 16:
            SetV1=0;
            SetV2=0;
            SetI1=0;
            SetI2=0;
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
            display(0x0C);
            display(0x80);
            display(0x14);
            display(0x14);
            display(0x14);
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
            delay(200000);
            show();
        break;
        case 63:
            c=0;
        break;
        case 64:
            c=1;
        break;
        case 123:
            I1=b;
        break;
        case 124:
            I2=b;
        break;
        case 125:
            V1_50V=b;
        break;
        case 126:
            V2_50V=b;
        break;
        case 127:
            V1_15V=b;
        break;
        case 128:
            V2_15V=b;
        break;
    }
        Serial.print("\t ADMUX=");
        Serial.flush();
        Serial.print(ADMUX, DEC);
        Serial.print("\t I1=");
        Serial.flush();
        Serial.print(I1, DEC);
        /*+Serial.flush();
        Serial.print("\t I2=");
        Serial.flush();
        Serial.print(I2, DEC);
        Serial.flush();
        Serial.print("\t V1_50=");
        Serial.flush();
        Serial.print(V1_50V, DEC);
        Serial.flush();
        Serial.print("\t V2_50=");
        Serial.flush();
        Serial.print(V2_50V, DEC);
        Serial.flush();
        Serial.print("\t V1_15=");
        Serial.flush();
        Serial.print(V1_15V, DEC);
        Serial.flush();
        Serial.print("\t V2_15=");
        Serial.flush();
        Serial.print(V1_15V, DEC);
        Serial.flush();*/
}