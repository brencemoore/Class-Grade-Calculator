#include "gradeCalc.h"


int loadFile(Course classList[], int numClasses) {
    ifstream fileInput;
    string data;

    fileInput.open("saveFile.txt");

    while (getline(fileInput, data, '#')) {
        classList[numClasses].name = data;
       
        getline(fileInput, data, '#');
        classList[numClasses].partsOfGrade = stoi(data);
        classList[numClasses].grade = new Grades [10];

        for (int i = 0; i < classList[numClasses].partsOfGrade; ++i) {
            getline(fileInput, data, '#');
            classList[numClasses].grade[i].name = data;

            getline(fileInput, data, '#');
            classList[numClasses].grade[i].weight = stod(data);

            getline(fileInput, data, '#');
            classList[numClasses].grade[i].numGrades = stoi(data);

            classList[numClasses].grade[i].gradeList = new double [30];

            for (int j = 0; j < 30; ++j) {
                classList[numClasses].grade[i].gradeList[j] = 0;
            }

            for (int j = 0; j < classList[numClasses].grade[i].numGrades; ++j) {
                getline(fileInput, data, '$');
                classList[numClasses].grade[i].gradeList[j] = stod(data);
            }
        }

        numClasses += 1;
    }

    if (numClasses > 10) {
        cout << "\nYou have the maximum number of classes added (10)." << endl;
    }

    fileInput.close();

    return numClasses;
}


int addClass(Course classList[], int numClasses) {
    if (numClasses < 10) {

        cout << "\nEnter data about your class below. (\"CANCEL\" to exit)" << endl
            << "Name of course:  ";
        getline(cin, classList[numClasses].name);

        if (classList[numClasses].name == "CANCEL") {
            return numClasses;
        }

        cout << "How many parts make up your grade:  ";
        cin >> classList[numClasses].partsOfGrade;
        cin.ignore();

        classList[numClasses].grade = new Grades [10];

        for (int i = 0; i < classList[numClasses].partsOfGrade; ++i) {
            classList[numClasses].grade[i].numGrades = 0;

            cout << "\nPart " << i + 1 << " name:  ";
            getline(cin, classList[numClasses].grade[i].name);

            cout << "Part " << i + 1 << " weight (0.00):  ";
            cin >> classList[numClasses].grade[i].weight;
            cin.ignore();

            classList[numClasses].grade[i].gradeList = new double [30];

            for (int j = 0; j < 30; ++j) {
                classList[numClasses].grade[i].gradeList[j] = 0;
            }
        }

        cout << "\nYou will add your grades by selecting \"Add Grades\" on the main menu." << endl;

        numClasses += 1;
    }
    else {
        cout << "\nYou have the maximum amount of classes added (10)." << endl;
    }

    return numClasses;
}


int editClass(Course classList[], int numClasses) {
    int classIndex, menuChoice, gradePartChoice, i;

    classIndex = printClasses(classList, numClasses, "Edit/Delete");

    if (classIndex == -1) {
        return numClasses;
    }

    cout << "\nChoose an how to edit the class " << classList[classIndex].name << "." << endl
         << "\t1.  Change name" << endl
         << "\t2.  Change part of grade name" << endl
         << "\t3.  Change part of grade weight" << endl
         << "\t4.  Add part of grade" << endl
         << "\t5.  Remove part of grade" << endl
         << "\t6.  Delete class" << endl
         << "\t7.  Cancel" << endl
         << "Enter 1-7:  ";
    cin >> menuChoice;
    cin.ignore();

    if (menuChoice == 1) {
        cout << "\nEnter a new name for " << classList[classIndex].name << ":  ";
        getline(cin, classList[classIndex].name);
    }

    if (menuChoice == 2) {
        cout << "\nChoose the part of grade that you want to change." << endl;
        for (i = 0; i < classList[classIndex].partsOfGrade; ++i) {
            cout << "\t" << i + 1 << ".  " << classList[classIndex].grade[i].name << endl;
        }
        cout << "Enter 1-" << i + 1 << ":  ";
        cin >> gradePartChoice;
        cin.ignore();

        cout << "\nEnter a new name for " << classList[classIndex].grade[gradePartChoice - 1].name << ".\n\tNew name:  ";
        getline(cin, classList[classIndex].grade[gradePartChoice - 1].name);
    }

    if (menuChoice == 3) {
        cout << "\nChoose the part of grade that you want to change." << endl;
        for (i = 0; i < classList[classIndex].partsOfGrade; ++i) {
            cout << "\t" << i + 1 << ".  " << classList[classIndex].grade[i].name
                 << "  WEIGHT:  " << fixed << setprecision(2) << classList[classIndex].grade[i].weight << endl;
        }
        cout << "Enter 1-" << i + 1 << ":  ";
        cin >> gradePartChoice;
        cin.ignore();

        cout << "\nEnter a new weight for " << classList[classIndex].grade[gradePartChoice - 1].name << ".\n\tNew weight:  ";
        getline(cin, classList[classIndex].grade[gradePartChoice - 1].name);
    }

    if (menuChoice == 6) {
        numClasses = deleteCourse(classList, numClasses, classIndex);
    }

    return numClasses;
}



