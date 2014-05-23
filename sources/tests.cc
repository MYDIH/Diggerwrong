#include "tests.hh"
#include "Animation.hh"
#include "Board.hh"
#include "BoardView.hh"
#include "squares.hh"
#include "GuiController.hh"
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


   GuiController gc;
   //EventHandler c;
//   c.run(window);



   ResourcesPool p;
   Normal::init( p );
   Bonus::init( p );
   Bomb::init( p );
   Digged::init( p );

   p.add(&MenuView::menuCorner);
   p.add(&Button::corner);
   p.add(&Button::back);

   p.add(&BoardView::DiggerResource);
   p.add(&BoardView::ExplosionResource);

   p.add(&BoardView::DeadResource);
   p.add(&BoardView::Score_font);
   p.add(&BoardView::Score_value_font);
   p.add(&BoardView::Score_sound);
   p.add(&BoardView::Bonus_sound);
   p.add(&BoardView::Life_sound);
   p.add(&BoardView::Fart);

   p.add(&GameController::Big_font);
   p.add(&GameController::Youwin);
   p.add(&GameController::Tryagain);
   p.add(&GameController::Levelup);
   p.add(&GameController::Gameover);
   p.add(&GameController::Star1);
   p.add(&GameController::Star2);

   p.add(&BoardView::DeadResource);


   try
   {
      p.load("themes/default");
   }
   catch (const std::string & f)
   {
      std::cout << "\n!! ERREUR concernant le fichier:\n" << f << "\n\n";
      exit(1);
   }
   
   //gc.run(window);
   
   Board b(8,8,0.5,10, 10);
   BoardView bv;
   bv.observe(&b, 1);




   sf::View view(sf::FloatRect(-500,-500,500,500));
   window.SetView(view);

   sf::Shape s = sf::Shape::Rectangle(0, 0, 10, 10, sf::Color(255, 255, 255));

   MenuView m;
   bool shot = false;


   std::vector<module> modules = {  {Bonus::init, Bonus::create , 0.05   , 0.001 }
				   ,{Bomb::init , Bomb::create  , 0.01   , 0.1   } };

   module first = {Digged::init, Digged::create, 0};
   module defaultmod ={Normal::init, Normal::create, 0    , 0};


   GameController game;
   game.Modules = &modules;
   game.First   = &first;
   game.Default = &defaultmod;
   
   game.new_game(20,11,20,2,3,0);
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

      //m.draw(window);

      bv.tick(now);
      window.Draw(s);
      view.Move(200,200);
      // --
      bv.draw(window, now);
      // --
      view.Move(-200,-200);

      window.Display();
   }

}

