#include "GameController.hh"
#include "utils.hh"
#include "consts.hh"

#include <cfloat>

AnimationResource GameController::Star1("", "star1.txt");
AnimationResource GameController::Star2("", "star2.txt");

FontResource GameController::Big_font("", "big-font.txt");

SoundResource GameController::Youwin(  "", "youwin.txt");
SoundResource GameController::Tryagain("", "tryagain.txt");
SoundResource GameController::Levelup( "", "levelup.txt");
SoundResource GameController::Gameover("", "gameover.txt");

GameController::GameController( const std::vector<module> & modules
                                ,const module & firstmod
                                ,const module & defaultmod )

    :Try( {&Try1,&Try2} )
,View( {&View1,&View2} )

,Width(0)
,Height(0)
,Target(0)
,Timelimit(0)
,Rank(0)
,Lifes(0)
,Score(0)

,Backgrounded(0,1,0.3, EASE_IN_OUT<15>)

,Waiting(false)
,How_to(false)
,How_to_mode(false)

,Big_flash(26,1,6)
,Cursor(1,0,0.5)
,State(CONTINUE)
,Slide(0,1,0.37, EASE_IN_OUT<10>)

,Back1(0,1,7, EASE_IN_OUT<16>)
,Back2(0,1,32, EASE_IN_OUT<10>)

,Modules(modules)
,First(firstmod)
,Default(defaultmod)
{
    Slide.start(-10);
    Back1.start(0);
    Back2.start(0);

    new_game();
}

void GameController::new_game(unsigned width, unsigned height, unsigned target, float timelimit
                              ,unsigned last_rank, unsigned lifes, unsigned score )

{
   Width  = width;
   Height = height;
   Target = target;
   Timelimit = timelimit;

   Rank   = last_rank;
   Lifes  = lifes;
   Score  = score;

   Waiting = false;
   How_to  = false;
   How_to_mode = false;
   Big_flash.start(FLT_MAX);
   State = CONTINUE;
   
   Level.generate( Width,Height,Target,Timelimit
		   ,inv(Rank), Modules, First, Default );
   
   
   *(Try.second) = Level;
   View.second->observe( Try.second, 0 );
}

void GameController::start(float at)
{
    Backgrounded.set_start_value(1);
    Backgrounded.set_end_value(0);
    Backgrounded.start(at);

    if (State == CONTINUE)
       Try.second -> start();
}
void GameController::stop(float at)
{
    Backgrounded.set_start_value(0);
    Backgrounded.set_end_value(1);
    Backgrounded.start(at);

    Try.second -> pause();
}

int GameController::tick(sf::RenderWindow & w, float now)
{
    View.second->tick(now);

    if ( (Try.second->tick()) )
    {
        if (Lifes >= 1)
        {
            State = TRY_AGAIN;
        }
        else
        {
            State = GAME_OVER;
        }
    }


    if (State != CONTINUE)
    {
        if (not Waiting and View.second->finished())
        {
            Try.second -> pause();
            Waiting = true;
            switch (State)
            {
            case GAME_OVER:
                Gameover.play_new();
                break;
            case TRY_AGAIN:
                Tryagain.play_new();
                break;
            case WON:
                Youwin.play_new();
                break;

            default:
                ;
            }

            Big_flash.start(now);
        }

        else if (Waiting and not Big_flash.running(now))
        {
            Big_flash.start(now);
            if (not How_to and State == GAME_OVER)
            {
                How_to = true;
                How_to_mode = true;
                *(Try.second) = Level;
                View.second -> observe(Try.second, now);
                //Try.second -> start();
                Try.second -> resolve();
            }
        }

        else if (How_to and View.second->finished())
            How_to = false;


        if (Waiting and State == GAME_OVER and not Cursor.running(now))
            Cursor.start(now);
    }


    if (not Back1.running(now))
    {
        Back1.swap();
        Back1.start(now);
    }

    if (not Back2.running(now))
    {
        Back2.swap();
        Back2.start(now);
    }

    need_refresh();
    return 0;
}

