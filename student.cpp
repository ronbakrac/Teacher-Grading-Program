#include <string>  
#include <vector> 
#include <fstream>
#include "student.h"

using namespace std;

void student::setUID(string fUID)
{
   UID = fUID;
}

void student::setexams(int exam)
{
   exams.push_back(exam);
}

string student::getUID()
{
   return UID;
}

vector<int> student::getexams()
{
   return exams;
}

void student::printexams(fstream &f1)
{
   vector<int>::iterator it;
   for(it=exams.begin(); it != exams.end(); ++it)
      f1 << (*it) << " ";
   
   f1 << endl;
}

void student::clearexams()
{
   exams.clear();
}

void student::changeStudentExam(int exnum, int newscore)
{
   exams.at(exnum) = newscore;
}
