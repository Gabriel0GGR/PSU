#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

void shift(int a);
void display(unsigned int a);
void set();
void show();
void power();
void settings();
void storage(unsigned int a, int b);

unsigned int SetV1=0, SetV2=0, SetI1=0, SetI2=0;

void setup()
{
  DDRB = 0b111111; //(1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); //Configura pinos de saída do PORTB
  DDRC = 0b000000; //(0 << DDC0) | (0 << DDC1) | (0 << DDC2) | (0 << DDC3) | (0 << DDC4) | (0 << DDC5); //Configura pinos de entrada do PORTC
  DDRD = 0b11110000; //(0 << DDD0) | (0 << DDD1) | (0 << DDD2) | (0 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7); //Configura pinos de entrada e saída do PORTD
  EICRA = (1 << ISC11); //Configura as interrupções
  EIMSK = (1 << INT1); //Ativa as interrupções
  ICR1 = 0x0FFF; //Configura TOP para 12 bits
  OCR1A = 0;
  OCR1B = 0;
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
  PORTD |= (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2) | (1 << PORTD3); //Ativa pull up
  delayMicroseconds(20000);
  shift(2);
  shift(-3);
  PORTD|=(1 << PORTD7);
  delayMicroseconds(10000);
  PORTD&=~(1 << PORTD7);
  PORTD|=(1 << PORTD7);
  delayMicroseconds(1000);
  PORTD&=~(1 << PORTD7);
  PORTD|=(1 << PORTD7);
  delayMicroseconds(1000);
  shift(1);
  shift(-4);
  PORTD|=(1 << PORTD7);
  delayMicroseconds(1000);
  PORTD&=~(1 << PORTD7);
  display(0x28);
  display(0x0C);
  display(0x01);
  delayMicroseconds(2000);
  PORTD|=(1 << PORTD5);
  display(' ');
  display(' ');
  display('P');
  display('o');
  display('w');
  display('e');
  display('r');
  display(' ');
  display('S');
  display('u');
  display('p');
  display('p');
  display('l');
  display('y');
  PORTD&=~(1 << PORTD5);
  display(0xC0);
  PORTD|=(1 << PORTD5);
  display('G');
  display('a');
  display('b');
  display('r');
  display('i');
  display('e');
  display('l');
  display(' ');
  display('D');
  display('e');
  display('v');
  display('i');
  display('c');
  display('e');
  display('s');
  PORTD&=~(1 << PORTD5);
  sei();
}

ISR(INT1_vect)
{
  EIMSK&=~(1 << INT1);
  shift(3);
  shift(0);
  if(!(PIND&(1 << PIND3)))
  {
    set();
  }
  else
  {
    shift(0);
    if(!(PIND&(1 << PIND3)))
    {
      show();
    }
    else
    {
      shift(0);
      if(!(PIND&(1 << PIND3)))
      {
        power();
      }
      else
      {
        shift(0);
        if(!(PIND&(1 << PIND3)))
        {
          settings();
        }
      }
    }
  }
  PORTD&=~(1 << PORTD5);
  shift(-3);
  EIMSK=(1 << INT1);
}

void loop()
{
  unsigned int i=0;
  i=0;
  for(i; i!=4096; i++)
  {
    OCR1A = i;
    OCR1B = i;
    delayMicroseconds(1000);
    if(i==4095)
    {
      for(i; i!=0; i--)
      {
        OCR1A = i;
        OCR1B = i;
        delayMicroseconds(1000);
      }
    }
  }
}

void shift(int a)
{
  int i=0;
  if(a>0)
  {
    PORTB|=(1 << PORTB4);
    for(i; i<a; i++)
    {
      PORTD|=(1 << PORTD4);
      PORTD&=~(1 << PORTD4);
    }
    PORTB|=(1 << PORTB3);
    PORTB&=~(1 << PORTB3);
  }
  else if(a<0)
  {
    PORTB&=~(1 << PORTB4);
    for(i; i>=a; i--)
    {
      PORTD|=(1 << PORTD4);
      PORTD&=~(1 << PORTD4);
    }
    PORTB|=(1 << PORTB3);
    PORTB&=~(1 << PORTB3);
  }
  else
  {
    PORTB&=~(1 << PORTB4);
    PORTD|=(1 << PORTD4);
    PORTD&=~(1 << PORTD4);
    PORTB|=(1 << PORTB3);
    PORTB&=~(1 << PORTB3);
  }
  a=0;
  i=0;
}

