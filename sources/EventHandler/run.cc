#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>

#include "EventHandler.hh"

#define MAY_INTERRUPT( x ) { int up; if ( (up = (x)) ) return up; }



int EventHandler::run(sf::RenderWindow & w)
{
   sf::View & view = w.GetDefaultView();
   

   while (true)
   {
      std::cout << "\n\t<< loop >>\n";

      view.SetFromRect(sf::FloatRect(0, 0, w.GetWidth(), w.GetHeight()));

      /* gestion évenements */
      MAY_INTERRUPT( draw(w) );
      w.Display();
      
      sf::Event e;
      while (w.GetEvent(e)) MAY_INTERRUPT( call(e) );
   } 
}

int EventHandler::call(sf::Event e)
{
   switch (e.Type)
   {
      case sf::Event::Closed:              return closed();
      case sf::Event::MouseButtonPressed:  return mouseButtonPressed(e.MouseButton); 
      case sf::Event::MouseButtonReleased: return mouseButtonReleased(e.MouseButton);

      default:
	 return 0;
   }
}

int EventHandler::closed()
{
   return 1;
}

EventHandler::~EventHandler()
{}







int EventDemo::draw(sf::RenderWindow & w)
{
   w.Clear();

   if (x != -1)
   {
      sf::Shape s = sf::Shape::Circle(x, y, 70, sf::Color(0, 200, 255));
      w.Draw(s);
   }

   return 0;
}

int EventDemo::mouseButtonPressed(sf::Event::MouseButtonEvent e)
{
   x = e.X;
   y = e.Y;

   return 0;
}

int EventDemo::mouseButtonReleased(sf::Event::MouseButtonEvent e)
{
   x = -1;
   y = -1;

   return 0;
}





