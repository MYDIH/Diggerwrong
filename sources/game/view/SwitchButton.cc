#include "SwitchButton.hh"

#include <iostream>

FontResource SwitchButton::labelsFont("", "labelFont.txt");
FontResource SwitchButton::arrowsFont("", "arrowsFont.txt");
const float SwitchButton::w = 134;
const float SwitchButton::h = 54;
const float SwitchButton::arrowsDy = -7;
const float SwitchButton::arrowsDx = (SwitchButton::w/2) + 40;
const sf::Vector2f SwitchButton::arrowsPos = sf::Vector2f(70, 10);

SwitchButton::SwitchButton(sf::Vector2f off) :
    offset(off),
    labelsOpacity(1, 0, 0.4),
    arrowLOpacity(1, 0, 0.4),
    arrowROpacity(1, 0, 0.4),
    offsetLabelsX(1, 0, 0.4)
{}

void SwitchButton::parseThemesNames()
{
    std::map<std::string, std::string> parseRes;

    parseFile(parseRes, "themes/themes.txt");

    for(const auto &s : parseRes)
        labels.push_back(s.second);
}

void SwitchButton::show(float at)
{
    parseThemesNames();
    if(labelsOpacity.end_value() != 1)
        labelsOpacity.swap();
    labelsOpacity.start(at + 0.4);
    arrowROpacity.start(at + 0.8);
}

const std::string & SwitchButton::onClick(float at, ArrowType t)
{
    switch(t)
    {
        case LEFT :
        {
            offsetLabelsX.set_start_value(SwitchButton::arrowsDx*current);
            offsetLabelsX.set_end_value(SwitchButton::arrowsDx*(current - 1));
            labelsOpacity.start(at);
            offsetLabelsX.start(at);
            if(current != 0)
                current--;
            direc = LEFT;
            break;
        }
        case RIGHT :
        {
            offsetLabelsX.set_start_value(-SwitchButton::arrowsDx*current);
            offsetLabelsX.set_end_value(-SwitchButton::arrowsDx*(current + 1));
            labelsOpacity.start(at);
            offsetLabelsX.start(at);
            if(current != labels.size() - 1)
                current++;
            direc = RIGHT;
            break;
        }
        default :
            {}
    }
    if(current == 0 || current == labels.size() - 1)
    {
        if(current == 0)
            disableLArrow(at);
        if(current == labels.size() - 1)
            disableRArrow(at);
    }
    else
    {
        if(disabled == LEFT)
            enableLArrow(at);
        if(disabled == RIGHT)
            enableRArrow(at);
    }
    return labels[current];
}

void SwitchButton::disableLArrow(float at)
{
    if(arrowLOpacity.end_value() != 0)
        arrowLOpacity.swap();
    arrowLOpacity.start(at);
    disabled = LEFT;
    std::cout << "disableLArrow" << std::endl;
}

void SwitchButton::disableRArrow(float at)
{
    if(arrowROpacity.end_value() != 0)
        arrowROpacity.swap();
    arrowROpacity.start(at);
    disabled = RIGHT;
    std::cout << "disableRArrow" << std::endl;
}

void SwitchButton::enableLArrow(float at)
{
    if(arrowLOpacity.end_value() != 1)
        arrowLOpacity.swap();
    arrowLOpacity.start(at);
    disabled = NONE;
}

void SwitchButton::enableRArrow(float at)
{
    if(arrowROpacity.end_value() != 1)
        arrowROpacity.swap();
    arrowROpacity.start(at);
    disabled = NONE;
}

