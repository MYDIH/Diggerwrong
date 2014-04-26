#include "EventHandler.hh"
#include "text.hh"

#include <cstdlib>
#include <cstring>
#include <ctime>

#include <iostream>

// Fichier temporaire

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
    else if(argc > 1 && strcmp(argv[1], "--sc") == 0)
       return textMain(1);
    else if(argc > 1 && strcmp(argv[1], "--s") == 0)
       return textMain(0);
    else if(argc > 1 && strcmp(argv[1], "--c") == 0)
       return textMain(2);
    else
        return textMain(3);
}



