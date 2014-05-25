#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hh"
#include "SwitchButton.hh"
#include "Animation.hh"
#include "GuiViews.hh"

class ConfigView : public GuiViews
{
public:
    ConfigView();

    void show(float at) override;
    void hide(float at) override;

    Button* isInButton(const sf::Vector2f &p) override;

    void draw(sf::RenderTarget &w, float now) override;

    Button cancel;
    SwitchButton themesSelect;

private:
    sf::Vector2f offsetThemeLabel;
    AnimatedValue offsetThemeLabelAnim;
};
