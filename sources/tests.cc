#include "tests.hh"
#include "Animation.hh"
#include "Board.hh"
#include "BoardView.hh"
#include "squares.hh"
#include "resources.hh"
#include "EventHandler.hh"

#include <iostream>
#include <SFML/Graphics.hpp>

void animation()
{
   const sf::Clock clock;
   sf::RenderWindow window(sf::VideoMode(500,500,32), "test animations");
   window.SetFramerateLimit(30);

   EventHandler c;
//   c.run(window);

   

   ResourcesPool p;
   Normal::init( p );
   Bonus::init( p );
   Bomb::init( p );
   Digged::init( p );

   p.add(&BoardView::DiggerResource);
   p.add(&BoardView::ExplosionResource);
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


   Board b(10,10,0.5,10, 10);
   BoardView bv;
   bv.observe(&b, 1);



   float now = clock.GetElapsedTime();

   sf::View v2(sf::FloatRect(-250,-250,250,250));
   window.SetView(v2);
      


   bool shot = false;


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


      bv.tick(now);
      bv.draw(window, now);
      //window.SetView(v);
      //sa.draw(window, now);

      window.Display();
   }

}

