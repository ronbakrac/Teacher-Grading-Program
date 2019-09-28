#include <iostream> //cin cout
#include <fstream> //fstream
#include <string>  //string
#include <vector>  //vector
#include <sstream> //stringstream
#include <ctype.h> // toupper
#include <iomanip> // setprecision
#include "datahandler.h"
#include "student.h"
#include "passchange.h"

using namespace std;

void datahandler::checkAccess()
{
   fstream f1;
   string line, username, fuser, password, filename="User\\passwords.txt";
   f1.open(filename, ios::in);
   
   if(access)
      return;
   
   else{
      cout << "You cannot change any settings without being logged in." << endl;
      cout << "Enter username: ";
      cin >> username;
      cout << "Enter password: ";
      cin >> password;
      
      if (!f1.is_open()) 
      {
         cout << "Could not open file " << filename << endl;
         exit(0);
      }
      
      while(username != fuser && !f1.eof())
      {
         f1 >> fuser;
         f1.get(); //gets rid of the space between user and pass
         getline(f1, line);
      }
      
      if(username == fuser && password == line)
      {
         cout << "Successfully logged in as " << fuser << endl;
         login = fuser;
         pass = password;
         access = 1;
         return;
      }
      
      else
         throw "Incorrect username or password.\n";
         
   }
}

int datahandler::isvalidID(string id)
{
   int i;
   
   //checks for valid UID
   for(i=1; i < id.size(); ++i)
   {
      if(id.at(0) != 'U' || !isdigit(id.at(i)))
      {
         cin.clear();
         throw "Invalid ID.";
      }
   }
   
   return 1;
}

int datahandler::enterExamNum(vector<student> &list)
{
   int i, exam;
   
   do
   {
      i=0;
      cout << "Enter an exam number: ";
      cin >> exam;
      
      if(exam <= 0 || exam > list.at(0).getexams().size()){
         cout << "Invalid exam number." << endl;
         cin.clear();
         cin.ignore(1000, '\n');
         i=1;
      }
      
      else if(cin.fail())
      {
         cout << "Invalid input." << endl;
         cin.clear();
         cin.ignore(1000, '\n');
      }
      
   }while(i);
   
   return exam;
}

//returns position of if it exists, else returns -1
int datahandler::doesIDexist(string id, vector<student> &list)
{
   int i=0;
   vector<student>::iterator it;
   for(it = list.begin(); it != list.end(); ++it, ++i)
   {
      if((*it).getUID() == id)
      {
         return i;
      }
   }
   
   return -1;
}

string datahandler::studentsearch(vector<student> &list, int &position)
{
   string id;
   
   cout << "Enter ID of student: ";
   cin >> id;
   
   datahandler::isvalidID(id);
   position = datahandler::doesIDexist(id, list);
   
   if(position < 0)
     throw "ID does not exist.";
      
   
   return id;
}

void datahandler::makeuser()
{
   fstream f1;
   string user, fuser, password, filename="User\\passwords.txt";
   f1.open(filename, ios::in|ios::out);
   
   if (!f1.is_open()) 
   {
      cout << "Could not open file " << filename << endl;
      exit(0);
   }
   
   cout << "Enter a new username: ";
   cin >> user;
   cout << "Enter a new password: ";
   cin >> password;
   
   if(password.size() < 1)
      throw "Password can't be empty string.";
   
   while(user != fuser && !f1.eof())
   {
      f1 >> fuser;  
      f1.ignore(200, '\n');
   }
   
   if(user==fuser)
      throw "Username already exists.";
   
   else
   {
      f1.clear();
      f1 << endl << user << " " << password;
      f1.close();
      cout << "Successfully created new account\nUser: " << user << endl << "You are now logged in as this user." << endl << endl;
      login = user;
      pass = password;
      access = 1;
   }
   
}

void datahandler::updateAccounts(ifstream &in1, ofstream &ou1, string &total, string &line)
{
   while(!in1.eof()){
      getline(in1, line);
      total += line + "\n";
   }
   in1.close();
   ou1.open("User\\passwords.txt", ios::trunc);
   ou1 << total;
   ou1.close();
}

