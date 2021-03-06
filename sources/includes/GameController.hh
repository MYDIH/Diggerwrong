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
   Board Level;

   Board Try1;
   Board Try2;
   std::pair<Board*,Board*> Try;
   
   BoardView View1;
   BoardView View2;
   std::pair<BoardView*,BoardView*> View;

   unsigned Width;
   unsigned Height;
   unsigned Target;
   float Timelimit;
   
   unsigned Rank;
   unsigned Lifes;
   unsigned Score;

   std::string Player_name;

   AnimatedValue Backgrounded;

   bool Waiting;
   bool How_to;
   bool How_to_mode;
   AnimatedValue Big_flash;
   AnimatedValue Cursor;
   enum
   {
      GAME_OVER
      ,TRY_AGAIN
      ,WON
      ,CONTINUE

   } State;

   AnimatedValue Slide;

   AnimatedValue Back1;
   AnimatedValue Back2;

   const std::vector<module> & Modules;
   const module & First;
   const module & Default;

public:
   static AnimationResource Star1;
   static AnimationResource Star2;

   static FontResource Big_font;

   static SoundResource Youwin;
   static SoundResource Tryagain;
   static SoundResource Levelup;
   static SoundResource Gameover;




   GameController( const std::vector<module> & modules
		   ,const module & firstmod
		   ,const module & defaultmod );

   point board_coords(float x, float y);

   void start(float at);
   void stop(float at);

   void new_game(unsigned width = 17, unsigned height = 10, unsigned target = 25, float timelimit = 42
		 ,unsigned last_rank = 0, unsigned lifes = 2, unsigned score = 0 );


   void draw_stars(sf::RenderTarget & r, float now
		   ,float dx, float dy
		   ,float var1, float var2);

   /* Evenements */
   void draw(sf::RenderTarget & r, float now) override;
   int tick(sf::RenderWindow & w, float now)  override;
   int mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now) override;

   int text_entered(sf::RenderWindow & w, sf::Event::TextEvent e, float now) override;

   //int resized(sf::RenderWindow & w, sf::Event::SizeEvent & e, float now) override;
   int key_pressed(sf::RenderWindow & w, sf::Event::KeyEvent & e, float now) override; // debug
};
