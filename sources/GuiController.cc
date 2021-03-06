#include "GuiController.hh"

#include <iostream>

SoundResource GuiController::Music("", "music.txt");

GuiController::GuiController(const sf::RenderTarget &r, std::vector<module> &modules, module &firstmod, module &defaultmod, ResourcesPool & pool) :
    Pool(pool),
    width(r.GetWidth()),
    height(r.GetHeight()),
    gControl(modules,firstmod,defaultmod),
    animOffsetMenu(0, 0),
    animOffsetConfig(-(width / 2 + vM.getSize().x), 0),
    slideAnim(width / 2 + vM.getSize().x, 0, 0.8, EASE_IN_OUT<10>)
{
    vM.show(0.5);
    Music.play();
}

int GuiController::launchGame(sf::RenderWindow & w, float now)
{
    lGame = false;
    reappear = true;

    gControl.start(now);

    return gControl.run(w);
}

void GuiController::draw(sf::RenderTarget & r, float now)
{
    gControl.draw(r, now);
    vM.setOffset(animOffsetMenu);
    vC.setOffset(animOffsetConfig);
    vM.draw(r, now);
    vC.draw(r, now);
}

int GuiController::tick(sf::RenderWindow & w, float now)
{
    gControl.tick(w,now);

    if(slideAnim.running(now) || slideAnim.remaining_time(now) < 1)
    {
        animOffsetMenu = sf::Vector2f(slideAnim.value(now), 0);
        animOffsetConfig = sf::Vector2f(-(width / 2 + vM.getSize().x) + slideAnim.value(now), 0);
    }

    if(lGame && vM.appearedOrHidden(now))
    {
	if(launchGame(w,now) == 1)
	    return 1;

	EventHandler::auto_resize(w);
    }

    if(reappear)
    {
        if(disableOldTickEvent >= 1)
        {
            gControl.stop(now);
            vM.show(now + 0.4);
            reappear = false;
            disableOldTickEvent = 0;
        }
        else
            disableOldTickEvent++;
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
        ArrowType t = NONE;
        sf::Vector2f vMousePos = w.ConvertCoords(e.X, e.Y);
        if(screen == 1)
            b = vM.isInButton(vMousePos);
        else
        {
            b = vC.isInButton(vMousePos);
            t = vC.themesSelect.contains(vMousePos);
            if(t != NONE)
            {
                const std::string &s = vC.themesSelect.onClick(now, t);

                reloadResources("themes/" + s);
            }
        }

        if(b != NULL)
        {
            if(e.Button == sf::Mouse::Button::Left)
            {
                if(b->name == "play")
                {
                    vM.hide(now);
                    lGame = true;
                }
                else if(b->name == "options")
                {
                    if(slideAnim.start_value() != 0)
                        slideAnim.swap();
                    slideAnim.start(now);
                    vC.show(now);
                    screen = 2;
                }
                else if(b->name == "cancel")
                {
                    slideAnim.swap();
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

int GuiController::resized(sf::RenderWindow & w, sf::Event::SizeEvent & e, float now)
{
    // éviter l'auto-resize chelou
    EventHandler::resized(w,e,now);

    if(slideAnim.end_value() == width / 2 + vM.getSize().x)
    {
        width = w.GetWidth();
        slideAnim.set_end_value(width / 2 + vM.getSize().x);
    }

    width = w.GetWidth();
    height = w.GetHeight();
    animOffsetConfig = sf::Vector2f(-(width / 2 + vM.getSize().x), 0);

    need_refresh();
    return 0;
}

void GuiController::reloadResources(const std::string &basePath)
{
    Music.stop();

    Pool.load(basePath);

    Music.play();

}
