#include "text.hh"
#include "tests.hh"

#include <boost/program_options.hpp>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <iostream>

namespace po = boost::program_options;

int guiMain(const std::string & themes, const std::string & hightscores)
{
   // tests
   animation();
   return 0;
   //




   return EXIT_SUCCESS;
}



int main(int argc, char ** argv)
{
   po::options_description options("Options");
   options.add_options()
      ("help,h"   , "afficher cette l'aide")
      ("gui,G"    , "[activé par défaut] lancer le jeu en mode graphique")
      ("scores,s" , po::value<std::string>() , "chemin vers le fichier des meilleurs scores (\"hightscores.txt\" dans le repertoire courant par defaut)")
      ("themes,t" , po::value<std::string>() , "chemin vers le repertoire des themes (\"themes\" dans le repertoire courant par defaut)")
      ("text,T"   , "lancer le jeu en mode texte (pour tester)")
      ("color,c"  , "utiliser des couleurs ANSI en mode texte (plus lisible)")
      ("unicode,u", "utiliser des caractères Unicode en mode texte (plus lisible)")
      ;


   bool fail = false;
   po::variables_map o;

   try
   {
      po::store(po::parse_command_line(argc, argv, options), o);
      //po::notify(o); 
   }
   catch(const po::error &e)
   {
      fail = true;
   }

   if (o.count("help") or fail)
   {
      std::cout << "\n-- diggewrong rev." << REV << "\n-- un clone du jeu Puru Puru Digger\n-- Timothée Jourde & Nicolas Gomez\n\n"
		<< options << std::endl;
      return EXIT_SUCCESS;
   }
   else if (o.count("text"))
   {
      const bool color   = o.count("color");
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
   else
   {
      const std::string themes = (o.count("themes") and not o["themes"].as<std::string>().empty()) ?
	 o["themes"].as<std::string>()
	 :
	 "themes" ;

      const std::string hightscores = (o.count("scores") and not o["scores"].as<std::string>().empty()) ?
	 o["scores"].as<std::string>()
	 :
	 "hightscores.txt" ;

      return guiMain(themes, hightscores);
   }
}



/* NOTES
  -- bons paramètres pour la génération
  bonus: 0.3   -> 0.002
  bomb : 0.005 -> 0.44
  LINE : 3

  beaucoup de temps et target élevé c plus rigolo
  42 secondes et 25 coups c pas mal

  taille pas mal : 10*17

  -- crédits :

  http://opengameart.org/content/rectangle-gems-etc-16px

  http://opengameart.org/content/more-explosions

  https://soundcloud.com/musiikkisirkus/ode-to-joy-beethovens-9th
*/

