#include "GameModel.hh"
#include "GameObserver.hh"
#include <cstdlib>
#include <iostream>

using namespace diggewrong;

int main()
{
    GameModel *model = new GameModel(18, 18, 0.5, 1, 5);
    std::cout << model->toString().c_str() << std::endl;
    std::cout << "Programme démarré" << std::endl;

    return EXIT_SUCCESS;
}


