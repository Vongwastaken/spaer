#include "board.hpp"

int Board::getBoardWidth() const
{
	return Board::width;
}
int Board::getBoardHeight()const
{
	return Board::height;
}





// generowanie planszy z minami
Board::Board(unsigned int w, unsigned int h, GameMode mode)
{
	this->width = w;
	this->height = h;
	double procent = 0;
	if (w > 100)
		w = 100;
	if (h > 100)
		h = 100;

	if (mode == EASY)
		procent = 0.1;
	else if (mode == NORMAL)
		procent = 0.2;

	else if (mode == HARD)
		procent = 0.3;

	//seting mines 
	for (unsigned int i = 0; i < ((h * w) * procent); i++) {
		//generate random numbers until you hit a field that has no mine
		while (true) {
			//chose random point on a board and check

			if (board[rand() % w][rand() % h].hasMine == false) {
				{
					board[rand() % w][rand() % h].hasMine = true;
				}
				break;
			}
		}
	}
	//test
	if (mode == DEBUG)
	{

		board[6][2].hasFlag = true;
		board[0][1].isRevealed = true;
		board[8][2].isRevealed = true;
		board[1][2].isRevealed = true;
		board[7][6].isRevealed = true;
		for (int i = 0; i < w; i++)
			for (int j = 0; j < h; j++)
			{
				if (j == 0)
					board[i][j].hasMine = true;
				if (i == j)
					board[i][j].hasMine = true;
				if (i == 0 && j % 2 == 0)
					board[i][j].hasMine = true;

			}

	}
}

//czy jest w planszy
bool Board::isInside(int x, int y) const
{
	if (x <= Board::getBoardWidth() && y <= Board::getBoardHeight() && x >= 0 && y >= 0)
		return true;
	else
		return false;
}
//czy pole jest odktyre
bool Board::isRevealed(int x, int y)const
{
	if (Board::board[x][y].isRevealed)
		return true;
	else
		return false;

}
//zlicz miny wokół pola
int Board::countMines(int x, int y) const
{
	int mines = 0;
	if (!isRevealed(x, y) || !isInside(x, y))
		return -1;
	else
		for (int i = 0; i <= 2; i++)
		{
			for (int j = 0; j <= 2; j++)
			{
				if (isInside(x - 1 + i, y - 1 + j) && Board::board[x - 1 + i][y - 1 + j].hasMine)
				{
					mines++;
				}
			}
		}
	return mines;
}
//czy pole ma falge
bool Board::hasFlag(int x, int y)const
{
	if (Board::board[x][y].hasFlag)
		return true;
	else if (Board::board[x][y].isRevealed || !isInside(x, y) | !Board::board[x][y].hasFlag)
		return false;
}
//ustaw flage
void Board::toggleFlag(int x, int y)
{
	if (!Board::board[x][y].isRevealed)
		Board::board[x][y].hasFlag = true;
}

bool Board::PierwszyMove()
{
	int kafelki = 0;
	for (int i = 0; i < Board::getBoardWidth(); i++)
	{
		for (int j = 0; j < Board::getBoardHeight(); j++)
			if (!isRevealed(i, j))
				kafelki++;

	}
	if (kafelki == (Board::getBoardWidth() * Board::getBoardHeight()))
		return true;
	else
		return false;
}
//odktryj pole
void Board::revealField(int x, int y)
{
	if (!isRevealed(x, y) && !Board::board[x][y].hasMine)
		(Board::board[x][y].isRevealed) = true;
	if (!isRevealed(x, y) && Board::board[x][y].hasMine && PierwszyMove())
	{
		board[x][y].hasMine = 0;
		board[rand() % width][rand() % height].hasMine = 1;
		Board::board[x][y].isRevealed = true;
	}
	else if (!isRevealed(x, y) && Board::board[x][y].hasMine)
		this->gstatus = FINISHED_LOS;


}

bool Board::WinGame()const

{
	double procent = 0;

	if (this->mode == EASY)
		procent = 0.1;
	else if (this->mode == NORMAL)
		procent = 0.2;

	else if (this->mode == HARD)
		procent = 0.3;

	int flags = 0;
	int revealed = 0;
	for (int i = 0; i < Board::getBoardWidth(); i++)
	{
		for (int j = 0; j < Board::getBoardHeight(); j++) {
			if (board[i][j].hasMine == 1 && board[i][j].hasFlag == 1)
			{
				flags++;
			}
			if (board[i][j].hasMine == 1 && board[i][j].isRevealed == 0)
			
				revealed++;
		

		}

	}
	if (flags == (Board::getBoardHeight() * Board::getBoardWidth()) * procent || revealed == (Board::getBoardHeight() * Board::getBoardWidth()) * procent)
	{
		return true;
	}
	else
		return false;

}

char Board::getFieldInfo(int x, int y)const
{
	if (!isInside(x, y))
		return '#';
	else if (!isRevealed(x, y) && hasFlag(x, y))
		return 'F';
	else if (!isRevealed(x, y) && !hasFlag(x, y))
		return '_';
	else if (isRevealed(x, y) && Board::board[x][y].hasMine)
		return 'x';
	else if (isRevealed(x, y) && countMines(x, y) == 0)
		return ' ';
	else if (isRevealed(x, y))
		return countMines(x, y);






}



GameState Board::getGameState() const
{

	if (WinGame() == true)
		return FINISHED_WIN;
	else if (this->gstatus == RUNNING)
		return RUNNING;
	else if (this->gstatus == FINISHED_LOS)
		return FINISHED_LOS;
	else
		return  RUNNING;

}


string Board::fieldDebug(const field& plansza) const {
	string display = "...";
	if (plansza.hasMine)
		display[0] = 'M';
	if (plansza.isRevealed)
		display[1] = 'O';
	if (plansza.hasFlag)
		display[2] = 'F';
	return display;
}

void Board::debugDisplay() const {
	for (unsigned int i = 0; i < this->height; i++) {
		for (unsigned int j = 0; j < this->width; j++) {
			cout << "[" << fieldDebug(board[j][i]) << "] ";
		}
		cout << std::endl;
	}
}
