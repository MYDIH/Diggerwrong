#pragma once

#include "Board.hh"
#include "consts.hh"
#include "resources.hh"

#include <string>
#include <sstream>



class Board;
class Square;

struct module
{
   void (*init)(ResourcesPool & pool);
   Square * (*create)(double difficulty, unsigned width, unsigned height);
   double proba;
   bool   good;
};


// Classe abstraite. Représente une case (model du MVC).
// Est manipulé par Board dans une collection hétérogène de manière générique/unique (pas de transtypage/identification...).
class Square
{
private:
   unsigned Retain_count = 1;

public:
   virtual ~Square();

   virtual bool dig(Board & model, int x, int y
		    ,int dx=0, int dy=0, int distance=-1) = 0;

   virtual Square * clone() const = 0;


   void retain();
   void release();


   // uniquement pour le débugage ; ne sert pas d'identifiant ; n'entre pas dans la logique de la conception
   virtual const std::string toString(const int &charSet) const = 0;
};

