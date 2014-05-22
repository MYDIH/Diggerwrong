#include "MenuView.hh"

#include <iostream>

MenuView::MenuView(const sf::View &windowV) :
    mView(windowV)
{
    mView.SetCenter(25, 250);
    play.SetPosition(sf::Vector2f(50, 50));
    options.SetPosition(sf::Vector2f(50, 100));
    quit.SetPosition(sf::Vector2f(50, 150));
}

void MenuView::draw(sf::RenderTarget &w)
{
    sf::View dw = w.GetDefaultView();
    w.SetView(mView);

    play.draw(w);
    options.draw(w);
    quit.draw(w);

    w.SetView(dw);
}
