#pragma once

#include "resources.hh"

#include <SFML/Graphics.hpp>

class Button : public sf::Shape
{
public:
  Button();
  Button(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::String &label, const GuiResource &res,
	 bool isAutoSized = true, bool isLabelCentered = true);
  Button(const sf::Vector2f &pos, const sf::Vector2f &size, const sf::String &label, const sf::Color &colBackground = sf::Color(255, 0, 0),
	 const sf::Color &colBorder = sf::Color(100, 100, 100), float bordW = 2, bool isAutoSized = true, bool isLabelCentered = true);

  void draw(sf::RenderTarget &w);

  //Accesseurs
  bool isAutoSized() const;
  bool isLabelCentered() const;
  const sf::String& getLabel() const;

  void setSizePolicy(bool isAuto);
  void setCenteringPolicy(bool isCentered);
  void setSize(const sf::Vector2f &s);
  void setLabel(const sf::String &l);
  void setPosition(const sf::Vector2f &pos);

private:
  sf::String m_label;
  bool m_isAutoSized;
  bool m_isLabelCentered;

  void autoSize();
  void centerLabel();
};
