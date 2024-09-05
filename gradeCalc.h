#ifndef GRADECALC_H
#define GRADECALC_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;


struct Grades {
    string name;
    double weight;
    int numGrades;
    double *gradeList;
};


struct Course {
    string name;
    int partsOfGrade;
    Grades *grade;
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
int printClasses(Course[], int, string);

void fakePrint(Course[], int);

#endif