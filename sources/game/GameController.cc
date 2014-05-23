#include "GameController.hh"
#include "utils.hh"
#include "consts.hh"

#include <cfloat>

AnimationResource GameController::Star("", "star.txt");

FontResource GameController::Big_font("", "big-font.txt");

SoundResource GameController::Youwin(  "", "youwin.txt");
SoundResource GameController::Tryagain("", "tryagain.txt");
SoundResource GameController::Levelup( "", "levelup.txt");
SoundResource GameController::Gameover("", "gameover.txt");


GameController::GameController()
   :Try( {&Try1,&Try2} )
   ,View( {&View1,&View2} )

   ,Width(0)
   ,Height(0)
   ,Target(0)
   ,Rank(0)
   ,Lifes(0)
   ,Score(0)
   
   ,Big_flash(11,1,2)
   ,State(CONTINUE)
   ,Slide(0,1,0.35, EASE_IN_OUT<10>)

   ,BackX(0,1,10, EASE_IN_OUT<7>)
   ,BackY(0,1,14, EASE_IN_OUT<9>)
{
   Slide.start(-10);
   BackX.start(0);
   BackY.start(0);
}

void GameController::new_game(unsigned width, unsigned height, unsigned target
			      ,unsigned last_rank, unsigned lifes, unsigned score )
			      
{
   Width  = width;
   Height = height;
   Target = target;

   Rank   = last_rank;
   Lifes  = lifes;
   Score  = score;

   Waiting = false;
   Big_flash.start(FLT_MAX);
   State = CONTINUE;

   Level.generate( Width,Height,Target
		   ,inv(Rank), *Modules, *First );
   
   *(Try.second) = Level;
   View.second->observe( Try.second, 0 );
}


int GameController::tick(sf::RenderWindow & w, float now)
{
   View.second->tick(now);

   if (State != CONTINUE)
   {
      if (not Waiting and View.second->finished())
      {
	 Waiting = true;
	 switch (State)
	 {
	    case GAME_OVER: Gameover.play_new(); break;
	    case TRY_AGAIN: Tryagain.play_new(); break;
	    case WON:       Youwin.play_new();   break;

	    default:;
	 }

      }

      else if (Waiting and not Big_flash.running(now))
	 Big_flash.start(now);
   }


   if (not BackX.running(now))
   {
      BackX.swap();
      BackX.start(now);
   }
   
   if (not BackY.running(now))
   {
      BackY.swap();
      BackY.start(now);
   }

   need_refresh();
   return 0;
}

void GameController::draw_background(sf::RenderTarget & r, float now)
{
   const sf::View & orig = r.GetView();
   sf::View v = orig;
   r.SetView(v);

   r.Clear(sf::Color(90,90,90));

   // -- AFFICHAGE des étoiles
   v.Zoom(BackX.value(now) * 0.5 + 0.5);
   v.Move(BackX.value(now) * 1000 -1000, BackY.value(now) * 1000 -1000);

   r.Draw( Star.frame(0,0) );
   // --

   r.SetView(orig);
}

