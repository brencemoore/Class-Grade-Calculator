#include "gradeCalc.h"

// Loads saved data from a text file (if there is any saved data)
int loadFile(Course classList[], int numClasses) {
    ifstream fileInput;
    string data;

    fileInput.open("saveFile.txt");

    // Returns 0 number of classes if no save file exists
    if (!fileInput.is_open()) {
        return 0;
    }

    // Reads entire file
    while (getline(fileInput, data, '#')) {
        classList[numClasses].name = data;      // Name of class
       
        getline(fileInput, data, '#');          // Reads number of parts of grade
        classList[numClasses].partsOfGrade = stoi(data);
        classList[numClasses].grade = new Grades [10];  // Creates a maximum of 10 parts of a grade for a class (this can only be changed in code)

        // Loops for each part of the grade
        for (int i = 0; i < classList[numClasses].partsOfGrade; ++i) {
            getline(fileInput, data, '#');
            classList[numClasses].grade[i].name = data;     // Reads and stores the name of this part of the class

            getline(fileInput, data, '#');
            classList[numClasses].grade[i].weight = stod(data); // Reads and stores the weight of this part of the class

            getline(fileInput, data, '#');
            classList[numClasses].grade[i].numGrades = stoi(data);  // Reads and stores the number of grades for this part of the class

            classList[numClasses].grade[i].gradeList = new double [100];    // Creates a list to hold a max of 100 grades

            for (int j = 0; j < 100; ++j) {
                classList[numClasses].grade[i].gradeList[j] = 0;    // Sets all grades in the list to 0
            }

            for (int j = 0; j < classList[numClasses].grade[i].numGrades; ++j) {
                getline(fileInput, data, '$');      // '$' sign makes reading saved files slightly easier
                classList[numClasses].grade[i].gradeList[j] = stod(data);   // Reads and stores every grade saved into the grade list
            }
        }
        if (numClasses > 10) {
            cout << "\nYou have the maximum number of classes added (" << 10 << ")." << endl;
            break;
        }
        else {
            numClasses += 1;
        }
    }
    fileInput.close();

    return numClasses;
}


// The user adds a class by answering specific questions
int addClass(Course classList[], int numClasses) {
    if (numClasses >= 10) {
        cout << "\nYou have the maximum amount of classes added (" << 10 << ")." << endl;
        return numClasses;
    }
    cout << "\nEnter data about your class below. (\"CANCEL\" to exit)" << endl
        << "Name of course:  ";
    getline(cin, classList[numClasses].name);

    // Cancels adding a class
    if (classList[numClasses].name == "CANCEL") {
        return numClasses;
    }

    // user inputs how many parts the class has
    cout << "How many parts make up your grade:  ";
    cin >> classList[numClasses].partsOfGrade;
    cin.ignore();

    classList[numClasses].grade = new Grades [10];  // Consistent with loading from a file

    // For each part of a grade the user enters the name and weight
    for (int i = 0; i < classList[numClasses].partsOfGrade; ++i) {
        classList[numClasses].grade[i].numGrades = 0;

        cout << "\nPart " << i + 1 << " name:  ";
        getline(cin, classList[numClasses].grade[i].name);

        cout << "Part " << i + 1 << " weight (0.00):  ";
        cin >> classList[numClasses].grade[i].weight;
        cin.ignore();

        classList[numClasses].grade[i].gradeList = new double [100];    // Creates a grade list for each part

        for (int j = 0; j < 100; ++j) {
            classList[numClasses].grade[i].gradeList[j] = 0;    // Initializes all grades to 0
        }
    }
    cout << "\nYou will add your grades by selecting \"Add Grades\" on the main menu." << endl;
    numClasses += 1;
    
    return numClasses;
}


