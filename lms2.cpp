#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

//structs

struct User
{
    string username;
    string password;
};

struct Course
{
    string courseCode;
    string courseName;
    int crtHrs;
    int semester;
};

struct CourseEnrollment
{
    string courseCode;
};

struct Student
{
    string regNo;
    string name;
    CourseEnrollment courses[10];
};

//initolliazer
void initializeCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
void initializeUsers(string usernames[], string passwords[], int size);

//function for data persistent
bool saveCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size);
bool loadUser(string usersList[], string passwordList[], int size);

//COURSE MANAGEMENT
int searchCourseCode(string codeList[], int size, string courseCode);
bool addCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester);
void viewCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size);
void viewSemesterCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, int semester);
bool updateCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester);
bool deleteCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode);

////add student,update////
bool addStudent(Student StudentArr[], int MAX_STUDENT, Student StudentStruct);
bool updateStudent(Student StudentArr[], int MAX_STUDENT, Student StudentStruct);
bool deleteStudent(Student StudentArr[], int MAX_STUDENT, Student StudentStruct);
bool registerCoursestring(Student StudentArr[], Course CourseStruct, Student StudentStruct, string codeList[], int MAX_STUDENT);
bool unRegisterCourse(Student StudentArr[], int MAX_STUDENT, Course CourseStruct, Student StudentStruct);
bool isValidRegistrationName(string regNo);
bool isValidStudentName(string stdname);
bool find(Student StudentArr[], int MAX_STUDENT, Student StudentStruct);
bool saveStudents(Student StudentArr[], int MAX_STUDENT);
bool loadStudents(Student StudentArr[], int MAX_STUDENT);

//VALIDATION FUNCTIONS
bool isValidCourseCode(string code);
bool isValidCreditHours(int creditHours);
bool isValidSemester(int semester);
bool isValidCourseName(string name);
bool validateAllData(string courseCode, string courseName, int credit, int semester);

//USER MANAGEMENT
bool userExist(string user[], string pass[], string users, string passs, int size);
void login(string &userName, string &password);

