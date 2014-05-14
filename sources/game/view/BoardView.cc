#include "BoardView.hh"
#include "consts.hh"

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

void BoardView::observe(Board * b)
{
   if (Observed)
      Observed -> unregisterObserver(this);

   delete_squares();
   
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
	    Squares[x][y].second = (SquareView*) s->clone(); // copie
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

   for (auto & col : Squares)
      for (auto & pair : col)
      {
	 if (pair.first)  pair.first  -> tick(now);
	 if (pair.second) pair.second -> tick(now);
      }
}

void BoardView::replace(unsigned x, unsigned y, Square * newone, float now)
{
   SquareView * s = ( dynamic_cast<const SquareView*>(newone) ) ?
      (SquareView*) newone->clone() // copie
      :
      nullptr;

   newone -> release();

   std::swap(Squares[x][y].first, Squares[x][y].second);
   Squares[x][y].second = s;

   Squares[x][y].first  -> disappear(now);
   Squares[x][y].second -> appear(now);
}


void BoardView::draw(sf::RenderTarget & drawer, float now) const
{
   const sf::View & orig = drawer.GetView();
   sf::View view(orig);
   drawer.SetView(view);

   view.Move( -(Squares.size()*SQUARE_WIDTH)/2 + SQUARE_WIDTH/2
	      ,-(Squares[0].size()*SQUARE_HEIGHT)/2 + SQUARE_HEIGHT/2);

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

	 view.Move(0, SQUARE_HEIGHT);
      }
      
      view.Move(SQUARE_WIDTH, - (Squares[0].size()-1)*SQUARE_HEIGHT);
   }

   drawer.SetView(orig);
}
