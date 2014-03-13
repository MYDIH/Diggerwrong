#pragma once

#include "GameObservable.hh"

#include <vector>

namespace diggewrong
{
   namespace square
   {
      // juste pour les tests
      class Square
      {
      public:
	 Square(double difficulty);
	 virtual ~Square();

	 virtual unsigned distance() const;
	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      };

      // class Normal : public Square
      // {
      // private:
      // 	 unsigned m_num;

      // public:
      // 	 Normal(unsigned num);

      // 	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      // };

      // class Bomb : public Square
      // {
      // public:
      // 	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      // };

      // class Digged : public Square
      // {
      // public:
      // 	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      // };

      // class HiddenBonus : public Normal
      // {
      // private:
      // 	 unsigned m_score, m_time, m_lifes;

      // public:
      // 	 HiddenBonus(unsigned score, unsigned time, unsigned lifes);

      // 	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      // };
   }

   struct point
   {
      unsigned x;
      unsigned y;
   };

   class GameModel: public GameObservable
   {
   private:
      std::vector< std::vector<square::Square*> > Board;

      point Digger;

      unsigned Target;
      unsigned Reached;

      unsigned Score;
      unsigned Lifes;
      //unsigned Timelimit;

      unsigned Bonus_score;
      unsigned Bonus_lifes;
      //unsigned Bonus_time;


      square::Square* newRandomSquare(double difficulty);

   public:
      GameModel(unsigned width, unsigned height, double difficulty
		,unsigned target, unsigned lifes, unsigned timelimit);

      ~GameModel();

      //void play();
      //void pause();

      bool move(char dx, char dy);
      

   };
}

