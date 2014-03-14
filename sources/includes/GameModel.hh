#pragma once

#include "GameObservable.hh"

#include <vector>

namespace diggewrong
{

   struct point
   {
      unsigned x;
      unsigned y;
   };
   

   class Square
   {
   public:
      virtual ~Square() = 0;

      virtual int value()           const = 0; // -1 si non supporté
      virtual const string & type() const = 0;
      // bomb, normal, bonus, digged...

      virtual point dig(GameModel & model, unsigned x, unsigned y
			,unsigned dx=0, unsigned dy=0, int distance=-1) = 0;
   };

   class Normal : public Square
   {
   private:
      string Type = "normal";
      unsigned Value;

   public:
      Normal(double difficulty);
      ~Normal() override;

      int value()           const override; // -1 si non supporté
      const string & type() const override;
      // bomb, normal, bonus, digged...

      point dig(unsigned dx, unsigned dy, int distance
		,GameModel & model, unsigned x, unsigned y) override;

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

