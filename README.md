# Class Grade Calculator

## Overview
**Class Grade Calculator** is a C++ program designed to help users efficiently calculate their class grades. By allowing users to input details about how each part of the grade is calculated (e.g., assignments, homework, quizzes, tests), the program computes the overall grade and saves time from manual calculations.

## Features
- Enter details for various grade components such as name and weight (e.g., assignments, homework, quizzes, tests).
- Add, update, and remove grades for each component.
- Add and remove classes at any time.
- Modify the name and weight of grade components as needed.
- Automatically saves all data to a text file upon exiting, so that all previous data is available upon restarting the program.
- Handles grade calculations using decimal percentages (no letter grades or traditional percentage inputs).

## Technologies Used
- **Language:** C++
- **Libraries:** Standard C++ libraries

## Usage
When you run the executable, a title and menu will appear in the terminal window. The user can interact with the program by selecting menu options using numbers 1-7:

### Menu Options:
1. **Add a Class:**  
   - Prompts the user with multiple questions to gather details about the class (e.g., class name, parts of the grade like tests, homework, etc.) and adds it to the program's memory.

2. **Edit/Delete a Class:**  
   - Provides options to modify the class details such as changing the class name, altering the names and weights of grade components, or deleting the class entirely.

3. **Add Grades:**  
   - Allows the user to add grades to a specific part of a class (e.g., add a grade to the "tests" part).

4. **Remove Grades:**  
   - Enables the user to remove grades from a specific part of a class.

5. **Print Grades:**  
   - Prints the grades for each part of a selected class and displays the overall grade.

6. **Print All:**  
   - Outputs detailed information about all classes, including each part that contributes to the grade, their weights, and the grades.

7. **Exit:**  
   - Exits the program and saves all entered data to a text file. If the user does not wish to save the new data, only the original data loaded at the start will remain.

### Important Notes:
- **Grade Components:** When the program refers to "part of a grade" or "parts of a grade," it means the components that make up the overall grade, such as tests, homework, quizzes, etc. These components should be entered as decimal values (e.g., 0.60 for 60%).
- **Cancel Options:** Most prompts provide a way to cancel the operation:
  - For string inputs, type "CANCEL" to cancel the action.
  - For numerical inputs, enter `-1` to cancel.
  - In menu selections, the cancel option is typically the last option in the menu.
- **Input Validation:** If a non-numeric input is provided when a number is expected, the program may crash. If this occurs, you can terminate the program using `^C` (Ctrl + C) or by closing the console window. Be aware that any new data entered during this session will not be saved.

This usage guide should help users navigate the Class Grade Calculator effectively while understanding how to interact with the program and avoid common pitfalls.

## Installation
### Running the Executable
1. Download the executable file and run it directly in a terminal window.

### Compiling from Source (not necessary, but an option)
1. Ensure you have a C++ compiler installed (e.g., GCC).
2. Download the source code files.
3. Open a terminal and navigate to the directory containing the source code.
4. Compile the code using the following command:
   g++ main.cpp functions.cpp -o calculator
   
- (calculator is the name of the exectuable so this can be whatever the user wants)
