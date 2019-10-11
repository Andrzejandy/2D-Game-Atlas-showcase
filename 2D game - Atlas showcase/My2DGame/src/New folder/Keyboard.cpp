#include "Keyboard.h"

Keyboard::Keyboard()
{
     w = false;
     a = false;
     s = false;
     d = false;
     z = false;
     x = false;
     isSet = false;
     KeyUpW, KeyUpS, KeyUpA, KeyUpD = false;
}

Keyboard::~Keyboard()
{
    //dtor
}

void Keyboard::SetKeyDown(char key)
{
 if(key == 'w')
 {
  w = true;
 }
 if(key == 'a')
 {
  a = true;
 }
 if(key == 's')
 {
  s = true;
 }
 if(key == 'd')
 {
  d = true;
 }
 if(key == 'z')
 {
  z = true;
 }
 if(key == 'x')
 {
  x = true;
 }
}

void Keyboard::SetKeyUp(char key)
{
 if(key == 'w')
 {
  w = false;
 }
 if(key == 'a')
 {
  a = false;
 }
 if(key == 's')
 {
  s = false;
 }
 if(key == 'd')
 {
  d = false;
 }
 if(key == 'z')
 {
  z = false;
 }
 if(key == 'x')
 {
  x = false;
 }
}

bool Keyboard::isKeyDown(char key)
{
 switch(key)
 {
 case('w'):
  return w;
  break;
 case('a'):
  return a;
  break;
 case('s'):
  return s;
  break;
 case('d'):
  return d;
  break;
 case('z'):
  return z;
  break;
 case('x'):
  return x;
  break;
 default:
  return false;
  break;

 }
}
