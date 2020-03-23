

#ifndef UNTITLED_MSBOARDTEXTVIEW_H
#define UNTITLED_MSBOARDTEXTVIEW_H

#include "Board.h"
#include <string>
class MSBoardTextView{
private:
    Board &board;
public:
    MSBoardTextView(Board &board);
    void display() const ;
    std::string GameStatus() const;
};

#endif //UNTITLED_MSBOARDTEXTVIEW_H
