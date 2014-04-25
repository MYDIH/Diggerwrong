#pragma once

#include <SFML/Graphics.hpp>

#include <string>

namespace diggewrong
{

   class EventHandler
   {
   public:
      virtual ~EventHandler();

      int run(sf::RenderWindow & w);
      int call(sf::Event t);
      
      
      
      /* Evenements */
      virtual int draw(sf::RenderWindow & w) = 0;
      virtual int mouseButtonPressed(sf::Event::MouseButtonEvent e)  = 0;
      virtual int mouseButtonReleased(sf::Event::MouseButtonEvent e) = 0;
      
      virtual int closed();
      
      
      
      
   };

   class EventDemo : public EventHandler
   {
   private:
      int x = -1, y = -1;
   public:
      int draw(sf::RenderWindow & w) override;
      int mouseButtonPressed(sf::Event::MouseButtonEvent e)  override;
      int mouseButtonReleased(sf::Event::MouseButtonEvent e) override;
   };


}

