#include "BoardView.hh"
#include "consts.hh"

#include <iostream>


BoardView::BoardView()
   :Observed(nullptr)
{}


BoardView::~BoardView()
{
   if (Observed)
      Observed -> unregisterObserver(this);

   delete_squares();
}

void BoardView::delete_squares()
{
   for (auto & col : Squares)
      for (auto & pair : col)
      {
	 if (pair.first)  delete pair.first;
	 if (pair.second) delete pair.second;
      }
}

void BoardView::observe(Board * b, float appear_at)
{
   if (Observed)
      Observed -> unregisterObserver(this);

   delete_squares();


   if (b == nullptr)
   {
      Observed = nullptr;
      Squares.clear();
      return;
   }

   
   Observed = b;
   Observed -> registerObserver(this);


   Squares.resize( Observed -> getWidth() );
   for (unsigned x = 0; x < Squares.size(); x++)
   {
      Squares[x].resize( Observed -> getHeight() );
      for (unsigned y = 0; y < Squares[0].size(); y++)
      {
	 Squares[x][y].first = nullptr;
	 const Square * s = Observed -> getSquare(x,y);
	 if ( dynamic_cast<const SquareView*>(s) ) // le module est compatible avec SquareView
	 {
	    Squares[x][y].second = dynamic_cast<SquareView*>(s->clone()); // copie
	    Squares[x][y].second -> appear(appear_at);
//	    Squares[x][y].second -> disappear(appear_at + 5); // TEST
	 }
	 else
	    Squares[x][y].second = nullptr;
      }
   }


   
}

bool BoardView::care(const Board::change& c)
{
   switch (c.type)
   {
//      case bc::LOST:     return true;
//      case bc::WON:      return true;
//      case bc::MOVE:     return true;
      case bc::REPLACE:
	 c.infos.square -> retain();
	 return true;
//      case bc::DESTRUCT: return true;

      default: return false;
   }
}

void BoardView::tick(float now)
{
   const Board::change * c;
   while ( (c = front()) )
   {
//      std::cout << "> a change\n";

      if ( c -> type == bc::MOVE )
      {
	 // --

	 if (false) // tant que le mouvement n'est pas terminé
	    break;
      }
      else switch ( c -> type )
	   {
	      case bc::REPLACE: 
		 replace(c -> location.x, c -> location.y, c -> infos.square, now);
		 break;
	    
	      default:;
	   }
      
      pop();
   }

//   std::cout << "changes finito\n";
//   std::cout << "H: " << Squares.size() << "  W: " << Squares[0].size() << "\n";



   for (auto & col : Squares)
      for (auto & pair : col)
      {
//	 std::cout << "-- loop\n";
	 
//	 std::cout << "first: " << pair.first << "   second:" << pair.second << "\n";

	 if (pair.first)  pair.first  -> tick(now);
	 if (pair.second) pair.second -> tick(now);
      }

//   std::cout << "tick finito\n";
}

void BoardView::replace(unsigned x, unsigned y, Square * newone, float now)
{
   SquareView * s = ( dynamic_cast<const SquareView*>(newone) ) ?
      dynamic_cast<SquareView*>(newone->clone()) // copie
      :
      nullptr;

   newone -> release();

   std::swap(Squares[x][y].first, Squares[x][y].second);
   Squares[x][y].second = s;

   if (Squares[x][y].first)  Squares[x][y].first  -> disappear(now);
   if (Squares[x][y].second) Squares[x][y].second -> appear(now);
}


void BoardView::draw(sf::RenderTarget & drawer, float now) const
{
   const sf::View & orig = drawer.GetView();
   sf::View view(orig);
   drawer.SetView(view);

   view.Move( (Squares.size()*SQUARE_WIDTH)/2 - SQUARE_WIDTH/2
   	      ,(Squares[0].size()*SQUARE_HEIGHT)/2 - SQUARE_HEIGHT/2);

   draw_squares(drawer,now,false);

   // on dessine ici (entre les 2 calques) le digger / les scores qui volent ...

   draw_squares(drawer,now,true);

   drawer.SetView(orig);
}

void BoardView::draw_squares(sf::RenderTarget & drawer, float now, bool above) const
{
   const sf::View & orig = drawer.GetView();
   sf::View view(orig);
   drawer.SetView(view);

   for (unsigned x = 0; x < Squares.size(); x++)
   {
      for (unsigned y = 0; y < Squares[0].size(); y++)
      {
	 if (above)
	 {
	    if (Squares[x][y].first)  Squares[x][y].first  -> draw_above(drawer,now);
	    if (Squares[x][y].second) Squares[x][y].second -> draw_above(drawer,now);
	 }
	 else
	 {
	    if (Squares[x][y].first)  Squares[x][y].first  -> draw(drawer,now);
	    if (Squares[x][y].second) Squares[x][y].second -> draw(drawer,now);
	 }

	 view.Move(0, -SQUARE_HEIGHT);
//	 std::cout << "draw X: " << x << "    Y: " << y << "\n";
//		   << "view X: " << view.X();
      }
      
      view.Move(-SQUARE_WIDTH, Squares[0].size()*SQUARE_HEIGHT);
   }

   drawer.SetView(orig);
}