int deleteCourse(Course classList[], int numClasses, int classIndex) {
    string tempName;
    double tempGradeList[30];
    int numGrades;

    tempName = classList[classIndex].name;

    for (int i = classIndex; i < numClasses - 1; ++i) {
        classList[i] = classList[i + 1];
    }

    for (int i = 0; i < classList[numClasses - 1].partsOfGrade; ++i) {
        delete [] classList[numClasses - 1].grade[i].gradeList;
    }
    delete [] classList[numClasses - 1].grade;

    numClasses -= 1;

    cout << endl << tempName << " was deleted." << endl;

    return numClasses;
}



void addGrades(Course classList[], int numClasses) {
    int classIndex, i, gradePartChoice, numGrades;
    double grade;

    classIndex = printClasses(classList, numClasses, "Add Grades");

    while (gradePartChoice != i + 1 && classIndex != -1) {
        grade = 0;
        cout << "\nChoose the part of grade that you want to add grades to." << endl;
        for (i = 0; i < classList[classIndex].partsOfGrade; ++i) {
            cout << "\t" << i + 1 << ".  " << classList[classIndex].grade[i].name << endl;
        }
        cout << "\t" << i + 1 << ".  Exit" << endl;
        cout << "Enter 1-" << i + 1 << ":  ";
        cin >> gradePartChoice;

        numGrades = classList[classIndex].grade[gradePartChoice - 1].numGrades;

        while (grade >= 0 && gradePartChoice != i + 1) {
            cout << "\nEnter a grade for " << classList[classIndex].grade[gradePartChoice - 1].name << ".\n\tNew grade (-1 to stop):  ";
            cin >> grade;

            if (grade >= 0) {
                classList[classIndex].grade[gradePartChoice - 1].gradeList[numGrades] = grade;
                numGrades += 1;
            }
        }

        classList[classIndex].grade[gradePartChoice - 1].numGrades = numGrades;
    }
}


void removeGrades(Course classList[], int numClasses) {
    int classIndex, i, gradePartChoice, numGrades, removeIndex = 0;
    double grade;

    classIndex = printClasses(classList, numClasses, "Remove Grades");

    while (gradePartChoice != i + 1 && classIndex != -1) {
        grade = 0;
        cout << "\nChoose the part of grade that you want to remove grades from." << endl;
        for (i = 0; i < classList[classIndex].partsOfGrade; ++i) {
            cout << "\t" << i + 1 << ".  " << classList[classIndex].grade[i].name << endl;
        }
        cout << "\t" << i + 1 << ".  Exit" << endl;
        cout << "Enter 1-" << i + 1 << ":  ";
        cin >> gradePartChoice;

        while (removeIndex != -1) {
            cout << "Grades for " << classList[classIndex].name << ", " << classList[classIndex].grade[gradePartChoice - 1].name << ":" << endl;

            for (i = 0; i < classList[classIndex].grade[gradePartChoice - 1].numGrades; ++i) {
                cout << i + 1 << ".\t" << classList[classIndex].grade[gradePartChoice - 1].gradeList[i] << endl;
            }

            cout << "Enter a number to remove that grade (-1 exits):  ";
            cin >> removeIndex;

            if (removeIndex == -1) {
                break;
            }

            for (i = removeIndex - 1; i < classList[classIndex].grade[gradePartChoice - 1].numGrades; ++i) {
                classList[classIndex].grade[gradePartChoice - 1].gradeList[i] = classList[classIndex].grade[gradePartChoice - 1].gradeList[i + 1];
            }
            classList[classIndex].grade[gradePartChoice - 1].numGrades -= 1;
        }
    }
}


