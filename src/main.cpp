#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

#include <start.h>
#include <shift.h>
#include <display.h>
#include <set.h>
#include <show.h>
#include <power.h>
#include <settings.h>

//void shift(int a);
//void display(unsigned int a);
//void set();
//void show();
//void power();
//void settings();
//void storage(unsigned int a, int b);

unsigned int SetV1=0, SetV2=0, SetI1=0, SetI2=0, I1=0, I2=0, V1_50V=0, V2_50V=0, V1_15V=0, V2_15V=0;
float voltage_pwm_coefficients[63][1][1]={{{0}}};

void setup()
{
  Serial.begin(230400);
  DDRB = 0b111111; //(1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); //Configura pinos de saída do PORTB
  DDRC = 0b000000; //(0 << DDC0) | (0 << DDC1) | (0 << DDC2) | (0 << DDC3) | (0 << DDC4) | (0 << DDC5); //Configura pinos de entrada do PORTC
  DDRD = 0b11110000; //(0 << DDD0) | (0 << DDD1) | (0 << DDD2) | (0 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7); //Configura pinos de entrada e saída do PORTD
  EICRA = (1 << ISC11); //Configura as interrupções
  EIMSK = (1 << INT1); //Ativa as interrupções
  ICR1 = 0x0FFF; //Configura TOP para 12 bits
  OCR1A = 0; //Zera registrador do Timer 1 do PWM 1
  OCR1B = 0; //Zera registrador do Timer 1 do PWM 2
  OCR2A = 200; //Zera registrador do Timer 2 do PWM 3
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11); //Configura PWMs e modo do Timer 1
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10); //Configura modo e prescaler do Timer 1
  TCCR2A = (1 << COM2A1) | (1 << COM2A0) | (1 << WGM21) | (1 << WGM20); //Configura PWMs e modo do Timer 2
  TCCR2B = (1 << CS20); //Configura prescaler do Timer 2
  PORTD |= (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2) | (1 << PORTD3); //Ativa pull up do PORTD
  PORTC = 0x00; //Desabilita pull up PORTC
  ADMUX = 0x00; //Habilita AREF e ajusta ADC à direita
  ADCSRA = 0b10001111; //Configura interrupção e prescaler do ADC
  ADCSRB = 0x00; //Habilita conversão contínua no ADC
  DIDR0 = 0xFF; //Desativa o PORTC como entrada digital
  //Inicialização do display:
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
  //Imprimi o menu inicial:
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
  ADCSRA |= (1 << ADSC); //Inicia conversões do ADC
  sei(); //Habilita as interrupções globais
  start(); //Executa a função de autostart
}

ISR(INT1_vect) //Interrupção INT1
{
  EIMSK&=~(1 << INT1); //Desativa interrupção INT1
  shift(3);
  shift(0);
  if(!(PIND&(1 << PIND3)))
  {
    set(); //Entra no menu SET
  }
  else
  {
    shift(0);
    if(!(PIND&(1 << PIND3)))
    {
      show(); //Entra no menu SHOW
    }
    else
    {
      shift(0);
      if(!(PIND&(1 << PIND3)))
      {
        power(); //Entra no menu POWER
      }
      else
      {
        shift(0);
        if(!(PIND&(1 << PIND3)))
        {
          settings(); //Entra no menu SETTINGS
        }
      }
    }
  }
  PORTD&=~(1 << PORTD5);
  shift(-3);
  EIMSK=(1 << INT1); //Habilita a interrupção INT1
}

ISR(ADC_vect)
{
  switch(ADMUX)
  {
    case 0:
      storage(123, ADC);
      ADMUX=1;
    break;
    case 1:
      storage(124, ADC);
      ADMUX=2;
    break;
    case 2:
      storage(125, ADC);
      ADMUX=3;
    break;
    case 3:
      storage(126, ADC);
      ADMUX=4;
    break;
    case 4:
      storage(127, ADC);
      ADMUX=5;
    break;
    case 5:
      storage(128, ADC);
      ADMUX=0;
    break;
  }
  ADCSRA |= (1 << ADSC);
}

void loop()
{
  unsigned int i=0;
  i=0;
  for(i; i!=4096; i++)
  {
    OCR1A = i;
    OCR1B = i;
    delayMicroseconds(10);
    if(i==4095)
    {
      for(i; i!=0; i--)
      {
        OCR1A = i;
        OCR1B = i;
        delayMicroseconds(10);
      }
    }
  }
}