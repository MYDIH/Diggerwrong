#include "ScoresTab.hh"

#include <iostream>

AnimationResource ScoresTab::tabLines("gui", "scores.txt");

ScoresTab::ScoresTab() :
  offset(sf::Vector2f(0, 0)),
  lines(&tabLines),
  opacity(255, 0, 0.4)
{}

void ScoresTab::show(float at)
{
    opacity.start(at);
    lines.start(at + 0.4);
}

void ScoresTab::setOffset(const sf::Vector2f &o)
{ offset = o; }

void ScoresTab::draw(sf::RenderTarget &w, float now)
{
    const sf::View & dw = w.GetView();
    sf::View mView(dw);
    w.SetView(mView);

    mView.Move(offset);

    lines.draw(w, now, 0, sf::Color(255, 255, 255, opacity.value(now)), sf::Vector2f(1.8, 1.8));

    w.SetView(dw);
}