void GameController::draw_stars(sf::RenderTarget & r, float now
                                ,float dx, float dy
                                ,float var1, float var2)
{
    const sf::View & orig = r.GetView();

    sf::View offset = orig;
    offset.Move(dx, dy);

    sf::View v      = offset;

    r.SetView(v);

    {
        // -- AFFICHAGE des étoiles
        offset.Zoom(var2 * 0.7 + 0.3);

        v = offset;
        v.Move(var1*800-400, var2*800-400);
        r.Draw( Star1.frame(0,0) );

        v = offset;
        v.Move(var2*500-250, -(var1*500-250));
        r.Draw( Star2.frame(0,0) );

        v = offset;
        v.Move(- (var1*1000-500), var2*1000-500);
        r.Draw( Star1.frame(0,0) );

        // --
        offset.Zoom(var1 * 0.6 + 0.4);
        // --

        v = offset;
        v.Move(- (var1*1200-600), - (var2*1200-600));
        r.Draw( Star2.frame(0,0) );

        v = offset;
        v.Move(var1*1200-600, var2*1200-600);
        r.Draw( Star1.frame(0,0) );

        // --
        //offset.Zoom(var2 * 0.5 + 0.5);
        // --

        v = offset;
        v.Move(var2*300-150, - (var1*300-150));
        r.Draw( Star2.frame(0,0) );

        v = offset;
        v.Move(-(var2*500-250), -(var1*500-250));
        r.Draw( Star1.frame(0,0) );

        // --
    }

    r.SetView(orig);
}

const unsigned color = 70;
void GameController::draw(sf::RenderTarget & r, float now)
{
    const sf::View & orig = r.GetView();
    sf::View view = orig;
    r.SetView(view);

    const float width = r.GetWidth();
    const float height = r.GetHeight();

    if (Backgrounded.value(now))
        view.Zoom((1-Backgrounded.value(now)) * 0.3 + 0.7);

    r.Clear(sf::Color(color,color,color));


    const float b1 = Back1.value(now);
    const float b2 = Back2.value(now);
    draw_stars(r,now,  0, 0, b1, b2);
    draw_stars(r,now,   width/1.6,  height/1.6, b1, b2);
    draw_stars(r,now,   width/1.6, -height/1.6, b2, b1);
    draw_stars(r,now,  -width/1.6,  height/1.6, b1, b2);
    draw_stars(r,now,  -width/1.6, -height/1.6, b2, b1);


    r.Draw( sf::Shape::Rectangle(-width, -height, width, height
                                 ,sf::Color(color,color,color
                                            ,220 * (1-Backgrounded.value(now)) )) );


    // -- AFFICHAGE plateau en cours
    {
        sf::View v = view;
        r.SetView(v);
        v.Move(-Slide.value(now) * width, 0);
        //const float z = (1-Slide.value(now));
        //v.Zoom(z*z*z * 0.5 + 0.5);

        View.second->draw(r,now);

        r.SetView(view);
    }
    // --




    if (Slide.running(now))
    {
        // -- AFFICHAGE plateau précédent
        sf::View v = view;
        r.SetView(v);
        v.Move((1-Slide.value(now)) * width, 0);
        //const float z = Slide.value(now);
        //v.Zoom(z*z*z * 0.5 + 0.5);

        View.first->draw(r,now);

        r.SetView(view);
        // --
    }



    const float hw = View.second -> get_width()  /2;
    const float hh = View.second -> get_height() /2;

    // -- AFFICHAGE scores
    {
        view.Move(hw,-hh);

        const std::string gvalues = ( std::to_string(Rank)
                                      + "\n" + std::to_string(Score)
                                      + "\n" + std::to_string(Lifes) );

        const sf::Vector2f gsize = BoardView::Score_value_font.draw_string(r, gvalues, 0,0,false);

        BoardView::Score_font.draw_string(r,("niveaux\n"
                                             "score totale\n"
                                             "vies\n"), gsize.x+10,0,false);



        view.Move(-hw,hh);
    }
    // --



    // -- AFFICHAGE flash
    if ( Waiting and (int)Big_flash.value(now)%5 != 0 )
        switch (State)
        {
        case GAME_OVER:
            Big_font.draw_string(r, "GAME OVER !");
            break;

        case TRY_AGAIN:
            Big_font.draw_string(r, "TRY AGAIN !");
            break;

        case WON:
            Big_font.draw_string(r, "YOU WIN !");
            break;

        default:
            ;

        }
    // --

    if (How_to_mode)
        Big_font.draw_string(r, "how to"
                             ,0, Big_font.font().GetGlyph('0').Rectangle.GetHeight(),true,0.80);


    // AFFICHAGE tu nom du joueur
    if (Waiting and State == GAME_OVER)
    {
        const int lfonth = BoardView::Score_font.font().GetGlyph('0').Rectangle.GetHeight();
        const int fonth  = BoardView::Score_value_font.font().GetGlyph('0').Rectangle.GetHeight();

        const sf::Vector2f size = BoardView::Score_font.draw_string(r, "quel est ton nom ?  "
                                  ,-hw, -hh -lfonth -BAR -10, false,0.9);

        const std::string cursor = (Cursor.value(now)>0.5)? "<" : "";

        BoardView::Score_value_font.draw_string(r, ">" + Player_name + cursor
                                                ,-hw +size.x, -hh -fonth -BAR -10, false, 1);
    }


    if (Backgrounded.value(now))
        r.Draw( sf::Shape::Rectangle(-width, -height, width, height
                                     ,sf::Color(30,30,30
                                                ,240 * Backgrounded.value(now) )) );



    r.SetView(orig);
}


