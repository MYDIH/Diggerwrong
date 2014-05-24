#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hh"
#include "Animation.hh"
#include "ScoresTab.hh"
#include "GuiViews.hh"

class MenuView : public GuiViews
{
public:
    MenuView();

    void draw(sf::RenderTarget &w, float now) override;

    void show(float at) override;
    void hide(float at) override;

    Button* isInButton(const sf::Vector2f &p) override;

    Button play;
    Button options;
    Button quit;

private:
    AnimatedValue opacityTab;

    ScoresTab tab;
};
