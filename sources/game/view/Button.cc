#include "Button.hh"

Button::Button() :
    sf::Shape(sf::Shape::Rectangle(0, 0, 100, 50, sf::Color(255, 0, 0), 5, sf::Color(100, 100, 100))),
    m_label("Default"),
    m_isAutoSized(true),
    m_isLabelCentered(true)
{}

Button::Button(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::String &label, const GuiResource &res,
               bool isAutoSized, bool isLabelCentered) :
    sf::Shape(sf::Shape::Rectangle(pos, size, res.forCol, res.bordW, res.bordCol)),
    m_label(label),
    m_isAutoSized(isAutoSized),
    m_isLabelCentered(isLabelCentered)
{}

Button::Button(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::String &label, const sf::Color &colBackground,
       const sf::Color &colBorder, float bordW, bool isAutoSized, bool isLabelCentered) :
    sf::Shape(sf::Shape::Rectangle(pos, size, colBackground, bordW, colBorder)),
    m_label(label),
    m_isAutoSized(isAutoSized),
    m_isLabelCentered(isLabelCentered)
{}

void Button::draw(sf::RenderTarget &w)
{
    w.Draw(*this);
    if(m_isAutoSized)
        autoSize();
    if(m_isLabelCentered)
        centerLabel();
    w.Draw(m_label);
}

bool Button::isAutoSized() const
{ return m_isAutoSized; }

bool Button::isLabelCentered() const
{ return m_isLabelCentered; }

const sf::String& Button::getLabel() const
{ return m_label; }

void Button::setSizePolicy(bool isAuto)
{ m_isAutoSized = isAuto; }

void Button::setCenteringPolicy(bool isCentered)
{ m_isLabelCentered = isCentered; }

void Button::setSize(const sf::Vector2f &s)
{
    sf::Vector2f p0pos = GetPointPosition(0);

    SetPointPosition(1, p0pos.x + s.x, p0pos.y);
    SetPointPosition(2, p0pos.x + s.x, p0pos.y + s.y);
    SetPointPosition(3, p0pos.x, p0pos.y + s.y);
}

void Button::setLabel(const sf::String &l)
{ m_label = l; }

void Button::autoSize()
{
    float w = 10 + m_label.GetRect().Right + 10;
    float h = 5 + m_label.GetRect().Bottom + 5;

    setSize(sf::Vector2f(w, h));
}

void Button::centerLabel()
{
    sf::Vector2f p0pos = GetPointPosition(0);
    sf::Vector2f p2pos = GetPointPosition(2);

    float w = p2pos.x - p0pos.x;
    float h = p2pos.y - p0pos.y;

    if(m_label.GetRect().Bottom < h && m_label.GetRect().Right < w)
        m_label.SetPosition(p0pos.x + ((w - m_label.GetRect().Right) / 2), p0pos.y + ((h - m_label.GetRect().Bottom) / 2));
}
