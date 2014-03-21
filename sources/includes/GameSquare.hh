#pragma once

#include "GameModel.hh"

#include <string>
#include <sstream>

namespace diggewrong
{
   class GameModel;

   class Square
   {
   private:
      unsigned Retain_count = 1;

   public:
      virtual ~Square();

      virtual int value()                const; // -1 si non implémenté
      virtual const std::string & type() const = 0;
      // bomb, normal, bonus, digged...

      virtual bool dig(GameModel & model, int x, int y
		       ,int dx=0, int dy=0, int distance=-1) = 0;
      virtual const std::string toString() const = 0;

      void retain();
      void release();
   };


   class Normal : public Square
   {
   private:
      std::string Type = "normal";
      unsigned Value;

   public:
      Normal(double difficulty, unsigned longestside);

      int value()                const override;
      const std::string & type() const override;
      const std::string toString() const override;

      bool dig(GameModel & model, int x, int y
	       ,int dx, int dy, int distance) override;

   };

   class Digged : public Square
   {
   private:
      std::string Type = "digged";

   public:
      const std::string & type() const override;
      const std::string toString() const override;

      bool dig(GameModel & model, int x, int y
	       ,int dx, int dy, int distance) override;

   };


   class Bomb : public Square
   {
   private:
      std::string Type = "bomb";

   public:
      const std::string & type() const override;
      const std::string toString() const override;

      bool dig(GameModel & model, int x, int y
	       ,int dx, int dy, int distance) override;

   };


}

