#pragma once
#include <avr/io.h>

void shift(int a) //Função do registrador de deslocamento
{
  int i=0;
  if(a>0) //Desloca o um ou uns
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
  else if(a<0) //Desloca zeros
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
  else //Desloca o zero
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