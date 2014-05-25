#include "ScoresTab.hh"

AnimationResource ScoresTab::tabLines("gui", "scores.txt");
FontResource ScoresTab::namesCol("", "namesColFont.txt");
FontResource ScoresTab::contenuCol("", "contenuColFont.txt");

bool operator<(const Score &a, const Score &b)
{
    return b.scoreInt < a.scoreInt;
}

ScoresTab::ScoresTab() :
    offset(sf::Vector2f(0, 0)),
    lines(&tabLines),
    opacity(255, 0, 0.4),
    opacityNamesCol(1, 0, 0.4),
    opacityContent(1, 0, 0.4)
{
}

void ScoresTab::show(float at)
{
    parseHighScoresFile();

    if(opacity.end_value() != 255)
        opacity.swap();
    if(opacityNamesCol.end_value() != 1)
        opacityNamesCol.swap();
    if(opacityContent.end_value() != 1)
        opacityContent.swap();
    opacity.start(at);
    lines.start(at + 0.3);
    opacityNamesCol.start(at + 0.7);
    opacityContent.start(at + 0.9);
}

void ScoresTab::hide(float at)
{
    if(opacity.value(at) == 255)
    {
        opacity.swap();
        if(opacityNamesCol.end_value() == 1)
            opacityNamesCol.swap();
        if(opacityContent.end_value() == 1)
            opacityContent.swap();
        opacity.start(at);
        opacityNamesCol.start(at);
        opacityContent.start(at);
    }
}

void ScoresTab::setOffset(const sf::Vector2f &o)
{
    offset = o;
}

void ScoresTab::parseHighScoresFile()
{
    std::map<std::string, std::string> parseRes;
    Score tmpScore;

    scoreList.clear();

    parseFile(parseRes, "highScores.txt");

    for(const auto &s : parseRes)
    {
        tmpScore.name = s.first;
        tmpScore.scoreInt = stoi(s.second);
        scoreList.push_back(tmpScore);
    }

    scoreList.sort();
}

void ScoresTab::draw(sf::RenderTarget &w, float now)
{
    std::list<Score>::iterator it;
    int off = 0;
    int i = 0;

    const sf::View & dw = w.GetView();
    sf::View mView(dw);
    w.SetView(mView);

    mView.Move(offset);

    lines.draw(w, now, 0, sf::Color(255, 255, 255, opacity.value(now)), sf::Vector2f(1.8, 1.8));
    namesCol.draw_string(w, "Noms", -65, -90, true, opacityNamesCol.value(now));
    namesCol.draw_string(w, "Score", 55, -90, true, opacityNamesCol.value(now));

    it = scoreList.begin();

    while(it != scoreList.end() && i < 5)
    {
        contenuCol.draw_string(w, it->name, -10 -65, -110 - off + 70, true, opacityContent.value(now));
        contenuCol.draw_string(w, std::to_string(it->scoreInt), -10 + 65, -110 - off + 70, true, opacityContent.value(now));
        off -= 30;

        ++it;
        i++;
    }

    w.SetView(dw);
}