void printGrades(Course classList[], int numClasses) {
    string line(40, '-');
    int highestIndex = 0, parts;

    cout << endl << left << setw(12) << "Class" << right << setw(10) << "Overall";

    for (int i = 1; i < numClasses; ++i) {
        if (classList[highestIndex].partsOfGrade < classList[i].partsOfGrade) {
            highestIndex = i;
        }
    }
    parts = classList[highestIndex].partsOfGrade;
    for (int i = 0; i < parts; ++i) {
        cout << setw(9) << "Part " << i + 1;
    }
    cout << endl << "-------------";
    for (int i = 0; i <= parts; ++i) {
        cout << "----------";
    }

    cout << endl << fixed << setprecision(2);

    for (int i = 0; i < numClasses; ++i) {
        cout << left << setw(12) << classList[i].name << "| " << right << setw(7) << calculateGrades(classList, i, true) << " | ";
        calculateGrades(classList, i, false);
        cout << endl;
    }
}

void fakePrint(Course classList[], int numClasses) {
    string line(40, '-');

    for (int i = 0; i < numClasses; ++i) {
        cout << endl << classList[i].name << ":" << endl
             << "Parts of grade:\t" << classList[i].partsOfGrade << endl;
        
        for (int j = 0; j < classList[i].partsOfGrade; ++j) {
            cout << "Part " << j + 1 << ":" << endl
                 << "Name:\t" << classList[i].grade[j].name << endl
                 << "Weight:\t" << classList[i].grade[j].weight << endl
                 << "NumGrades:\t" << classList[i].grade[j].numGrades << endl
                 << "Grades:" << endl;

            for (int k = 0; k < classList[i].grade[j].numGrades; ++k) {
                cout << classList[i].grade[j].gradeList[k] << endl;
            }
        }
    }
}





double calculateGrades(Course classList[], int index, bool doTotalGrade) {
    double partTotal = 0, partAverage = 0, overallTotal = 0;

    if (doTotalGrade) {
        for (int i = 0; i < classList[index].partsOfGrade; ++i) {
            partTotal = 0;
            for (int j = 0; j < classList[index].grade[i].numGrades; ++j) {
                partTotal += classList[index].grade[i].gradeList[j];
            }
            partAverage = (partTotal / classList[index].grade[i].numGrades) * classList[index].grade[i].weight;

            overallTotal += partAverage;
        }
        return overallTotal;
    }
    else {
        for (int i = 0; i < classList[index].partsOfGrade; ++i) {
            partTotal = 0;
            for (int j = 0; j < classList[index].grade[i].numGrades; ++j) {
                partTotal += classList[index].grade[i].gradeList[j];
            }
            partAverage = (partTotal / classList[index].grade[i].numGrades);

            cout << setw(7) << partAverage << " | ";
        }

        return partAverage;
    }
}


void saveToFile(Course classList[], int numClasses) {
    ofstream fileOutput;

    fileOutput.open("saveFile.txt");

    for (int i = 0; i < numClasses; ++i) {
        fileOutput << classList[i].name << "#"
                   << classList[i].partsOfGrade << "#";
        for (int j = 0; j < classList[i].partsOfGrade; ++j) {
            fileOutput << classList[i].grade[j].name << "#"
                       << classList[i].grade[j].weight << "#"
                       << classList[i].grade[j].numGrades << "#";
            for (int k = 0; k < classList[i].grade[j].numGrades; ++k) {
                fileOutput << classList[i].grade[j].gradeList[k] << "$";
            }
        }
    }

    fileOutput.close();
}


int printClasses(Course classList[], int numClasses, string option) {
    int classChoice, i;

    cout << "\nSelect a class to " << option << "." << endl;
    for (i = 0; i < numClasses; ++i) {
        cout << " " << i + 1 << "." << setw(36) << classList[i].name << endl;
    }
    cout << " " << i + 1 << "." << setw(36) << "Cancel" << endl;

    cout << "\nEnter a number 1-" << numClasses + 1 << ":  ";
    cin >> classChoice;

    while (classChoice - 1 > numClasses || classChoice - 1 < 0) {
        cout << "\nEnter a number 1-" << numClasses + 1 << ":  ";
        cin >> classChoice;
    }

    if (classChoice == numClasses + 1) {
        return -1;
    }

    return classChoice - 1;
}