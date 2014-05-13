#include "tests.hh"
#include "Animation.hh"

#include <iostream>
#include <SFML/Graphics.hpp>

void animation()
{
   const sf::Clock clock;
   sf::RenderWindow window(sf::VideoMode(400,400,32), "test animations");
   window.SetFramerateLimit(30);



   AnimationResource once(60,30,false);


   AnimationResource loop(200,30,true);



   Animation a(&loop);

   // SquareAnimation sa(&once
   // 		      ,nullptr

   // 		      ,&loop
   // 		      ,nullptr

   // 		      ,&once
   // 		      ,nullptr);

   
   float now = clock.GetElapsedTime();

   // sa.appear(now + 1);
   // sa.disappear(now + 15);


   a.start(now + 2);
   a.stop(now + 10);

   sf::View v(sf::FloatRect(-100,-100,100,100));
   sf::View v2(sf::FloatRect(-100,-100,100,100));
   v2.Move(-30,-30);


   while (true)
   {
      now = clock.GetElapsedTime();
//      std::cout << "[TICK] " << now << "\n";

      window.Clear();

      //window.SetView(v);
      //sa.draw(window, now);

      window.SetView(v2);
      a.draw(window, now);

      window.Display();
   }

}

