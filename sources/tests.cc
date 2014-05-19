#include "tests.hh"
#include "Animation.hh"
#include "Board.hh"
#include "BoardView.hh"
#include "squares.hh"
#include "resources.hh"

#include <iostream>
#include <SFML/Graphics.hpp>

void animation()
{
   const sf::Clock clock;
   sf::RenderWindow window(sf::VideoMode(500,500,32), "test animations");
   window.SetFramerateLimit(30);

   ResourcesPool p;
   Normal::init( p );
   Bonus::init( p );
   Bomb::init( p );
   p.load("themes/default");


   Board b(10,10,0.5,10, 10);
   BoardView bv;
   bv.observe(&b, 1);



   float now = clock.GetElapsedTime();

   sf::View v2(sf::FloatRect(-250,-250,250,250));
   window.SetView(v2);
      

//   exit(0);
   while (true)
   {
      now = clock.GetElapsedTime();
//      std::cout << "[TICK] " << now << "\n";

      window.Clear();


      bv.tick(now);
      bv.draw(window, now);
      //window.SetView(v);
      //sa.draw(window, now);

      window.Display();
   }

}

