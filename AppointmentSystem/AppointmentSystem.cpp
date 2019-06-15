    #include <iostream>                  //To use I/O functions
    #include <cstring>                   //To use string data type
    #include <fstream>                   //To use file methods
    #include <sstream>                   //To use string stream
    #include <stdlib.h>                  //to use system("CLS");
    #include <windows.h>                 //to use sleep();
    #define S_LIMIT 20                   //Stands for limit number of students
    #define L_LIMIT 10                   //Stands for limit number of lecturers
    #define A_LIMIT 50                   //Stands for limit number of appointments

    using namespace std;
    class Human{
        public:
            Human();
            int    getID();
            string getFirstName();
            string getLastName();
            string getDepartment();
            string getEmail();
            string getPhone();

        protected:
            int    idNumber;
            string FirstName;
            string LastName;
            string department;
            string email;
            string phone;
    }
    class Student:public Human{
        public:
            Student();
            void   setParameters(string data);
            int    getsUniversityStart();
        private:
            int    universityStart;
           
    }static listOfStudents[S_LIMIT];    //All students will keep in this class array by limited with S_LIMIT

    class Lecturer{
        public:
            Lecturer();
            void   setParameters(string data);
            string getAcademicChair();

        private:
            string academicChair;
    }static listOfLecturers[L_LIMIT];   //All lecturers will keep in this class array by limited with L_LIMIT

    class Appointment{
        public:
            Appointment();
            void   setParameters(string data);
            int    getLecturerID();
            int    getsStudentID();
            string getDate();
            int    getTime();
            Student student;
            Lecturer Lecturer;
        private:
            int    lecturerID;
            int    studentID;
            string date;
            int    time;

    }static listOfAppointments[A_LIMIT];    //All appointments will keep in this class array by limited with A_LIMIT

    /*  Student Global Pointer and Functions */
    Student * stdPtr = listOfStudents;      // Points to the first student of the list
    void addStudentFromFile();              // Adds student to list from text file
    void addStudentManuel();                // Adds student from console
    void addStudentToFile(int tempValue);   // Adds students from list to file (which not added before)
    int  studentListCheck(int sId);         // Checks for studentId match on the student list
    int  studentFileCheck(int sId);         // Checks for studentId match on the student text file
    void printStudentInfo();                // Prints the studentId, firstName and lastName of the all students on list to the screen
    void updateStudent();                   // Adds the student from list to text file (which not added before)

    /* Lecturer Global Pointer and Functions */
    Lecturer * lctPtr = listOfLecturers;    // Points to the first lecturer of the list
    void addLecturerFromFile();             // Adds lecturer to list from text file
    void addLecturerManuel();               // Adds lecturer from console
    void addLecturerToFile(int tempValue);  // Adds lecturer from list to file (which not added before)
    int  lecturerListCheck(int lId);        // Checks for lecturerId match on the lecturer list
    int  lecturerFileCheck(int lId);        // Checks for lecturerId match on the lecturer text file
    void printLecturerInfo();               // Prints the lecturerId, firstName and lastName of the all lecturers on list to the screen
    void updateLecturer();                  // Adds the lecturer from list to text file (which not added before)

    /* Appointment Global Pointer and Functions */
    Appointment * appPtr = listOfAppointments;
    void addAppointmentFromFile();                 // Adds appointment to list from text file
    void addAppointmentManuel();                   // Adds appointment from console
    void addAppointmentToFile(int tempValue);      // Adds appointment from list to file (which not added before)
    int  appointmentListCheck(int,int,string,int); // Checks for appointmentID match on the appointment list
    int  appointmentFileCheck(int,int,string,int);            // Checks for appointmentID match on the appointment text file
    void printAppointmentInfo();                   // Prints the appointmentID, studentID and lecturerID of the all appointments on list to the screen
    void updateAppointment();                      // Adds the appointment from list to text file (which not added before)

    void ApplicationStart();/**---------MAIN FUNTION---------**/

    /* *********************************************************    MAIN     ********************************************************************* */
    int main(){

        ApplicationStart(); //Menu application function called

        return 0;
    }


    /************************ STUDENT PART *************************/
    Student::Student(){
        this->studentId = 0;
    }

    void Student::setParameters(string data){
        stringstream tempString;
        int          tempInt;

        tempString << data;
        tempString >> tempInt;

        if(tempInt > 0 && !studentListCheck(tempInt))
            this->studentId = tempInt;
        else{
            cout << "\nStudent can not added due to student ID";
            return;
        }

        tempString >> this->sFirstName;
        tempString >> this->sLastName;
        tempString >> this->department;

        tempString >> tempInt;
        if(tempInt > 0)
            this->universityStart = tempInt;
        else{
            cout << "\n\n Student can not added due to "
            << "university start date \n\n";
            return;
        }

        tempString >> this->studentEmail;
        tempString >> this->sPhone;

        cout << "\nStudent added.";
        stdPtr++;
    }

    /******** GET ********/
    int    Student::getStudentID(){
        return this->studentId;
    }

    string Student::getsFirstName(){
        return this->sFirstName;
    }

    string Student::getsLastName(){
        return this->sLastName;
    }

    string Student::getsDepartment(){
        return this->department;
    }

    int    Student::getsUniversityStart(){
        return this->universityStart;
    }

    string Student::getsStudentEmail(){
        return this->studentEmail;
    }

    string Student::getsPhone(){
        return this->sPhone;
    }

    /****** GLOBAL *******/
    void addStudentFromFile(){
         fstream fStudent;
         string  info;

         cout << "\n------------------------------------\n"
         << "    Student adding from file ...\n";

         fStudent.open("student.txt", ios::in|ios::out|ios::app);

         while(!fStudent.eof()){                    //Will run till end of file
                getline(fStudent,info);             //Read a line and assigns it to the info
                if(info != "")                      //In case it is not a null
                    stdPtr->setParameters(info);    //Sends the parameter to add it on the current position of the student list
         }

         fStudent.close();

         cout << "\n\n    Student adding finished."
         << "\n------------------------------------\n";
    }

    void addStudentManuel(){
        stringstream userInfo;
        string       tempString;
        int          tempInt,request = 0;

        cout << "\n************************************************"
        << "\n\tWelcome to Student adding page!";

        cout << "\nEnter the ID of the student: ";
        cin >> tempInt;

        if(tempInt < 1){                                                    //In case is less than 1 it will be invalid
            cout <<"\nEntered invalid ID.Please enter 1 to try again.";     //Asking for request
            cin  >> request;
            if(request == 1){                                               //If there is ...
                cout << "\nRequest accepted...";
                Sleep(1000);                                                //Sleeps console for 1 second :)
                system("CLS");
                addStudentManuel();                                         //Call this function from beginning
                return;
            }
            else{
                cout << "\nStudent add cancelled by user.";                 //Otherwise it will exit from this function
                return;
            }
        }
        else{
            userInfo << tempInt;                                            //If all requirements are ok ...
        }


        /* Other info */
        cout << "\nEnter the first name of the student: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\nEnter the last name of the student: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\nEnter the department of the student: ";
        cin >> tempString;
        userInfo << " " << tempString;


        /* University start year must be greater than 2000 */
        cout << "\nEnter the university start year of the student: ";
        cin >> tempInt;

        if(tempInt < 2000){                                                 //In case is less than 2000 and  it will be invalid :)
            cout <<"\nEntered invalid year.Please enter 1 to try again.";   //Asking for request
            cin  >> request;
            if(request == 1){                                               //If there is ...
                cout << "\nRequest accepted...";
                Sleep(1000);                                                //Sleeps console for 1 second :)
                system("CLS");
                addStudentManuel();                                         //Call this function from beginning
                return;
            }
            else{
                cout << "\nStudent add cancelled by user.";                 //Otherwise it will exit from this function
                return;
            }
        }
        else{
            userInfo << " " << tempInt;                                  //If all requirements are ok ...
        }


        /* Other info */
        cout << "\nEnter the e-mail of the student: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\nEnter the phone number of the student: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\t\tAdding student...\n";
        tempString = userInfo.str();                                        //Assigns all stringstream  to the tempString
        stdPtr->setParameters(tempString);                                  //Calls the current students setter function

        cout << "\n************************************************\n";
    }

    void addStudentToFile(int tempValue){
        fstream fStudent;
        fStudent.open("student.txt", ios::in|ios::out|ios::app);

        fStudent << endl << listOfStudents[tempValue].getStudentID()
        << " " << listOfStudents[tempValue].getsFirstName() << " "
        << listOfStudents[tempValue].getsLastName() << " "
        << listOfStudents[tempValue].getsDepartment() << " "
        << listOfStudents[tempValue].getsUniversityStart() << " "
        << listOfStudents[tempValue].getsStudentEmail() << " "
        << listOfStudents[tempValue].getsPhone();

        cout << "\nStudent ADDED ON FILE";
        fStudent.close();
    }

    int  studentListCheck(int sId){
        int checkInt = 0;

        while(&listOfStudents[checkInt] != stdPtr ){            // Will run till the last student of the list (NOT END OF THE LIST)
            if(listOfStudents[checkInt].getStudentID() == sId)
                return 1;
            checkInt++;
        }
        return 0;
    }

    int  studentFileCheck(int sId){
        fstream fStudent;
        string  checkString;
        int     checkInt;

        fStudent.open("student.txt",ios::in|ios::out|ios::app);

        while(!fStudent.eof()){
            stringstream temporaryString;

            getline(fStudent,checkString);  //Gets the line
            temporaryString << checkString; //Puts the string into the temporaryString

            temporaryString >> checkInt;    //Pulls first word from line
            if(checkInt == sId){            //Equal case
                fStudent.close();
                return 1;
            }
        }

        fStudent.close();
        return 0;
    }

    void printStudentInfo(){
        int tempValue = 0;

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "\tStudent List Printing ...\n";

        while(&listOfStudents[tempValue]!=stdPtr){            // Will run till the last student of the list (NOT END OF THE LIST)
            cout << endl << tempValue + 1 << ".Student: "
            << listOfStudents[tempValue].getStudentID() << " - "
            << listOfStudents[tempValue].getsFirstName() << " "
            << listOfStudents[tempValue].getsLastName() << endl;

            tempValue++;
        };

        cout << "\n       All students are printed.\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

    void updateStudent(){
        int tempValue = 0, numberOfStudent = 0;

        cout << "\n*****************************\n"
        << "       Student Update\n";

        while(&listOfStudents[tempValue] != stdPtr){            // Will run till the last student of the list (NOT END OF THE LIST)
            if(!studentFileCheck(listOfStudents[tempValue].getStudentID())){
                addStudentToFile(tempValue);
                numberOfStudent++;
            }
            tempValue++;
        }

        cout << endl << "    " << numberOfStudent
        << " student(s) updated.\n*****************************\n";
    }


    /************************ LECTURER PART *************************/
    Lecturer::Lecturer(){
        this->lecturerId = 0;
    }

    void Lecturer::setParameters(string data){
        stringstream tempString;
        int          tempInt;

        tempString << data;
        tempString >> tempInt;

        if(tempInt > 0 && !lecturerListCheck(tempInt))  //Checks if there is any lecturer with same ID
            this->lecturerId = tempInt;
        else{
            cout << "\nLecturer can not added due to lecturer ID";
            return;
        }

        tempString >> this->lFirstName;
        tempString >> this->lLastName;
        tempString >> this->lDepartment;
        tempString >> this->lEmail;
        tempString >> this->lPhone;
        tempString >> this->academicChair;

        cout << "\nLecturer added.";
        lctPtr++;
    }

    /******** GET ********/
    int    Lecturer::getLecturerId(){
        return this->lecturerId;
    }

    string Lecturer::getlFirstName(){
        return this->lFirstName;
    }

    string Lecturer::getlLastName(){
        return this->lLastName;
    }

    string Lecturer::getlDepartment(){
        return this->lDepartment;
    }

    string Lecturer::getlEmail(){
        return this->lEmail;
    }

    string Lecturer::getlPhone(){
        return this->lPhone;
    }

    string Lecturer::getAcademicChair(){
        return this->academicChair;
    }

    /****** GLOBAL *******/
    void addLecturerFromFile(){
        fstream fLecturer;
        string  info;

        cout << "\n------------------------------------\n"
        << "    Lecturer adding from file ...\n";

        fLecturer.open("lecturer.txt", ios::in|ios::out|ios::app);

        while(!fLecturer.eof()){
            getline(fLecturer,info);
            if(info != "")
                lctPtr->setParameters(info);
        }

        fLecturer.close();

        cout << "\n\n    Lecturer adding finished."
        << "\n------------------------------------\n";
    }

    void addLecturerManuel(){
        stringstream userInfo;
        string       tempString;
        int          lTempInt,request = 0;

        cout << "\n************************************************"
        << "\n\tWelcome to Lecturer adding page!";


        cout << "\nEnter the ID of the lecturer: ";
        cin >> lTempInt;
        if(lTempInt < 1){                                                   //In case is less than 1 it will be invalid
            cout <<"\nEntered invalid ID.Please enter 1 to try again.";     //Asking for request
            cin  >> request;
            if(request == 1){                                               //If there is ...
                cout << "\nRequest accepted...";
                Sleep(1000);                                                //Sleeps console for 1 second :)
                system("CLS");
                addStudentManuel();                                         //Call this function from beginning
                return;
            }
            else{
                cout << "\nStudent add cancelled by user.";                 //Otherwise it will exit from this function
                return;
            }
        }
        else{
            userInfo << lTempInt;                                           //If all requirements are ok ...
        }

        /* Other info */
        cout << "\nEnter the first name of the lecturer: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\nEnter the last name of the lecturer: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\nEnter the department of the lecturer: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\nEnter the e-mail of the lecturer: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\nEnter the phone number of the lecturer: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\nEnter the academic chair of the lecturer: ";
        cin >> tempString;
        userInfo << " " << tempString;

        cout << "\n************************************************\n"
        << "\t\tAdding lecturer ...\n";

        tempString = userInfo.str();                                       //Assigns all stringstream  to the tempString
        lctPtr->setParameters(tempString);                                 //Calls the current lecturers setter function
    }

    void addLecturerToFile(int tempValue){
        fstream fLecturer;

        fLecturer.open("lecturer.txt", ios::in|ios::out|ios::app);

        fLecturer << endl << listOfLecturers[tempValue].getLecturerId()
        << " " << listOfLecturers[tempValue].getlFirstName() << " "
        << listOfLecturers[tempValue].getlLastName() << " "
        << listOfLecturers[tempValue].getlDepartment() << " "
        << listOfLecturers[tempValue].getlEmail() << " "
        << listOfLecturers[tempValue].getlPhone() << " "
        << listOfLecturers[tempValue].getAcademicChair();

        fLecturer.close();

        cout << "\nLecturer ADDED ON FILE";
    }

    int  lecturerListCheck(int lId){
        int checkInt = 0;

        while(&listOfLecturers[checkInt] != lctPtr ){            // Will run till the last lecturer of the list (NOT END OF THE LIST)
            if(listOfLecturers[checkInt].getLecturerId() == lId)
                return 1;
            checkInt++;
        }
        return 0;
    }

    int  lecturerFileCheck(int lId){
        fstream fLecturer;
        string  checkString;
        int     checkInt;

        fLecturer.open("lecturer.txt",ios::in|ios::out|ios::app);

        while(!fLecturer.eof()){
            stringstream temporaryString;

            getline(fLecturer,checkString); //Gets the line
            temporaryString << checkString; //Puts the string into the temporaryString

            temporaryString >> checkInt;    //Pulls first word from line
            if(checkInt == lId){            //Equal case
                fLecturer.close();
                return 1;
            }
        }

        fLecturer.close();

        return 0;
    }

    void printLecturerInfo(){
        int tempValue = 0;

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "\tLecturer List Printing ...\n";

        while(&listOfLecturers[tempValue]!=lctPtr){
            cout << endl << tempValue + 1 << ".Lecturer: "
            << listOfLecturers[tempValue].getLecturerId() << " - "
            << listOfLecturers[tempValue].getlFirstName() << " "
            << listOfLecturers[tempValue].getlLastName()  << endl;

            tempValue++;
        };

        cout << "\n      All lecturers are printed.\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    }

    void updateLecturer(){
        int tempValue = 0, numberOfLecturer = 0;

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "       Lecturer Update\n";

        while(&listOfLecturers[tempValue] != lctPtr){

            if(!lecturerFileCheck(listOfLecturers[tempValue].getLecturerId())){
                addLecturerToFile(tempValue);
                numberOfLecturer++;
            }
            tempValue++;
        }

        cout << endl << "    " << numberOfLecturer
        << " lecturer(s) updated.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }


    /*********************** APPOINTMENT PART ************************/
    Appointment::Appointment(){
        this->studentID  = 0;
        this->lecturerID = 0;
        this->date       = "";
        this->time       = 0;
    }

    void   Appointment::setParameters(string data){
        stringstream tempString;
        string       tempDate;
        int          tempInt,tempInt2,tempTime;

        tempString << data;         //Insert the data into the tempString
        tempString >> tempInt;      //Student ID
        tempString >> tempInt2;     //Lecturer ID
        tempString >> tempDate;     //Date
        tempString >> tempTime;     //Time as hour

        if(tempInt < 1 || !studentListCheck(tempInt)){ //Checks if there any student on system with given ID
            cout << "\nAppointment can not accepted due to invalid student ID";
            //return;
        }

        if(tempInt2 < 1 || !lecturerListCheck(tempInt2)){//Checks if there any lecturer on system with given ID
            cout << "\nAppointment can not accepted due to invalid lecturer ID";
            return;
        }

        if(tempTime < 8 || tempTime > 17 || tempTime == 12){
            cout <<"\nAppointment can not accepted due to invalid time";
            return;
        }

        if(!appointmentListCheck(tempInt,tempInt2,tempDate,tempTime)){//Checks is there any same appointment
            this->studentID  = tempInt;
            this->lecturerID = tempInt2;
            this->date       = tempDate;
            this->time       = tempTime;
            cout << "\nAppointment added.";
            appPtr++;
        }
        else{
            cout << "\nAppointment can not added.";
            return;
        }

    }

    /******** GET ********/
    int    Appointment::getLecturerID(){
        return this->lecturerID;
    }

    int    Appointment::getsStudentID(){
        return this->studentID;
    }

    string Appointment::getDate(){
        return this->date;
    }

    int    Appointment::getTime(){
        return this->time;
    }

    /****** GLOBAL *******/
    void addAppointmentFromFile(){
        fstream fAppointment;
        string  info;

        cout << "\n------------------------------------\n"
        << "    Appointment adding from file ...\n";

        fAppointment.open("appointment.txt", ios::in|ios::out|ios::app);

        while(!fAppointment.eof()){
            getline(fAppointment,info);
            if(info != "")
                appPtr->setParameters(info);
        }

        fAppointment.close();

        cout << "\n\n    Appointment adding finished."
        << "\n------------------------------------\n";
    }

    void addAppointmentManuel(){
        stringstream userInfo;
        string       tempString;
        int          aTempInt,request = 0;

        cout << "\n************************************************"
        << "\n\tWelcome to Appointment booking page!";

        cout << "\nEnter the ID of the student: ";
        cin  >> aTempInt;
        userInfo << aTempInt << " ";

        cout << "\nEnter the ID of the lecturer: ";
        cin  >> aTempInt;
        userInfo << aTempInt;

        /*      Taking day from user    */
        cout << "\nEnter the day of the appointment: ";
        cin  >> aTempInt;
        if(aTempInt < 1 || aTempInt > 31){
            cout <<"\nEntered invalid day.Please enter 1 to try again.";
            cin  >> request;
            if(request == 1){
                cout << "\nRequest accepted...";
                Sleep(1000);
                system("CLS");
                addAppointmentManuel();
                return;
            }
            else{
                cout << "\nAppointment cancelled by user.";
                return;
            }
        }
        else{
            userInfo << " " << aTempInt;
        }

        /*      Taking month from user    */
        cout << "\nEnter the month of the appointment: ";
        cin  >> aTempInt;
        if(aTempInt < 1 || aTempInt > 12){
            cout <<"\nEntered invalid month.Please enter 1 to try again.";
            cin  >> request;
            if(request == 1){
                cout << "\nRequest accepted...";
                Sleep(1000);
                system("CLS");
                addAppointmentManuel();
                return;
            }
            else{
                cout << "\nAppointment cancelled by user.";
                return;
            }
        }
        else{
            userInfo <<"/"<< aTempInt;
        }

        /*      Taking year from user    */
        cout << "\nEnter the year of the appointment(Only 2019 excepted for now): ";
        cin  >>aTempInt;
        if(aTempInt != 2019){
            cout <<"\nEntered invalid year.Please enter 1 to try again.";
            cin  >> request;
            if(request == 1){
                cout << "\nRequest accepted...";
                system("CLS");
                addAppointmentManuel();
                return;
            }
            else{
                cout << "\nAppointment cancelled by user.";
                return;
            }
        }
        else{
            userInfo <<"/"<< aTempInt;
        }

        /*      Taking hour from user    */
        cout << "\nEnter the hour of the appointment(for 2pm enter 14): ";
        cin  >> aTempInt;
        if(aTempInt > 17 || aTempInt < 8 || aTempInt ==12){
            cout <<"\nEntered invalid hour.Please enter 1 to try again.";
            cin  >> request;
            if(request == 1){
                cout << "\nRequest accepted...";
                system("CLS");
                addAppointmentManuel();
                return;
            }
            else{
                cout << "\nAppointment cancelled by user.";
                return;
            }
        }
        else{
            userInfo <<" "<< aTempInt;
        }

        cout << "\t\tBooking ...\n";
        tempString = userInfo.str();
        appPtr->setParameters(tempString);

        cout << "\n************************************************\n";
    }

    void addAppointmentToFile(int tempValue){
        fstream fAppointment;
        int     tempSID,tempLID,tempTIME;
        string  tempDATE;

        tempSID  = listOfAppointments[tempValue].getsStudentID();
        tempLID  = listOfAppointments[tempValue].getLecturerID();
        tempDATE = listOfAppointments[tempValue].getDate();
        tempTIME = listOfAppointments[tempValue].getTime();

        fAppointment.open("appointment.txt", ios::in|ios::out|ios::app);

        if(!appointmentFileCheck(tempSID,tempLID,tempDATE,tempTIME)){
            fAppointment << endl << tempSID << " " << tempLID << " "
            << tempDATE << " " << tempTIME;
            cout << "\nAppointment ADDED ON FILE";
        }
        else{
            cout << "\nAppointment NOT ADDED ON FILE (ALREADY EXIST)";
        }

        fAppointment.close();
    }

    int  appointmentListCheck(int sID, int lID, string date, int time){
        int checkInt = 0;

        while(&listOfAppointments[checkInt] != appPtr ){                // Will run till the last appointment of the list (NOT END OF THE LIST

            if(listOfAppointments[checkInt].getsStudentID() == sID &&   //Checks is there any same appointment
               listOfAppointments[checkInt].getLecturerID() == lID &&
               listOfAppointments[checkInt].getDate() == date &&
               listOfAppointments[checkInt].getTime() == time){
                cout << "\nAppointment already exist.\n";
                return 1;
            }

            if(listOfAppointments[checkInt].getsStudentID() == sID &&   //Checks is there any appointment withs same student at the same time
               listOfAppointments[checkInt].getDate() == date &&
               listOfAppointments[checkInt].getTime() == time){
                cout << "\nStudent has an appointment at given time.\n";
                return 1;
            }

            if(listOfAppointments[checkInt].getLecturerID() == lID &&   //Checks is there any appointment withs same lecturer at the same time
               listOfAppointments[checkInt].getDate() == date &&
               listOfAppointments[checkInt].getTime() == time){
                cout << "\nLecturer has an appointment at given time.\n";
                return 1;
            }

            checkInt++;
        }
        return 0;
    }

    int  appointmentFileCheck(int sID, int lID, string date, int time){
        fstream fAppointment;
        string  checkString,appDate;
        int     studentID,lecturerID,appTime;

        fAppointment.open("appointment.txt",ios::in|ios::out|ios::app);

        while(!fAppointment.eof()){
            stringstream temporaryString;

            getline(fAppointment,checkString);
            temporaryString << checkString;

            temporaryString >> studentID;
            temporaryString >> lecturerID;
            temporaryString >> appDate;
            temporaryString >> appTime;
            //cout << endl << studentID << lecturerID << appDate << appTime << endl;

            if(studentID == sID && lecturerID == lID && appDate == date && appTime == time){
                fAppointment.close();
                return 1;
            }
        }

        fAppointment.close();

        return 0;
    }

    void printAppointmentInfo(){
        int tempValue = 0;

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "\tAppointment List Printing ...\n";

        while(&listOfAppointments[tempValue] != appPtr){
            cout << endl << tempValue + 1 << ".Appointment: Student-"
            << listOfAppointments[tempValue].getsStudentID() << " Lecturer-"
            << listOfAppointments[tempValue].getLecturerID() << " Date-"
            << listOfAppointments[tempValue].getDate() << " Hour-"
            << listOfAppointments[tempValue].getTime() << endl;

            tempValue++;
        };

        cout << "\n      All appointments are printed.\n"
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

    void updateAppointment(){
        int    tempValue = 0, numberOfAppointment = 0;
        int    tempSID,tempLID,tempTIME;
        string tempDATE;

        cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
        << "   Appointment Update\n";

        while(&listOfAppointments[tempValue] != appPtr){
            tempSID  = listOfAppointments[tempValue].getsStudentID();
            tempLID  = listOfAppointments[tempValue].getLecturerID();
            tempDATE = listOfAppointments[tempValue].getDate();
            tempTIME = listOfAppointments[tempValue].getTime();

            if(!appointmentFileCheck(tempSID,tempLID,tempDATE,tempTIME)){
                addAppointmentToFile(tempValue);
                numberOfAppointment++;
            }
            tempValue++;
        }

        cout << endl << "    " << numberOfAppointment
        << " appointment(s) updated.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    }


    /********************** MAIN FUNCTION PART ***********************/
    void ApplicationStart(){

        int option=1;

        addStudentFromFile();
        Sleep(2000);
        system("CLS");
        addLecturerFromFile();
        Sleep(2000);
        system("CLS");
        addAppointmentFromFile();
        Sleep(2000);
        system("CLS");

        while(option!=0)
        {
            cout << "\n************************************************"
            << "\n\tAppointment System Main Menu\n\n"
            << "1.Student Add\n2.Lecturer Add\n"
            << "3.List all Students\n4.List all Lecturers\n"
            << "5.List all Appointments\n6.Book an Appointment\n(0 for exit)"
            << "\n\n************************************************\n";

            cout << "Choose any option: ";
            cin  >> option;

            switch (option){
                case 0:
                    cout << "\nExitting ...\n";
                    break;
                case 1:
                    system("CLS");
                    addStudentManuel();
                    updateStudent();
                    break;
                case 2:
                    system("CLS");
                    addLecturerManuel();
                    updateLecturer();
                    break;
                case 3:
                    system("CLS");
                    printStudentInfo();
                    break;
                case 4:
                    system("CLS");
                    printLecturerInfo();
                    break;
                case 5:
                    system("CLS");
                    printAppointmentInfo();
                    break;
                case 6:
                    system("CLS");
                    addAppointmentManuel();
                    updateAppointment();
                    break;
                default :
                    cout << "\nInvalid value entered.\n";
                    break;
            }
        }
        system("CLS");
        Sleep(2000);
        system("CLS");
    }
