#pragma once

#include "Board.hh"
#include "SquareView.hh"

#include <queue>
#include <vector>
#include <tuple>

class BoardView : public Board::Observer
{
private:
   typedef Board::change bc;

   std::vector< std::vector< std::pair<SquareView*, SquareView*> > > Squares;
   Board * Observed;

   void delete_squares();
   void replace(unsigned x, unsigned y, const Square * newone, float now);

public:
   BoardView();
   ~BoardView();

   bool care(const Board::change&) const override;

   void observe(Board * b);
   void tick(float now);

};

