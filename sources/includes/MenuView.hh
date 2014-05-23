#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hh"
#include "Animation.hh"
#include "ScoresTab.hh"

class MenuView
{
public:
    static AnimationResource menuCorner;
    static FontResource title;

    MenuView();

    void draw(sf::RenderTarget &w, float now);

    void setOffset(const sf::Vector2f &o);

    void show(float at);
    Button* isInButton(const sf::Vector2f &p);

    Button play;
    Button options;
    Button quit;

private:
    sf::Vector2f offset;
    AnimatedValue offBordX;
    AnimatedValue offBordY;
    AnimatedValue opacityMenu;
    AnimatedValue opacityTitle;
    AnimatedValue opacityTab;
    Animation menuCornerTopLeft;
    Animation menuCornerBottomRight;

    ScoresTab tab;
};
