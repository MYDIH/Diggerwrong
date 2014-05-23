#include "GuiController.hh"

#include <iostream>

GuiController::GuiController() :
   animOffsetMenu(10, 0),
   animOffsetConfig(0, 0),
   slideAnim(2000, 0, 5)
{}

void GuiController::draw(sf::RenderTarget & r, float now)
{
   vM.setOffset(animOffsetMenu);
   vC.setOffset(animOffsetConfig);
   //vM.draw(r);
   vC.draw(r);
}

int GuiController::tick(sf::RenderWindow & w, float now)
{
   animOffsetMenu = sf::Vector2f(slideAnim.value(now), 0);
   animOffsetConfig = sf::Vector2f(slideAnim.value(now), 0);
   need_refresh();

   return 0;
}

int GuiController::mouse_button_released(sf::RenderWindow &w, sf::Event::MouseButtonEvent & e, float now)
{
   if(!slideAnim.running(now))
   {
      sf::Vector2f vMousePos = w.ConvertCoords(e.X, e.Y);

      if(e.Button == sf::Mouse::Button::Left)
      {
	 if(vM.play.contains(vMousePos))
	 {
	 }
	 else if(vM.options.contains(vMousePos))
	 {
	    slideAnim.start(now);
	 }
	 else if(vM.quit.contains(sf::Vector2f(vMousePos.x + animOffsetMenu.x, vMousePos.y + animOffsetMenu.y)))
	    return -1;
	 return 0;
      }
   }
}
