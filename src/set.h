#pragma once
#include <avr/io.h>
#include <Arduino.h>
#include <display.h>
#include <show.h>
#include <power.h>
#include <storage.h>

void set() //Menu SET
{
  char a=0, i=0;
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