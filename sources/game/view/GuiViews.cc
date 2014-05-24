#include "GuiViews.hh"

AnimationResource GuiViews::viewCorner("gui","cadre.txt");
FontResource GuiViews::title("","menu-Title.txt");

GuiViews::GuiViews() :
   offset(sf::Vector2f(0, 0)),
   offBordX(220, 0, 0.8),
   offBordY(130, 0, 0.8),
   opacityView(255, 0, 0.4),
   opacityTitle(1, 0, 0.4),
   viewCornerOne(&viewCorner),
   viewCornerTwo(&viewCorner)
{
    size = sf::Vector2f(offBordX.end_value() * 2, offBordY.end_value() * 2);
}

void GuiViews::setOffset(const sf::Vector2f &o)
{ offset = o; }

const sf::Vector2f& GuiViews::getSize() const
{ return size; }

bool GuiViews::appearedOrHidden(float at)
{ return !opacityView.running(at); }
