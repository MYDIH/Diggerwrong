#include <SFML/Graphics.hpp>

#include "EventHandler.hh"
#include "GuiContainer.hh"
#include "Button.hh"
#include "Animation.hh"

class MenuView
{
public:
   MenuView();
   
   void draw(sf::RenderTarget &w);
   void start(float at);
   void update(float now);

private:
   GuiContainer gContainer;
   ValueAnimation moveAnim;
   sf::Drawable *play;
   sf::Drawable *options;
   sf::Drawable *quit;  
};
