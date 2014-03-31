#include "GameModel.hh"
#include "GameObserver.hh"
#include <cstdlib>
#include <string>
#include <iostream>
#include <locale>
#include "Constantes.hh"

using namespace diggewrong;

///////////////afficherMenu()///////////////////
//Description : Cette Fonction affiche le menu//
//Auteur : Nicolas Gomez                      //
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

        if(tempStr == "o" || tempStr == GameModel::intToString(4))
            state = model->move(0, -1);
        else if(tempStr == "n" || tempStr == GameModel::intToString(8))
            state = model->move(-1, 0);
        else if(tempStr == "e" || tempStr == GameModel::intToString(6))
            state = model->move(0, 1);
        else if(tempStr == "s" || tempStr == GameModel::intToString(2))
            state = model->move(1, 0);
        else if(tempStr == "no" || tempStr == GameModel::intToString(7))
            state = model->move(-1, -1);
        else if(tempStr == "ne" || tempStr == GameModel::intToString(9))
            state = model->move(-1, 1);
        else if(tempStr == "se" || tempStr == GameModel::intToString(3))
            state = model->move(1, 1);
        else if(tempStr == "so" || tempStr == GameModel::intToString(1))
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
//Auteur : Nicolas Gomez                        //
//////////////////////////////////////////////////
void printModel(GameModel *model, int lifes)
{
    std::string tempTarget = "Cible a atteindre : " + GameModel::intToString(model->getTarget());       //
    std::string tempReached = "Nombre de déplacement : " + GameModel::intToString(model->getReached()); //  On créé les lignes de statu
    std::string tempScore = "Votre Score : " + GameModel::intToString(model->getScore());               //
    std::string tempLifes = "Vies Restantes : " + GameModel::intToString(lifes);                        //

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
    tempTarget += "|    \"" + COLOR_YELLOW + "☾x☽" + RESET_COLOR + "\" Représente une case avec un bonus";
    tempReached += " |    \" ☉ \" Représente la position du mineur";
    tempScore += "|    \"   \" Représente une case déjà visitée";
    tempLifes += "|    \" " + COLOR_RED + "☠" + RESET_COLOR + " \" Représente une bombe";

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

    realModel = new GameModel(18, 18, 0.2, 10);

    while(state != QUIT)
    {
        modelForGame = new GameModel(*realModel);

        printModel(modelForGame, lifes);
        state = menu(modelForGame, lifes);

        while(state == CONTINUE && lifes > 0) // Tantque le jeu continu => Le joueur ne souhaite pas quitter et il n'a pas perdu
        {
            printModel(modelForGame, lifes);
            state = menu(modelForGame, lifes);
        }

        if((lifes < 1 && state != QUIT) || state == WON)
        {
            if(state != WON)
                lifes = 5;
            delete realModel;

            realModel = new GameModel(18, 18, 0.2, 10, 5);
        }

        delete modelForGame;
    }

    delete realModel;

    return EXIT_SUCCESS;
}


