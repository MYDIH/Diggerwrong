#include "ScoresTab.hh"

#include <iostream>

AnimationResource ScoresTab::tabLines("gui", "scores.txt");

ScoresTab::ScoresTab() :
  offset(sf::Vector2f(0, 0)),
  lines(&tabLines)
{}

void ScoresTab::setOffset(const sf::Vector2f &o)
{ offset = o; }

void ScoresTab::show(float at)
{
  lines.start(at);
}

void ScoresTab::draw(sf::RenderTarget &w, float now)
{
    const sf::View & dw = w.GetView();
    sf::View mView(dw);
    w.SetView(mView);

    mView.Move(offset);

    lines.draw(w, now);

    w.SetView(dw);
}
