#ifndef GRADECALC_H
#define GRADECALC_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;


struct Grades {
    string name;        // Tests, Quizzes, Homework, etc.
    double weight;      // What percent does this contribute to your total grade (EX: 0.70 = %70)
    int numGrades;      // How many grades in this part. (EX: number of quizzes)
    double *gradeList;  // A list of all of those grades for this part
};


struct Course {
    string name;        // Class name
    int partsOfGrade;   // EX: Tests, Exams, Homework, Attendance, Quizzes, Projects, etc. (how many of these make categories make up your total grade)
    Grades *grade;      // A pointer to create an array of parts of your grade (EX: index_0 = Tests, index_1 = Quizzes, etc.)
};


int loadFile(Course[], int);
int addClass(Course[], int);
int editClass(Course[], int);
int deleteCourse(Course[], int, int);
void addGrades(Course[], int);
void removeGrades(Course[], int);
void printGrades(Course[], int);
double calculateGrades(Course[], int, bool);
void saveToFile(Course[], int);
int printClasses(Course[], int, string);    // Prints all classes with overall grade and a grade for each part of the class
void printAll(Course[], int);               // Prints all (most) of the data stored related to classes when the program is running

#endif