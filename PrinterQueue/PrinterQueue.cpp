/* In this C++ program, we will make a fake printer queue and show which process
    is running now with printing information about the document on the screen 
    Selen KUTANOGLU
    December 2018 */

#include <iostream>                          //For use i/o functions
#include <cstring>                           //For use string datatype
#include <fstream>                           //For use file methods
#include <unistd.h>                          //For use sleep function in linux 
//#include <Windows.h> //Sleep(x*1000);      //For use sleep function in Windows
#include <sstream>                           //For use stringstream type
#define LIMIT 3

using namespace std;

int counter = 0,readSpeed = 0,printSpeed = 0,currentTime = 0; 
/* counter will count the document(s) of the printerList - currentTime will
count the exact time - readSpeed will sleep the print func to take data - 
printSpeed will represent in number of paper get print (per minute) */

struct Owner{                                 /* User infos */
    string name;
    string surname;
    string username;
    string email;
    string dateOfBirth;
};

struct Date{                                  /* Document insertion date struct */
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

struct Document{                              /* File will be printed */
    string fileName = " ";                    //I use assingment as checking if its full or empty
    string Dsize;                             //Document size
    int numberOfPages;                        //It will keep number of pages document has (NEVER CHANGED!!)
    int paperLast;                            //Will keep how many pages left to print (In every print func called it will decrement)
    Date insertionDate;                       //Date struct as a member
    Owner owner;                              //Owner as a member
}static printerList[LIMIT];                   //static struct list

Document * readPtr  = printerList;            //Assign it to the first document file
Document * writePtr = printerList;            //Assign it to the first document file

bool isEmpty();                               //Checks if its empty
void assignData(string& data);                //Assigns the data to the struct
void addIt(string& info);                     //Adds the document to the array
void deleteIt();                              //Deletes the struct from the array
void printIt();                               //Prints the struct from the array
void startPrint();                            //Printer process

int main(){
    cout << "Enter the read speed of the printer : " ;
    cin  >> readSpeed ;
    cout << endl << "Enter the printing speed of a page : ";
    cin  >> printSpeed;
    startPrint();    //Process called
    return 0;
}

void startPrint(){                                              /* The MAIN function to starts to Virtual Printer :) */
    fstream filePrint;                                                            //Create filePrint for file
    filePrint.open("print.txt", ios::in|ios::out|ios::app);                       //Open file for read write and create if its uncreated
    string info;                                                                  //Declare a string to assign the line from txt file

    while(!filePrint.eof()){                                                      //Will run till end of the file
        if (currentTime % readSpeed == 0){                                        //In every readSpeed seconds it will try to read file and add it on the list
            if(writePtr->fileName == " "){                                        //Check if there is any space to add document
                getline(filePrint,info);                                          //Gets the line from the file
                if(!filePrint.eof())                                              //Incase its not end of the file
                addIt(info);                                                      //Adding ...
            }
            else if (writePtr->fileName != " "){                                  //Reason of using else if is that to we blocked it to get in this if too
            cout << endl << currentTime <<  "s List is full at that moment \t\t --X--" << endl;
            }
        }

        if(currentTime % printSpeed == 0){                                         //In every printSpeed seconds it will run this part
            if (readPtr->fileName != " ")                                          //If there is document to print
            printIt();                                                             //Printing ...
            else                                                                   //Incase there is no docs in the list and process is not finished :(
            cout << endl << currentTime << "s list is empty. Waiting for inputs  \t_-_-_" << endl ;
        }
        currentTime++;                                                             //Current time must be increment :)
        sleep(1);                                                                  //For simulate it as a real process
    }

    while(!isEmpty()){                                                             //After first while loop if there is some pages and/or files it will run this part
        printIt();                                                                 //Printing ...
        currentTime++;                                                             //Current time must be increment :)
        sleep(1);                                                                  //For simulate it as a real process
    }
    printIt();                                                                     //Printing ...
}

bool isEmpty(){                                                 /* Check if its empty and returns bool */
    return (writePtr->fileName == " " && readPtr->fileName == " ");
}

void assignData(string & data){                                 /* Assigns all datas to the struct which reading */
    stringstream tempString;                                    //Define a stringstream type string for read from it word by word
    tempString << data;
    tempString >> writePtr->fileName;
    tempString >> writePtr->Dsize;
    tempString >> writePtr->numberOfPages;
    writePtr->paperLast = writePtr->numberOfPages;
    tempString >> writePtr->owner.name;
    tempString >> writePtr->owner.surname;
    tempString >> writePtr->owner.username;
    tempString >> writePtr->owner.email;
    tempString >> writePtr->owner.dateOfBirth;
    tempString >> writePtr->insertionDate.second;
    tempString >> writePtr->insertionDate.minute;
    tempString >> writePtr->insertionDate.hour;
    tempString >> writePtr->insertionDate.day;
    tempString >> writePtr->insertionDate.month;
    tempString >> writePtr->insertionDate.year;
}

void addIt(string & data){                                      /* Add the struct in the list */
        assignData(data);                                        //Assign all datas to the struct
        cout << endl << currentTime << "s ---> " << writePtr->fileName << " is added on the queue." << endl;
        counter++;                                               //In each adding process we increment counter
        if(writePtr == &printerList[LIMIT-1])                    //Incase its points the last struct of the list
            writePtr = &printerList[0];                         //Return it to the first struct of the list
        else
            writePtr++;                                         //Otherwise it will point the next struct
}

void deleteIt(){                                                /* Deletes the document from the list */
        readPtr->fileName = " ";                                //Assign it as the empty
        if(readPtr == &printerList[LIMIT-1])                    //Incase its point to the last value of array
            readPtr = &printerList[0];                          //It will point the first value then
        else                                                    //Exclude last value
            readPtr++;                                          //Will point the next value
        counter--;                                              //It will decrement the number of document on list
}

void printIt(){                                                 /* Prints only one paper of the document in each called */
    if(readPtr->fileName == " ")                                //Process finished and list queue is empty
        cout << endl << currentTime << "s Empty printer queue. \n\n----- Process completed ! -----" << endl;
    else{
        if(readPtr->paperLast > 0){                             //Incase there are pages to print
            cout << endl << currentTime << "s " << readPtr->fileName << " of " << readPtr->owner.name << " is printing ...\t( " << readPtr->paperLast << " pages )" << endl;
            readPtr->paperLast--;                               //decrement number of pages will be printed
            return;                                             //Incase the last page printed it will continue to run next if.I use it for time saving(It wont check the next if even its false)
        }
        if (readPtr->paperLast == 0){                           //Printing is finished
            cout << endl << currentTime << "s " << readPtr->fileName << " took " << readPtr->numberOfPages*printSpeed << " s\t\t\t --F--" << endl;    //Prints the time it took
            deleteIt();                                         //Deleting ...
        }
    }
}
