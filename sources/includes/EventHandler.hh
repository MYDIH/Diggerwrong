#pragma once

#include <SFML/Window.hpp>

#include <string>

namespace diggewrong
{

   class EventHandler
   {
   private:
      int call(sf::Event t);

   public:
      //MainLoop();

      int run(sf::Window & w);


      /* Evenements */
      virtual int draw(sf::Window & w) = 0;
      virtual int mouseButtonPressed(sf::Event::MouseButtonEvent e)  = 0;
      virtual int mouseButtonReleased(sf::Event::MouseButtonEvent e) = 0;

      virtual int closed();
   



   };


}

