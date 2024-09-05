#include "gradeCalc.h"

int main() {

    int menuChoice, numClasses = 0;
    string line(40, '-');
    Course classList[10];       // Number of Maximum Classes can be changed in the header file
    char save;

    cout << endl << endl << line << endl << setw(28) << "GRADE CALCULATOR" << endl << line << endl << endl;

    numClasses = loadFile(classList, numClasses);

    // Loops until user chooses to quit
    do {
        menuChoice = 0;

        cout << "\nChoose an option below." << endl << line << endl << right << setfill('.')
             << " 1.  " << setw(32) << "  Add a Class" << endl
             << " 2.  " << setw(32) << "  Edit/Delete a Class" << endl
             << " 3.  " << setw(32) << "  Add Grades" << endl
             << " 4.  " << setw(32) << "  Remove Grades" << endl
             << " 5.  " << setw(32) << "  Print Grades" << endl
             << " 6.  " << setw(32) << "  Print All Data" << endl
             << " 7.  " << setw(32) << "  Exit" << endl << setfill(' ');

        // Validates user menu selection choice
        while (menuChoice > 7 || menuChoice < 1) {
            cout << " Enter a number 1-7:  ";
            cin >> menuChoice;
            cin.ignore();
        }

        // Add a class
        if (menuChoice == 1) {
            numClasses = addClass(classList, numClasses);
        }
        
        // Edit/Delete a Class
        if (menuChoice == 2) {
            numClasses = editClass(classList, numClasses);
        }

        // Add Grades
        if (menuChoice == 3) {
            addGrades(classList, numClasses);
        }

        // Remove Grades
        if (menuChoice == 4) {
            removeGrades(classList, numClasses);
        }

        // Print Grades
        if (menuChoice == 5) {
            printGrades(classList, numClasses);
        }

        // Print All Data
        if (menuChoice == 6) {
            printAll(classList, numClasses);
        }

    } while (menuChoice != 7);

    cout << "\nDo you want to save your classes?\nSelecting no will keep the data that was stored before opening\n(y or n):  ";
    cin >> save;

    // If user chooses, the class data will be saved on a text (.txt) file
    if (save == 'y') {
        saveToFile(classList, numClasses);
    }

    // Deletes all alocated data created if/when loadFile allocated memory
    for (int i = 0; i < numClasses; ++i) {
        for (int j = 0; j < classList[i].partsOfGrade; ++j) {
            delete [] classList[i].grade[j].gradeList;
        }
        delete [] classList[i].grade;
    }

    return 0;
}