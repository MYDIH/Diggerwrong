#include "EventHandler.hh"

#include <cstdlib>
#include <cstring>
#include <ctime>

#include <iostream>

// Fichier temporaire

int textMain();

int guiMain()
{
   sf::RenderWindow window(sf::VideoMode::GetDesktopMode(), "Demo !");
   window.SetFramerateLimit(35);
   EventDemo demo;
   

   std::cout << "\nrun() giving up with code : " << demo.run(window) << "\n";

   return EXIT_SUCCESS;
}


int main(int argc, char ** argv)
{
    srand(time(NULL));

    if (argc > 1 && strcmp(argv[1], "--gui") == 0)
       return guiMain();
    else
       return textMain();
}



