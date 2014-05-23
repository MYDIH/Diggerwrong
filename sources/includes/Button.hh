#pragma once

#include "resources.hh"
#include "Animation.hh"

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
  static const float w;
  static const float h;
  static AnimationResource corner;
  static AnimationResource back;
  
  std::string name = "default";

  Button(sf::String label = sf::String("Default"), bool isLabelCentered = true, sf::Vector2f off = sf::Vector2f(0, 0));

  void draw(sf::RenderTarget &w, float now);

  //Accesseurs
  bool isLabelCentered() const;
  sf::Vector2f getSize() const;
  const sf::String& getLabel() const;

  void setCenteringPolicy(bool isCentered);
  bool contains(const sf::Vector2f &p) const;
  void setLabel(const sf::String &l);

  void onEnter(float at);
  void show(float at);
  void onLeave(float at);

private:
  sf::String m_label;
  sf::Vector2f offset;
  bool m_isLabelCentered;
  Animation cornerAnim;
  Animation backAnim;
  AnimatedValue opacity;
  AnimatedValue backOpacity;
  AnimatedValue cornerX;
  AnimatedValue cornerY;

  void centerLabel(const sf::Vector2f &offView);
};
