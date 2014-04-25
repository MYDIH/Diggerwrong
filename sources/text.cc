#include "Board.hh"
#include "consts.hh"

#include <cstdlib>
#include <string>
#include <iostream>
#include <locale>


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
GameState menu(Board *model, int &lifes)
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

        if(tempStr == "o" || tempStr == Board::intToString(4))
            state = model->move(0, -1);
        else if(tempStr == "n" || tempStr == Board::intToString(8))
            state = model->move(-1, 0);
        else if(tempStr == "e" || tempStr == Board::intToString(6))
            state = model->move(0, 1);
        else if(tempStr == "s" || tempStr == Board::intToString(2))
            state = model->move(1, 0);
        else if(tempStr == "no" || tempStr == Board::intToString(7))
            state = model->move(-1, -1);
        else if(tempStr == "ne" || tempStr == Board::intToString(9))
            state = model->move(-1, 1);
        else if(tempStr == "se" || tempStr == Board::intToString(3))
            state = model->move(1, 1);
        else if(tempStr == "so" || tempStr == Board::intToString(1))
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
void printModel(Board *model, int lifes, const int &charSet)
{
    std::string tempTarget = "Cible a atteindre : " + Board::intToString(model->getTarget());       //
    std::string tempReached = "Nombre de déplacement : " + Board::intToString(model->getReached()); //  On créé les lignes de statu
    std::string tempScore = "Votre Score : " + Board::intToString(model->getScore());               //
    std::string tempLifes = "Vies Restantes : " + Board::intToString(lifes);                        //

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
    tempTarget += "|    \"" + CHARS[charSet][1] + "x" + CHARS[charSet][2] + "\" Représente une case avec un bonus";
    tempReached += " |    \"" + CHARS[charSet][3] + "\" Représente la position du mineur";
    tempScore += "|    \"   \" Représente une case déjà visitée";
    tempLifes += "|    \"" + CHARS[charSet][0] + "\" Représente une bombe";

    // On affiche le tout
    std::cout << model->toString(charSet) << std::endl
              << std::endl
              << tempTarget << std::endl
              << tempReached << std::endl
              << tempScore << std::endl
              << tempLifes << std::endl << std::endl;
}


int textMain()
{
    //srand(time(NULL)); // Initialise l'aléatoire
    Board *realModel;
    Board *modelForGame;
    GameState state = CONTINUE;
    int lifes = 5;
    int charSet = 1;

    realModel = new Board(18, 18, 0.2, 10);

    while(state != QUIT)
    {
        modelForGame = new Board(*realModel);

        printModel(modelForGame, lifes, charSet);
        state = menu(modelForGame, lifes);

        while(state == CONTINUE && lifes > 0) // Tantque le jeu continu => Le joueur ne souhaite pas quitter et il n'a pas perdu
        {
            printModel(modelForGame, lifes, charSet);
            state = menu(modelForGame, lifes);
        }

        if((lifes < 1 && state != QUIT) || state == WON)
        {
            if(state != WON)
                lifes = 5;
            delete realModel;

            realModel = new Board(18, 18, 0.2, 10);
        }

        delete modelForGame;
    }

    delete realModel;

    return EXIT_SUCCESS;
}

