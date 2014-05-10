#pragma once

#include "Board.hh"
#include "consts.hh"

#include <string>
#include <sstream>


class Board;

// Classe abstraite. Représente une case (model du MVC).
// Est manipulé dans une collection hétérogène de manière générique/unique (pas de transtypage/identification...).
class Square
{
private:
   unsigned Retain_count = 1;

public:
   virtual ~Square();

   virtual bool dig(Board & model, int x, int y
		    ,int dx=0, int dy=0, int distance=-1) = 0;

   virtual Square * clone() = 0;


   void retain();
   void release();


   // uniquement pour le débugage ; ne sert pas d'identifiant ; n'entre pas dans la logique de la conception
   virtual const std::string toString(const int &charSet) const = 0;
};

