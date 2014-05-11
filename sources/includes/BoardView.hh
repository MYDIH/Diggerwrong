#pragma once

#include "Board.hh"
#include "SquareView.hh"

#include <queue>

class BoardView
{

private:
   std::vector< std::vector<SquareView*> > Squares;

   const Board * Observed;
   std::queue<Board::change> Changes;

   void delete_squares();

public:
   BoardView();
   ~BoardView();


   void push(const Board::change&);
   void observe(const Board * b);

};
