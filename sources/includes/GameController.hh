#pragma once

#include "EventHandler.hh"
#include "Board.hh"
#include "BoardView.hh"



class GameController : public EventHandler
{
private:
   Board     Level;
   BoardView View;
   
   unsigned Lifes;
   unsigned Score;

   unsigned Target;

public:
   GameController();
   
   void new_game(unsigned last_rank, unsigned lifes, unsigned score
		 ,unsigned target);


   /* Evenements */
   void draw(sf::RenderTarget & r, float now) override;
   int tick(sf::RenderWindow & w, float now)  override;
   int mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now) override;
   //int resized(sf::RenderWindow & w, sf::Event::SizeEvent & e, float now) override;
};
