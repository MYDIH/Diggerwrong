#pragma once

#include "resources.hh"
#include "Animation.hh"
#include "utils.hh"

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
  static const float w;
  static const float h;
  static AnimationResource corner;
  static AnimationResource back;
  static AnimationResource foreg;
  static FontResource labelFont;

  std::string name = "default";

  Button(const std::string &label = "Default", sf::Vector2f off = sf::Vector2f(0, 0));

  void draw(sf::RenderTarget &w, float now);

  //Accesseurs
  bool isLabelCentered() const;
  sf::Vector2f getSize() const;
  const std::string& getLabel() const;

  void setCenteringPolicy(bool isCentered);
  bool contains(const sf::Vector2f &p) const;
  void setLabel(const std::string &l);

  void onEnter(float at);
  void show(float at);
  void hide(float at);
  void onLeave(float at);

private:
  std::string m_label;
  sf::Vector2f offset;
  bool m_isLabelCentered;
  bool toggle = true;
  Animation cornerAnim;
  Animation backAnim;
  Animation foregAnim;
  AnimatedValue opacity;
  AnimatedValue inOpacity;
  AnimatedValue labelOpacity;
  AnimatedValue cornerX;
  AnimatedValue cornerY;
};
