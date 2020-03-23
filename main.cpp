
#include <iostream>
#include <ctime>
#include "Board.h"
#include "MSBoardTextView.h"
using namespace std;

int main() {
    srand(time(NULL));// do generowania randomowych liczb
    Board tablica(10,10,NORMAL); //actual generation of the board
    //Board tablica(9, 7, DEBUG);// test
    MSBoardTextView view ( tablica);


    view.display();
    tablica.revealField(5,3);
    tablica.toggleFlag(3,6);
    view.display();
    tablica.revealField(0,3);
    view.display();
    tablica.revealField(9,6);
    view.display();
    cout<<tablica.isInside(100,100);
    return 0;
}