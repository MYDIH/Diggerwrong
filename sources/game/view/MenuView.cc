#include "MenuView.hh"

#include <iostream>

MenuView::MenuView() :
    play("Play", sf::Vector2f(170, 10)),
    options("Options", sf::Vector2f(170, -50)),
    quit("Quit", sf::Vector2f(170, -110))
{
   play.name = "play";
   options.name = "options";
   quit.name = "quit";
}

void MenuView::show(float at)
{
    if(opacityView.end_value() != 255)
        opacityView.swap();
    if(opacityTitle.end_value() != 1)
        opacityTitle.swap();
   opacityView.start(at);
   viewCornerOne.start(at + 0.4);
   viewCornerTwo.start(at + 0.4);
   offBordX.start(at + 0.4);
   offBordY.start(at + 0.4);
   opacityTitle.start(at + 1.3);
   tab.show(at + 1.7);
   play.show(at + 1.3);
   options.show(at + 1.5);
   quit.show(at + 1.7);
}

void MenuView::hide(float at)
{
    if(opacityView.value(at) == 255)
    {
        opacityView.swap();
        opacityTitle.swap();
        opacityView.start(at);
        opacityTitle.start(at);
        tab.hide(at);
        play.hide(at);
        options.hide(at);
        quit.hide(at);
    }
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
   viewCornerOne.draw(w, now, 0, sf::Color(255, 255, 255, opacityView.value(now)));
   mView.Move(-bordX, -bordY);
   //--
   mView.Move(-bordX, -bordY);
   viewCornerTwo.draw(w, now, 180, sf::Color(255, 255, 255, opacityView.value(now)));
   mView.Move(bordX, bordY);
   //--
   mView.Move(-120, -45);
   tab.draw(w, now);
   mView.Move(120, 45);
   //--

   w.SetView(dw);
}
