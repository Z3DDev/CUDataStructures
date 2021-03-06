/*
Ashley Wood and Zachary Jagoda
Student ID: 2271425 and Student ID: 2274813
Student Emails: wood198@mail.chapman.edu jagod101@mail.chapman.edu
CPSC 350-02
*/

#include "Menu.h"

Menu::Menu() {

}

Menu::~Menu() {

}
void Menu::readFile() {
  ifstream MSFile;
  ifstream MFFile;

  string input;
  int numStudent = 0;
  int numFaculty = 0;
  int totalFaculty = 0;
  int totalAdvisee = 0;
  int numLine = 1;

  //Student
  int srID = 0;
  string sname = "";
  string slevel = "";
  string smajor = "";
  double gpa = 0;
  int advisorID = 0;

  //Faculty
  int frID = 0;
  string fname = "";
  string flevel = "";
  string department = "";
  int adviseeID = 0;

  //Faculty Import
  MFFile.open("facultyTable.txt");

  if(MFFile.is_open()) {
    try {
      getline(MFFile, input);

      if(input != "") {
        numFaculty = atoi(input.c_str());
      }
    }
    catch(exception e) {
      cout << "\nIncorrect File Format" << endl;
    }

    //Reads the imported file and distributes the lines to their correct variables
    while(getline(MFFile, input)) {
      switch(numLine) {
        case 1: {
          if(input != "--") {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 2: {
          try {
            frID = atoi(input.c_str());
          }
          catch(exception e) {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 3: {
          fname = input;
          break;
        }
        case 4: {
          flevel = input;
          break;
        }
        case 5: {
          department = input;
          break;
        }
        case 6: {
          try {
            totalAdvisee = atoi(input.c_str());
          }
          catch(exception e) {
            cout << "\nIncorrect File Format" << endl;
          }

          Faculty *faculty = new Faculty(frID, fname, flevel, department);
          totalFaculty++;

          for(int j = 0; j < totalAdvisee; ++j) {
            getline(MFFile, input);
            try {
              adviseeID = atoi(input.c_str());
            }
            catch(exception e) {
              cout << "\nIncorrect File Format" << endl;
            }
            faculty->addAdvisee(adviseeID);
          }

          TreeNode<Faculty> *facultyNode = new TreeNode<Faculty>(faculty, frID);
          masterFaculty.put(facultyNode);
          break;
        }
        default:
          break;
      }

      ++numLine;

      if(totalFaculty == numFaculty) {
        break;
      }
      if(numLine > 6) {
        numLine = 1;
      }
    }
  }
  else {
    cout << "\nNo File Found For Faculty Table - Program Starting With Blank File" << endl;
  }

  MFFile.close();

  //Student Import
  MSFile.open("studentTable.txt");

  if(MSFile.is_open()) {
    try {
      getline(MSFile, input);

      if(input != "") {
        numStudent = atoi(input.c_str());
      }
    }
    catch(exception e) {
      cout << "\nIncorrect File Format" << endl;
    }

    for(int i = 0; i < (7 * numStudent); ++i) {
      getline(MSFile, input);

      switch(numLine) {
        case 1: {
          if(input != "--") {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 2: {
          try {
            srID = atoi(input.c_str());
          }
          catch(exception e) {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 3: {
          sname = input;
          break;
        }
        case 4: {
          slevel = input;
          break;
        }
        case 5: {
          smajor = input;
        }
        case 6: {
          try {
            gpa = atof(input.c_str());
          }
          catch(exception e) {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        case 7: {
          try {
            advisorID = atoi(input.c_str());

            Student *student = new Student(srID, sname, slevel, smajor, gpa, advisorID);
            TreeNode<Student> *studentNode = new TreeNode<Student>(student, srID);
            masterStudent.put(studentNode);
          }
          catch(exception e) {
            cout << "\nIncorrect File Format" << endl;
          }
          break;
        }
        default:
          break;
      }

      ++numLine;
      if(numLine > 7) {
        numLine = 1;
      }
    }
  }
  else {
    cout << "\nNo File Found For Student Table - Program Starting With Blank File" << endl;
  }

  MSFile.close();
}

void Menu::writeFile() {
  ofstream MSFile;
  ofstream MFFile;

  //Student
  MSFile.open("studentTable.txt");
  if(MSFile.is_open()) {
    MSFile << masterStudent.getSize() << endl;
    TreeNode<Student> *s = masterStudent.getRoot();
    outputMS(s, "studentTable.txt");
  }

  MSFile.close();

  //Faculty
  MFFile.open("facultyTable.txt");
  if(MFFile.is_open()) {
    MFFile << masterFaculty.getSize() << endl;
    TreeNode<Faculty> *f = masterFaculty.getRoot();
    outputMF(f, "facultyTable.txt");
  }

  MFFile.close();
}

//traverses the tree to print the students
void Menu::printMS(TreeNode<Student> *s) {
  if(s != NULL) {
    if(s->left != NULL) {
      printMS(s->left);
    }
    s->data->printStudent();

    if(s->right != NULL) {
      printMS(s->right);
    }
  }

  else {
    cout << "Student Database is Empty" << endl;
  }
}

//traveses the tree to print the faculty
void Menu::printMF(TreeNode<Faculty> *f) {
  if(f != NULL) {
    if(f->left != NULL) {
      printMF(f->left);
    }
    f->data->printFaculty();

    if(f->right != NULL) {
      printMF(f->right);
    }
  }

  else {
    cout << "Faculty Database is Empty" << endl;
  }
}

//outputs the students to the file to be used when opening the program again
void Menu::outputMS(TreeNode<Student> *s, string student) {
  ofstream out;
  out.open(student.c_str());

  if(s != NULL) {
    out << "--" << endl;
    out << s->data->getID() << endl;
    out << s->data->getName() << endl;
    out << s->data->getLevel() << endl;
    out << s->data->getMajor() << endl;
    out << s->data->getGPA() << endl;
    out << s->data->getAdvisor() << endl;

    if(s->left != NULL) {
      outputMS(s->left, student);
    }

    if(s->right != NULL) {
      outputMS(s->right, student);
    }
  }
  else {
    cout << "Student Database is Empty" << endl;
  }

  out.close();
}

//outputs the faculty to the file to be used when opening the program again
void Menu::outputMF(TreeNode<Faculty> *f, string faculty) {
  ofstream out;
  out.open(faculty.c_str());

  if(f != NULL) {
    out << "--" << endl;
    out << f->data->getID() << endl;
    out << f->data->getName() << endl;
    out << f->data->getLevel() << endl;
    out << f->data->getDepartment() << endl;
    out << f->data->getAdviseeID() << endl;

    if(f->data->getAdviseeID() > 0) {
      for(int i = 0; i < f->data->maxSize; ++i) {
        if(f->data->adviseeArray[i] != -1) {
          out << f->data->adviseeArray[i] << endl;
        }
      }
    }

    if(f->left != NULL) {
      outputMF(f->left, faculty);
    }
    if(f->right != NULL) {
      outputMF(f->right, faculty);
    }
  }
  else {
    cout << "Faculty Database is Empty" << endl;
  }

  out.close();
}

TreeNode<Student>* Menu::getMSRoot() {
  return masterStudent.getRoot();
}

TreeNode<Faculty>* Menu::getMFRoot() {
  return masterFaculty.getRoot();
}

//print the menu to the user and sends them to the option they choose
void Menu::printMenu() {
  string input;
  int numInput;
  bool triggered;
  bool running = true;

  while (running) {
    cout << "\n****************** MENU ******************" << endl;
    cout << 1 << ".  Print (all) Student Info (by ascending ID)" << endl;
    cout << 2 << ".  Print (all) Faculty Info (by ascending ID)" << endl;
    cout << 3 << ".  Print Student Info (by student ID)" << endl;
    cout << 4 << ".  Print Faculty Info (by faculty ID)" << endl;
    cout << 5 << ".  Print Advisor Info (by student ID)" << endl;
    cout << 6 << ".  Print Advisee Info (by faculty ID)" << endl;
    cout << 7 << ".  Add New Student" << endl;
    cout << 8 << ".  Delete Student (by student ID)" << endl;
    cout << 9 << ".  Add New Faculty" << endl;
    cout << 10 << ". Delete Faculty (by faculty ID)" << endl;
    cout << 11 << ". Change Advisor (by student ID and faculty ID)" << endl;
    cout << 12 << ". Remove Advisee (by student ID and faculty ID)" << endl;
    cout << 13 << ". Rollback" << endl;
    cout << 14 << ". Exit" << endl;
    cout << "\nPlease Select a Menu Option: ";

    cin >> input;

    try {
      numInput = atoi(input.c_str());

      if(numInput < 0 || numInput > 14) {
        cout << "Glitch Within the Matrix - Please Enter a Valid Menu Option \n" << endl;
        triggered = true;
        numInput = 15;
      }
    }
    catch(exception e) {
      triggered = false;
      numInput = 15;
    }

    switch(numInput) {
      case 1:
        printAllStudents();
        break;
      case 2:
        printAllFaculty();
        break;
      case 3:
        printStudent();
        break;
      case 4:
        printFaculty();
        break;
      case 5:
        printAdvisor();
        break;
      case 6:
        printAdvisee();
        break;
      case 7:
        addStudent();
        break;
      case 8:
        deleteStudent();
        break;
      case 9:
        addFaculty();
        break;
      case 10:
        deleteFaculty();
        break;
      case 11:
        changeAdvisor();
        break;
      case 12:
        removeAdvisee();
        break;
      case 13:
        rollback();
        break;
      case 14:
        exit();
        return;
      default:
        if(triggered == true) {
          continue;
        }
        else {
          cout << "Glitch Within the Matrix - Please Enter a Valid Menu Option \n" << endl;
          continue;
        }
    }
  }
}

//go through the tree printing all the students IN ORDER
void Menu::printAllStudents() {
  if(masterStudent.isEmpty()) {
    cout << "\nStudent Database is Empty" << endl;
  }
  else {
    printMS(masterStudent.getRoot());
  }
}

//go through the tree printing all the faculty IN ORDER
void Menu::printAllFaculty() {
  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty Database is Empty" << endl;
  }
  else {
    printMF(masterFaculty.getRoot());
  }
}

void Menu::printStudent() {
  string input;
  int srID;

  if(masterStudent.isEmpty()) {
    cout << "\nStudent Database is Empty" << endl;
  }
  else {
    while(true) {
      cout << "\nPlease Provide a Student ID: ";
      cin >> input;

      try {
        srID = atoi(input.c_str());

        if(masterStudent.contains(srID)) {
          masterStudent.find(srID)->printStudent();
          break;
        }
        else {
          cout << "\nStudent ID: " << srID << "Does Not Exist Within Database" << endl;
        }
      }
      catch(exception e) {
        cout << "\nPlease Enter Valid Input" << endl;
      }
    }
  }
}

//Prints a single faculty member and their information that the user chooses
void Menu::printFaculty() {
  string input;
  int frID;

  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty Database is Empty" << endl;
  }
  else {
    while(true) {
      cout << "\nPlease Provide a Faculty ID: ";
      cin >> input;

      try {
        frID = atoi(input.c_str());

        if(masterFaculty.contains(frID)) {
          masterFaculty.find(frID)->printFaculty();
          break;
        }
        else {
          cout << "\nFaculty ID: " << frID << " Does Not Exist Within Database" << endl;
        }
      }
      catch(exception e) {
        cout << "\nPlease Enter Valid Input" << endl;
      }
    }
  }
}

//prints an advisor given a student ID number from the user
void Menu::printAdvisor() {
  string input;
  int srID;

  if(masterStudent.isEmpty()) {
    cout << "\nStudent Database is Empty" << endl;
  }
  else {
    cout << "\nList of Students Within Database: " << endl;
    printMS(masterStudent.getRoot());

    while(true) {
      cout << "\nPlease Provide a Student ID: ";
      cin >> input;

      try {
        srID = atoi(input.c_str());

        if(masterStudent.contains(srID)) {
          Student *student = masterStudent.find(srID);

          masterFaculty.find(student->getAdvisor())->printFaculty();
          break;
        }
        else {
          cout << "\nStudent ID: " << srID << " Does Not Exist Within Database" << endl;
        }
      }
      catch(exception e) {
        cout << "\nPlease Enter Valid Input" << endl;
      }
    }
  }
}

//prints an advisee information given the faculty ID user provides
void Menu::printAdvisee() {
  string input;
  int frID;

  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty Database is Empty" << endl;
  }
  else {
    cout << "\nList of Faculty Within Database: " << endl;
    printMF(masterFaculty.getRoot());

    while(true) {
      cout << "\nPlease Provide a Faculty ID: ";
      cin >> input;

      try {
        frID = atoi(input.c_str());

        if(masterFaculty.contains(frID)) {
          Faculty *faculty = masterFaculty.find(frID);

          for(int i = 0; i < faculty->getSizeArray(); ++i) {
            if(faculty->adviseeArray[i] != -1) {
              masterStudent.find(faculty->adviseeArray[i])->printStudent();
              break;
            }
            else {
              cout << "\nFaculty Member Has No Advisees" << endl;
            }
          }
          break;
        }
        else {
          cout << "\nFaculty ID: " << frID << " Does Not Exist Within Database" << endl;
        }
      }
      catch(exception e) {
        cout << "\nPlease Enter Valid Input" << endl;
      }
    }
  }
}

//allows the user to add a student to the records
void Menu::addStudent() {
  //Rollback Implementation
  //studentStack.push(masterStudent);
  //facultyStack.push(masterFaculty);
  //---------------------->

  string input;

  //Generate Student ID
  bool goodID = false;
  srand(time(NULL));
  int srID = rand() % 4000 + 1000; // will generate a number between 1000 and 4999

  while(goodID == false){
    if(masterStudent.contains(srID) == false){
      goodID = true;
    }
    else {
      int srID = rand() % 4000 + 1000;
      goodID = false;
    }
  }

  cout << "\nNew Students Generated ID: " << srID << endl;
  cin.fail();

  string name;
  cout << "New Student Name: ";
  cin.ignore();
  getline(cin, name);

  string level;
  cout << "New Student Grade: ";
  cin >> level;

  string major;
  cout << "New Student Major: ";
  cin >> major;

  double gpa;
  while(true) {
    input = "";
    cout << "New Student GPA: ";
    cin >> input;

    try {
      gpa = atof(input.c_str());

      if(gpa > 5 || gpa < 0) {
        cout << "\nEnter GPA From 0-5" << endl;
      }
      else {
        break;
      }
    }
    catch(exception e) {
      cout << "\nPlease Enter Valid Input" << endl;
    }
  }

  int advisorID;

  if(!masterFaculty.isEmpty()) {
    while(true) {
      input = "";
      cout << "New Student Advisor ID: ";
      cin >> input;

      try {
        advisorID = atoi(input.c_str());

        if(masterFaculty.contains(advisorID) || advisorID == -1) {
          Faculty *faculty = masterFaculty.find(advisorID);
          faculty->addAdvisee(srID);
          break;
        }
        else {
          input = "";
          cout << "\nFaculty ID: " << advisorID << " Does Not Exist Within Database" << endl;
          cout << "(Y/N) Would You Like a List of Faculty? ";
          cin >> input;

          if(input == "Y" || input == "Yes") {
            printAllFaculty();
          }
          else {
            break;
          }
        }
      }
      catch(exception e) {
        cout << "\nPlease Enter Valid Input" << endl;
      }
    }
  }
  else {
    advisorID = -1;
  }

  Student *student = new Student(srID, name, level, major, gpa, advisorID);
  TreeNode<Student> *studentNode = new TreeNode<Student>(student, srID);
  masterStudent.put(studentNode);
}

//allows the user to input a student ID number and delete that student from the records
void Menu::deleteStudent() {
  //Rollback Implementation
  //studentStack.push(masterStudent);
  //facultyStack.push(masterFaculty);
  //---------------------->

  string input;
  int srID = 0;

  if(masterStudent.isEmpty()) {
    cout << "\nStudent Database is Empty" << endl;
  }
  else {
    cout << "\nList of Students Within Database: " << endl;
    printMS(masterStudent.getRoot());

    while(true) {
      input = "";
      cout << "\nPlease Provide a Student ID: ";
      cin >> input;

      try {
        srID = atoi(input.c_str());

        if(masterStudent.contains(srID)) {
          if(masterStudent.find(srID)->getAdvisor() != -1) {
            masterFaculty.find(masterStudent.find(srID)->getAdvisor())->removeAdvisee(srID);
          }
          masterStudent.erase(srID);
          break;
        }
        else {
          cout << "\nStudent ID: " << srID << " Does Not Exist Within Database" << endl;
        }
      }
      catch(exception e) {
        cout << "\nPlease Provide Valid Input" << endl;
      }
    }
  }
}

//allows the user to add a faculty member to the records
void Menu::addFaculty() {
  //Rollback Implementation
  //studentStack.push(masterStudent);
  //facultyStack.push(masterFaculty);
  //---------------------->

  string input;
  int newAdviseeTotal = 0;
  int srID = 0;

  //Generate Faculty ID
  bool goodID = false;
  srand(time(NULL));
  int frID = rand() % 5000 + 5000; // will generate a number between 5000 and 9999

  while(goodID == false){
    if(masterFaculty.contains(frID) == false){
      goodID = true;
    }
    else {
      int frID = rand() % 5000 + 5000;
      goodID = false;
    }
  }

  cout << "New Faculty ID: " << frID << endl;
  cin.clear();

  string name;
  cout << "New Faculty Name: ";
  cin.ignore();
  getline(cin, name);

  string level;
  cout << "New Faculty Level: ";
  cin >> level;

  string department;
  cout << "New Faculty Department: ";
  cin >> department;

  Faculty *faculty = new Faculty(frID, name, level, department);

  if(!masterStudent.isEmpty()) {
    while(true) {
      cout << "How Many Advisees Does New Faculty Have: ";
      cin >> input;

      try {
        newAdviseeTotal = atoi(input.c_str());
        break;
      }
      catch(exception e) {
        cout << "Please Provide Valid Input" << endl;
      }
    }

    if(newAdviseeTotal != 0) {
      cout << "\nList of Students Within Database: " << endl;
      printAllStudents();
    }

    for(int i = 0; i < newAdviseeTotal; ++i) {
      while(true) {
        input = "";
        cout << "[" << newAdviseeTotal << " Remaining] Please Provide a Student ID: ";
        cin >> input;

        try {
          srID = atoi(input.c_str());

          if(masterStudent.contains(srID)) {
            faculty->addAdvisee(srID);
            masterStudent.find(srID)->setAdvisor(frID);
            --newAdviseeTotal;
            break;
          }
          else {
            cout << "Student ID: " << srID << " Does Not Exist Within Database" << endl;
          }
        }
        catch(exception e) {
          cout << "\nPlease Provide Valid Input" << endl;
        }
      }
    }
  }

  TreeNode<Faculty> *facultyNode = new TreeNode<Faculty>(faculty, frID);
  masterFaculty.put(facultyNode);
}

//allows the user to delete a faculty member from the records given an ID number and transfer their advisees to a new advisor
void Menu::deleteFaculty() {
  //Rollback Implementation
  //studentStack.push(masterStudent);
  //facultyStack.push(masterFaculty);
  //---------------------->

  string input;
  int frID = 0;
  int transferID = 0;

  if(masterFaculty.isEmpty()) {
    cout << "\nFaculty Database is Empty" << endl;
  }
  else {
    cout << "\nList of Faculty Within Database: " << endl;
    printMF(masterFaculty.getRoot());

    while(true) {

      input = "";
      cout << "\nPlease Provide a Faculty ID: ";
      cin >> input;

      try {
        frID = atoi(input.c_str());
        if(masterFaculty.contains(frID)) {
          if(masterFaculty.find(frID)->numAdvisee > 0) {
            while(true) {
              input = "";
              cout << "\nPlease Provide a Faculty ID to Transfer Advisees To: ";
              cin >> input;

              try {
                transferID = atoi(input.c_str());

                if(masterFaculty.contains(transferID)) {
                  for(int i = 0; i < masterFaculty.find(frID)->maxSize; ++i) {
                    if(masterFaculty.find(frID)->adviseeArray[i] != -1) {
                      masterStudent.find(masterFaculty.find(frID)->adviseeArray[i])->setAdvisor(transferID);
                    }
                  }
                }
                else {
                  cout << "\nFaculty Transfer ID: " << transferID << " Does Not Exist Within Database" << endl;
                }
                break;
              }
              catch(exception e) {
                cout << "\nPlease Provide Valid Input" << endl;
              }
            }
          }
          else {
            masterFaculty.erase(frID);
            break;
          }
        }
        else {
          cout << "\nFaculty ID: " << frID << " Does Not Exist Within Database" << endl;
        }
        break;
      }
      catch(exception e) {
        cout << "\nPlease Provide Valid Input" << endl;
      }
    }
  }
}

//allows the user to change the advisor of a student from one faculty member
// to another given all the IDs neccessary
void Menu::changeAdvisor() {
  //Rollback Implementation
  //studentStack.push(masterStudent);
  //facultyStack.push(masterFaculty);
  //---------------------->

  string input;
  int srID = 0;
  int frID = 0;

  if(masterFaculty.isEmpty() || masterStudent.isEmpty()) {
    cout << "\nStudent and/or Faculty Database is Empty" << endl;
  }
  else {
    cout << "\nList of Students Within Database: ";
    printMS(masterStudent.getRoot());

    while(true) {
      input = "";
      cout << "\nPlease Provide a Student ID: ";
      cin >> input;

      try {
        srID = atoi(input.c_str());

        if(masterStudent.contains(srID)) {
          while(true) {
            input = "";
            cout << "\nPlease Provide a Faculty ID: ";
            cin >> input;

            try {
              frID = atoi(input.c_str());

              if(masterFaculty.contains(frID)) {
                break;
              }
              else {
                cout << "\nFaculty ID: " << frID << " Does Not Exist Within Database" << endl;
              }
            }
            catch(exception e) {
              cout << "\nPlease Provide Valid Input" << endl;
            }
          }
          break;
        }
        else {
          cout << "\nStudent ID: " << srID << " Does Not Exist Within Database" << endl;
        }
      }
      catch(exception e) {
        cout << "\nPlease Enter Valid Input" << endl;
      }
    }
    masterStudent.find(srID)->setAdvisor(frID);
    masterFaculty.find(frID)->addAdvisee(srID);
  }
}

//allows the user to remove an advisee from an advisor given the ID numbers of both
void Menu::removeAdvisee() {
  //Rollback Implementation
  //studentStack.push(masterStudent);
  //facultyStack.push(masterFaculty);
  //---------------------->

  string input;
  int srID = 0;
  int frID = 0;

  if(masterFaculty.isEmpty() || masterStudent.isEmpty()) {
    cout << "\nStudent and/or Faculty Database is Empty" << endl;
  }
  else {
    cout << "List of Faculty Within Database: ";
    printMF(masterFaculty.getRoot());

    while(true) {
      input = "";
      cout << "\nPlease Provide a Faculty ID: ";
      cin >> input;

      try {
        frID = atoi(input.c_str());

        if(masterFaculty.contains(frID)) {
          cout << "\nList of Advisees for Faculty ID: " << frID << endl;
          masterFaculty.find(frID)->printAdvisee();

          while(true) {
            input = "";
            cout << "\nPlease Provide a Student ID: ";
            cin >> input;

            try {
              srID = atoi(input.c_str());

              if(masterStudent.contains(srID)) {
                break;
              }
              else {
                cout << "\nStudent ID: " << srID << " Does Not Exist Within Database" << endl;
              }
            }
            catch(exception e) {
              cout << "\nPlease Provide Valid Input" << endl;
            }
          }
          break;
        }
        else {
          cout << "\nFaculty ID: " << frID << " Does Not Exist Within Database" << endl;
        }
      }
      catch(exception e) {
        cout << "\nPlease Enter Valid Input" << endl;
      }
    }

    if(masterFaculty.find(frID)->removeAdvisee(srID)) {
      masterStudent.find(srID)->setAdvisor(-1);
    }

    input = "";
    cout << "\n(Y/N) Would You Like To Set a New Advisor? ";
    cin >> input;

    if(input == "Y" || input == "y" ) {
      cout << "\nHere is List of All Faculty: ";
      printAllFaculty();

      while(true) {
        input = "";
        cout << "Please Provide a Faculty ID: ";
        cin >> input;

        try {
          frID = atoi(input.c_str());

          if(masterFaculty.contains(frID)) {
            break;
          }
          else {
            cout << "Faculty ID: " << frID << " Does Not Exist Within Database" << endl;
          }
        }
        catch(exception e) {
          cout << "Please Provide Valid Input" << endl;
        }
      }

      masterStudent.find(srID)->setAdvisor(frID);
    }
  }
}

//allows the user to undo the last five commands they did
void Menu::rollback() {
/*
  try {
    masterStudent = studentStack.pop();
    masterFaculty = facultyStack.pop();
  }
  catch(exception e) {
    cout << "Undo Function is Unavailable" << endl;
  }
*/
}

//exits the program
void Menu::exit() {
  cout << "EXITING PROGRAM..." << endl;
}
