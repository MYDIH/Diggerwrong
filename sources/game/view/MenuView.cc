#include "MenuView.hh"

#include <iostream>

MenuView::MenuView() :
  play(sf::Vector2f(-260, 30)),
  options(sf::Vector2f(-260, 80)),
  quit(sf::Vector2f(-260, 130)),
  offset(sf::Vector2f(0, 0))
{}

void MenuView::setOffset(const sf::Vector2f &o)
{ offset = o; }

void MenuView::draw(sf::RenderTarget &w)
{
    const sf::View & dw = w.GetView();
    sf::View mView(dw);
    w.SetView(mView);

    mView.Move(offset);

    play.draw(w);
    options.draw(w);
    quit.draw(w);

    w.SetView(dw);
}
