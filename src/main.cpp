#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Arduino.h>

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

void setup()
{
  DDRB = 0b111111; //(1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5); //Configura pinos de saída do PORTB
  DDRC = 0b000000; //(0 << DDC0) | (0 << DDC1) | (0 << DDC2) | (0 << DDC3) | (0 << DDC4) | (0 << DDC5); //Configura pinos de entrada do PORTC
  DDRD = 0b11110000; //(0 << DDD0) | (0 << DDD1) | (0 << DDD2) | (0 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7); //Configura pinos de entrada e saída do PORTD
  EICRA = (1 << ISC11); //Configura as interrupções
  EIMSK = (1 << INT1); //Ativa as interrupções
  ICR1 = 0x0FFF; //Configura TOP para 12 bits
  OCR1A = 0; //Zera registrador do timer do PWM 1
  OCR1B = 0; //Zera registrador do timer do PWM 2
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11); //Configura modo e prescaler do PWM 1
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10); //Configura modo e prescaler do PWM 2
  PORTD |= (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2) | (1 << PORTD3); //Ativa pull up
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
  sei(); //Habilita as interrupções globais
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