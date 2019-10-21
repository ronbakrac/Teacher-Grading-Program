# Teacher Grading Application

This program is a console program that allows a user/teacher to insert test scores for their students. The user must create an account and password and is then able to insert students and their exam scores. There is no (realistic) limit as to how many students or exams the user can enter. Students must be entered by using a 'U' then a corresponding number, this program does not recognize names. The user can update scores per student or overall, add a new test score for each student, display average score of a student, average of a test, display all the scores of a student, and change their account password. The password changer includes ability to randomly generate your own password with settings such as length, digits only, or numbers only.

# Example Windows
<img src="./Example Pictures/pr1.PNG">
<img src="./Example Pictures/pr2.PNG">
<img src="./Example Pictures/pr3.PNG">
<img src="./Example Pictures/pr4.PNG">

# How To Compile/Run
To run the program, simply run ``runproject.bat``
Alternatively, you can use the makefile and compile.
(g++ compiler required for both these options. Program tested in a Windows environment only, should work in Linux)

User login and student data are stored in plain text so you may edit and view directly in the text file if needed. The default files in this repository have sample student and test data along with a <strong>default login of "admin" with password of "password"</strong>
