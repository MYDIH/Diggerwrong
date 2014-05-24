#include "BoardView.hh"
#include "consts.hh"
#include "utils.hh"

#include <iostream>
#include <cfloat>

AnimationResource BoardView::DiggerResource("","digger.txt");
AnimationResource BoardView::ExplosionResource("","explosion.txt");
AnimationResource BoardView::DeadResource("","dead.txt");

FontResource BoardView::Score_font("", "score-font.txt");
FontResource BoardView::Score_value_font("", "score-value-font.txt");

SoundResource BoardView::Score_sound("", "score-sound.txt");
SoundResource BoardView::Bonus_sound("", "bonus-sound.txt");
SoundResource BoardView::Life_sound("", "life-sound.txt");
SoundResource BoardView::Fart(    "", "fart.txt");


BoardView::BoardView()
   :Observed(nullptr)
   ,DiggerX(0,0,0.13)
   ,DiggerY(0,0,0.20)
   ,Digger(&DiggerResource)
   ,Explosion(&ExplosionResource)
   ,Dead(&DeadResource)

{
   Digger.start(0);
}


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

void BoardView::observe(Board * b, float show_at)
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
	    Squares[x][y].second -> show(show_at);
	 }
	 else
	    Squares[x][y].second = nullptr;
      }
   }


   point pos = Observed -> getDigger();
   DiggerX.set_value(pos.x);
   DiggerY.set_value(pos.y);

   Target      = Observed -> getTarget();
   Reached     = Observed -> getReached();
   Score       = Observed -> getScore();
   Bonus_score = Observed -> getBonusScore();
   Bonus_lifes = Observed -> getBonusLifes();

   Digger.start(0);
   Explosion.start(FLT_MAX);
}

bool BoardView::care(const Board::change& c)
{
   switch (c.type)
   {
      case bc::LOST:  return true;
      case bc::WON:   return true;
      case bc::MOVE:  return true;
      case bc::SCORE: return true;
      case bc::SCORE_BONUS: return true;
      case bc::LIFE_BONUS:  return true;

      case bc::REPLACE:
	 c.infos.square -> retain();
	 return true;
//      case bc::DESTRUCT: return true;

      default: return false;
   }
}

bool BoardView::moving() const
{
   return ((front()) and front()->type == bc::MOVE);
}
bool BoardView::finished() const
{
   return (front() == nullptr);
}

void BoardView::tick(float now)
{
   const Board::change * c;
   while ( (c = front()) and not DiggerX.running(now) and not DiggerY.running(now) )
      // si il y a un changement à traité et qu'aucun mouvement n'est en cours
   {
//      std::cout << "> a change\n";

      if ( c -> type == bc::MOVE )
      {
	 DiggerX.restart_at_end(c->location.x);
	 DiggerY.restart_at_end(c->location.y);

	 DiggerX.start(now);
	 DiggerY.start(now);

	 Reached = c -> infos.value.total;

	 std::cout << "[move catched] REACHED=" << Reached << "\tmyTARGET=" << Target << std::endl;
      }
      else switch ( c -> type )
	   {
	      case bc::REPLACE: 
		 std::cout << "[replace catched]\n";
		 replace(c -> location.x, c -> location.y, c -> infos.square, now);
		 break;

	      case bc::LOST:
		 std::cout << "[lost catched]\n";
		 Explosion.start(now);
		 Digger.stop(now);
		 Fart.play_new();
		 break;

	      case bc::SCORE:
		 Score = c -> infos.value.total;
		 Score_sound.play_new();
		 break;

	      case bc::SCORE_BONUS:
		 Bonus_score = c -> infos.value.total;
		 Bonus_sound.play_new();
		 break;

	      case bc::LIFE_BONUS:
		 Bonus_lifes = c -> infos.value.total;
		 Life_sound.play_new();
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


   const float width  = Squares.size()*SQUARE_WIDTH;
   const float height = Squares[0].size()*SQUARE_HEIGHT;


   //const int h = Score_value_font.font().GetGlyph('0').Rectangle.GetHeight();
   //drawer.Draw( sf::Shape::Rectangle(-width/2, -height/2, width/2, height/2, sf::Color(70,70,70,140)) );



   // on se décale en haut à gauche
   view.Move( width/2
   	      ,height/2);
   
   const float pg = Observed -> progress();
   drawer.Draw( sf::Shape::Rectangle(-2, -2 -BAR, -2 + width*(1-pg), -2 -5
				     ,sf::Color( 170*pg, 200*(1-pg), 100,140 )) );
   drawer.Draw( sf::Shape::Rectangle(0, -BAR, width*(1-pg), -5
				     ,sf::Color( 255*pg, 255*(1-pg), 70,190 )) );


   view.Move( - SQUARE_WIDTH/2
   	      ,- SQUARE_HEIGHT/2 );
   draw_squares(drawer,now,false);


   // on dessine ici (entre les 2 calques) le digger / les scores qui volent ...

   // -- AFFICHAGE digger
   {
      float x = DiggerX.value(now)*SQUARE_WIDTH;
      float y = DiggerY.value(now)*SQUARE_HEIGHT;
      view.Move(-x,-y);

      if (Digger.running(now))
	 Digger.draw(drawer,now);
      else
	 Dead.draw(drawer,now);

      if (Explosion.running(now))
	 Explosion.draw(drawer,now);

      view.Move(x,y);
   }
   // --

   // -- AFFICHAGE scores
   {
      view.Move(SQUARE_WIDTH/2, -height + SQUARE_HEIGHT/2);

      const std::string values = ( std::to_string( MAX(0, (int)Target - (int)Reached) )
				   + "\n" + std::to_string( Score       )
				   + "\n" + std::to_string( Bonus_score )
				   + "\n" + std::to_string( Bonus_lifes ));
      
      
      
      const sf::Vector2f size = Score_value_font.draw_string(drawer, values, width/2 +30,0,false);

      float d = width/2 +30 + 10;
      d = MAX( d + size.x, d + Score_value_font.font().GetGlyph('0').Advance*3 );

      Score_font.draw_string(drawer,("cases restantes\n"
				     "score\n"
				     "score bonus\n"
				     "vies bonus"), d,0,false);


      view.Move(-SQUARE_WIDTH/2, height - SQUARE_HEIGHT/2);
   }
   // --

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

float BoardView::get_width()  const
{
   return Squares.size()*SQUARE_WIDTH;
}
float BoardView::get_height() const
{
   return Squares[0].size()*SQUARE_HEIGHT;
}
