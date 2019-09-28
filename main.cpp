#include <iostream> //cin cout
#include <fstream> //fstream
#include <string>  //string
#include <vector>  //vector
#include <sstream> //stringstream
#include <ctype.h> // toupper
#include <stdlib.h> //srand
#include <time.h>  //time
#include "passchange.h"
#include "student.h"
#include "datahandler.h"


using namespace std;

int main()
{
   datahandler dat1;
   vector<student> list;
   int input, exam;
   fstream if1;
   istringstream iss;
   string line, fuid, examline, filename="Data\\scores.txt";
   if1.open(filename, ios::in);
   int i=0;
   srand(time(0));
   
   if (!if1.is_open()) 
   {
      cout << "Could not open file " << filename << endl;
      exit(0);
   }
   
   //This block scans scores.txt and creates an object, student, for every ID it finds. Every student object
   //has a string ID and a vector of integers for their score (which this block of code fills in)
   while(!if1.eof())
   {
      student stu;
      if1 >> fuid;
      if(if1.fail())
      {
         if1.clear();
         break;
      }
      stu.setUID(fuid);
      getline(if1, line);
      iss.str(line);
      while(iss >> exam)
         stu.setexams(exam);
    
      list.push_back(stu);
      iss.clear();
   }
   if1.close();
   
   do
   {
      cout << "(1) Create a new user\n(2) Change password\n(3) Display scores of a student\n(4) Display scores of an exam\n"
               "(5) Display avg score of a student\n(6) Display avg score of an exam\n(7) Insert scores of a new exam to all students\n"
               "(8) Insert scores of all exams of a student who is not in file\n(9) Update an exam score of a student\n"
               "(10) Update an exam score of every student\n(11) Exit\nEnter: ";
   
      cin >> input;
      cin.clear();
      cin.ignore(1000, '\n');
   
      try
      {
         switch(input)
         {
            case 1:
               dat1.makeuser();
               break;
            case 2:
               dat1.changePassword();
               break;
            case 3:
               dat1.displayscores(list);
               break;
            case 4:
               dat1.displayexam(list);
               break;
            case 5:
               dat1.studentavg(list);
               break;
            case 6:
               dat1.examavg(list);
               break;
            case 7:
               dat1.insertNewExam(list);
               break;
            case 8:
               dat1.newstudent(list);
               break;
            case 9:
               dat1.updateStudentExam(list);
               break;
            case 10:
               dat1.updateAllExams(list);
               break;
            default: //inputting anything will quit the program
               exit(0);
        }
     } 
     
     catch(char const* error)
     {
       cout << error << endl << endl;
     }
     
   }while(input);
   
   return 0;
}
