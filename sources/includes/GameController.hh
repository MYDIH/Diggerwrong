#pragma once

#include "EventHandler.hh"
#include "Board.hh"
#include "BoardView.hh"
#include "resources.hh"
#include "Animation.hh"

#include <tuple>


class GameController : public EventHandler
{
private:
   Board     Level;

   Board Try1;
   Board Try2;
   std::pair<Board*,Board*> Try;
   
   BoardView View1;
   BoardView View2;
   std::pair<BoardView*,BoardView*> View;

   unsigned Width;
   unsigned Height;
   unsigned Target;
   
   unsigned Rank;
   unsigned Lifes;
   unsigned Score;


   bool Waiting;
   AnimatedValue Big_flash;
   enum
   {
      GAME_OVER
      ,TRY_AGAIN
      ,WON
      ,CONTINUE

   } State;

   AnimatedValue Slide;

public:
   static FontResource Big_font;

   const std::list<module> * Modules;
   const module * First;

   GameController();

   point board_coords(float x, float y);

   void new_game(unsigned width, unsigned height, unsigned target
		 ,unsigned last_rank, unsigned lifes, unsigned score );


   /* Evenements */
   void draw(sf::RenderTarget & r, float now) override;
   int tick(sf::RenderWindow & w, float now)  override;
   int mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now) override;
   //int resized(sf::RenderWindow & w, sf::Event::SizeEvent & e, float now) override;
   int key_released(sf::RenderWindow & w, sf::Event::KeyEvent & e, float now) override; // debug
};
