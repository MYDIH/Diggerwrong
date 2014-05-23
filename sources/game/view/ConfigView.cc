#include "ConfigView.hh"

#include <iostream>

ConfigView::ConfigView() :
  //play(sf::Vector2f(-260, 30)),
  //options(sf::Vector2f(-260, 80)),
  //quit(sf::Vector2f(-260, 130)),
  offset(sf::Vector2f(0, 0))
{}

void ConfigView::setOffset(const sf::Vector2f &o)
{ offset = o; }

void ConfigView::draw(sf::RenderTarget &w, float now)
{
    const sf::View & dw = w.GetView();
    sf::View mView(dw);
    w.SetView(mView);

    mView.Move(offset);

    //play.draw(w);
    //options.draw(w);
    //quit.draw(w);

    w.SetView(dw);
}
