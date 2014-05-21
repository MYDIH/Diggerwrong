#include "tests.hh"
#include "Animation.hh"
#include "Board.hh"
#include "BoardView.hh"
#include "squares.hh"
#include "resources.hh"
#include "EventHandler.hh"
#include "Button.hh"
#include "MenuView.hh"

#include <iostream>
#include <SFML/Graphics.hpp>

void animation()
{
   const sf::Clock clock;
   float now = clock.GetElapsedTime();

   sf::RenderWindow window(sf::VideoMode(1000,1000,32), "test animations");
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


   Board b(8,8,0.5,10, 10);
   BoardView bv;
   bv.observe(&b, 1);




   sf::View view(sf::FloatRect(-500,-500,500,500));
   window.SetView(view);

   MenuView m;
   m.start(now + 3);


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

