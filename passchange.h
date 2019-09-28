#ifndef PASSCHANGE_H
#define PASSCHANGE_H

#include <string>

using namespace std;

class Pwdg
{
   public:
      Pwdg(int L) : length(L){}
      string getPWD();
      int getLength();
      int setLength(int x);
   
   private:
      int length;
};

class Simple_pwdg : public Pwdg
{
   public:
      Simple_pwdg(int L) : Pwdg(L){}
      string getSimplePWD(char x);
};
#endif