#include "gradeCalc.h"

int main() {

    int menuChoice, numClasses = 0;
    string line(40, '-');
    Course classList[10];
    char save;

    cout << endl << endl << line << endl << setw(28) << "GRADE CALCULATOR" << endl << line << endl << endl;

    numClasses = loadFile(classList, numClasses);

    do {

        cout << "\nChoose an option below." << endl << line << endl << right << setfill('.')
             << " 1.  " << setw(32) << "  Add a Class" << endl
             << " 2.  " << setw(32) << "  Edit/Delete a Class" << endl
             << " 3.  " << setw(32) << "  Add Grades" << endl
             << " 4.  " << setw(32) << "  Remove Grades" << endl
             << " 5.  " << setw(32) << "  Print Grades" << endl
             << " 6.  " << setw(32) << "  Exit" << endl << setfill(' ')
             << line << endl << " Enter a number 1-6:  ";
        cin >> menuChoice;
        cin.ignore();

        while (menuChoice > 7 || menuChoice < 1) {
            cout << " Enter a number 1-6:  ";
            cin >> menuChoice;
            cin.ignore();
        }


        if (menuChoice == 1) {
            numClasses = addClass(classList, numClasses);
        }

        if (menuChoice == 2) {
            numClasses = editClass(classList, numClasses);
        }

        if (menuChoice == 3) {
            addGrades(classList, numClasses);
        }

        if (menuChoice == 4) {
            removeGrades(classList, numClasses);
        }

        if (menuChoice == 5) {
            printGrades(classList, numClasses);
        }

        if (menuChoice == 7) {
            fakePrint(classList, numClasses);
        }

    } while (menuChoice != 6);

    cout << "\nDo you want to save your classes? (y or n):  ";
    cin >> save;
    if (save == 'y') {
        saveToFile(classList, numClasses);
    }


    for (int i = 0; i < numClasses; ++i) {
        for (int j = 0; j < classList[i].partsOfGrade; ++j) {
            delete [] classList[i].grade[j].gradeList;
        }
        delete [] classList[i].grade;
    }

    return 0;
}