int GameController::mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now)
{
   if (Slide.running(now) or Backgrounded.value(now))
      return 0;


   if (Waiting)
   {
      switch (State)
      {
	 case GAME_OVER:

	    break;

	 case TRY_AGAIN:
	    Lifes--;
	    
	    std::swap(Try.first,Try.second);
	    std::swap(View.first,View.second);

	    *(Try.second) = Level;
	    View.second -> observe( Try.second, now + 0.2 );

	    State = CONTINUE;
	    Big_flash.start(FLT_MAX);
	    Slide.start(now);

	    Try.second -> start();
	    Waiting = false;
	    break;

	 case WON:
	    Rank++;
	    Score += Try.second->getScore();
	    Score += Try.second->getBonusScore();
	    Lifes += Try.second->getBonusLifes();

	    Level.generate( Width,Height,Target,Timelimit
			    ,inv(Rank), Modules, First, Default );

	    std::swap(Try.first,Try.second);
	    std::swap(View.first,View.second);

	    *(Try.second) = Level;
	    View.second -> observe( Try.second, now + 0.2 );

	    State = CONTINUE;
	    Big_flash.start(FLT_MAX);
	    Slide.start(now);

	    Levelup.play_new();

	    Try.second -> start();	    
	    Waiting = false;
	    break;

	 default:;
      }

      return 0;
   }




   
   const sf::Vector2f click = w.ConvertCoords(e.X, e.Y);
   const point square = board_coords(click.x, click.y);
   
   const point digger = Try.second->getDigger();
   
   const int dx = -(digger.x - square.x);
   const int dy = -(digger.y - square.y);
   

   if ( dx >= -1 and dx <= 1 and dy >= -1 and dy <= 1 )
   {
      switch ( Try.second->move(dx,dy) )
      {
	 case GameState::LOST:
	    if (Lifes >= 1)
	    {
	       State = TRY_AGAIN;
	    }
	    else
	    {
	       State = GAME_OVER;
	    }
	    break;
	    
	    
	 case GameState::WON:
	    State = WON;
	    break;
	    
	 default:;
      }
   }

   return 0;
}


int GameController::text_entered(sf::RenderWindow & w, sf::Event::TextEvent e, float now)
{
    if (Slide.running(now) or Backgrounded.value(now))
        return 0;


    if (Waiting and State == GAME_OVER)
    {
        if (e.Unicode == '\b' and Player_name.size() > 0)
            Player_name.pop_back();

        else if (e.Unicode >= 32 and e.Unicode <= 126)
            Player_name += static_cast<char>(e.Unicode);
    }



    return 0;
}

int GameController::key_pressed(sf::RenderWindow & w, sf::Event::KeyEvent & e, float now)
{
    if (Slide.running(now) or Backgrounded.value(now))
        return 0;


    if ( Waiting and State == GAME_OVER )
    {
        if (e.Code == sf::Key::Code::Return)
        {
            // enregistrement score... blabla
            std::map<std::string,std::string> f;
            parseFile(f, "highScores.txt");

	    try
	    {
	       if ( std::stoi(f[Player_name]) < (int)Score )
		  f[Player_name] = std::to_string(Score);
	    }
	    catch(const std::invalid_argument &ia)
	    {
	       f[Player_name] = std::to_string(Score);
	    }

            writeFile(f, "highScores.txt");


            new_game(Width,Height,Target,Timelimit
                     ,0,2,0);

            stop(now);
            return 3;
        }
    }
    else if (e.Code == sf::Key::Code::Space
             or e.Code == sf::Key::Code::Pause)
    {
        stop(now);
        return 2;
    }

    return 0;
}

point GameController::board_coords(float x, float y)
{
    point p;

    p.x = - (-(Width*SQUARE_WIDTH)/2   - x);
    p.y = - (-(Height*SQUARE_HEIGHT)/2 - y);

    p.x = p.x / SQUARE_WIDTH;
    p.y = p.y / SQUARE_HEIGHT;

    return p;
}
