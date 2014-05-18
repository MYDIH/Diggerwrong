#include "Animation.hh"

#include "consts.hh"
#include "utils.hh"

#include <iostream>
#include <cfloat>
#include <string>
#include <map>
#include <stdexcept>

#define MAX(a,b) ( ((a)>(b)) ? (a) : (b) )

AnimationResource::AnimationResource(std::string dir) :
    Dir(dir)
{
    Frames.push_back(new sf::Sprite());
}

AnimationResource::AnimationResource(unsigned frame_count, float fps, bool loop)
    :Fps(fps)
    ,Loop(loop)
{
    sf::Shape model;
    model.AddPoint(-7,-7);
    model.AddPoint(+7,-7);
    model.AddPoint(0,+10);
    model.EnableFill(true);
    model.EnableOutline(false);
    model.SetColor(sf::Color(50,150,0));

    if (loop)
    {
        const float rotation = 720 / (float)frame_count;

        for (unsigned i = 0; i < frame_count; i++)
        {
	   sf::Shape * shape = new sf::Shape(model);
	   Frames.push_back(shape);
	    
	   shape -> Rotate(i * rotation);
//	 std::cout << "frame rot=" << (unsigned)(2*i*rotation) << "\n";
        }
    }
    else
    {
        const float alpha = 255 / (float)frame_count;

        unsigned i;
        for (i = 0; i < frame_count; i++)
        {
            sf::Shape * shape = new sf::Shape(model);
            Frames.push_back(shape);

            shape -> SetColor(sf::Color(50,150,0,i*alpha));
        }
    }
}

AnimationResource::~AnimationResource()
{
    dealloc();
}

const sf::Drawable & AnimationResource::frame(float elapsed_time, float stopping_since = FLT_MAX) const
{
    const unsigned size = Frames.size();

    if (Loop)
    {
        if (elapsed_time >= stopping_since)
        {
            const float frame_f = (stopping_since * Fps);
            const unsigned integer_part = frame_f;
            const float delta = frame_f - integer_part;

            const unsigned stopped_at_frame = integer_part % size;
            const unsigned frame = ((elapsed_time - stopping_since) * Fps + delta) + stopped_at_frame;

            if (frame >= size-1)
            {
//	    std::cout << "ret. frame " << size-1 << "\n";
                return *( Frames[ size-1 ] );
            }
            else
            {
//	    std::cout << "ret. frame " << frame << "\n";
                return *( Frames[ frame ] );
            }

        }
        else
        {
//	 std::cout << "ret. frame " << (unsigned)(elapsed_time * Fps) % size << "\n";
            return *( Frames[ (unsigned)(elapsed_time * Fps) % size ] );
        }
    }
    else
    {
        const unsigned frame = elapsed_time * Fps;

        if (frame >= size-1)
        {
//	 std::cout << "ret. frame " << size-1 << "\n";
            return *( Frames[ size-1 ] );
        }
        else
        {
//	 std::cout << "ret. frame " << frame << "\n";
            return *( Frames[ frame ] );
        }
    }
}


float AnimationResource::remaining_time(float elapsed_time, float stopping_since = FLT_MAX) const
{
    const unsigned size = Frames.size();

    if (Loop)
    {
        if (elapsed_time >= stopping_since)
        {
            const float frame_f = (stopping_since * Fps);
            const unsigned integer_part = frame_f;
            const float delta = frame_f - integer_part;

            const unsigned stopped_at_frame = integer_part % size;

            return MAX(0, (size - stopped_at_frame - delta) / Fps - (elapsed_time - stopping_since));
        }
        else
            return FLT_MAX;
    }
    else
        return MAX(0, (size / Fps) - elapsed_time);
}

void AnimationResource::dealloc()
{
for (sf::Drawable * frame : Frames)
        delete frame;

    Frames.clear();
}

void AnimationResource::load(const std::string & basepath)
{
    std::map<std::string, std::string> descMap;

    dealloc();

//    exit(1);

    std::cout << basepath +'/'+ Dir +'/'+ DESC_FILENAME << std::endl;
    parseFile(descMap, basepath +'/'+ Dir +'/'+ DESC_FILENAME);
    if(descMap.size() >= 3)
    {
        try
        {
            if(Image.LoadFromFile(basepath +'/'+ Dir +'/'+ SPRITE_FILENAME))
            {
	        int spriteX = 0;
                int frameWidth = Image.GetWidth() / std::stoi(descMap.at("NbFrames"));
                Fps = std::stof(descMap.at("Fps"));
                descMap.at("Loop") == "true" ? Loop = true : Loop = false;
		
                for(int i = 1; i<=std::stoi(descMap.at("NbFrames")); i++)
                {
                    sf::IntRect clipRect(spriteX, 0, frameWidth*i, Image.GetHeight());
		    
                    Frames.push_back(new sf::Sprite(Image));
                    ((sf::Sprite*)Frames.back())->SetSubRect(clipRect);
                    ((sf::Sprite*)Frames.back())->SetCenter(frameWidth/2, Image.GetHeight()/2);
		    
                    spriteX += frameWidth;
                }
            }
            else
            {
                std::cout << "img loading Error" << std::endl;
                createErrorImg();
            }
        }
        catch(const std::out_of_range &oor)
        {
            createErrorImg();
            std::cout << "exception error" << std::endl;
        }
    }
    else
    {
        createErrorImg();
        std::cout << "Parse Error" << descMap.size() << std::endl;
    }
}

void AnimationResource::createErrorImg()
{
    Image.Create(50, 50, sf::Color(255, 0, 0));
    Fps = 1;
    Loop = false;

    Frames.push_back(new sf::Sprite(Image));
}

//////////////////////////////////////Animation///////////////////////////////////////////////////

Animation::Animation(const AnimationResource * r)
    :Resource(r)
    ,Start_at(FLT_MAX)
    ,Stop_after(0)
{}

Animation::Animation(const Animation & o)
    :Resource(o.Resource)
    ,Start_at(o.Start_at)
    ,Stop_after(o.Stop_after)
{}

void Animation::start(float at)
{
    Start_at = MAX(0, at);

    Stop_after = (Resource == nullptr) ? 0 : Resource -> remaining_time(0);
}
void Animation::stop(float at)
{
    if (at >= Start_at)
        Stop_after = at - Start_at;
}

bool Animation::running(float at) const
{
    if (at >= Start_at and at < (Start_at+Stop_after + remaining_time(Start_at + Stop_after)))
        return true;
    else
        return false;
}

float Animation::remaining_time(float at) const
{
    if (Resource != nullptr)
        return Resource -> remaining_time(MAX(0, at - Start_at), Stop_after);
    else
        return 0;
}

void Animation::draw(sf::RenderTarget & drawer, float now) const
{
    if (Resource != nullptr)
        drawer.Draw( Resource -> frame(MAX(0, now - Start_at), Stop_after) );
}



