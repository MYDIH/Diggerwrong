#pragma once

#include "GameObservable.hh"

#include <vector>

namespace diggewrong
{
   namespace square
   {
      class Square
      {
      public:
	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      };

      class Normal : public Square
      {
      private:
	 unsigned m_num;

      public:
	 Normal(unsigned num);

	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      };

      class Bomb : public Square
      {
      public:
	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      };

      class Digged : public Square
      {
      public:
	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      };

      class HiddenBonus : public Normal
      {
      private:
	 unsigned m_score, m_time, m_lifes;

      public:
	 HiddenBonus(unsigned score, unsigned time, unsigned lifes);

	 virtual bool dig(unsigned & score, unsigned & time, unsigned & lifes) const;
      };
   }


   class GameModel: public GameObservable
   {
   private:
      std::vector<square::Square*> board;

      square::Square* newRandomSquare(double difficulty);

   public:
      GameModel(unsigned width, unsigned height);
   };
}
