#pragma once

#include "GameSquare.hh"

#include <vector>
#include <string>
#include <sstream>

namespace diggewrong
{
   class Square;

   enum GameState
   {
        WON,
        CONTINUE,
        LOST
   };

   struct point
   {
      unsigned x;
      unsigned y;
   };

   class GameModel
   {
      friend class Square;

   private:
      std::vector< std::vector<Square*> > Board;

      point Digger;

      unsigned Target;
      unsigned Reached;

      unsigned Score;
      //unsigned Lifes;
      //unsigned Timelimit;

      unsigned Bonus_score;
      unsigned Bonus_lifes;
      //unsigned Bonus_time;

      GameState State = CONTINUE;

      Square* newRandomSquare(double difficulty, unsigned longestside); // temporaire

   public:
      GameModel(unsigned width, unsigned height, double difficulty
		,unsigned target, unsigned lifes);

      ~GameModel();

      //void play();
      //void pause();

      GameState move(int dx, int dy);

      const std::string toString() const;
      static std::string intToString(const int &e);

      void addBonusScore(unsigned score);
      void addBonusLifes(unsigned lifes);


      bool isOutOfRange(int x, int y) const;
      bool digAt(int x, int y
		 ,int dx = 0, int dy = 0, int distance = -1);

      void replaceSquare(int x, int y, Square * newone);

      //Accesseurs
      unsigned getTarget()  const;
      unsigned getReached() const;
      unsigned getScore()   const;
      //unsigned getLifes  () const;
      point    getDigger()  const;
      
   };
}