void datahandler::changePassword()
{
   int length;
   char an;
   ifstream in1;
   ofstream ou1;
   string fuser, password, newpass, line, total;
   
   in1.open("User\\passwords.txt");
   
   if (!in1.is_open())
   {
      cout << "Could not open file" << endl;
      exit(0);
   }
   
   cout << "Enter a password length: ";
   cin >> length;
   
   while(!in1.eof())
   {
      in1 >> fuser;
      total += fuser + " ";
      if(fuser == login){
         getline(in1, line);
         break;
      }
      in1 >> password;
      total += password + "\n";
   }

   if(login != fuser)
      throw "Fatal error.";
      
   do
   {
      cout << "Want a password containing digits only? (y/n) ";
      cin >> an;
      if(toupper(an) == 'Y')
      {
         Simple_pwdg pass(length);
         newpass = pass.getSimplePWD('D');
         cout << "Your new password is: " << newpass << endl << endl;
         total += newpass + "\n";
         
         datahandler::updateAccounts(in1, ou1, total, line);
         
         return;
      }
   }while(toupper(an) != 'N');
   
   do
   {
      cout << "Want a password containing letters only? (y/n) ";
      cin >> an;
      if(toupper(an) == 'Y')
      {
         Simple_pwdg pass(length);
         newpass = pass.getSimplePWD('L');
         cout << "Your new password is: " << newpass << endl << endl;
         total += newpass + "\n";
         
         datahandler::updateAccounts(in1, ou1, total, line);
         
         return;
      }
   }while(toupper(an) != 'N');
   
   Pwdg pass(length);
   newpass = pass.getPWD();
   cout << "Your new password is: " << newpass << endl << endl;
   total += newpass + "\n";
   datahandler::updateAccounts(in1, ou1, total, line);
   return;
}

void datahandler::displayscores(vector<student> &list)
{
   string UID;
   int pos, i;
   
   datahandler::checkAccess();
   
   UID = datahandler::studentsearch(list, pos);
   
   cout << list.at(pos).getUID() << ": ";
   for(i=0; i < list.at(pos).getexams().size(); ++i)
      cout << list.at(pos).getexams().at(i) << " ";
   
   cout << endl << endl;
   return;
}

void datahandler::displayexam(vector<student> &list)
{
   int exam, i=0;
   
   datahandler::checkAccess();
   
   do
   {
      cout << "Enter an exam number: ";
      cin >> exam;
      i=0;
      if(cin.fail() || exam > list.at(0).getexams().size() || exam <= 0){
         cin.clear();
         cin.ignore(100, '\n');
         cout << "Invalid exam input." << endl << endl;
         i=1;
      }
   }while(i);
   
   vector<student>::iterator it;
   for(it = list.begin(); it != list.end(); ++it)
      cout << (*it).getUID() << ": " << (*it).getexams().at(exam-1) << endl;
   
   cin.ignore(1000, '\n');
   cin.clear();
   cout << endl;
   return;
}


void datahandler::studentavg(vector<student> &list)
{
   int pos, i;
   string UID;
   double avg=0;
   
   datahandler::checkAccess();
   
   UID = datahandler::studentsearch(list, pos);

   for(i=0; i < list.at(pos).getexams().size(); ++i)
      avg += (list.at(pos).getexams().at(i));
   
   
   avg /= list.at(pos).getexams().size();
   cout << "Average of " << UID << ": " <<  fixed << setprecision(2) << avg << endl << endl;
   return;

}

void datahandler::examavg(vector<student> &list)
{
   int i=0, exam;
   double avg=0;
   
   datahandler::checkAccess();
   
   exam = datahandler::enterExamNum(list);
   
   vector<student>::iterator it;
   for(it = list.begin(); it != list.end(); ++it, ++i)
      avg += (*it).getexams().at(exam-1);
   
   avg /= i;
   
   cout << "Average for exam " << exam << ": " << avg << endl << endl;
}

