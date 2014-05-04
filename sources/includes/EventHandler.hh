#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class EventHandler
{
private:
   bool Need_refresh;
   static const sf::Clock Clock;

public:
   EventHandler();
   virtual ~EventHandler();

   int run(sf::RenderWindow & w);
   int call(sf::RenderWindow & w, sf::Event & t);
   void need_refresh();
      
      
   /* Evenements */
   virtual void draw(sf::RenderWindow & w);
   virtual int tick(sf::RenderWindow & w, float now);
   virtual int mouse_button_pressed(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e);
   virtual int mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e);
   virtual int key_pressed(sf::RenderWindow & w, sf::Event::KeyEvent & e);
   virtual int key_released(sf::RenderWindow & w, sf::Event::KeyEvent & e);
   virtual int mouse_moved(sf::RenderWindow & w, sf::Event::MouseMoveEvent & e);
   virtual int resized(sf::RenderWindow & w, sf::Event::SizeEvent & e);
   virtual int closed(sf::RenderWindow & w);
};

