#pragma once
#include <avr/io.h>
#include <Arduino.h>
#include <shift.h>

void display(unsigned int a) //Função do display LCD
{
  char i=8;
  for(; i>0; i--)
  {
    shift((a & (1 << (i-1))) ? 1 : 0); //Extrai bit a bit o valor de 'a'
  }
  PORTD|=(1 << PORTD7);
  delayMicroseconds(8);
  PORTD&=~(1 << PORTD7);
  shift(-3);
  PORTD|=(1 << PORTD7);
  delayMicroseconds(8);
  PORTD&=~(1 << PORTD7);
}