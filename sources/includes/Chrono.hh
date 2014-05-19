#pragma once

#include <chrono>
#include <ctime>
#include <string>


typedef std::chrono::duration<double> seconds;
typedef std::chrono::time_point<std::chrono::system_clock> systemclock;

class Chrono
{
public:
    Chrono();
    Chrono(unsigned delay);
    Chrono(const Chrono &other);

    void addDelay(unsigned newDelay);
    bool setDelay(unsigned newDelay);
    void start();
    bool pause();
    bool update();

    unsigned getDelay() const;
    unsigned getTimeFC() const;

    static std::string getCurrentTime();

private:
    systemclock firstTime;
    systemclock workingTime;
    unsigned intFLS = 0;
    unsigned m_delay = 0;
    unsigned m_workingDelay = 0;

    bool isPaused = false;
};

