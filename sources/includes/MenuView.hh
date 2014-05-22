#include <SFML/Graphics.hpp>

#include "Button.hh"
#include "Animation.hh"

class MenuView
{
public:
    MenuView(const sf::View &windowV);

    void draw(sf::RenderTarget &w);

private:
    sf::View mView;
    Button play;
    Button options;
    Button quit;
};
