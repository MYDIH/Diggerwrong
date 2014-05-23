#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hh"
#include "Animation.hh"

class ScoresTab
{
public:
    static AnimationResource tabLines;

    ScoresTab();

   void setOffset(const sf::Vector2f &o);
    void show(float at);

    void draw(sf::RenderTarget &w, float now);

private:
    sf::Vector2f offset;
    Animation lines;
};
