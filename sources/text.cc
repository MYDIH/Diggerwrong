#include "text.hh"

#include <ctime>

///////////////afficherMenu()///////////////////
//Description : Cette Fonction affiche le menu//
////////////////////////////////////////////////
void afficherMenu()
{
   std::cout << "Pour se déplacer dans les 8 directions : O,N,E,S,NO,NE,SO,SE ou 4,8,6,2,7,9,3,1" << std::endl
	     << "Quitter le jeu : Q" << std::endl;
}

///////////////toLowerCase()////////////////////
//Paramètre : "&s" : Référence vers la string //
//            a modifier                      //
//Description : Décapitalise une string       //
////////////////////////////////////////////////
void toLowerCase(std::string &s)
{
   std::locale loc;
   for (std::string::size_type i=0; i<s.length(); ++i)
      s[i] = std::tolower(s[i],loc);
}

///////////////toLowerCase()////////////////////
//Paramètre : "*model" : pointeur vers le     //
//            model                           //
//Description : Fonction permettant de gérer  //
//              le menu en appelant les       //
//              méthodes adéquates            //
//Valeur de Retour : Booléen a vrai si le jeu //
//                   continu, a faux sinon    //
////////////////////////////////////////////////
GameState menu(Board *model, unsigned&lifes)
{
   std::string tempStr = "";
   bool rightStr = false;
   GameState state;

   afficherMenu();
   std::cin >> tempStr;

   while(!rightStr) // Tant que la string envoyée est invalide
   {
      rightStr = true;
      toLowerCase(tempStr); // On Décapitalise

      if(tempStr == "o" || tempStr == typeToString<int>(4))
	 state = model->move(0, -1);
      else if(tempStr == "n" || tempStr == typeToString<int>(8))
	 state = model->move(-1, 0);
      else if(tempStr == "e" || tempStr == typeToString<int>(6))
	 state = model->move(0, 1);
      else if(tempStr == "s" || tempStr == typeToString<int>(2))
	 state = model->move(1, 0);
      else if(tempStr == "no" || tempStr == typeToString<int>(7))
	 state = model->move(-1, -1);
      else if(tempStr == "ne" || tempStr == typeToString<int>(9))
	 state = model->move(-1, 1);
      else if(tempStr == "se" || tempStr == typeToString<int>(3))
	 state = model->move(1, 1);
      else if(tempStr == "so" || tempStr == typeToString<int>(1))
	 state = model->move(1, -1);
      else if(tempStr == "q")
	 return QUIT; // On quitte le jeu
      else
      {
	 std::cout << "Veuillez entrer O,N,E,S,NO,NE,SO,SE,4,8,6,2,7,9,3,1 ou Q !" << std::endl;
	 std::cin >> tempStr;
	 rightStr = false;
      }
   }

   switch(state)
   {
      case WON :
	 std::cout << "-------------------------Vous Avez Gagné !-------------------------" << std::endl;
	 break;
      case LOST :
	 std::cout << "-------------------------Vous Avez Perdu !-------------------------" << std::endl;
	 lifes--;
	 if(lifes < 1)
	    std::cout << "-----------------------------Game Over-----------------------------" << std::endl;
	 break;
      case CONTINUE :
	 break;
      default : {}
   }

   return state;
}

