#include <SFML/Graphics.hpp>

#include "EventHandler.hh"
#include "Button.hh"

class MenuView : public sf::View
{
    public:
        MenuView();
        MenuView(const sf::FloatRect &rect);
        MenuView(const sf::View &view);

        void draw(sf::RenderTarget &w);

    private:
        Button play;
        Button options;
        Button quit;
};
