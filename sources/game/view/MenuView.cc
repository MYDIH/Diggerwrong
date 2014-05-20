#include "MenuView.hh"

MenuView::MenuView() :
    sf::View(sf::FloatRect(100, 100, 100, 100))
{}

MenuView::MenuView(const sf::FloatRect &rect) :
    sf::View(rect)
{}

MenuView::MenuView(const sf::View &view) :
    sf::View(view)
{
    play.SetPosition(100, 100);
}

void MenuView::draw(sf::RenderTarget &w)
{
    play.draw(w);
    //options.draw(w);
    //quit.draw(w);
}
