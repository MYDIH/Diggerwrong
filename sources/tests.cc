#include "tests.hh"
#include "Animation.hh"
#include "Board.hh"
#include "BoardView.hh"
#include "squares.hh"
#include "resources.hh"
#include "MenuView.hh"

#include <iostream>
#include <SFML/Graphics.hpp>

void animation()
{
   const sf::Clock clock;
   sf::RenderWindow window(sf::VideoMode(500,500,32), "test animations");
   window.SetFramerateLimit(30);


   /*ResourcesPool p;
   Normal::init( p );
   Bonus::init( p );
   Bomb::init( p );
   Digged::init( p );

   try
   {
      p.load("themes/default");
   }
   catch (const std::string & f)
   {
      std::cout << "\n!! ERREUR concernant le fichier:\n" << f << "\n\n";
      exit(1);
   }


   Board b(10,10,0.5,10, 10);
   BoardView bv;
   bv.observe(&b, 1);



   float now = clock.GetElapsedTime();

   sf::View v2(sf::FloatRect(-250,-250,250,250));
   window.SetView(v2);*/

   MenuView m(window.GetDefaultView());

//   exit(0);
   while (true)
   {
     //now = clock.GetElapsedTime();
//      std::cout << "[TICK] " << now << "\n";

      //b.draw(window);
      window.Clear(sf::Color(100,100,100));

      m.draw(window);
      //bv.tick(now);
      //bv.draw(window, now);
      //window.SetView(v2);
      //sa.draw(window, now);

      window.Display();
   }

}

