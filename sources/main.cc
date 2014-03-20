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
    bool found = false;

    afficherMenu();
    std::cin >> tempStr;

    while(!found)
    {
        found = true;

        if(tempStr == "O")
            model->move(-1, 0);
        else if(tempStr == "N")
            model->move(0, -1);
        else if(tempStr == "E")
            model->move(1, 0);
        else if(tempStr == "S")
            model->move(0, 1);
        else if(tempStr == "NO")
            model->move(-1, -1);
        else if(tempStr == "NE")
            model->move(1, -1);
        else if(tempStr == "SO")
            model->move(-1, 1);
        else if(tempStr == "SE")
            model->move(1, 1);
        else if(tempStr == "Q")
            return false;
        else
        {
            std::cout << "Veuillez entrer O,N,E,S,NO,NE,SO,SE ou Q !" << std::endl;
            std::cin >> tempStr;
            found = false;
        }
    }

    return true;
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
    srand(time(NULL));
    GameModel *model = new GameModel(20, 20, 0.2, 20, 5);

    printModel(model);

    while(menu(model))
        printModel(model);

    delete model;

    return EXIT_SUCCESS;
}


