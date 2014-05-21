#include "GuiContainer.hh"

void GuiContainer::addDrawable(sf::Drawable *d)
{
    objs.push_back(d);
}

sf::Drawable* GuiContainer::removeLast()
{
    sf::Drawable *l = objs.back();
    objs.pop_back();

    return l;
}

void GuiContainer::clear()
{
    objs.clear();
}

void GuiContainer::SetPosition(const sf::Vector2f &pos)
{
    posContainer = pos;
    for(sf::Drawable *d : objs)
        d->SetPosition(pos.x + d->GetPosition().x, pos.y + d->GetPosition().y);
}

void GuiContainer::Move(const sf::Vector2f &pos)
{
    //posContainer = pos;
    for(sf::Drawable *d : objs)
    {
        sf::Vector2f offset(d->GetPosition().x - posContainer.x, d->GetPosition().y - posContainer.y);
        d->SetPosition(pos.x + posContainer.x + offset.x, pos.y + posContainer.y + offset.y);
    }
}

void GuiContainer::draw(sf::RenderTarget &w)
{

    for(sf::Drawable *d : objs)
    {
        Button *t = dynamic_cast<Button*>(d);
        if(t != NULL)
            t->draw(w);
        else
            w.Draw(*d);
    }
}
