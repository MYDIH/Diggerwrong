#include "utils.hh"
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
#include "ScoresTab.hh"
#include "GameController.hh"

#include <map>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>


void animation()
{
   std::map<std::string,std::string> test;
   test["robert"]="3435";
   test["jean"]="400";
   test["jack"]="393939";
   writeFile(test, "KIKOO.txt");


   sf::RenderWindow window(sf::VideoMode(1000,1000,32), "test animations");
   window.SetFramerateLimit(40);

   srand(time(NULL));
   

   ResourcesPool p;
   Normal::init( p );
   Bonus::init( p );
   Bomb::init( p );
   Digged::init( p );

   p.add(&MenuView::menuCorner);
   p.add(&MenuView::title);
   p.add(&Button::corner);
   p.add(&Button::back);
   p.add(&Button::labelFont);
   p.add(&ScoresTab::namesCol);
   p.add(&ScoresTab::contenuCol);
   p.add(&ScoresTab::tabLines);

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



   std::vector<module> modules = {  {Bonus::init, Bonus::create , 0.3    , 0.002  }
				    ,{Bomb::init, Bomb::create   ,0.005  , 0.44   } };

     module firstmod   = {Digged::init, Digged::create, 0,0};
     module defaultmod = {Normal::init, Normal::create, 0,0};


     GuiController gc(modules, firstmod, defaultmod);


     gc.run(window);

}
