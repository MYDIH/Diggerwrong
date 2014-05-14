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
   void replace(unsigned x, unsigned y, Square * newone, float now);
   void draw_squares(sf::RenderTarget & drawer, float now, bool above) const;

public:
   BoardView();
   ~BoardView();

   bool care(const Board::change&) override;

   void observe(Board * b);
   void tick(float now);

   void draw(sf::RenderTarget & drawer, float now) const;
};

