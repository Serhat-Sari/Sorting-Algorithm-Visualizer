#include<SFML/Graphics.hpp>
#include <unistd.h>
#include <time.h>
#include <iostream>

/* TODO 

1-) Implement rest of the sorting algorithms -- DONE --
2-) Instead of asking from the command line, take inputs from the window(how??)
3-) Use OOP ( reading design patterns rn, will do this later.)

*/

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(601, 600), "Sorting Algorithm Visualizer!");
vector<int> theVector;
unsigned int microsecond = 1000000;
bool sorted=false;

void dispSort(int index){

    window.clear();
    for(int i=0; i<theVector.size(); i++){
        RectangleShape block(Vector2f(4, theVector[i]));
        block.setPosition(i*4, 600-theVector[i]);
        if(i == index)
            block.setFillColor(Color(255,255,255));
        else if (sorted)
            block.setFillColor(Color(91,182,234));
        else
            block.setFillColor(Color(149,82,189));
        window.draw(block);
    }
    window.display();
}

int takeSize(){

    cout << "Please enter a number between 10 and 150 for the number of elements in the array: \n";
    int vectorSize;
    while(true){
        cin >> vectorSize;
        if(vectorSize >=10 && vectorSize <=199)
            return vectorSize;
        else{
            cout << "Please enter a valid number between the given ranges!\n";
            continue;
        }
    }
}

void takeAlgorithm(){

    cout << "Please press the corresponding number to select the sorting algorithm you want to be visualized: \n";
    cout << "1-) Bubble Sort\n";
    cout << "2-) Merge Sort\n";
    cout << "3-) Insertion Sort\n";
    cout << "4-) Selection Sort\n";
    cout << "5-) Gnome Sort\n";

}

void bubbleSort(){


    usleep(microsecond*0.75);
    int i;

    for(i = 0;i<theVector.size();i++){
        for(int j = 0; j<theVector.size()-i;j++){
            if(theVector[j] > theVector[j+1]){
                swap(theVector[j],theVector[j+1]);
            }
            usleep(microsecond*0.0001); // Delete here to speed up the process.
            dispSort(j);
        }
    }

    sorted = true;

    dispSort(i);

}

void insertionSort() {

    usleep(microsecond*0.75);
    int i,key,j;
    for(int i = 1 ; i<theVector.size();i++){
        key = theVector[i];
        j = i - 1;
        while(j>=0 && theVector[j] > key){
            theVector[j+1] = theVector[j];
            j--;
            dispSort(j);
            usleep(microsecond*0.005); // Delete here to speed up the process.
        }
        theVector[j+1] = key;
    }
    sorted = true;
    dispSort(i);
}

void merge(int p, int q, int r){

    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1), M(n2);

    for (int i = 0; i < n1; i++)
        L[i] = theVector[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = theVector[q + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            theVector[k] = L[i];
        i++;
        } 
        else {
            theVector[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        theVector[k] = L[i];
        i++;
        k++;
        dispSort(k);
    }

    while (j < n2) {
        theVector[k] = M[j];
        j++;
        k++;
        dispSort(k);
    }

}

void mergeSort(int l,int r){    

    usleep(microsecond*0.001);
    if(l < r){
        int m = l + (r-l) / 2;
        mergeSort(l,m);
        mergeSort(m+1,r);
        merge(l,m,r);
    }
    sorted = true;
    dispSort(r);
}

void selectionSort(){

    usleep(microsecond*0.75);
    int i,j,minx;
    for(int i = 0 ; i<theVector.size()-1;i++){
        minx = i;
        for(int j = i+1; j<theVector.size();j++){
            if(theVector[j] < theVector[minx])
                minx = j;
                dispSort(j);
               //usleep(microsecond*0.005); // Delete here to speed up the process.
        }
        if(minx != i)
            swap(theVector[minx],theVector[i]);
    }
    sorted = true;
    dispSort(i);
}

void gnomeSort(){
    usleep(microsecond);
    int index = 0;
    while(index < theVector.size()){
        if(index == 0){
            index++;
            dispSort(index);}
        if(theVector[index] >= theVector[index-1]){
            index++;
            dispSort(index);}
        else{
            swap(theVector[index],theVector[index-1]);
            index--;
            dispSort(index);
        }
    }
    sorted = true;
    dispSort(index);
}

void algorithmSelector(){
    
    if(Keyboard::isKeyPressed(Keyboard::Num1))
        bubbleSort();
        
    else if(Keyboard::isKeyPressed(Keyboard::Num2))
        mergeSort(0,theVector.size()-1);

    else if(Keyboard::isKeyPressed(Keyboard::Num3))
        insertionSort();

    else if(Keyboard::isKeyPressed(Keyboard::Num4))
        selectionSort();

    else if(Keyboard::isKeyPressed(Keyboard::Num5))
        gnomeSort();
    
}

void fillArray(int Size){

    srand(time(NULL));
    for(int i = 0; i<Size;i++){
        int random = 1 + rand()%550;
        theVector.push_back(random);
    }
}

int main(){

    int Size = takeSize();
    fillArray(Size);
    takeAlgorithm();
    while(window.isOpen()){

        Event event;

        while (window.pollEvent(event))
            if(event.type == Event::Closed) window.close();    

        if(!sorted){
            dispSort(0);
            algorithmSelector();
        }

    }
    return 0;
}