// User can edit parts of the class or delete the class
int editClass(Course classList[], int numClasses) {
    int classIndex, menuChoice = -1, gradePartChoice = -1, i;
    string confirm, newName;
    double newWeight;

    // Prompts user and stores index for class chosen
    classIndex = printClasses(classList, numClasses, "Edit/Delete");

    // User chose to exit to main menu
    if (classIndex == -1) {
        return numClasses;
    }
    cout << "\nChoose an how to edit the class " << classList[classIndex].name << "." << endl
         << "\t1.  Change name" << endl
         << "\t2.  Change part of grade name" << endl
         << "\t3.  Change part of grade weight" << endl
         << "\t4.  Delete class" << endl
         << "\t5.  Cancel" << endl;

    // Validates user menu selection
    while (menuChoice > 5 || menuChoice < 1) {
        cout << "Enter 1-5:  ";
        cin >> menuChoice;
        cin.ignore();
    }

    // Changes the name of a class
    if (menuChoice == 1) {
        cout << "\nEnter a new name for " << classList[classIndex].name << " or CANCEL:  ";
        getline(cin, newName);

        // Checks if user canceled name change
        if (newName != "CANCEL") {
            classList[classIndex].name = newName;
        }
    }

    // Changes the name of a part of a class
    if (menuChoice == 2) {

        // Prints each part of the class
        cout << "\nChoose the part of grade that you want to change." << endl;
        for (i = 0; i < classList[classIndex].partsOfGrade; ++i) {
            cout << "\t" << i + 1 << ".  " << classList[classIndex].grade[i].name << endl;
        }
        cout << "\t" << i + 1 << ".  Cancel" << endl;

        // Validates user selection
        while (gradePartChoice > i + 1 || gradePartChoice < 1) {
            cout << "Enter 1-" << i + 1 << ":  ";
            cin >> gradePartChoice;
            cin.ignore();
        }
        // Cancels name change
        if (gradePartChoice == i + 1) {
            return numClasses;
        }
        cout << "\nEnter a new name for " << classList[classIndex].grade[gradePartChoice - 1].name << " or CANCEL.\n\tNew name:  ";
        getline(cin, newName);

        // Checks if user no longer wants to change the name for a part of a grade
        if (newName != "CANCEL") {
            classList[classIndex].grade[gradePartChoice - 1].name = newName;
        }
    }

    // Changes the weight of a part of a class
    if (menuChoice == 3) {

        // Prints each part of the grade and corresponding weight
        cout << "\nChoose the part of grade that you want to change." << endl;
        for (i = 0; i < classList[classIndex].partsOfGrade; ++i) {
            cout << "\t" << i + 1 << ".  " << classList[classIndex].grade[i].name
                 << "  WEIGHT:  " << fixed << setprecision(2) << classList[classIndex].grade[i].weight << endl;
        }
        cout << "\t" << i + 1 << ". Cancel" << endl;

        // Selection validation and cancel option
        while (gradePartChoice > i + 1 || gradePartChoice < 1) {
            cout << "Enter 1-" << i + 1 << ":  ";
            cin >> gradePartChoice;
            cin.ignore();
        }
        // Cancels weight change
        if (gradePartChoice == i + 1) {
            return numClasses;
        }

        // User enters a new weight for selected part of class
        cout << "\nEnter a new weight for " << classList[classIndex].grade[gradePartChoice - 1].name << " or -1 to Cancel.\n\tNew weight:  ";
        cin >> newWeight;

        // Checks if user didn't cancel weight change
        if (newWeight != -1) {
            classList[classIndex].grade[gradePartChoice - 1].weight = newWeight;
        }
    }

    // Deletes The class
    if (menuChoice == 4) {
        cout << "\nAre you sure? You cannot undo this. (y or n):  ";
        getline(cin, confirm);

        if (confirm == "y") {
            cout << endl << numClasses << endl;
            numClasses = deleteCourse(classList, numClasses, classIndex);   // deleteCourse deletes the class
            cout << endl << numClasses << endl;
        }
    }
    return numClasses;
}


// Deletes a class and all data
int deleteCourse(Course classList[], int numClasses, int classIndex) {
    string tempName;
    double tempGradeList[30];
    int numGrades;

    tempName = classList[classIndex].name;  // Used for printing

    // Moves all classes after the index one index down (causes the last class to have a duplicate)
    for (int i = classIndex; i < numClasses - 1; ++i) {
        classList[i] = classList[i + 1];
    }
    // Deletes the now duplicate last class's parts' grade list
    for (int i = 0; i < classList[numClasses - 1].partsOfGrade; ++i) {
        delete [] classList[numClasses - 1].grade[i].gradeList;
    }
    // Finally, deletes the last duplicate class
    delete [] classList[numClasses - 1].grade;

    // Notifies user and updates number of classes
    numClasses -= 1;
    cout << endl << tempName << " was deleted." << endl;
    return numClasses;
}


