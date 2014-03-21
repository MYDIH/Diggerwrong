#include "GameModel.hh"
#include "GameObserver.hh"
#include <cstdlib>
#include <string>
#include <iostream>
#include <locale>

const unsigned DECALAGE_CONSOLE = 35; // Distance entre Statu et Explications

using namespace diggewrong;

///////////////afficherMenu()///////////////////
//Description : Cette Fonction affiche le menu//
//Auteur : Nicolas Gomez                      //
////////////////////////////////////////////////
void afficherMenu()
{
    std::cout << "Pour se déplacer dans les 8 directions : O,N,E,S,NO,NE,SO,SE" << std::endl
              << "Quitter le jeu : Q" << std::endl;
}

///////////////toLowerCase()////////////////////
//Paramètre : "&s" : Référence vers la string //
//            a modifier                      //
//Description : Décapitalise une string       //
//Auteur : Nicolas Gomez                      //
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
//Auteur : Nicolas Gomez                      //
////////////////////////////////////////////////
bool menu(GameModel *model)
{
    std::string tempStr = "";
    bool found = false;

    afficherMenu();
    std::cin >> tempStr;

    while(!found) // Tant que la string envoyée est invalide
    {
        found = true;
        toLowerCase(tempStr); // On Décapitalise

        if(tempStr == "o")
            model->move(-1, 0);
        else if(tempStr == "n")
            model->move(0, -1);
        else if(tempStr == "e")
            model->move(1, 0);
        else if(tempStr == "s")
            model->move(0, 1);
        else if(tempStr == "no")
            model->move(-1, -1);
        else if(tempStr == "ne")
            model->move(1, -1);
        else if(tempStr == "so")
            model->move(-1, 1);
        else if(tempStr == "se")
            model->move(1, 1);
        else if(tempStr == "q")
            return false; // On quitte le jeu
        else
        {
            std::cout << "Veuillez entrer O,N,E,S,NO,NE,SO,SE ou Q !" << std::endl;
            std::cin >> tempStr;
            found = false;
        }
    }

    return true;
}

//////////////////printModel()////////////////////
//Paramètre : "*model" : pointeur sur le modèle //
//            à afficher                        //
//Description : Affiche un modèle               //
//Auteur : Nicolas Gomez                        //
//////////////////////////////////////////////////
void printModel(GameModel *model)
{
    std::string tempTarget = "Cible a atteindre : " + GameModel::intToString(model->getTarget());       //
    std::string tempReached = "Nombre de déplacement : " + GameModel::intToString(model->getReached()); //  On créé les lignes de statu
    std::string tempScore = "Votre Score : " + GameModel::intToString(model->getScore());               //
    std::string tempLifes = "Vies Restantes : " + GameModel::intToString(model->getLifes());            //

    // On rends le résultat potable en ramenant chaque ligne de statu à la même longueur
    while(tempTarget.length() < DECALAGE_CONSOLE || tempReached.length() < DECALAGE_CONSOLE || tempScore.length() < DECALAGE_CONSOLE || tempLifes.length() < DECALAGE_CONSOLE)
    {
        if(tempTarget.length() < DECALAGE_CONSOLE)
            tempTarget += ' ';
        if(tempReached.length() < DECALAGE_CONSOLE)
            tempReached += ' ';
        if(tempScore.length() < DECALAGE_CONSOLE)
            tempScore += ' ';
        if(tempLifes.length() < DECALAGE_CONSOLE)
            tempLifes += ' ';
    }

    // On inscrit des précisions sur les représentations au sein de la matrice a droite du statu
    tempTarget += '|';
    tempReached += " |    \"@@@\" Représente la position du mineur dans la Matrice";
    tempScore += "|    \"   \" Représente une case déjà visitée";
    tempLifes += '|';

    // On affiche le tout
    std::cout << model->toString() << std::endl
              << std::endl
              << tempTarget << std::endl
              << tempReached << std::endl
              << tempScore << std::endl
              << tempLifes << std::endl << std::endl;
}

int main()
{
    srand(time(NULL)); // Initialise l'aléatoire
    GameModel *model = new GameModel(20, 20, 0.2, 20, 5);

    printModel(model);

    while(menu(model)) // Tantque le jeu continu => Le joueur ne souhaite pas quitter
        printModel(model);

    delete model;

    return EXIT_SUCCESS;
}