int main()
{

    //Maximum Size of All arrays
    int MAX_COURSES = 10;
    int MAX_USERS = 10;
    bool flag = false;
    string userName;
    string password;
    string courseCode;
    string courseName;
    int credit;
    int semester;
    int input;
    //Declare All Arrays
    string usersList[MAX_USERS], passwordList[MAX_USERS];
    string codeList[MAX_COURSES], nameList[MAX_COURSES];
    int creditHours[MAX_COURSES], semList[MAX_COURSES];

    //student section
    int count = 0;
    int MAX_STUDENT = 10;
    Student StudentStruct;
    Course CourseStruct;
    User UserStruct;
    User usersArr[MAX_STUDENT];
    Student StudentArr[MAX_STUDENT];

    //Initialize all arrays
    initializeCourses(codeList, nameList, creditHours, semList, MAX_COURSES);
    initializeUsers(usersList, passwordList, MAX_USERS);

    //This function will load the courses in arrays
    loadCourses(codeList, nameList, creditHours, semList, MAX_COURSES);

    //This function will load the users in array
    loadUser(usersList, passwordList, MAX_USERS);
    //load studenta
    loadStudents(StudentArr,MAX_STUDENT);
        //For starting code
        login(userName, password);

    do
    {

        while (userExist(usersList, passwordList, userName, password, MAX_USERS) != true || (userName == "" && password == ""))
        {
            cout << "Incorrect info please reenter username and password" << endl;
            cout << "Enter User name: ";
            cin >> userName;
            cout << "Enter Password: ";
            cin >> password;
            cout << endl;
        }

        if (userExist(usersList, passwordList, userName, password, MAX_USERS))
        {
        return1:
            cout << "Choose the following option" << endl;
            cout << "1   Add Courses" << endl;
            cout << "2   Update Courses" << endl;
            cout << "3   Delete Courses" << endl;
            cout << "4   View All Courses" << endl;
            cout << "5   View Courses of a Semester" << endl;
            cout << "6   Add New Student" << endl;
            cout << "7   Update Student " << endl;
            cout << "8   Delete Student " << endl;
            cout << "9   View All Students " << endl;
            cout << "10  Register the course for student " << endl;
            cout << "11  Unregister the course for student" << endl;
            cout << "12  Logout of the system" << endl;
            cout << "13  Exit Program" << endl;
            cout << "Enter the option: ";
            cin >> input;
            switch (input)
            {
            // This case for adding the course details
            case 1:

                cout << "Enter the details of the course: ";
                cin >> courseCode;
                cin >> credit;
                cin >> semester;
                cin.ignore();
                getline(cin, courseName);

                //Check validity of all inputs
                if (validateAllData(courseCode, courseName, credit, semester))
                {
                    //Call addCourse function
                    if (addCourses(codeList, nameList, creditHours, semList, MAX_COURSES, courseCode, courseName, credit, semester))
                    {
                        cout << "Course Successfully added" << endl;
                    }
                    else
                    {
                        cout << "Sorry No space to add new course" << endl;
                    }
                }
                else
                {
                    //If any validity is false it will not add the course
                    cout << "Invalid details" << endl;
                }

                break;

            // This case for Updating the course details
            case 2:

                cout << "Enter the course code" << endl;
                cin >> courseCode;

                //check validity of courseCode
                if (!isValidCourseCode(courseCode))
                {

                    //Find the index of courseCode which user entered to update the course details

                    cout << "Enter the details of the course: ";
                    cin >> courseCode;
                    cin >> credit;
                    cin >> semester;
                    cin.ignore();
                    getline(cin, courseName);
                    //Check validity of all details entered by user
                    if (validateAllData(courseCode, courseName, credit, semester))
                    {

                        if (updateCourse(codeList, nameList, creditHours, semList, MAX_COURSES, courseCode, courseName, credit, semester))
                        {
                            cout << "Course successfully updated" << endl;
                        }
                        else
                        {
                            cout << "No course found" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid data" << endl;
                    }
                }
                else
                {
                    //here we will show message of not valid data
                    cout << "Invalid Data" << endl;
                }

                break;

                //This case for deleting the course details

            case 3:
                cout << "Enter Course code" << endl;
                cin >> courseCode;
                //Validate the course Code
                if (!isValidCourseCode(courseCode))
                {
                    //call function to delete the course detail which has same course code as user enter
                    if (deleteCourse(codeList, nameList, creditHours, semList, MAX_COURSES, courseCode))
                    {
                        cout << "Course Successfully deleted" << endl;
                    }
                    else
                    {
                        cout << "Sorry No Course found " << endl;
                    }
                }
                else
                {
                    //if course code is invalid then this message will show
                    cout << "Invalid Course code" << endl;
                }

                break;

                //This case for displaying all details of all courses

            case 4:
                //View All details of All courses
                viewCourses(codeList, nameList, creditHours, semList, MAX_COURSES);
                break;

            //This case for displaying course details of specific semester
            case 5:
                cout << "Enter the semester:";
                cin >> semester;
                //Check valildidty of semester entered by user
                if (isValidSemester(semester))
                {
                    //Show All details of course of the semester entered by user
                    viewSemesterCourse(codeList, nameList, creditHours, semList, MAX_COURSES, semester);
                }
                else
                {
                    //If our semester is invalid
                    cout << "Invalid data" << endl;
                }

                break;

            //////////////////////////add a student///////////////////////////////////
            case 6:
                cout << "Enter Details:";
                cin >> StudentStruct.regNo;
                cin.get();
                getline(cin, StudentStruct.name, '\n');
                if (isValidRegistrationName(StudentStruct.regNo) && isValidStudentName(StudentStruct.name))
                {
                    if (addStudent(StudentArr, MAX_STUDENT, StudentStruct))
                    {
                        cout << "Student Added Successfully!!" << endl;
                    }
                    else
                    {
                        cout << "This Registration Number is Already Registered " << endl;
                    }
                }
                else
                {
                    cout << "You have Enter Wrong Credits" << endl;
                }
                cout << "Press any Key To continue" << endl;
                getch();
                system("CLS");
                break;

            //////////////////////////update student
            case 7:
                cout << "Enter registration Number of the student to edit:";
                cin >> StudentStruct.regNo;
                if (find(StudentArr, MAX_STUDENT, StudentStruct))
                {
                    cout << "User Found!!..Please Enter New Data" << endl;
                    cout << "Enter details of Student:" << StudentStruct.regNo << " ";
                    cin.get();
                    getline(cin, StudentStruct.name);
                    if (isValidStudentName(StudentStruct.name))
                    {
                        if (updateStudent(StudentArr, MAX_STUDENT, StudentStruct))
                        {
                            cout << "Student has been edited successfully" << endl;
                        }
                    }
                    else
                    {
                        cout << "You Have Enter wrong Name please try again..." << endl;
                    }
                }
                else
                {
                    cout << "No Record For this Reg.Number.." << endl;
                }
                cout << "Press any Key To continue" << endl;
                getch();
                system("CLS");
                break;

                //Del A Student
            case 8:
                cout << "Enter registration Number of the student to delete:";
                cin >> StudentStruct.regNo;
                if (deleteStudent(StudentArr, MAX_STUDENT, StudentStruct))
                {
                    cout << "Student has been deleted successfully!!!" << endl;
                }
                cout << "Press any Key To continue" << endl;
                getch();
                system("CLS");
                break;

            //view Student...
            case 9:
                cout << setw(35) << left << "Student Registration Number";
                cout << setw(35) << left << "Student Name";
                cout << "Registered Course" << endl;
                cout << "***************************************************************************************" << endl;
                for (int i = 0; i < 10; i++)
                {
                    if (StudentArr[i].name != "")
                    {
                        cout << setw(35) << left << StudentArr[i].regNo;
                        cout << setw(35) << left << StudentArr[i].name;
                        for (int j = 0; j < 10; j++)
                        {
                            if (StudentArr[i].courses[j].courseCode != "")
                            {
                                if (j == 0)
                                {
                                    cout << StudentArr[i].courses[j].courseCode;
                                }
                                else
                                {
                                    cout << ":" << StudentArr[i].courses[j].courseCode;
                                }
                            }
                        }
                        cout << endl;

                        //break;
                    }
                }
                cout << "_______________________________________________________________________________________" << endl;
                cout << endl;

                cout << "Press any Key To continue" << endl;
                getch();
                system("CLS");
                break;

            //Register Student
            case 10:
                cout << "Enter registration Number of the student for course registration:";
                cin >> StudentStruct.regNo;
                if (find(StudentArr, MAX_STUDENT, StudentStruct))
                {
                    cout << "Enter Course Code to register:";
                    cin >> CourseStruct.courseCode;
                    flag = isValidCourseCode(CourseStruct.courseCode);
                    if (flag == true)
                    {
                        if (registerCoursestring(StudentArr, CourseStruct, StudentStruct, codeList, MAX_STUDENT))
                        {
                            cout << "Course has been registered for student" << endl;
                        }
                        else
                        {
                            cout << "CourseCode Don't Match" << endl;
                        }
                    }
                }
                else
                {
                    cout << "No Record For this Reg.Number.." << endl;
                }
                cout << "Press any Key To continue" << endl;
                getch();
                system("CLS");
                break;

                //unregister course
            case 11:
                cout << "Enter registration Number of the student:";
                cin >> StudentStruct.regNo;
                if (find(StudentArr, MAX_STUDENT, StudentStruct))
                {
                    cout << "Enter Course Code to unregister:";
                    cin >> CourseStruct.courseCode;
                    if (isValidCourseCode(CourseStruct.courseCode))
                    {
                        if (unRegisterCourse(StudentArr, MAX_STUDENT, CourseStruct, StudentStruct))
                        {
                            cout << "Course has been unregistered" << endl;
                        }
                        else
                        {
                            cout << "Course Not Found" << endl;
                        }
                    }
                }
                else
                {
                    cout << "Reg.Number not found.." << endl;
                }
                cout << "Press any Key To continue" << endl;
                getch();
                system("CLS");
                break;

            // For Closing the Program
            case 12:
                if (saveCourse(codeList, nameList, creditHours, semList, MAX_COURSES))
                {
                    cout << "All courses Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                userName = "";
                password = "";
                login(userName, password);
                break;
            case 13:
                if (saveCourse(codeList, nameList, creditHours, semList, MAX_COURSES))
                {
                    cout << "All courses Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                cout << "Program closed ";
                if (saveStudents(StudentArr, MAX_STUDENT))
                {
                    cout << "All Students Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                cout << "Program closed ";
                break;
            default:
                cout << "Invalid choice";
            }
        }
    } while (input != 13);

    return 0;
}

void initializeCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    for (int s = 0; s < size; s++)
    {
        codeList[s] = " ";
        nameList[s] = " ";
        crtHrsList[s] = 0;
        semList[s] = 0;
    }
}

void initializeUsers(string usernames[], string passwords[], int size)
{
    for (int s = 0; s < size; s++)
    {
        usernames[s] = " ";
        passwords[s] = " ";
    }
}

bool saveCourse(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    // This variable for read data from file
    ofstream myfile;
    /*Open the file if exist if not exist then make new file of this name ios::app maens that the new data will append in file and 
	not remove previous content of file */
    myfile.open("Courses.txt");
    //This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        for (int i = 0; i < size; i++)
        {
            if (codeList[i] != "" && nameList[i] != "" && crtHrsList[i] != 0 && semList[i] != 0)
            {
                //These lines will write all array data to the file and make a comma separated file
                myfile << codeList[i] << ",";
                myfile << nameList[i] << ",";
                myfile << crtHrsList[i] << ",";
                myfile << semList[i] << endl;
            }
        }

        myfile.close();
        return true;
    }
    else
    {
        //If there is error while opening file this function will return false
        return false;
    }
}
//Function to load course in arrays
bool loadCourses(string codeList[], string nameList[], int crtHrsList[], int semList[], int size)
{
    int i = 0;
    ifstream getCourse("Courses.txt");
    if (!getCourse.is_open())
    {
        cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string courseCode, courseName;
        string creditHours, semester;
        int credit, sem;
        string line;
        while (!getCourse.eof() && i < size)
        {
            getline(getCourse, line);
            if (line == "")
                continue;
            stringstream ss(line);
            getline(ss, courseCode, ',');
            codeList[i] = courseCode;
            getline(ss, courseName, ',');
            nameList[i] = courseName;
            getline(ss, creditHours, ',');
            credit = stoi(creditHours);
            crtHrsList[i] = credit;
            getline(ss, semester, ',');
            sem = stoi(semester);
            semList[i] = sem;
            i++;
        }

        getCourse.close();
        return true;
    }
}

//Fuunction to read users from file and load then onto the arrays
bool loadUser(string usersList[], string passwordList[], int size)
{
    int i = 0;
    ifstream getUsers("Users.txt");
    if (!getUsers.is_open())
    {
        cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string username, password;
        string line;
        while (!getUsers.eof() && i < size)
        {
            getline(getUsers, line);
            stringstream ss(line);
            getline(ss, username, ',');
            usersList[i] = username;
            getline(ss, password, ',');
            passwordList[i] = password;
            i++;
        }

        getUsers.close();
        return true;
    }
}

int searchCourseCode(string codeList[], int size, string courseCode)
{
    int index = -1;
    for (int i = 0; i < size; i++)
    {
        if (codeList[i] == courseCode)
        {
            index = i;
            break;
        }
    }
    return index;
}
//This Function Will add the function
bool addCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester)
{
    bool flag = false;
    int i = searchCourseCode(codeList, size, " ");
    if (i != -1)
    {

        codeList[i] = courseCode;
        nameList[i] = courseName;
        creditHours[i] = credit;
        semList[i] = semester;
        flag = true;
    }
    return flag;
}

// This Function will display all course details
void viewCourses(string codeList[], string nameList[], int creditHours[], int semList[], int size)
{

    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    cout << left;
    cout << setw(10) << "Course"
         << setw(50) << "Course"
         << setw(10) << "Credit"
         << setw(10) << "Semester" << endl;
    cout << setw(10) << "Code"
         << setw(50) << "Name"
         << setw(10) << "Hours"
         << setw(10) << "" << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        if (codeList[i] != " ")
        {

            cout << setw(10) << codeList[i]
                 << setw(50) << nameList[i]
                 << setw(10) << creditHours[i]
                 << setw(10) << semList[i] << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

//This function will display the course details of the specific semester
void viewSemesterCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, int semester)
{

    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    cout << left;
    cout << setw(10) << "Course"
         << setw(50) << "Course"
         << setw(10) << "Credit"
         << setw(10) << "Semester" << endl;
    cout << setw(10) << "Code"
         << setw(50) << "Name"
         << setw(10) << "Hours"
         << setw(10) << "" << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        if (semList[i] == semester && codeList[i] != "")
        {
            cout << setw(10) << codeList[i]
                 << setw(50) << nameList[i]
                 << setw(10) << creditHours[i]
                 << setw(10) << semList[i] << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}

// This function will update the course by using courseCode index which we define as globel varaible
bool updateCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode, string courseName, int credit, int semester)
{
    bool flag = false;
    int updateIndex = searchCourseCode(codeList, size, courseCode);
    if (updateIndex != -1)
    {
        codeList[updateIndex] = courseCode;
        nameList[updateIndex] = courseName;
        creditHours[updateIndex] = credit;
        semList[updateIndex] = semester;
        flag = true;
    }
    return flag;
}

// This function will delete the course by using courseCode
bool deleteCourse(string codeList[], string nameList[], int creditHours[], int semList[], int size, string courseCode)
{
    bool flag = false;
    int i = searchCourseCode(codeList, size, courseCode);
    if (i != -1)
    {
        codeList[i] = " ";
        nameList[i] = " ";
        creditHours[i] = 0;
        semList[i] = 0;
        flag = true;
    }

    return flag;
}
//checking validity of coursecode
bool isValidCourseCode(string code)
{
    int x = code.length();
    bool flag = true;
    if (x == 5)
    {

        for (int i = 0; i < 2; i++)
        {
            if (!((code[i] >= 'a' && code[i] <= 'z') || (code[i] >= 'A' && code[i] <= 'Z')))
            {
                flag = false;
                break;
            }
        }

        for (int i = 2; i < 5 && flag; i++)
        {
            if (!(code[i] >= '0' && code[i] <= '9'))
            {
                flag = false;
                break;
            }
        }
    }

    return flag;
}

// checking the credit hours
bool isValidCreditHours(int creditHours)
{
    bool flag = true;
    if (!(creditHours >= 1 && creditHours <= 3))
    {
        flag = false;
    }

    return flag;
}

//checking semester
bool isValidSemester(int semester)
{
    bool flag = true;
    if (!(semester >= 1 && semester <= 9))
    {
        flag = false;
    }
    return flag;
}

//checking coursename
bool isValidCourseName(string name)
{
    bool flag = true;
    if (name.length() <= 50)
    {
        for (int i = 0; i < name.length(); i++)
        {
            if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] == ' ')))
                flag = false;
        }
    }
    else
        flag = false;

    return flag;
}

