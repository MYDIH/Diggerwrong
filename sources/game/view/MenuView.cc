#include "MenuView.hh"

#include <iostream>

MenuView::MenuView() :
  moveAnim(200)
{
  play = new Button;
  options = new Button;
  quit = new Button;

  play->SetPosition(0, 0);
  gContainer.addDrawable(play);
  options->SetPosition(0, 50);
  gContainer.addDrawable(options);
  quit->SetPosition(0, 100);
  gContainer.addDrawable(quit);

  //gContainer.SetPosition(sf::Vector2f(200, 0));
}

void MenuView::draw(sf::RenderTarget &w)
{
  gContainer.draw(w);
}

void MenuView::start(float at)
{
  moveAnim.start(at);
}

void MenuView::update(float now)
{
  gContainer.Move(sf::Vector2f(moveAnim.getValue(now), 0));
}
