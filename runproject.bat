echo off
title Batch file for Teacher Grading Program, by Ron Bakrac
cd %~dp0
g++ -o Grader main.cpp datahandler.cpp student.cpp passchange.cpp
start Grader