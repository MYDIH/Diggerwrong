#include "EventHandler.hh"

#include <SFML/Window.hpp>

#include <string>
#include <iostream>

using namespace diggewrong;




int EventHandler::run(sf::Window & w)
{
   while (true)
   {
      std::cout << "\t<< loop >>\n";

      draw(w);

      int up;
      sf::Event e;
      while ( w.GetEvent(e)  )
	 if ( (up = call(e)) ) return up;
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




