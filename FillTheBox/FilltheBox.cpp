/* In this C++ program, we will crete a space(shown with matrix) and fill 
   it with boxes with given parameters.
   Selen KUTANOGLU 
   November 2018*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

#define SPACE_H 10
#define SPACE_W 10
#define BOX_NUM 20

using namespace std;
int countOfBoxes = 0; //ERROR = 0;

static int matrix[SPACE_H][SPACE_W] = {0,0};
double     middleX[BOX_NUM] = {0};
double     middleY[BOX_NUM] = {0};
void printSpace();  //Prints on screen the space

class Coordinate {
    public:
        void setCoordinate();
        int  getX();
        int  getY();
    private:
        int  x_coordinate;
        int  y_coordinate;
};

class Box {
    public:
        Coordinate coordinateOfBox;
        void setParameters(int limitOfSize,int d);
        int getH();
        int getW();
        int getD();
    private:
        int height;
        int width;
        int density;
};

class Space{
    public:
        void fillRandomBox(int num_of_box,int max_size_of_box,int density_of_box);
        void addMatrix(Box* boxObj);
        bool checkMatrix(Box* obj);
        void calculateCenter();
    private:
        Box boxOfSpace[BOX_NUM];
        double centerOfMassX;
        double centerOfMassY;
};

int main(){
    srand(time(NULL));
    cout << "Space (" << SPACE_H << "," << SPACE_W << ") is created." << endl << endl;
    
    
    printSpace(); 
    Space object1;
    object1.fillRandomBox(9,5,1);   //Fill the space with random boxes
    printSpace();

    cout << endl << "Number of box added : " << countOfBoxes;
    object1.calculateCenter();

    for(int i=0;middleX[i]!=0;i++){
        cout << endl << middleX[i] << " - " << middleY[i];
    }

    return 0;
}

void printSpace(){
    for(int i=0;i<SPACE_H;i++){             
        for(int j=0;j<SPACE_W;j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

void Coordinate::setCoordinate(){
    this->x_coordinate = (rand()%SPACE_W);
    this->y_coordinate = (rand()%SPACE_H);
};

int Coordinate::getX(){
    return this->x_coordinate;
};

int Coordinate::getY(){
    return this->y_coordinate;
};

void Box::setParameters(int limitOfSize,int d){
    this->height  = (rand()%limitOfSize)+1;
    this->width   = (rand()%limitOfSize)+1;
    this->density = d;
    this->coordinateOfBox.setCoordinate();
};

int Box::getH(){
    return this->height;
};

int Box::getW(){
    return this->width;
};

int Box::getD(){
    return this->density;
};

void Space::fillRandomBox(int num_of_box,int max_size_of_box,int density_of_box){
    for(int i=0;i<num_of_box;i++){
        this->boxOfSpace[i].setParameters(max_size_of_box,density_of_box);
        
        cout << endl << i+1 << ". box width: " << this->boxOfSpace[i].getW() 
        << "  height: " << this->boxOfSpace[i].getH() << " to (" 
        << this->boxOfSpace[i].coordinateOfBox.getX()+1 << "," 
        << this->boxOfSpace[i].coordinateOfBox.getY()+1 << ")" << endl;
        
        Box* boxObj = &this->boxOfSpace[i];
        
        if(checkMatrix(boxObj)){
            middleX[i] = ((double)this->boxOfSpace[i].coordinateOfBox.getX()) + (((double)this->boxOfSpace[i].getW()+1.0)/2.0) +0.5;
            middleY[i] = ((double)this->boxOfSpace[i].coordinateOfBox.getY() + (double)((double)this->boxOfSpace[i].getH()+1)/2) +0.5;
            addMatrix(boxObj);
            cout << endl << i+1 << ". Box added on space" << endl;
        }
        else
            cout << endl << i+1 << ". Box can not added\t X" << endl;
    }
};

void Space::addMatrix(Box* boxObj){
    for(int i = 0; i<boxObj->getH(); i++){
        for(int j=0; j<boxObj->getW(); j++)
            matrix[(boxObj->coordinateOfBox.getY())+i][(boxObj->coordinateOfBox.getX())+j] = (countOfBoxes+1);
    }
    countOfBoxes++;
};

bool Space::checkMatrix(Box* obj){
    int full = 1;
    for(int i = 0; i<obj->getH(); i++){
        for(int j=0; j<obj->getW(); j++){
            if(matrix[(obj->coordinateOfBox.getY())+i][(obj->coordinateOfBox.getX())+j] != 0)//Incase full
                full = 0;
            else if(obj->coordinateOfBox.getY()+i > SPACE_H-1 || obj->coordinateOfBox.getX()+j > SPACE_W-1)//Incase out of space
                full = 0;
        }
    }
    return full;
};

void Space::calculateCenter(){ //Calculates center of gravity of the space
    int i;
    for(i=0 ;middleX[i]!=0 && middleY[i]!=0;i++){
        middleX[0]+=middleX[i+1];
        middleY[0]+=middleY[i+1];
    }
    
    i--;
    
    this->centerOfMassX = middleX[0]/countOfBoxes;
    this->centerOfMassY = middleY[0]/countOfBoxes;
    
    cout << endl << "Center of mass : " << this->centerOfMassX << "," << this->centerOfMassY;
};