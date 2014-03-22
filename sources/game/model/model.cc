#include "GameModel.hh"

#include <cstdlib>
#include <iostream>
#include <sstream>

// debug
#include <iostream>


using namespace diggewrong;

GameModel::GameModel(unsigned width, unsigned height, double difficulty
                     ,unsigned target, unsigned lifes)


    :Board(width)

    ,Digger({width/2, height/2})

,Target(target)
,Reached(0)

,Score(0)
,Lifes(lifes)
//,Timelimit(timelimit)

,Bonus_score(0)
,Bonus_lifes(0)
//,Bonus_time(0)
{
    const unsigned longestside = (width > height) ? width : height;

    for (auto & column : Board)
    {
        column.resize(height);

        for (auto & square : column)
        {
            square = newRandomSquare(difficulty, longestside);
        }
    }
}

GameModel::~GameModel()
{
    for (auto & column : Board)
    {
        for (auto & square : column)
        {
            square -> release();
        }
    }
}


bool GameModel::move(int dx, int dy)
{
    if ( digAt(Digger.x + dx, Digger.y + dy, dx, dy) )
    {

        return true;
    }
    else
    {

        return false;
    }
}

Square* GameModel::newRandomSquare(double difficulty, unsigned longestside)
{
    double r = rand() / (double) RAND_MAX;

    double pbomb  = difficulty * 0.7;
    double pbonus = (1 - pbomb) * 0.2;

    if      (r <= pbomb)          return new Normal(difficulty, longestside); // bomb
    else if (r <= pbomb + pbonus) return new Normal(difficulty, longestside); // bonus
    else                          return new Normal(difficulty, longestside); // normal
}

const std::string GameModel::toString() const
{
    std::string tempString = "";
    std::string tempLine = "";

    tempLine += "+";
    for(unsigned i=0; i<Board[0].size(); i++)
        tempLine += "---";
    tempLine += "+";

    //std::cout << Board[Digger.x][Digger.y]->toString() << std::endl;
    for(unsigned i=0; i<Board.size(); i++)
    {
        for(unsigned j=0; j<Board[i].size(); j++)
        {
            if(i == 0 && j == 0)
                tempString += tempLine + '\n';
            if(j == 0)
                tempString += '|';
            if(i == Digger.x && j == Digger.y)
                tempString += "@@@";
            else
                tempString += Board[i][j]->toString();
            if(j == Board[i].size() - 1)
                tempString += '|';
        }
        tempString += '\n';
        if(i == Board.size() - 1)
            tempString += tempLine;
    }

    return tempString;
}

std::string GameModel::intToString(const int &e)
{
    std::ostringstream stream;
    stream << e;

    return stream.str();
}

bool GameModel::isOutOfRange(int x, int y)
{
    if (x >= 0 and y >= 0 and (unsigned)x < Board.size() and (unsigned)y < Board[0].size())
        return false;
    else
        return true;
}

bool GameModel::digAt(int x, int y
                      ,int dx, int dy, int distance)
{
    if (isOutOfRange(x,y))
    {
        return true;
    }
    else
    {
        Digger.x = x;
        Digger.y = y;
        Reached++;

        Board[x][y] -> retain();
        const bool ret = Board[x][y] -> dig(*this,x,y,dx,dy,distance);
        Board[x][y] -> release();

        return ret;
    }
}

void GameModel::addScore(unsigned score)
{
    Score += score;
}

void GameModel::replaceSquare(int x, int y, Square * newone)
{
    if (not isOutOfRange(x,y))
    {
        Board[x][y] -> release();
        newone -> retain();
        Board[x][y] = newone;
    }
}

// Accesseurs :

unsigned GameModel::getTarget()
{
    return Target;
}

unsigned GameModel::getReached()
{
    return Reached;
}

unsigned GameModel::getScore()
{
    return Score;
}

unsigned GameModel::getLifes()
{
    return Lifes;
}
