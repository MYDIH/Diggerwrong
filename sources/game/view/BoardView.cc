#include "BoardView.hh"

BoardView::BoardView()
   :Observed(nullptr)
{}


BoardView::~BoardView()
{
   if (Observed)
//      Observed -> unregisterObserver(push);

   delete_squares();
}

void BoardView::delete_squares()
{
   for (auto v : Squares)
      for (SquareView* s : v)
	 if (s) delete s;
}

void BoardView::observe(const Board * b)
{
   if (Observed)
//      Observed -> unregisterObserver(push);

   delete_squares();
   
   Observed = b;
//   Observed -> registerObserver(push);

   
}

void BoardView::push(const Board::change& c)
{ Changes.push(c); }




