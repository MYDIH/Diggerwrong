#include "GameModel.hh"
#include "GameObserver.hh"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace diggewrong;

void afficherMenu()
{
    std::cout << "Pour se déplacer dans les 8 directions : O,N,E,S,NO,NE,SO,SE" << std::endl
              << "Quitter le jeu : Q" << std::endl;
}

bool menu(GameModel *model)
{
    std::string tempStr = "";

    afficherMenu();
    std::cin >> tempStr;

    if(tempStr == "O")
    {}
    else if(tempStr == "N")
    {}
    else if(tempStr == "E")
    {}
    else if(tempStr == "S")
    {}
    else if(tempStr == "NO")
    {}
    else if(tempStr == "NE")
    {}
    else if(tempStr == "SO")
    {}
    else if(tempStr == "SE")
    {}
    else if(tempStr == "Q")
        return true;
    else
    {
        std::cout << "Veuillez entrer O,N,E,S,NO,NE,SO,SE ou Q !" << std::endl;
        menu(model);
    }
}

void printModel(GameModel *model)
{
    std::cout << model->toString() << std::endl
              << std::endl
              << "Cible a atteindre : " + GameModel::intToString(model->getTarget()) << std::endl
              << "Nombre de déplacement : " + GameModel::intToString(model->getReached()) << std::endl
              << "Votre Score : " + GameModel::intToString(model->getScore()) << std::endl
              << "Vies Restantes : " + GameModel::intToString(model->getLifes()) << std::endl << std::endl;
}

int main()
{
    bool quit = false;
    GameModel *model = new GameModel(20, 20, 0.2, 20, 5);

    while(!quit)
    {
        printModel(model);
        quit = menu(model);
    }

    delete model;

    return EXIT_SUCCESS;
}


