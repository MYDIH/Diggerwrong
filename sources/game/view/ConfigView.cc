#include "ConfigView.hh"

#include <iostream>

ConfigView::ConfigView() :
    cancel("Retour", sf::Vector2f(0, -60))
{
    cancel.name = "cancel";
}

void ConfigView::show(float at)
{
    if(opacityView.end_value() != 255)
        opacityView.swap();
    opacityView.start(at);
    viewCornerOne.start(at + 0.4);
    viewCornerTwo.start(at + 0.4);
    offBordX.start(at + 0.4);
    offBordY.start(at + 0.4);
    opacityTitle.start(at + 1.3);
    cancel.show(at + 1.3);
}

void ConfigView::hide(float at)
{
    if(opacityView.value(at) == 255)
    {
        opacityView.swap();
        opacityView.start(at);
        cancel.hide(at + 1.3);
    }
}

Button* ConfigView::isInButton(const sf::Vector2f &p)
{
    //std::cout << "\tCV : " << p.x << " - " << offset.y << std::endl;
    if(cancel.contains(sf::Vector2f(p.x - offset.x, p.y - offset.y)))
        return &cancel;
    return NULL;
}

void ConfigView::draw(sf::RenderTarget &w, float now)
{
    const sf::View & dw = w.GetView();
    sf::View mView(dw);
    w.SetView(mView);

    float bordX =  offBordX.value(now);
    float bordY =  offBordY.value(now);

    mView.Move(offset);

    cancel.draw(w, now);

    //--
    mView.Move(-bordX, bordY);
    viewCornerOne.draw(w, now, -90, sf::Color(255, 255, 255, opacityView.value(now)));
    mView.Move(bordX, -bordY);
    //--
    mView.Move(bordX, -bordY);
    viewCornerTwo.draw(w, now, 90, sf::Color(255, 255, 255, opacityView.value(now)));
    mView.Move(-bordX, bordY);
    //--

    w.SetView(dw);
}
