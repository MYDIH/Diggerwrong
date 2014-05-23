#include "MenuView.hh"

#include <iostream>

AnimationResource MenuView::menuCorner("gui","cadre.txt");
FontResource MenuView::title("","menu-Title.txt");

MenuView::MenuView() :
   play(sf::String("Play"), true, sf::Vector2f(170, 10)),
   options(sf::String("Options"), true, sf::Vector2f(170, -50)),
   quit(sf::String("Quit"), true, sf::Vector2f(170, -110)),
   offset(sf::Vector2f(0, 0)),
   offBordX(220, 0, 0.8),
   offBordY(130, 0, 0.8),
   opacityMenu(255, 0, 0.4),
   opacityTitle(1, 0, 0.4),
   menuCornerTopLeft(&menuCorner),
   menuCornerBottomRight(&menuCorner)
{
   play.name = "play";
   options.name = "options";
   quit.name = "quit";
   show(1);
}

void MenuView::show(float at)
{
   opacityMenu.start(at);
   menuCornerTopLeft.start(at + 0.4);
   menuCornerBottomRight.start(at + 0.4);
   offBordX.start(at + 0.4);
   offBordY.start(at + 0.4);
   opacityTitle.start(at + 1.3);
   //tab.show
   play.show(at + 1.3);
   options.show(at + 1.5);
   quit.show(at + 1.7);
}

Button* MenuView::isInButton(const sf::Vector2f &p)
{
    //std::cout << "\tMV : " << p.x << " - " << offset.y << std::endl;
   if(play.contains(sf::Vector2f(p.x - offset.x, p.y - offset.y)))
     return &play;
   else if(options.contains(sf::Vector2f(p.x - offset.x, p.y - offset.y)))
      return &options;
   else if(quit.contains(sf::Vector2f(p.x - offset.x, p.y - offset.y)))
      return &quit;
   return NULL;
}

void MenuView::setOffset(const sf::Vector2f &o)
{ offset = o; }

void MenuView::draw(sf::RenderTarget &w, float now)
{
   const sf::View & dw = w.GetView();
   sf::View mView(dw);

   float bordX =  offBordX.value(now);
   float bordY =  offBordY.value(now);

   w.SetView(mView);

   mView.Move(offset);

   play.draw(w, now);
   options.draw(w, now);
   quit.draw(w, now);

   title.draw_string(w, "Diggewrong", 0, -135, true, opacityTitle.value(now));

   //--
   mView.Move(bordX, bordY);
   menuCornerTopLeft.draw(w, now, 0, sf::Color(255, 255, 255, opacityMenu.value(now)));
   mView.Move(-bordX, -bordY);
   //--
   mView.Move(-bordX, -bordY);
   menuCornerBottomRight.draw(w, now, 180, sf::Color(255, 255, 255, opacityMenu.value(now)));
   mView.Move(bordX, bordY);
   //--
   //mView.Move()

   w.SetView(dw);
}