void SwitchButton::drawLabels(sf::RenderTarget &w, float now)
{
    for(unsigned i = 0; i<labels.size(); i++)
    {
        if(direc == RIGHT)
        {
            if(i == current)
            {
                if(i == 0)
                    labelsFont.draw_string(w, labels[i], offsetLabelsX.value(now), SwitchButton::arrowsDy, true, labelsOpacity.value(now));
                else
                    labelsFont.draw_string(w, labels[i], offsetLabelsX.value(now) + (SwitchButton::arrowsDx)*i, SwitchButton::arrowsDy, true, labelsOpacity.value(now));
            }
            else if(i == current - 1  && isLaunched)
            {
                labelsFont.draw_string(w, labels[i], offsetLabelsX.value(now) + (SwitchButton::arrowsDx)*i, SwitchButton::arrowsDy, true, 1 - labelsOpacity.value(now));
            }
            else
            {
                if(i == 0)
                    labelsFont.draw_string(w, labels[i], offsetLabelsX.value(now), SwitchButton::arrowsDy, true, 0);
                else
                    labelsFont.draw_string(w, labels[i], offsetLabelsX.value(now) + (SwitchButton::arrowsDx)*i, SwitchButton::arrowsDy, true, 0);
            }
        }
        if(direc == LEFT)
        {

            if(i == current)
            {
                if(i == 0)
                    labelsFont.draw_string(w, labels[i], -offsetLabelsX.value(now), SwitchButton::arrowsDy, true, labelsOpacity.value(now));
                else
                    labelsFont.draw_string(w, labels[i], -offsetLabelsX.value(now) + (SwitchButton::arrowsDx)*i, SwitchButton::arrowsDy, true, labelsOpacity.value(now));
            }
            else if(i == current + 1)
            {
                if(i == 0)
                    labelsFont.draw_string(w, labels[i], -offsetLabelsX.value(now), SwitchButton::arrowsDy, true, 1 - labelsOpacity.value(now));
                else
                    labelsFont.draw_string(w, labels[i], -offsetLabelsX.value(now) + (SwitchButton::arrowsDx)*i, SwitchButton::arrowsDy, true, 1 - labelsOpacity.value(now));
            }
            else
            {
                if(i == 0)
                    labelsFont.draw_string(w, labels[i], -offsetLabelsX.value(now), SwitchButton::arrowsDy, true, 0);
                else
                    labelsFont.draw_string(w, labels[i], -offsetLabelsX.value(now) + (SwitchButton::arrowsDx)*i, SwitchButton::arrowsDy, true, 0);
            }
        }
    }
    if(labelsOpacity.value(now) == 1)
        isLaunched = true;
}

void SwitchButton::draw(sf::RenderTarget &w, float now)
{
    const sf::View & dw = w.GetView();
    sf::View mView(dw);

    w.SetView(mView);

    mView.Move(offset);

    //--
    mView.Move(arrowsPos.x, arrowsPos.y);
    arrowsFont.draw_string(w, "<", 0, 0, true, arrowLOpacity.value(now));
    mView.Move(-arrowsPos.x, -arrowsPos.y);
    //--
    mView.Move(-arrowsPos.x, arrowsPos.y);
    arrowsFont.draw_string(w, ">", 0, 0, true, arrowROpacity.value(now));
    mView.Move(arrowsPos.x, -arrowsPos.y);
    //--
    drawLabels(w, now);

    w.SetView(dw);
}

ArrowType SwitchButton::contains(const sf::Vector2f &p) const
{
    sf::Rect<float> leftArrowRect(-offset.x - arrowsPos.x, -offset.y - arrowsPos.y, -offset.x - arrowsPos.x + 20, -offset.y - arrowsPos.y + 20);
    sf::Rect<float> rightArrowRect(-offset.x + arrowsPos.x, -offset.y - arrowsPos.y, -offset.x + arrowsPos.x + 20, -offset.y - arrowsPos.y + 20);

    if(leftArrowRect.Contains(p.x, p.y) && disabled != LEFT)
        return LEFT;
    else if(rightArrowRect.Contains(p.x, p.y) && disabled != RIGHT)
        return RIGHT;
    return NONE;
}

sf::Vector2f SwitchButton::getSize() const
{
    return sf::Vector2f(w, h);
}