void GameController::draw(sf::RenderTarget & r, float now)
{
   draw_background(r,now);

   const sf::View & orig = r.GetView();
   sf::View view = orig;
   r.SetView(view);

   const float out = r.GetWidth();

   // -- AFFICHAGE plateau en cours
   {
      sf::View v = view;
      r.SetView(v);
      v.Move(-Slide.value(now) * out, 0);
      //const float z = (1-Slide.value(now));
      //v.Zoom(z*z*z * 0.5 + 0.5);

      View.second->draw(r,now);

      r.SetView(view);
   }
   // --




   if (Slide.running(now))
   {
      // -- AFFICHAGE plateau précédent
      sf::View v = view;
      r.SetView(v);
      v.Move((1-Slide.value(now)) * out, 0);
      //const float z = Slide.value(now);
      //v.Zoom(z*z*z * 0.5 + 0.5);

      View.first->draw(r,now);

      r.SetView(view);
      // --
   }



   // -- AFFICHAGE scores
   {
      const float hw = (Try.second -> getWidth() * SQUARE_WIDTH)/2;
      const float hh = (Try.second -> getHeight()* SQUARE_HEIGHT)/2;
      view.Move(hw,-hh);

      const std::string gvalues = ( std::to_string(Rank)
				    + "\n" + std::to_string(Score)
				    + "\n" + std::to_string(Lifes) );

      const sf::Vector2f gsize = BoardView::Score_value_font.draw_string(r, gvalues, 0,0,false);

      BoardView::Score_font.draw_string(r,("niveau\n"
				"score totale\n"
				"vies\n"), gsize.x+10,0,false);



      view.Move(-hw,hh);
   }
   // --



   // -- AFFICHAGE flash
   if ( Waiting and (int)Big_flash.value(now)%5 != 0 )
      switch (State)
      {
	 case GAME_OVER:
	    Big_font.draw_string(r, "GAME OVER !");
	    break;

	 case TRY_AGAIN:
	    Big_font.draw_string(r, "TRY AGAIN !");
	    break;

	 case WON:
	    Big_font.draw_string(r, "YOU WIN !");
	    break;

	 default:;
				 
      }
   // --

   



   r.SetView(orig);
}


int GameController::mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now)
{
   if (Slide.running(now))
      return 0;


   if (Waiting)
   {
      switch (State)
      {
	 case GAME_OVER:
	    std::cout << "\n>> GAME OVER, je rend la mains." << std::endl;
	    return 5;
	    break;

	 case TRY_AGAIN:
	    std::cout << "\n>> go TRY AGAIN" << std::endl;
	    Lifes--;
	    
	    std::swap(Try.first,Try.second);
	    std::swap(View.first,View.second);

	    *(Try.second) = Level;
	    View.second -> observe( Try.second, now + 0.2 );

	    State = CONTINUE;
	    Big_flash.start(FLT_MAX);
	    Slide.start(now);

	    Waiting = false;
	    break;

	 case WON:
	    std::cout << "\n>> go NEXT" << std::endl;
	    Rank++;
	    Score += Try.second->getScore();
	    Score += Try.second->getBonusScore();
	    Lifes += Try.second->getBonusLifes();

	    Level.generate( Width,Height,Target
			    ,inv(Rank), *Modules, *First );

	    std::swap(Try.first,Try.second);
	    std::swap(View.first,View.second);

	    *(Try.second) = Level;
	    View.second -> observe( Try.second, now + 0.2 );

	    State = CONTINUE;
	    Big_flash.start(FLT_MAX);
	    Slide.start(now);

	    Levelup.play_new();
	    
	    Waiting = false;
	    break;

	 default:;
      }

      return 0;
   }




   
   const sf::Vector2f click = w.ConvertCoords(e.X, e.Y);
   const point square = board_coords(click.x, click.y);
   
   const point digger = Try.second->getDigger();
   
   const int dx = -(digger.x - square.x);
   const int dy = -(digger.y - square.y);
   
   std::cout << "\nclick at: " << square.x << "," << square.y << " | " << dx << "," << dy <<  "  (" << now << ")";
   std::cout.flush();

   if ( dx >= -1 and dx <= 1 and dy >= -1 and dy <= 1 )
   {
      std::cout << "     [valid]";
      std::cout.flush();
      switch ( Try.second->move(dx,dy) )
      {
	 case GameState::LOST:
	    if (Lifes >= 1)
	    {
	       State = TRY_AGAIN;
	    }
	    else
	    {
	       State = GAME_OVER;
	    }
	    break;
	    
	    
	 case GameState::WON:
	    State = WON;
	    break;
	    
	 default:;
      }
   }

   return 0;
}

int GameController::key_released(sf::RenderWindow & w, sf::Event::KeyEvent & e, float now)
{
   return 0;
}

point GameController::board_coords(float x, float y)
{
   point p;
   
   p.x = - (-(Width*SQUARE_WIDTH)/2   - x);
   p.y = - (-(Height*SQUARE_HEIGHT)/2 - y);

   p.x = p.x / SQUARE_WIDTH;
   p.y = p.y / SQUARE_HEIGHT;

   return p;
}
