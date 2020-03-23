
#include <iostream>
#include <iomanip>
#include "MSBoardTextView.h"

MSBoardTextView::MSBoardTextView(Board &board) : board(board){}
void MSBoardTextView::display() const
{
    std::cout<<this->GameStatus()<<std::endl;
    for(int x=0;x<this->board.getBoardWidth();x++)
    {
     std::cout<<std::setw(5)<<x;
    }
    cout<<std::endl;
    for(int y=0;y<this->board.getBoardHeight();y++)
    {
        std::cout<<y<<" ";
        for(int x=0;x<this->board.getBoardWidth();x++)
        {
            std::cout << "[ " << this->board.getFieldInfo(x, y) <<  " ]";

        }
        std::cout<<std::endl;
        }



}
std::string MSBoardTextView::GameStatus() const {
    if(this->board.getGameState()==GameState::RUNNING)
    {return "running";}
    if(this->board.getGameState()==GameState::FINISHED_WIN)
    {return "Win";};
    return "LOSS";
}