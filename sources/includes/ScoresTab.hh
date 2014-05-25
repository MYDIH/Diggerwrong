#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include <string>

#include "Animation.hh"
#include "resources.hh"
#include "utils.hh"

struct Score
{
    std::string name;
    int scoreInt;
};

class ScoresTab
{
public:
    static AnimationResource tabLines;
    static FontResource namesCol;
    static FontResource contenuCol;

    ScoresTab();

    void show(float at);
    void hide(float at);

    void setOffset(const sf::Vector2f &o);

    void parseHighScoresFile();

    void draw(sf::RenderTarget &w, float now);

private:
    sf::Vector2f offset;
    Animation lines;
    AnimatedValue opacity;
    AnimatedValue opacityNamesCol;
    AnimatedValue opacityContent;

    std::list<Score> scoreList;
};
