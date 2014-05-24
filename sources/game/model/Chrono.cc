#include "Chrono.hh"


Chrono::Chrono()
{
    setDelay(60);
    //start();
}

Chrono::Chrono(unsigned delay)
{
    setDelay(delay);
    //start();
}

Chrono::Chrono(const Chrono &other) :
    Chrono(other.m_delay)
{}

void Chrono::addDelay(unsigned delay)
{
    m_delay += delay;
    m_workingDelay += delay;
}

bool Chrono::setDelay(unsigned newDelay)
{
    if(newDelay > m_delay)
    {
        m_delay = newDelay;
        m_workingDelay = m_delay;
        return true;
    }
    return false;
}

void Chrono::start()
{
   if(!isPaused)
    {
        firstTime = std::chrono::system_clock::now();
        workingTime = firstTime;
    }
    else
    {
        workingTime = std::chrono::system_clock::now();
        isPaused = false;
    }
}

bool Chrono::update()
{
    systemclock currentTime = std::chrono::system_clock::now();
    seconds timeSeconds = (currentTime - workingTime);
    intFLS = timeSeconds.count();

    if(!isPaused)
       m_workingDelay -= intFLS;

    if(m_workingDelay < 1)
        return false;
    return true;
}

bool Chrono::pause()
{
    if(update() && !isPaused)
    {
        isPaused = true;
        return true;
    }
    return false;
}

unsigned Chrono::getTimeFC() const
{
    systemclock currentTime = std::chrono::system_clock::now();
    seconds TFC = (currentTime - firstTime);

    return TFC.count();
}

