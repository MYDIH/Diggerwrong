#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Button.hh"
#include "Animation.hh"

class ScoresTab
{
public:
    static AnimationResource tabLines;

    ScoresTab();

    void show(float at);

    void setOffset(const sf::Vector2f &o);

    void draw(sf::RenderTarget &w, float now);

private:
    sf::Vector2f offset;
    Animation lines;
    AnimatedValue opacity;

    std::vector<sf::String> names;
    std::vector<sf::String> scores;
};
