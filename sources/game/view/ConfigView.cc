#include "ConfigView.hh"

#include <iostream>

ConfigView::ConfigView() :
  cancel(sf::String("Annuler"), false, sf::Vector2f(260, -30)),
  offset(sf::Vector2f(0, 0))
{
  cancel.name = "cancel";
}

void ConfigView::setOffset(const sf::Vector2f &o)
{ offset = o; }

void ConfigView::show(float at)
{
  cancel.show(at);
}

const Button* ConfigView::isInButton(const sf::Vector2f &p)
{
   if(cancel.contains(sf::Vector2f(p.x - offset.x, p.y - offset.y)))
     return &cancel;
   return NULL;
}

void ConfigView::draw(sf::RenderTarget &w, float now)
{
    const sf::View & dw = w.GetView();
    sf::View mView(dw);
    w.SetView(mView);

    mView.Move(offset);

    cancel.draw(w, now);
    //options.draw(w);
    //quit.draw(w);

    w.SetView(dw);
}