bool validateAllData(string courseCode, string courseName, int credit, int semester)
{
    cout << isValidCourseCode(courseCode) << endl;
    cout << isValidCourseName(courseName) << endl;
    cout << isValidCreditHours(credit) << endl;
    cout << isValidSemester(semester) << endl;
    if (!(isValidCourseCode(courseCode) && isValidCreditHours(credit) && isValidSemester(semester) && isValidCourseName(courseName)))
    {
        return false;
    }
    return true;
}

bool userExist(string user[], string pass[], string users, string passs, int size)
{
    bool flag = false;
    int i;
    for (i = 0; i < size; i++)
    {
        if (user[i] == users && pass[i] == passs)
        {
            flag = true;
            break;
        }
    }

    return flag;
}

void login(string &userName, string &password)
{

    system("cls");
    cout << endl;
    cout << "** Welcome To University Learning Management System ** " << endl;
    cout << "Dear users current software is intended for authorized users only." << endl;
    cout << "Login to the system to get access" << endl;
    cout << "Enter User name: ";
    cin >> userName;
    cout << "Enter Password: ";
    cin >> password;
    cout << endl;
}
bool isValidRegistrationName(string regNo)
{
    int x = regNo.length();
    bool flag_reg = false;
    if (x == 11)
    {
        if (regNo[0] == '2' && regNo[1] == '0' && regNo[5] == 'C' && regNo[4] == '-' && regNo[7] == '-')
        {
            flag_reg == true;
            for (int n = 2; n < 4; n++)
            {
                if (regNo[n] >= '0' && regNo[n] <= '9')
                {
                    flag_reg = true;
                }
                else
                {
                    flag_reg = false;
                    break;
                }
            }
            if (flag_reg == true)
            {
                if (regNo[6] >= 'A' && regNo[6] <= 'Z')
                {
                    flag_reg = true;
                }
                else
                {
                    flag_reg = false;
                }
            }
            if (flag_reg == true)
            {
                for (int j = 8; j < 11; j++)
                {
                    if (regNo[j] >= '0' && regNo[j] <= '9')
                    {
                        flag_reg = true;
                    }
                    else
                    {
                        flag_reg = false;
                        break;
                    }
                }
            }
        }
        else
        {
            flag_reg = false;
        }
    }

    return flag_reg;
}
bool isValidStudentName(string stdname)
{
    bool flag;
    int size = stdname.length();
    if (size <= 40)
    {
        for (int i = 0; i < size; i++)
        {
            if ((stdname[i] >= 'A' && stdname[i] <= 'Z') || (stdname[i] >= 'a' && stdname[i] <= 'z') || stdname[i] == ' ')
            {
                flag = true;
            }
            else
            {
                flag = false;
                break;
            }
        }
    }
    return flag;
}
bool addStudent(Student StudentArr[], int MAX_STUDENT, Student StudentStruct)
{
    bool flag;
    for (int i = 0; i < MAX_STUDENT; i++)
    {
        if (StudentStruct.regNo == StudentArr[i].regNo)
        {
            return false;
        }
        else
        {
            if (StudentArr[i].name == "")
            {
                StudentArr[i].name = StudentStruct.name;
                StudentArr[i].regNo = StudentStruct.regNo;
                flag = true;
                break;
            }
            else
            {
                flag = false;
            }
        }
    }
    return flag;
}
bool updateStudent(Student StudentArr[], int MAX_STUDENT, Student StudentStruct)
{
    bool flag = false;
    for (int i = 0; i < MAX_STUDENT; i++)
    {
        if (StudentStruct.regNo == StudentArr[i].regNo)
        {
            StudentArr[i].name = StudentStruct.name;
            flag = true;
            break;
        }
    }
    return flag;
}
bool find(Student StudentArr[], int MAX_STUDENT, Student StudentStruct)
{
    bool flag = false;
    for (int i = 0; i < MAX_STUDENT; i++)
    {
        if (StudentStruct.regNo == StudentArr[i].regNo)
        {
            flag = true;
        }
    }
    return flag;
}
bool deleteStudent(Student StudentArr[], int MAX_STUDENT, Student StudentStruct)
{
    bool flag;
    for (int i = 0; i < MAX_STUDENT; i++)
    {
        if (StudentStruct.regNo == StudentArr[i].regNo)
        {
            StudentArr[i].regNo = "";
            StudentArr[i].name = "";
            StudentArr[i].courses[i].courseCode = "";
            flag = true;
        }
    }
    return flag;
}
bool registerCoursestring(Student StudentArr[], Course CourseStruct, Student StudentStruct, string codeList[], int MAX_STUDENT)
{
    bool flag;
    for (int j = 0; j < MAX_STUDENT; j++)
    {
        if (CourseStruct.courseCode == codeList[j])
        {
            flag = true;
        }
    }
    if (flag == true)
    {
        for (int i = 0; i < MAX_STUDENT; i++)
        {
            if (StudentStruct.regNo == StudentArr[i].regNo)
            {
                for (int k = 0; k < MAX_STUDENT; k++)
                {
                    if (StudentArr[i].courses[k].courseCode == "")
                    {
                        StudentArr[i].courses[k].courseCode = CourseStruct.courseCode;
                        flag = true;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        flag = false;
    }

    return flag;
}
bool unRegisterCourse(Student StudentArr[], int MAX_STUDENT, Course CourseStruct, Student StudentStruct)
{
    bool flag = false;
    for (int i = 0; i < MAX_STUDENT; i++)
    {
        if (StudentStruct.regNo == StudentArr[i].regNo)
        {
            for (int j = 0; j < MAX_STUDENT; j++)
            {
                if (CourseStruct.courseCode == StudentArr[i].courses[j].courseCode)
                {
                    StudentArr[i].courses[j].courseCode = {""};
                    flag = true;
                }
            }
        }
    }
    return flag;
}
bool saveStudents(Student StudentArr[], int MAX_STUDENT)
{
    bool flag;
    ofstream save;
    save.open("students.txt");
    if (save.is_open())
    {
        for (int i = 0; i < MAX_STUDENT; i++)
        {
            if (StudentArr[i].regNo != "")
            {
                save << StudentArr[i].regNo << "," << StudentArr[i].name << ",";
                for (int j = 0; j < MAX_STUDENT; j++)
                {
                    if (StudentArr[i].courses[j].courseCode != "")
                    {
                        if (j == 0)
                        {
                            save << StudentArr[i].courses[j].courseCode;
                        }
                        else
                        {
                            save << ":" << StudentArr[i].courses[j].courseCode;
                        }
                    }
                }
                save << endl;
            }
        }
        flag == true;
    }
    else
    {
        flag = false;
    }
    return flag;
}
bool loadStudents(Student StudentArr[],int MAX_STUDENT)
{
    bool flag;
    int i = 0;
    ifstream load;
    load.open("students.txt");
    if (!load.is_open())
    {
        flag = false;
    }
    else
    {
        string reg, name, course;
        string courses;
        string line;
        while (!load.eof() && i < MAX_STUDENT)
        {
            getline(load, line);
            if (line == "")
                continue;
            stringstream ss(line);
            getline(ss, reg, ',');
            StudentArr[i].regNo = reg;
            getline(ss, name, ',');
            StudentArr[i].name = name;
            getline(ss, course, '\n');
            courses = course;
            int size=course.length();
            int counter=0;
            for(int i=0;i<size;i++)
            {
                if(courses[i]=':')
                {
                counter=counter+1;
                }
            }
            stringstream mm(courses);
            for(int j=0;j<(counter+1);j++)
            {
              getline(mm, courses, ':');
              courses=StudentArr[i].courses[j].courseCode;
            }
            i++;
        }
        load.close();
        flag = true;
    }

    return flag;
}