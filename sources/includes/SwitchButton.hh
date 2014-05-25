#pragma once

#include <SFML/Graphics.hpp>

#include "Animation.hh"

enum ArrowType
{
    RIGHT,
    LEFT,
    NONE
};

class SwitchButton
{
public:
    static const float w;
    static const float h;
    static const float arrowsDy;
    static const float arrowsDx;
    static const sf::Vector2f arrowsPos;
    static const std::string error;
    static FontResource labelsFont;
    static FontResource arrowsFont;

    SwitchButton(sf::Vector2f off = sf::Vector2f(0, 0));

    void draw(sf::RenderTarget &w, float now);

    //Accesseurs
    bool isLabelCentered() const;
    sf::Vector2f getSize() const;

    void setCenteringPolicy(bool isCentered);
    ArrowType contains(const sf::Vector2f &p) const;

    const std::string & onClick(float at, ArrowType t);
    void show(float at);
    void hide(float at);

private:
    ArrowType direc = RIGHT;
    sf::Vector2f offset;
    bool isLaunched = false;
    ArrowType disabled = LEFT;
    unsigned current = 0;
    std::vector<std::string> labels;
    AnimatedValue labelsOpacity;
    AnimatedValue arrowLOpacity;
    AnimatedValue arrowROpacity;
    AnimatedValue offsetLabelsX;

    void disableLArrow(float at);
    void disableRArrow(float at);
    void enableLArrow(float at);
    void enableRArrow(float at);
    void parseThemesNames();
    void drawLabels(sf::RenderTarget &w, float now);
};