//////////////////printModel()////////////////////
//Paramètre : "*model" : pointeur sur le modèle //
//            à afficher                        //
//Description : Affiche un modèle               //
//////////////////////////////////////////////////
void printModel(Board *model, unsigned lifes, unsigned globalScore, unsigned level, int charSet)
{
   std::string tempTarget = "Cible a atteindre : " + typeToString<int>(model->getTarget());        //
   std::string tempReached = "Nombre de déplacement : " + typeToString<int>(model->getReached());  //
   std::string tempScore = "Votre Score : " + typeToString<int>(model->getScore());                //
   std::string tempScoreBonus = "Votre Score bonus : " + typeToString<int>(model->getBonusScore());//  On créé les lignes de statu
   std::string lifesBonus = "Vos vies bonus : " + typeToString<int>(model->getBonusLifes());
   std::string lifeStr = "Vies Restantes : " + typeToString<int>(lifes);                             //
   std::string levelStr = "Niveau n°" + typeToString<int>(level) + " (difficulté: " + typeToString<int>(inv(level)*100) + "%)";                                     //
   std::string globalScoreStr = "Votre Score totale : " + typeToString<int>(globalScore);          //


   // On rends le résultat potable en ramenant chaque ligne de statu à la même longueur
   while(tempTarget.length() < DECALAGE_CONSOLE || tempReached.length() < DECALAGE_CONSOLE || tempScore.length() < DECALAGE_CONSOLE || tempScoreBonus.length() < DECALAGE_CONSOLE || lifesBonus.length() < DECALAGE_CONSOLE || globalScoreStr.length() < DECALAGE_CONSOLE)
   {
      if(tempTarget.length() < DECALAGE_CONSOLE)
	 tempTarget += ' ';
      if(tempReached.length() < DECALAGE_CONSOLE)
	 tempReached += ' ';
      if(tempScore.length() < DECALAGE_CONSOLE)
	 tempScore += ' ';
      if(tempScoreBonus.length() < DECALAGE_CONSOLE)
	 tempScoreBonus += ' ';
      if(lifesBonus.length() < DECALAGE_CONSOLE)
	 lifesBonus += ' ';
      if(globalScoreStr.length() < DECALAGE_CONSOLE)
	 globalScoreStr += ' ';
   }

   // On inscrit des précisions sur les représentations au sein de la matrice a droite du statu
   tempTarget += "|    \"" + CHARS[charSet][1] + "x" + CHARS[charSet][2] + "\" Représente une case avec un bonus";
   tempReached += " |    \"" + CHARS[charSet][3] + "\" Représente la position du mineur";
   tempScore += "|    \"   \" Représente une case déjà visitée";
   tempScoreBonus += "|    \"" + CHARS[charSet][0] + "\" Représente une bombe";

   // On affiche le tout
   std::cout << model->toString(charSet) << std::endl
	     << std::endl
	     << tempTarget << std::endl
	     << tempReached << std::endl
	     << tempScore << std::endl
	     << tempScoreBonus << std::endl
	     << lifesBonus << std::endl
	     << std::endl
	     << levelStr << std::endl
	     << lifeStr << std::endl
	     << globalScoreStr<< std::endl << std::endl;
}

GameState try_level(int charSet, unsigned & lifes, unsigned & score, unsigned level, const Board & orig)
{
   Board atry(orig);

   while (true)
   {
      printModel(&atry, lifes, score, level, charSet);
	 
      switch (menu(&atry, lifes))
      {
	 case WON:
	    score += atry.getScore() + atry.getBonusScore();
	    lifes += atry.getBonusLifes();
	    return WON;
	    
	 case LOST:
	 {
	    if (lifes < 1)
	       return LOST;
	    else
	       atry = orig;
	 }
	 break;
	    
	 case QUIT:
	    return QUIT;

	 default:;
      }

   }
}

GameState play(int charSet)
{
   unsigned score = 0;
   unsigned lifes = 5;
   unsigned level = 1;

   while (true)
   {
      Board board(18,18, inv(level), 22);

      switch ( try_level(charSet, lifes, score, level, board) )
      {
	 case WON:
	    level++;
	    break;
	    
	 case LOST:
	    return LOST;
	    
	 case QUIT:
	    return QUIT;

	 default:;
      }
   }
}

int textMain(int charSet)
{
   /*for(unsigned i = 1; i < 20; i++)
     {
     std::cout << i << "::" << typeToString<int>(inv(i)*100) << "% -> ";
     }
     std::cout << std::endl;*/


   srand(time(NULL));

   while (play(charSet) != QUIT);

   return EXIT_SUCCESS;
}

