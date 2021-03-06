#ifndef board_h
#define board_h
#include <iostream>

using std::cout;
using std::string;

enum GameMode { DEBUG, EASY, NORMAL, HARD };
enum GameState {RUNNING, FINISHED_WIN, FINISHED_LOS };

struct field
{
    bool hasMine = false;
    bool hasFlag = false;
    bool isRevealed =false;
};

class Board {
    field board[100][100];
    unsigned int width;
    unsigned int height;

public:
    GameState gstatus;
    GameMode mode;


    Board(unsigned int w, unsigned int h, GameMode mode);
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMinesCount() const;
    int countMines(int x, int y)const;
    bool isInside(int x, int y)const;
    bool hasFlag(int x, int y) const;
    void toggleFlag(int x, int y);
    bool PierwszyMove();
    void revealField(int x, int y);
    bool isRevealed(int x, int y) const;
    GameState getGameState() const;
    char getFieldInfo(int x, int y) const;

};

#endif