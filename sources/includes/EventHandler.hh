#pragma once

#include <SFML/Window.hpp>

#include <string>

namespace diggewrong
{

   class MainLoop
   {
   private:
      sf::Window Window;


      void (& Draw_handler)(const T &) = NULL;


   public:
      MainLoop(const std::string & window_title, unsigned max_fps);

      void run();
      void draw();

      void hook( void (& handler)(const T &) )
      {
      }
   
   };


}

