#pragma once

#include "Square.hh"
#include "Chrono.hh"
#include "utils.hh"

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

class Square;

enum GameState
{
   WON,
   CONTINUE,
   LOST,

   QUIT // temporaire ; ne devrai pas être lié à Board
};

struct point
{
   unsigned x;
   unsigned y;
};



// représente le plateau de jeu (model du MVC) ; voir le rapport de conception pour quelques explications
class Board
{
public:
   struct change
   {
      enum
      {
	 SCORE
	 ,SCORE_BONUS
	 ,LIFE_BONUS
	 ,MOVE
	 ,LOST
	 ,WON
	 ,REPLACE
	 ,DESTRUCT

      } type;

      point location;

      union
      {
	 struct
	 {
	    unsigned delta;
	    unsigned total;

	 } value;
	 // SCORE* LIFE* MOVE (Reached)

	 Square * square;
	 // REPLACE

      } infos;
   };

   class Observer
   {
   private:
      std::queue<Board::change> Changes;
   protected:
      void pop();
      const Board::change * front();
   public:
      void push(const Board::change&);
      virtual bool care(const Board::change&);
   };



private:
   std::vector< std::vector<Square*> > Squares;
   std::set<Observer*> Observers;

   point Digger;

   unsigned Target;
   unsigned Reached;

   unsigned Score;
   unsigned Timelimit;

   unsigned Bonus_score;
   unsigned Bonus_lifes;
   unsigned Bonus_time;

   GameState State;

   Chrono levelChrono;

   void copySquares(const Board &m);
   void releaseSquares();

   void notify(const change&) const;

// temporaire ; la génération aléatoire sera plus complexe
   Square* newRandomSquare(double difficulty, unsigned longestside);

public:
   Board(unsigned width, unsigned height, double difficulty, unsigned target, unsigned timeLimit);
   Board(const Board &m);

   const Board & operator=(const Board &m);

   ~Board();

   GameState move(int dx, int dy);

// interface pour Square
   void addScore(unsigned score);
   void addBonusScore(unsigned score);
   void addBonusLifes(unsigned lifes);
   bool isOutOfRange(int x, int y) const;
   bool digAt(int x, int y
	      ,int dx = 0, int dy = 0, int distance = -1);
   void replaceSquare(int x, int y, Square * newone);

// accesseurs
   unsigned getTarget()  const;
   unsigned getReached() const;
   unsigned getScore()      const;
   unsigned getBonusScore() const;
   unsigned getBonusLifes() const;
   point    getDigger() const;
   unsigned getWidth()  const;
   unsigned getHeight() const;
   const Square * getSquare(unsigned x, unsigned y) const;


   void registerObserver(Observer* o);
   void unregisterObserver(Observer* o);


// pour tests / affichage en mode texte uniquement ; n'entre pas dans la logique de la conception
   const std::string toString(const int &charSet) const;
};

