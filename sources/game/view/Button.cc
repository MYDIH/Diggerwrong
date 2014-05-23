#include "Button.hh"

AnimationResource Button::corner("gui/buttons", "corners.txt");
AnimationResource Button::back("gui/buttons", "back.txt");
const float Button::w = 118;
const float Button::h = 38.7;

Button::Button(sf::String label, bool isLabelCentered, sf::Vector2f off) :
   m_label(label),
   offset(off),
   m_isLabelCentered(isLabelCentered),
   cornerAnim(&corner),
   backAnim(&back),
   opacity(255, 0, 0.4),
   backOpacity(255, 0, 0.4),
   cornerX(Button::w/2, 7, 0.8),
   cornerY(Button::h/2, 7, 0.8)
{
   show(5);
}

void Button::show(float at)
{
   opacity.start(at);
   cornerX.start(at + 0.4);
   cornerY.start(at + 0.4);
}

void Button::onEnter(float at)
{
   if(backOpacity.start_value() != 0)
      backOpacity.restart_at_end(255);
   backOpacity.start(at);
}

void Button::onLeave(float at)
{
   backOpacity.restart_at_end(0);
   backOpacity.start(at);
}

void Button::draw(sf::RenderTarget &w, float now)
{
   const sf::View & dw = w.GetView();
   sf::View mView(dw);

   float cornX =  cornerX.value(now);
   float cornY =  cornerY.value(now);
    
   w.SetView(mView);

   mView.Move(offset);
   
   //--
   mView.Move(cornX, cornY);
   cornerAnim.draw(w, now, 0, sf::Color(255, 255, 255, opacity.value(now)));
   mView.Move(-cornX, -cornY);
   //--
   mView.Move(-cornX, cornY);
   cornerAnim.draw(w, now, -90, sf::Color(255, 255, 255, opacity.value(now)));
   mView.Move(cornX, -cornY);
   //--
   mView.Move(-cornX, -cornY);
   cornerAnim.draw(w, now, 180, sf::Color(255, 255, 255, opacity.value(now)));
   mView.Move(cornX, cornY);
   //--
   mView.Move(cornX, -cornY);
   cornerAnim.draw(w, now, 90, sf::Color(255, 255, 255, opacity.value(now)));
   mView.Move(-cornX, cornY);
   //--
   mView.Move(-1, -1);
   backAnim.draw(w, now, 0, sf::Color(255, 255, 255, backOpacity.value(now)));
   mView.Move(1, 1);
   //--

   w.SetView(dw);
}

bool Button::isLabelCentered() const
{ return m_isLabelCentered; }

bool Button::contains(const sf::Vector2f &p) const
{ return sf::Rect<float>(-offset.x - Button::w / 2, -offset.y - Button::h / 2, -offset.x + Button::w / 2, -offset.y + Button::h / 2).Contains(p.x, p.y); }

sf::Vector2f Button::getSize() const
{ return sf::Vector2f(Button::w, Button::h); }

const sf::String& Button::getLabel() const
{ return m_label; }

void Button::setCenteringPolicy(bool isCentered)
{ m_isLabelCentered = isCentered; }

void Button::setLabel(const sf::String &l)
{ m_label = l; }

void Button::centerLabel(const sf::Vector2f &offView)
{
   //  if(m_label.GetRect().Right >
}
