#pragma once

#include "EventHandler.hh"
#include "GameController.hh"
#include "Animation.hh"
#include "MenuView.hh"
#include "ConfigView.hh"
#include "squares.hh"

#include <list>

class GuiController : public EventHandler
{
public:
    GuiController(std::list<module> &modules, module &first);

    void draw(sf::RenderTarget & r, float now) override;
    int tick(sf::RenderWindow & w, float now) override;
    int mouse_moved(sf::RenderWindow & w, sf::Event::MouseMoveEvent & e, float now) override;
    int mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now) override;

private:
    MenuView vM;
    ConfigView vC;
    int screen = 1;

    GameController gControl;
    sf::Vector2f animOffsetMenu;
    sf::Vector2f animOffsetConfig;
    AnimatedValue slideAnim;
};
