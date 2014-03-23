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
GameState menu(GameModel *model, int &lifes)
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

        if(tempStr == "o")
            state = model->move(0, -1);
        else if(tempStr == "n")
            state = model->move(-1, 0);
        else if(tempStr == "e")
            state = model->move(0, 1);
        else if(tempStr == "s")
            state = model->move(1, 0);
        else if(tempStr == "no")
            state = model->move(-1, -1);
        else if(tempStr == "ne")
            state = model->move(-1, 1);
        else if(tempStr == "so")
            state = model->move(1, -1);
        else if(tempStr == "se")
            state = model->move(1, 1);
        else if(tempStr == "q")
            return QUIT; // On quitte le jeu
        else
        {
            std::cout << "Veuillez entrer O,N,E,S,NO,NE,SO,SE ou Q !" << std::endl;
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
//Auteur : Nicolas Gomez                        //
//////////////////////////////////////////////////
void printModel(GameModel *model)
{
    std::string tempTarget = "Cible a atteindre : " + GameModel::intToString(model->getTarget());       //
    std::string tempReached = "Nombre de déplacement : " + GameModel::intToString(model->getReached()); //  On créé les lignes de statu
    std::string tempScore = "Votre Score : " + GameModel::intToString(model->getScore());               //

    // je vient de percuter mais le nombre de vies ne peut pas être gérer au niveau du model
    // puisque une instance du model ne représente qu'un niveau
    std::string tempLifes = "Vies Restantes : kikou ! retrouve moi ligne <123>";// GameModel::intToString(model->getLifes());            //

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
    tempTarget += "|    \"{x}\" Représente une case avec un bonus";
    tempReached += " |    \"@@@\" Représente la position du mineur";
    tempScore += "|    \"   \" Représente une case déjà visitée";
    tempLifes += "|    \" * \" Représente une bombe";

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
    GameModel *realModel;
    GameModel *modelForGame;
    GameState state = CONTINUE;
    int lifes = 5;

    realModel = new GameModel(20, 20, 0.2, 10, 5);

    while(state != QUIT)
    {
        modelForGame = new GameModel(*realModel);

        printModel(modelForGame);
        state = menu(modelForGame, lifes);

        while(state != QUIT && state != LOST && lifes > 0) // Tantque le jeu continu => Le joueur ne souhaite pas quitter et il n'a pas perdu
        {
            printModel(modelForGame);
            state = menu(modelForGame, lifes);
        }

        if(lifes < 1 && state != QUIT)
        {
            std::cout << "-------------------------Game Over-------------------------" << std::endl;

            lifes = 5;
            delete realModel;
            realModel = new GameModel(20, 20, 0.2, 10, 5);
        }

        delete modelForGame;
    }

    delete realModel;

    return EXIT_SUCCESS;
}


