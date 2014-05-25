#pragma once

#include "EventHandler.hh"
#include "GameController.hh"
#include "Animation.hh"
#include "MenuView.hh"
#include "ConfigView.hh"
#include "SwitchButton.hh"
#include "squares.hh"
#include "consts.hh"

#include <list>
#include <vector>

class GuiController : public EventHandler
{
public:
    GuiController(const sf::RenderTarget &r, std::vector<module> &modules, module &firstmod, module &defaultmod);

    int launchGame(sf::RenderWindow & w, float now);

    void reloadResources(const std::string &basePath);

    void draw(sf::RenderTarget & r, float now) override;
    int tick(sf::RenderWindow & w, float now) override;
    int mouse_moved(sf::RenderWindow & w, sf::Event::MouseMoveEvent & e, float now) override;
    int mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now) override;
    int resized(sf::RenderWindow & w, sf::Event::SizeEvent & e, float now);

private:
    MenuView vM;
    ConfigView vC;
    bool lGame = false;
    bool reappear = false;
    int screen = 1;
    int disableOldTickEvent = 0;
    int width;
    int height;

    GameController gControl;
    sf::Vector2f animOffsetMenu;
    sf::Vector2f animOffsetConfig;
    AnimatedValue slideAnim;
};
