#include "EventHandler.hh"

#include <SFML/Window.hpp>

#include <string>
#include <iostream>

using namespace diggewrong;


MainLoop::MainLoop(const std::string & window_title, unsigned max_fps)

   :Window(sf::VideoMode::GetDesktopMode(), window_title)

{
   Window.SetFramerateLimit(max_fps);
}

void MainLoop::run()
{
   while (true)
   {
      std::cout << "kikou" << std::endl;

      draw();
   }
   
}

void MainLoop::draw()
{
   Window.Display();
}