void display(unsigned int a)
{
  char i=8;
  for(i; i>0; i--)
  {
    shift((a & (1 << (i-1))) ? 1 : 0);
  }
  PORTD|=(1 << PORTD7);
  delayMicroseconds(8);
  PORTD&=~(1 << PORTD7);
  shift(-3);
  PORTD|=(1 << PORTD7);
  delayMicroseconds(8);
  PORTD&=~(1 << PORTD7);
}

void set()
{
  char a=0, i=0;
  SetV1=0, SetV2=0, SetI1=0, SetI2=0;
  display(0x01);
  delayMicroseconds(2000);
  PORTD|=(1 << PORTD5);
  display(' ');
  display('S');
  display('E');
  display('T');
  display(' ');
  display('V');
  display('O');
  display('L');
  display('T');
  display('A');
  display('G');
  display('E');
  display(' ');
  display('+');
  display(' ');
  display('-');
  PORTD&=~(1 << PORTD5);
  display(0xC0);
  PORTD|=(1 << PORTD5);
  display(' ');
  display('S');
  display('E');
  display('T');
  display(' ');
  display('C');
  display('U');
  display('R');
  display('R');
  display('E');
  display('N');
  display('T');
  display(' ');
  display('+');
  display(' ');
  display('-');
  PORTD&=~(1 << PORTD5);
  delay(30000);
  display(0x01);
  delayMicroseconds(2000);
  PORTD|=(1 << PORTD5);
  display('V');
  display(' ');
  display('+');
  display('_');
  display('_');
  display('.');
  display('_');
  display('_');
  display(' ');
  display('-');
  display('_');
  display('_');
  display('.');
  display('_');
  display('_');
  display(' ');
  PORTD&=~(1 << PORTD5);
  display(0xC0);
  PORTD|=(1 << PORTD5);
  display('I');
  display(' ');
  display('+');
  display('_');
  display('.');
  display('_');
  display('_');
  display('_');
  display(' ');
  display('-');
  display('_');
  display('.');
  display('_');
  display('_');
  display('_');
  display(' ');
  PORTD&=~(1 << PORTD5);
  display(0x80);
  display(0x14);
  display(0x14);
  display(0x14);
  display(0x0F);
  PORTD|=(1 << PORTD5);
  loop:
  shift(3);
  shift(0);
  delayMicroseconds(2000);
  if((!(PIND&(1 << PIND0)))|(!(PIND&(1 << PIND1)))|(!(PIND&(1 << PIND2)))|(!(PIND&(1 << PIND3))))
  {
    if(!(PIND&(1 << PIND0)))
    {
      display('1');
      storage(i, 1);
      a=1;
    }
    else if(!(PIND&(1 << PIND1)))
    {
      display('2');
      storage(i, 2);
      a=2;
    }
    else if(!(PIND&(1 << PIND2)))
    {
      display('3');
      storage(i, 3);
      a=3;
    }
    else if(!(PIND&(1 << PIND3)))
    {
      set();
    }
    wait0:
    delayMicroseconds(2000);
    if((!(PIND&(1 << PIND0)))|(!(PIND&(1 << PIND1)))|(!(PIND&(1 << PIND2)))|(!(PIND&(1 << PIND3))))
      goto wait0;
  }
  else
  {
    shift(0);
    if((!(PIND&(1 << PIND0)))|(!(PIND&(1 << PIND1)))|(!(PIND&(1 << PIND2)))|(!(PIND&(1 << PIND3))))
    {
      if(!(PIND&(1 << PIND0)))
      {
        display('4');
        storage(i, 4);
        a=4;
      }
      else if(!(PIND&(1 << PIND1)))
      {
        display('5');
        storage(i, 5);
        a=5;
      }
      else if(!(PIND&(1 << PIND2)))
      {
        display('6');
        storage(i, 6);
        a=6;
      }
      else if(!(PIND&(1 << PIND3)))
      {
        show();
      }
      wait1:
      delayMicroseconds(2000);
      if((!(PIND&(1 << PIND0)))|(!(PIND&(1 << PIND1)))|(!(PIND&(1 << PIND2)))|(!(PIND&(1 << PIND3))))
        goto wait1;
    }
    else
    {
      shift(0);
      if((!(PIND&(1 << PIND0)))|(!(PIND&(1 << PIND1)))|(!(PIND&(1 << PIND2)))|(!(PIND&(1 << PIND3))))
      {
        if(!(PIND&(1 << PIND0)))
        {
          display('7');
          storage(i, 7);
          a=7;
        }
        else if(!(PIND&(1 << PIND1)))
        {
          display('8');
          storage(i, 8);
          a=8;
        }
        else if(!(PIND&(1 << PIND2)))
        {
          display('9');
          storage(i, 9);
          a=9;
        }
        else if(!(PIND&(1 << PIND3)))
        {
          power();
        }
        wait2:
        delayMicroseconds(2000);
        if((!(PIND&(1 << PIND0)))|(!(PIND&(1 << PIND1)))|(!(PIND&(1 << PIND2)))|(!(PIND&(1 << PIND3))))
          goto wait2;
      }
      else
      {
        shift(0);
        if((!(PIND&(1 << PIND0)))|(!(PIND&(1 << PIND1)))|(!(PIND&(1 << PIND2)))|(!(PIND&(1 << PIND3))))
        {
          if(!(PIND&(1 << PIND0)))
          {
            if((a!=-1)&(i!=0))
            {
              switch (i)
              {
                case 2:
                  PORTD&=~(1 << PORTD5);
                  display(0x10);
                  PORTD|=(1 << PORTD5);
                break;
                case 4:
                  PORTD&=~(1 << PORTD5);
                  display(0x10);
                  display(0x10);
                  PORTD|=(1 << PORTD5);
                break;
                case 6:
                  PORTD&=~(1 << PORTD5);
                  display(0x10);
                  PORTD|=(1 << PORTD5);
                break;
                case 8:
                  PORTD&=~(1 << PORTD5);
                  display(0x80);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  display(0x14);
                  PORTD|=(1 << PORTD5);
                break;
                case 9:
                  PORTD&=~(1 << PORTD5);
                  display(0x10);
                  PORTD|=(1 << PORTD5);
                break;
                case 12:
                  PORTD&=~(1 << PORTD5);
                  display(0x10);
                  display(0x10);
                  PORTD|=(1 << PORTD5);
                break;
                case 13:
                  PORTD&=~(1 << PORTD5);
                  display(0x10);
                  PORTD|=(1 << PORTD5);
                break;
              }
              PORTD&=~(1 << PORTD5);
              display(0x10);
              PORTD|=(1 << PORTD5);
              i-=1;
              storage(i, -a);
            }
            a=-1;
            goto loop;
          }
          else if(!(PIND&(1 << PIND1)))
          {
            display('0');
          }
          else if(!(PIND&(1 << PIND2)))
          {
            i=15;
          }
          else if(!(PIND&(1 << PIND3)))
          {
            if(i<8)
            {
              PORTD&=~(1 << PORTD5);
              display(0xC0);
              display(0x14);
              display(0x14);
              display(0x14);
              PORTD|=(1 << PORTD5);
              i=8;
              goto loop;
            }
            else
            {
              PORTD&=~(1 << PORTD5);
              display(0x80);
              display(0x14);
              display(0x14);
              display(0x14);
              PORTD|=(1 << PORTD5);
              i=-1;
            }
          }
          wait3:
          delayMicroseconds(2000);
          if((!(PIND&(1 << PIND0)))|(!(PIND&(1 << PIND1)))|(!(PIND&(1 << PIND2)))|(!(PIND&(1 << PIND3))))
            goto wait3;
        }
        else
        {
          goto loop;
        }
      }
    }
  }
  i++;
  switch (i)
  {
    case 2:
      PORTD&=~(1 << PORTD5);
      display(0x14);
      PORTD|=(1 << PORTD5);
    break;
    case 4:
      PORTD&=~(1 << PORTD5);
      display(0x14);
      display(0x14);
      PORTD|=(1 << PORTD5);
    break;
    case 6:
      PORTD&=~(1 << PORTD5);
      display(0x14);
      PORTD|=(1 << PORTD5);
    break;
    case 8:
      PORTD&=~(1 << PORTD5);
      display(0xC0);
      display(0x14);
      display(0x14);
      display(0x14);
      PORTD|=(1 << PORTD5);
    break;
    case 9:
      PORTD&=~(1 << PORTD5);
      display(0x14);
      PORTD|=(1 << PORTD5);
    break;
    case 12:
      PORTD&=~(1 << PORTD5);
      display(0x14);
      display(0x14);
      PORTD|=(1 << PORTD5);
    break;
    case 13:
      PORTD&=~(1 << PORTD5);
      display(0x14);
      PORTD|=(1 << PORTD5);
    break;
    case 16:
      i=0;
      storage(32, 0);
    break;
  }
  goto loop;
}

void show()
{
  display(0x01);
}

void power()
{
  display(0x01);
}

void settings()
{
  display(0x01);
}

void storage(unsigned int a, int b)
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
      else if(SetI2=0)
        SetI2=SetI1;
      else if(SetI1=0)
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