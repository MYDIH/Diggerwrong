#include "tests.hh"
#include "Animation.hh"
#include "Button.hh"

#include <iostream>
#include <SFML/Graphics.hpp>

void animation()
{
   const sf::Clock clock;
   sf::RenderWindow window(sf::VideoMode(400,400,32), "test animations");
   window.SetFramerateLimit(30);

   AnimationResource sonicAnim("smiley/");
   sonicAnim.load("/home/nicgomez/Documents/Diggewrong/ressources/Default/");

   SpriteAnimation a(&sonicAnim);
   ValueAnimation b(255, 100, 3, true);
   Button butt;

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
   b.start(now + 3);

   sf::View v2(sf::FloatRect(-200,-200, 200,200));


   while (true)
   {
      now = clock.GetElapsedTime();
//      std::cout << "[TICK] " << now << "\n";

      window.Clear();

      //window.SetView(v);
      //sa.draw(window, now);

      window.SetView(v2);
      butt.draw(window);
      butt.SetColor(sf::Color(b.getValue(now), 0, 0));
      //a.draw(window, now);
      std::cout << b.getValue(now) << std::endl;

      window.Display();
   }

}

