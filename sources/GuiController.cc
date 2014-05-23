#include "GuiController.hh"

#include <iostream>

GuiController::GuiController(std::list<module> &modules, module &first) :
    animOffsetMenu(0, 0),
    animOffsetConfig(-2000, 0),
    slideAnim(2000, 0, 0.8)
{
    gControl.Modules = &modules;
    gControl.First = &first;

    gControl.new_game(25, 15, 20, 2, 5, 0);
}

void GuiController::draw(sf::RenderTarget & r, float now)
{
    vM.setOffset(animOffsetMenu);
    vC.setOffset(animOffsetConfig);
    vM.draw(r, now);
    vC.draw(r, now);
}

int GuiController::tick(sf::RenderWindow & w, float now)
{
    if(slideAnim.running(now) || slideAnim.remaining_time(now) < 1)
    {
        animOffsetMenu = sf::Vector2f(slideAnim.value(now), 0);
        animOffsetConfig = sf::Vector2f(-2000 + slideAnim.value(now), 0);
    }
    need_refresh();

    return 0;
}

int GuiController::mouse_moved(sf::RenderWindow & w, sf::Event::MouseMoveEvent & e, float now)
{
    Button *b;
    sf::Vector2f vMousePos = w.ConvertCoords(e.X, e.Y);

    if(screen == 1)
        b = vM.isInButton(sf::Vector2f(vMousePos.x, vMousePos.y));
    else
        b = vC.isInButton(sf::Vector2f(vMousePos.x, vMousePos.y));

    if(b != NULL)
        b->onEnter(now);
    else
    {
        vM.play.onLeave(now);
        vM.options.onLeave(now);
        vM.quit.onLeave(now);
        vC.cancel.onLeave(now);
    }

    return 0;
}

int GuiController::mouse_button_released(sf::RenderWindow &w, sf::Event::MouseButtonEvent & e, float now)
{
    if(!slideAnim.running(now))
    {
        const Button *b;
        sf::Vector2f vMousePos = w.ConvertCoords(e.X, e.Y);
        //std::cout << vMousePos.x  << " - " << animOffsetMenu.x << std::endl;
        if(screen == 1)
            b = vM.isInButton(sf::Vector2f(vMousePos.x, vMousePos.y));
        else
            b = vC.isInButton(sf::Vector2f(vMousePos.x, vMousePos.y));

        if(b != NULL)
        {
            if(e.Button == sf::Mouse::Button::Left)
            {
                if(b->name == "play")
                    //std::cout << "Game Launched" << std::endl;
                    gControl.run(w);
                else if(b->name == "options")
                {
                    if(slideAnim.start_value() != 0)
                        slideAnim.restart_at_end(2000);
                    slideAnim.start(now);
                    vC.show(now);
                    screen = 2;
                }
                else if(b->name == "cancel")
                {
                    slideAnim.restart_at_end(0);
                    slideAnim.start(now);
                    vM.show(now);
                    screen = 1;
                }
                else if(b->name == "quit")
                    return -1;
            }
        }
    }
    return 0;
}
