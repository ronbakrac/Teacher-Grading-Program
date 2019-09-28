#include <string>
#include "passchange.h"

using namespace std;

string Pwdg::getPWD()
{
   int i, j;
   string list="0123456789!@#$%^&*+-=abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   string password;
   
   for(i=0; i<length; ++i)
   {
      j=rand()%(list.size());
      password.push_back(list.at(j));
   }

   return password;
}

int Pwdg::getLength()
{
   return length;
}

int Pwdg::setLength(int x)
{
   length = x;
}


string Simple_pwdg::getSimplePWD(char x)
{
   int i, j;
   string list="0123456789!@#$%^&*+-=abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   string password;
   
   if(x=='D')
   {
      for(i=0; i<Pwdg::getLength(); ++i)
      {
         j=rand()%10;
         password.push_back(list.at(j));
      }
      
      return password;
    }
    
    
    else if(x=='L')
    {
      for(i=0; i<Pwdg::getLength(); ++i)
      {
         j=rand()%(list.size()-21) + 21;
         password.push_back(list.at(j));
      }
      
      return password;
    }
    
    else
      Pwdg::getPWD();
}