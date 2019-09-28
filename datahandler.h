#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string> 
#include <vector>
#include <fstream> 
#include <sstream> 
#include "student.h"

using namespace std;

class datahandler
{
   public:
      void makeuser();
      void changePassword();
      void displayscores(vector<student> &list);
      void displayexam(vector<student> &list);
      void studentavg(vector<student> &list);
      void examavg(vector<student> &list);
      void insertexam();
      void insertNewExam(vector<student> &list);
      void newstudent(vector<student> &list);
      int enterscore(istringstream &inSS);
      int isvalidID(string id);
      int enterExamNum(vector<student> &list);
      int doesIDexist(string id, vector<student> &list);
      void updateFile(vector<student> &list);
      void updateStudentExam(vector<student> &list);
      string studentsearch(vector<student> &list, int &position);
      void updateAllExams(vector<student> &list);
      void checkAccess();
      void updateAccounts(ifstream &in1, ofstream &of1, string &total, string &line);
   private:
      string login, pass;
      bool access = 0;
};
#endif