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
    labelOpacity(255, 0, 0.4),
    cornerX(Button::w/2, 7, 0.8),
    cornerY(Button::h/2, 7, 0.8)
{
    m_label.SetColor(sf::Color(180, 180, 180));
}

void Button::show(float at)
{
    opacity.start(at);
    cornerX.start(at + 0.4);
    cornerY.start(at + 0.4);
    labelOpacity.start(at + 1.2);
}

void Button::onEnter(float at)
{
    if(!backOpacity.running(at) && labelOpacity.value(at) == 255) // Si l'animation est terminée et si le menu est affiché
    {
        if(toggle)
        {
            if(backOpacity.start_value() != 0) // Si ce n'est pas la première fois qu'on anime
                backOpacity.restart_at_end(255);
            backOpacity.start(at);
            toggle = false;
        }
    }
}

void Button::onLeave(float at)
{
    if(!backOpacity.running(at) && labelOpacity.value(at) == 255) // Si l'animation est terminée et si le menu est affiché
    {
        if(!toggle)
        {
            backOpacity.restart_at_end(0);
            backOpacity.start(at);
            toggle = true;
        }
    }
}

void Button::draw(sf::RenderTarget &w, float now)
{
    const sf::View & dw = w.GetView();
    sf::View mView(dw);

    float cornX =  cornerX.value(now);
    float cornY =  cornerY.value(now);

    w.SetView(mView);

    mView.Move(offset);
    m_label.SetColor(sf::Color(m_label.GetColor().r, m_label.GetColor().g, m_label.GetColor().b, labelOpacity.value(now)));

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
    if(m_isLabelCentered)
    {
        mView.Move(m_label.GetRect().Right / 2, m_label.GetRect().Bottom / 2);
        w.Draw(m_label);
        mView.Move(-(m_label.GetRect().Right / 2), -(m_label.GetRect().Bottom / 2));
    }
    else
        w.Draw(m_label);

    w.SetView(dw);
}

bool Button::isLabelCentered() const
{
    return m_isLabelCentered;
}

bool Button::contains(const sf::Vector2f &p) const
{
    return sf::Rect<float>(-offset.x - Button::w / 2, -offset.y - Button::h / 2, -offset.x + Button::w / 2, -offset.y + Button::h / 2).Contains(p.x, p.y); /*std::cout << "\t\tB : " << -offset.x - Button::w / 2 << ", " << -offset.y - Button::h / 2 << ", " << -offset.x + Button::w / 2 << ", " << -offset.y + Button::h / 2 << std::endl; */
}

sf::Vector2f Button::getSize() const
{
    return sf::Vector2f(Button::w, Button::h);
}

const sf::String& Button::getLabel() const
{
    return m_label;
}

void Button::setCenteringPolicy(bool isCentered)
{
    m_isLabelCentered = isCentered;
}

void Button::setLabel(const sf::String &l)
{
    m_label = l;
}
