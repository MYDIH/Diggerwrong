#include "tests.hh"
#include "Animation.hh"
#include "Board.hh"
#include "BoardView.hh"
#include "squares.hh"
#include "resources.hh"
#include "EventHandler.hh"
#include "Button.hh"
#include "MenuView.hh"
#include "GameController.hh"

#include <iostream>
#include <SFML/Graphics.hpp>

void animation()
{
   const sf::Clock clock;
   float now = clock.GetElapsedTime();

   sf::RenderWindow window(sf::VideoMode(1000,1000,32), "test animations");
   window.SetFramerateLimit(30);

   

   ResourcesPool p;
   Normal::init( p );
   Bonus::init( p );
   Bomb::init( p );
   Digged::init( p );

   p.add(&BoardView::DiggerResource);
   p.add(&BoardView::ExplosionResource);
   p.add(&BoardView::DeadResource);
   p.add(&BoardView::Score_font);
   p.add(&BoardView::Score_value_font);
   p.add(&BoardView::Score_sound);
   p.add(&BoardView::Bonus_sound);
   p.add(&BoardView::Life_sound);

   p.add(&GameController::Big_font);

   try
   {
      p.load("themes/default");
   }
   catch (const std::string & f)
   {
      std::cout << "\n!! ERREUR concernant le fichier:\n" << f << "\n\n";
      exit(1);
   }


   Board b(8,8,0.5,10, 10);
   BoardView bv;
   bv.observe(&b, 1);




   sf::View view(sf::FloatRect(-500,-500,500,500));
   window.SetView(view);

   MenuView m;
   m.start(now + 3);


   bool shot = false;


   std::list<module> modules = { {Normal::init, Normal::create, 0.92, true}
				 ,{Bonus::init, Bonus::create , 0.01, true}
				 ,{Bomb::init , Bomb::create  , 0.07, false} };

   module first = {Digged::init, Digged::create, 0};

   GameController game;
   game.Modules = &modules;
   game.First   = &first;
   
   game.new_game(15,15,20,2,3,0);
   game.run(window);

//   exit(0);
   while (true)
   {
      now = clock.GetElapsedTime();
//      std::cout << "[TICK] " << now << "\n";

      if (now > 6 and not shot)
      {
	 b.move(-1,0);
	 b.move(0,1);
	 b.move(1,1);
	 b.move(1,0);
	 b.move(0,-1);
	 shot = true;
	 std::cout << "--> GOCOWS!\n";
      }

      
      

      window.Clear(sf::Color(100,100,100));

      m.update(now);
      m.draw(window);

      bv.tick(now);

      view.Move(200,200);
      // --
      bv.draw(window, now);
      // --
      view.Move(-200,-200);

      window.Display();
   }

}

