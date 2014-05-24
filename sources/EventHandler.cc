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
   w.SetView(View);
   View.SetCenter(0,0);
   View.SetHalfSize(w.GetWidth()/2.f, w.GetHeight()/2.f);


   while (true)
   {
      const float now = Clock.GetElapsedTime();

      sf::Event e;
      while (w.GetEvent(e))
	 MAY_INTERRUPT( call(w,e,now) );

      MAY_INTERRUPT( tick(w,now) );


      if (Need_refresh)
      {
	 w.Clear(sf::Color(80,80,80));

	 draw(w,now);
	 w.Display();
	 Need_refresh = false;
      }
   }
}

int EventHandler::call(sf::RenderWindow & w, sf::Event & e, float now)
{
   switch (e.Type)
   {
      case sf::Event::Closed:
	 return closed(w,now);

      case sf::Event::MouseButtonPressed:
	 return mouse_button_pressed(w, e.MouseButton,now);

      case sf::Event::MouseButtonReleased:
	 return mouse_button_released(w, e.MouseButton,now);

      case sf::Event::KeyPressed:
	 return key_pressed(w, e.Key, now);

      case sf::Event::KeyReleased:
	 return key_released(w, e.Key, now);

      case sf::Event::Resized:
	 return resized(w, e.Size, now);

      case sf::Event::MouseMoved:
	 return mouse_moved(w, e.MouseMove, now);

      case sf::Event::TextEntered:
	 return text_entered(w, e.Text, now);

      default:
	 return 0;
   }
}

void EventHandler::need_refresh()
{
   Need_refresh = true;
}

void EventHandler::draw(sf::RenderTarget & r, float now)
{}

int EventHandler::tick(sf::RenderWindow & w, float now)
{
   need_refresh();
   return 0;
}

int EventHandler::mouse_button_pressed(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now)
{
   return 0;
}

int EventHandler::mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now)
{
   return 0;
}

int EventHandler::key_pressed(sf::RenderWindow & w, sf::Event::KeyEvent & e, float now)
{
   return 0;
}

int EventHandler::key_released(sf::RenderWindow & w, sf::Event::KeyEvent & e, float now)
{
   return 0;
}

int EventHandler::mouse_moved(sf::RenderWindow & w, sf::Event::MouseMoveEvent & e, float now)
{
   return 0;
}

int EventHandler::closed(sf::RenderWindow & w, float now)
{
   return 1;
}

int EventHandler::text_entered(sf::RenderWindow & w, sf::Event::TextEvent e, float now)
{
   return 0;
}

int EventHandler::resized(sf::RenderWindow & w, sf::Event::SizeEvent & e, float now)
{
   // éviter l'auto-resize chelou
   View.SetHalfSize(w.GetWidth()/2.f, w.GetHeight()/2.f);

   need_refresh();
   return 0;
}



