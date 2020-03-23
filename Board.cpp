//
// Created by Vong on 2020-03-22.
//


#include "board.h"

int Board::getBoardWidth() const
{
    return this->width;
}
int Board::getBoardHeight()const
{
    return this->height;
}
int Board::getMinesCount() const
{
    if (mode == EASY)
        return Board::getBoardWidth()*Board::getBoardHeight()*0.1;

    else if(mode == NORMAL)
        return Board::getBoardWidth()*Board::getBoardHeight()*0.2;

    else if(mode ==HARD)
        return Board::getBoardWidth()*Board::getBoardHeight()*0.3;
    else
        return 18;
}







Board::Board(unsigned int w, unsigned int h, GameMode mode)
{
    this->mode=mode;
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

            if (!board[rand() % w][rand() % h].hasMine ) {
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


        board[2][1].isRevealed = true;
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


bool Board::isInside(int x, int y) const
{
    return x < Board::getBoardWidth() && y < Board::getBoardHeight() && x >= 0 && y >= 0;
}

bool Board::isRevealed(int x, int y)const
{
    return Board::board[x][y].isRevealed;


}

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

bool Board::hasFlag(int x, int y)const
{
    if (Board::board[x][y].hasFlag)
        return true;
    else if (Board::board[x][y].isRevealed || !isInside(x, y) | !Board::board[x][y].hasFlag)
        return false;
}


void Board::toggleFlag(int x, int y)
{
if(!isRevealed(x,y)&&!hasFlag(x,y))
( Board::board[x][y].hasFlag)=true;
else if(!isRevealed(x,y)&&hasFlag(x,y))
    ( Board::board[x][y].hasFlag)=false;
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
    return kafelki == (Board::getBoardWidth() * Board::getBoardHeight());
}

void Board::revealField(int x, int y)
{
    if (!isRevealed(x, y) && !Board::board[x][y].hasMine)
        (Board::board[x][y].isRevealed) = true;
    if (!isRevealed(x, y) && Board::board[x][y].hasMine && PierwszyMove())
    {
        board[x][y].hasMine = false;
        board[rand() % width][rand() % height].hasMine = true;
        Board::board[x][y].isRevealed = true;
    }
    else if (!isRevealed(x, y) && Board::board[x][y].hasMine)
        this->gstatus = FINISHED_LOS;


}





char Board::getFieldInfo(int x, int y)const
{

    if (!isInside(x, y))return '#';
    if (!isRevealed(x, y) && hasFlag(x, y))return 'F';
    if (!isRevealed(x, y) && !hasFlag(x, y))return '_';
    if (isRevealed(x, y) && Board::board[x][y].hasMine)return 'x';
    if (isRevealed(x, y) && countMines(x, y) == 0)return ' ';
    if(board[x][y].isRevealed==1 && Board::countMines(x,y)==0) return ' ';
    if(board[x][y].isRevealed==1 && Board::countMines(x,y)==1) return '1';
    if(board[x][y].isRevealed==1 && Board::countMines(x,y)==2) return '2';
    if(board[x][y].isRevealed==1 && Board::countMines(x,y)==3) return '3';
    if(board[x][y].isRevealed==1 &&Board::countMines(x,y)==4) return '4';
    if(board[x][y].isRevealed==1 && Board::countMines(x,y)==5) return '5';
    if(board[x][y].isRevealed==1 && Board::countMines(x,y)==6) return '6';
    if(board[x][y].isRevealed==1 && Board::countMines(x,y)==7) return '7';
    if(board[x][y].isRevealed==1 && Board::countMines(x,y)==8) return '8';
}

GameState Board::getGameState() const{
    bool loss;
    int flagonMine=0;
    int unrevealed=0;
    for(int i=0;i<Board::getBoardHeight();i++) {
        for (int j = 0; j < Board::getBoardWidth(); j++){
            if(board[i][j].isRevealed && board[i][j].hasMine) {
                loss = false;
                return FINISHED_LOS;
            }
            if(board[i][j].hasFlag && board[i][j].hasMine) flagonMine++;
            if(board[i][j].isRevealed) unrevealed++;
        }
    }
    if(flagonMine==Board::getMinesCount())
        return FINISHED_WIN;
    if(unrevealed==Board::getMinesCount())
        return FINISHED_WIN;
    if(flagonMine!=Board::getMinesCount() && unrevealed!=Board::getMinesCount() && loss!=true)
        return RUNNING;
    }
