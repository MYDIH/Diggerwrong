#include "GameChrono.hh"

// ya tout ce qu'il faut dans la sfml, alors je sait pas si c'est utile ^^

GameChrono::GameChrono(int delay)
{
    setDelay(delay);
    start();
}

GameChrono::GameChrono(const GameChrono& other)
{}

bool GameChrono::addDelay(const int & delay)
{
    if(delay > 0)
    {
        m_delay += delay;
        return true;
    }
    return false;
}

bool GameChrono::setDelay(const int & newDelay)
{
    if(newDelay > m_delay)
    {
        m_delay = newDelay;
        return true;
    }
    return false;
}

void GameChrono::start()
{
    firstTime = std::chrono::system_clock::now();
    update();
}

bool GameChrono::update()
{
    systemclock currentTime = std::chrono::system_clock::now();
    timeFromConstruction = (currentTime - firstTime);
    intTFC = timeFromConstruction.count();

    if(intTFC > m_delay)
        return false;
    return true;
}

int GameChrono::getTimeFC() const
{ return intTFC; }
