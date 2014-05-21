#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Button.hh"

class GuiContainer
{
public:
    void addDrawable(sf::Drawable *d);
    sf::Drawable* removeLast();
    void clear();
    void SetPosition(const sf::Vector2f &pos);
    void Move(const sf::Vector2f &pos);

    void draw(sf::RenderTarget &w);

private:
    std::vector<sf::Drawable*> objs;
    sf::Vector2f posContainer;
};
