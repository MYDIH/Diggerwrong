#pragma once

#include "Square.hh"
#include "utils.hh"

#include <vector>
#include <string>
#include <sstream>


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
private:
   std::vector< std::vector<Square*> > Squares;

   point Digger;

   unsigned Target;
   unsigned Reached;

   unsigned Score;
   //unsigned Timelimit;

   unsigned Bonus_score;
   unsigned Bonus_lifes;
   //unsigned Bonus_time;

   GameState State;


   // temporaire ; la génération aléatoire sera plus complexe
   Square* newRandomSquare(double difficulty, unsigned longestside);

public:
   Board(unsigned width, unsigned height, double difficulty, unsigned target);
   Board(const Board &m);

   const Board & operator=(const Board &m);

   void copy_squares(const Board &m);
   void release_squares();

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



   // pour tests / affichage en mode texte uniquement ; n'entre pas dans la logique de la conception
   const std::string toString(const int &charSet) const;
};