// Allows user to add grades to any part of any class
void addGrades(Course classList[], int numClasses) {
    int classIndex, i, gradePartChoice, numGrades;
    double grade;

    // Prompts user and stores index for class chosen
    classIndex = printClasses(classList, numClasses, "Add Grades");

    // Loop allows the user to quickly add grades to different parts
    while (classIndex != -1) {
        grade = 0;
        gradePartChoice = -1;

        // Prints each part of the class for user to choose
        cout << "\nChoose the part of grade that you want to add grades to." << endl;
        for (i = 0; i < classList[classIndex].partsOfGrade; ++i) {
            cout << "\t" << i + 1 << ".  " << classList[classIndex].grade[i].name << endl;
        }
        cout << "\t" << i + 1 << ".  Exit" << endl;

        // Validates user input
        while (gradePartChoice > i + 1 || gradePartChoice < 1) {
            cout << "Enter 1-" << i + 1 << ":  ";
            cin >> gradePartChoice;

            if (gradePartChoice == i + 1) {
                return;
            }
        }

        // Variable used for readability
        numGrades = classList[classIndex].grade[gradePartChoice - 1].numGrades;

        // Loop allows for the user to quickly add multiple grades
        while (grade >= 0) {
            cout << "\nEnter a grade for " << classList[classIndex].grade[gradePartChoice - 1].name << ".\n\tNew grade (-1 to stop):  ";
            cin >> grade;

            // Checks if user is done adding grades
            if (grade >= 0) {
                classList[classIndex].grade[gradePartChoice - 1].gradeList[numGrades] = grade;
                numGrades += 1;
            }
        }
        // Updates class part's number of grades
        classList[classIndex].grade[gradePartChoice - 1].numGrades = numGrades;
    }
}


// Allows user to remove grades from any part of any class
void removeGrades(Course classList[], int numClasses) {
    int classIndex, i, gradePartChoice, numGrades, removeIndex = 0;

    // Prompts user and stores index for class chosen
    classIndex = printClasses(classList, numClasses, "Remove Grades");

    // This loop allows the user to remove grades from multiple parts of a class
    while (classIndex != -1) {
        gradePartChoice = -1;

        // Prints each part of the class
        cout << "\nChoose the part of grade that you want to remove grades from." << endl;
        for (i = 0; i < classList[classIndex].partsOfGrade; ++i) {
            cout << "\t" << i + 1 << ".  " << classList[classIndex].grade[i].name << endl;
        }
        cout << "\t" << i + 1 << ".  Exit" << endl;

        // Validates user input
        while (gradePartChoice > i + 1 || gradePartChoice < 1) {
            cout << "Enter 1-" << i + 1 << ":  ";
            cin >> gradePartChoice;

            if (gradePartChoice == i + 1) {
                return;
            } 
        }

        // Will loop so that the user can delete mutiple grades quickly
        while (removeIndex != -1) {
            removeIndex = 0;

            // Prints the class and part of class
            cout << "Grades for " << classList[classIndex].name << ", " << classList[classIndex].grade[gradePartChoice - 1].name << ":" << endl;

            //Prints each grade in the list of grades for that part of that class
            for (i = 0; i < classList[classIndex].grade[gradePartChoice - 1].numGrades; ++i) {
                cout << i + 1 << ".\t" << classList[classIndex].grade[gradePartChoice - 1].gradeList[i] << endl;
            }

            // Validates user input
            while (removeIndex > i || removeIndex < 1) {
                cout << "Enter a number 1-" << i << " to remove that grade (-1 to stop):  ";
                cin >> removeIndex;

                // Stops selecting grades to delete
                if (removeIndex == -1) {
                    break;
                }
            }

            if (removeIndex != -1) {

                // Moves each grade after the index of the grade being removed is moved 1 index lower. Only grades in the part of the class selected are altered
                for (i = removeIndex - 1; i < classList[classIndex].grade[gradePartChoice - 1].numGrades; ++i) {
                    classList[classIndex].grade[gradePartChoice - 1].gradeList[i] = classList[classIndex].grade[gradePartChoice - 1].gradeList[i + 1];
                }
                classList[classIndex].grade[gradePartChoice - 1].numGrades -= 1;
            }
        }
    }
}


