#include <iostream>
#include <time.h>
#include "board.hpp"

using namespace std;

int main() {
	srand(time(NULL));// do generowania randomowych liczb
	//Board tablica(10,10,NORMAL); //actual generation of the board
	Board tablica(9, 7, DEBUG);// test
	tablica.revealField(8, 6);
	tablica.debugDisplay();

	cout <<"ile min otacza punkt 0,1= " <<tablica.countMines(0, 1) << endl;
		cout <<"ile min otacza punkt 8,2= " <<tablica.countMines(8, 2) << endl;
			cout <<"ile min otacza punkt 1, 2= " <<tablica.countMines(1, 2) << endl;
	         cout <<"ile min otacza punkt 7 ,6= " <<tablica.countMines(7, 6) << endl;


	return 0;
}