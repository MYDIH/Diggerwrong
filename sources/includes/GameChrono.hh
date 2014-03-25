#pragma once

#include <chrono>
#include <ctime>
#include <string>

typedef std::chrono::duration<double> seconds;
typedef std::chrono::time_point<std::chrono::system_clock> systemclock;

class GameChrono
{
    public:
        GameChrono();
        GameChrono(int delay);
        GameChrono(const GameChrono& other);

        bool addDelay(const int & newDelay);
        bool setDelay(const int & newDelay);
        void start();
        bool update();
        int getTimeFC() const;

        static std::string getCurrentTime();

    private:
        systemclock firstTime;
        seconds timeFromConstruction;
        int intTFC = 0;
        int m_delay = 0;
};