void datahandler::insertNewExam(vector<student> &list)
{
   string line;
   istringstream inSS;
   int exam = 0;
   
   datahandler::checkAccess();
   
   cout << "Entering scores for exam " << list.at(0).getexams().size() + 1 << endl;
   vector<student>::iterator it;
   for(it = list.begin(); it != list.end(); ++it)
   {
      cout << (*it).getUID() << ": ";
      cin >> line;
      inSS.str(line);
      exam = datahandler::enterscore(inSS);
      
      (*it).setexams(exam);
   }
   
   datahandler::updateFile(list);
   cout << "Successfully inserted new exam." << endl << endl;
}


int datahandler::enterscore(istringstream &inSS)
{
	int score=0;
   
   inSS.clear();
   while(!inSS.eof())
   {
   	inSS >> score;
   	if (inSS.fail())
      {
   		inSS.clear();
   		inSS.ignore(20, ' ');
         continue;
   	}
      
      if(score < 0 || score > 100)
      {
         cout << "Invalid score detected. Setting to 0..." << endl;
         score = 0;
      }
      
   	return score;
   }
	return 0;
}

void datahandler::updateFile(vector<student> &list)
{
   fstream f1;
   
   f1.open("Data\\scores.txt", ios::out|ios::trunc);
   vector<student>::iterator it;
   for(it = list.begin(); it != list.end(); ++it)
   {
      f1 << (*it).getUID() << " ";
      (*it).printexams(f1);
   }
   
   f1.close();
}


void datahandler::newstudent(vector<student> &list)
{
   string id;
   string line;
   student newstud;
   istringstream inSS;
   vector<int> newstudentexams;
   int i, j;
   
   datahandler::checkAccess();

   cout << "Enter ID of new student: ";
   cin >> id;
   
   datahandler::isvalidID(id);
      
   if(datahandler::doesIDexist(id, list) >= 0)
     throw "ID already exists.";

   
   cin.clear();
   cin.ignore(1000, '\n');
   
   newstud.setUID(id);
   
   cout << "Enter exam scores for student " << id << ": ";
   getline(cin, line);
   inSS.str(line);
    
   for(j=0; j != list.at(0).getexams().size(); ++j)
   {	
      i = datahandler::enterscore(inSS);
      newstud.setexams(i);
   }     
      
   list.push_back(newstud);
   
   datahandler::updateFile(list);
   cout << "Successfully added new student." << endl << endl;
}

void datahandler::updateStudentExam(vector<student> &list)
{
   string id, line;
   int score, exam, pos=0;
   istringstream inSS;
   
   datahandler::checkAccess();
   
   //function only returns when a valid ID is input/found. Then returns ID
   id = datahandler::studentsearch(list, pos);
   
   //Only returns when a valid exam number is entered. Returns exam number
   exam = datahandler::enterExamNum(list);
   
   cout << "\nEnter new score for " << id << " on exam " << exam << ": ";
   cin >> line;
   inSS.str(line);
   score = datahandler::enterscore(inSS);
   
   list.at(pos).changeStudentExam(exam-1, score);
   datahandler::updateFile(list);
   
   cout << "Successfully updated student exam. " << endl << endl;

}

void datahandler::updateAllExams(vector<student> &list)
{
   int exam, diff=0, i, newscore=0;
   
   datahandler::checkAccess();
   
   exam = enterExamNum(list);
   cout << "Enter number change for every student (eg -5, 10): ";
   cin >> diff;
   
   if(cin.fail())
   {
      cin.clear();
      cin.ignore(100, '\n');
      throw "Improper input.";
   }
   
   if(diff > 100)
      throw "Invalid difference entered. Must be <=100. ";
   
   vector<student>::iterator it;
   for(it = list.begin(); it != list.end(); ++it)
   {
      newscore = (*it).getexams().at(exam-1) + diff;
      if(newscore < 0)
      {
         (*it).changeStudentExam(exam-1, 0);
      }
      
      else if(newscore > 100)
      {
         (*it).changeStudentExam(exam-1, 100);
      }
      
      else
          (*it).changeStudentExam(exam-1, newscore);
   }
   
   datahandler::updateFile(list);
   cout << "Successfully updated all student exams." << endl << endl;
}
