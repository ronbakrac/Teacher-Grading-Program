#ifndef STUDENT_H
#define STUDENT_H

#include <string>  
#include <vector> 

using namespace std;

class student
{
   public:
      void setUID(string ID);
      void setexams(int exam);
      string getUID();
      vector<int> getexams();
      void printexams(fstream &f1);
      void clearexams();
      void changeStudentExam(int exnum, int newscore);
   private:
      vector<int> exams;
      string UID;

};
#endif