// Prints the calculated grade of each class
void printGrades(Course classList[], int numClasses) {
    string line(40, '-');
    int highestIndex = 0, parts;

    cout << endl << left << setw(12) << "Class" << right << setw(10) << "Overall";

    // Finds which class has the most parts (for formatting and aesthetics)
    for (int i = 1; i < numClasses; ++i) {
        if (classList[highestIndex].partsOfGrade < classList[i].partsOfGrade) {
            highestIndex = i;
        }
    }
    // Prints the number of columns that the class with the most parts has
    parts = classList[highestIndex].partsOfGrade;
    for (int i = 0; i < parts; ++i) {
        cout << setw(9) << "Part " << i + 1;    // Part is used instead of the name of each part because different classes may be in different orders
    }
    cout << endl << "-------------";
    for (int i = 0; i <= parts; ++i) {
        cout << "----------";
    }

    cout << endl << fixed << setprecision(2);

    // Prints the grades for each class and each class part using the calculateGrades function
    for (int i = 0; i < numClasses; ++i) {
        cout << left << setw(12) << classList[i].name << "| " << right << setw(7) << calculateGrades(classList, i, true) << " | ";
        calculateGrades(classList, i, false);
        cout << endl;
    }
}


// Prints most of the relevant class data all at once
void printAll(Course classList[], int numClasses) {
    string line(40, '-');

    // Prints each class
    for (int i = 0; i < numClasses; ++i) {
        cout << endl << classList[i].name << ":" << endl
             << "Parts of grade:\t" << classList[i].partsOfGrade << endl;
        
        // Prints all parts and data of each class
        for (int j = 0; j < classList[i].partsOfGrade; ++j) {
            cout << "Part " << j + 1 << ":" << endl
                 << "Name:\t" << classList[i].grade[j].name << endl
                 << "Weight:\t" << classList[i].grade[j].weight << endl
                 << "NumGrades:\t" << classList[i].grade[j].numGrades << endl
                 << "Grades:" << endl;

            // Prints all grades for each part of each class
            for (int k = 0; k < classList[i].grade[j].numGrades; ++k) {
                cout << classList[i].grade[j].gradeList[k] << endl;
            }
        }
    }
}


// Calculates the overall grade for the class and each part's grade
double calculateGrades(Course classList[], int index, bool doTotalGrade) {
    double partTotal = 0, partAverage = 0, overallTotal = 0;

    // Calculates grade for whole class
    if (doTotalGrade) {
        for (int i = 0; i < classList[index].partsOfGrade; ++i) {
            partTotal = 0;
            for (int j = 0; j < classList[index].grade[i].numGrades; ++j) {

                // Sums all grades in grade list
                partTotal += classList[index].grade[i].gradeList[j];
            }
            // Gets the average of sum and multiplies by weight
            partAverage = (partTotal / classList[index].grade[i].numGrades) * classList[index].grade[i].weight;

            // Adds weighted average to an overall grade
            overallTotal += partAverage;
        }
        return overallTotal;
    }
    // Calculates grade for each part
    else {
        for (int i = 0; i < classList[index].partsOfGrade; ++i) {
            partTotal = 0;
            for (int j = 0; j < classList[index].grade[i].numGrades; ++j) {

                // Sums all grades in grade list
                partTotal += classList[index].grade[i].gradeList[j];
            }
            // Gets the average of sum
            partAverage = (partTotal / classList[index].grade[i].numGrades);

            // Outputs each parts grade (unweighted)
            cout << setw(7) << partAverage << " | ";
        }

        return partAverage;
    }
}


// Saves all data in a file so that data can be loaded when the program is run again
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


// Prints the prompt that the user uses to pick a class during one of the menu functions
int printClasses(Course classList[], int numClasses, string option) {
    int classChoice, i;

    // Prints options 1-x
    cout << "\nSelect a class to " << option << "." << endl;
    for (i = 0; i < numClasses; ++i) {
        cout << " " << i + 1 << "." << setw(36) << classList[i].name << endl;
    }
    cout << " " << i + 1 << "." << setw(36) << "Cancel" << endl;

    // User prompt
    cout << "\nEnter a number 1-" << numClasses + 1 << ":  ";
    cin >> classChoice;

    // User input validation
    while (classChoice - 1 > numClasses || classChoice - 1 < 0) {
        cout << "\nEnter a number 1-" << numClasses + 1 << ":  ";
        cin >> classChoice;
    }

    if (classChoice == numClasses + 1) {
        return -1;  // User selected "Cancel"
    }
    return classChoice - 1; // the -1 is because the menu is 1 number higher than the respective array of classes
}