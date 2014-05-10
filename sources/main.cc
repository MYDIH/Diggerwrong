#include "text.hh"
#include "tests.hh"

#include <boost/program_options.hpp>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <iostream>

namespace po = boost::program_options;

int guiMain() // temporaire...
{
   animation();

   return EXIT_SUCCESS;
}


int main(int argc, char ** argv)
{
   po::options_description options("Options");
   options.add_options()
      ("help,h"   , "afficher l'aide")
      ("gui,G"    , "lancer le jeu en mode graphique")
      ("text,T"   , "[activé par défaut] lancer le jeu en mode texte (pour tester)")
      ("color,c"  , "utiliser des couleurs ANSI en mode texte (plus lisible)")
      ("unicode,u", "utiliser des caractères Unicode en mode texte (plus lisible)")
      ;


   po::variables_map o;
   
   po::store(po::parse_command_line(argc, argv, options), o);
   po::notify(o); 

   if (o.count("help"))
   {
      std::cout << "\n-- diggewrong rev." << REV << "\n-- un clone du jeu Puru Puru Digger\n-- Timothée Jourde & Nicolas Gomez\n\n"
		<< options << std::endl;
      return EXIT_SUCCESS;
   }
   else if (o.count("gui"))
   {
      return guiMain();
   }
   else
   {
      const bool color = o.count("color");
      const bool unicode = o.count("unicode");

      int charset;

      if (color and unicode)
	 charset = 1;
      else if (unicode)
	 charset = 0;
      else if (color)
	 charset = 2;
      else
	 charset = 3;

      return textMain(charset);
   }
}



