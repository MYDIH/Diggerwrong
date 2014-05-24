#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hh"
#include "Animation.hh"

class GuiViews
{
public:
    static AnimationResource viewCorner;
    static FontResource title;

    GuiViews();

    virtual void draw(sf::RenderTarget &w, float now) = 0;

    virtual void show(float at) = 0;
    virtual void hide(float at) = 0;

    virtual Button* isInButton(const sf::Vector2f &p) = 0;

    void setOffset(const sf::Vector2f &o);
    bool appearedOrHidden(float at);

    const sf::Vector2f& getSize() const;

protected:
    sf::Vector2f offset;
    sf::Vector2f size;
    AnimatedValue offBordX;
    AnimatedValue offBordY;
    AnimatedValue opacityView;
    AnimatedValue opacityTitle;
    Animation viewCornerOne;
    Animation viewCornerTwo;
};
