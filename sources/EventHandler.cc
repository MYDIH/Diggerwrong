#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

#include "EventHandler.hh"


const sf::Clock EventHandler::Clock;

EventHandler::EventHandler()
   :Need_refresh(true)
{}

EventHandler::~EventHandler()
{}


#define MAY_INTERRUPT( x ) { int up; if ( (up = (x)) ) return up; }

int EventHandler::run(sf::RenderWindow & w)
{
   while (true)
   {
      if (Need_refresh)
      {
	 draw(w);
	 w.Display();
	 Need_refresh = false;
      }
      
      sf::Event e;
      while (w.GetEvent(e))
	 MAY_INTERRUPT( call(w,e) );

      MAY_INTERRUPT( tick(w,Clock.GetElapsedTime()) );
   } 
}

int EventHandler::call(sf::RenderWindow & w, sf::Event & e)
{
   switch (e.Type)
   {
      case sf::Event::Closed:              return closed(w);
      case sf::Event::MouseButtonPressed:  return mouse_button_pressed(w, e.MouseButton); 
      case sf::Event::MouseButtonReleased: return mouse_button_released(w, e.MouseButton);
      case sf::Event::KeyPressed:          return key_pressed(w, e.Key);
      case sf::Event::KeyReleased:         return key_released(w, e.Key);
      case sf::Event::Resized:             return resized(w, e.Size);
      case sf::Event::MouseMoved:          return mouse_moved(w, e.MouseMove);

      default:
	 return 0;
   }
}

void EventHandler::need_refresh()
{
   Need_refresh = true;
}

void EventHandler::draw(sf::RenderWindow & w)
{}
int EventHandler::tick(sf::RenderWindow & w, float now)
{ return 0; }
int EventHandler::mouse_button_pressed(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e)
{ return 0; }
int EventHandler::mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e)
{ return 0; }
int EventHandler::key_pressed(sf::RenderWindow & w, sf::Event::KeyEvent & e)
{ return 0; }
int EventHandler::key_released(sf::RenderWindow & w, sf::Event::KeyEvent & e)
{ return 0; }
int EventHandler::mouse_moved(sf::RenderWindow & w, sf::Event::MouseMoveEvent & e)
{ return 0; }
int EventHandler::closed(sf::RenderWindow & w)
{ return 1; }

int EventHandler::resized(sf::RenderWindow & w, sf::Event::SizeEvent & e)
{
   // éviter l'auto-resize chelou
   w.GetDefaultView().SetFromRect(sf::FloatRect(0, 0, w.GetWidth(), w.GetHeight()));
   
   Need_refresh = true;
   return 0;
}



