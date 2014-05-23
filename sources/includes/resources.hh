#pragma once

#include "utils.hh"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <list>
#include <map>
#include <stdexcept>
#include <iostream>


class Resource
{
public:
   virtual ~Resource();
   virtual void load(const std::string & basepath) = 0;
};

class ResourcesPool : public Resource
{
private:
   std::list<Resource*> Pool;

public:
   void add(Resource*);
   void load(const std::string & basepath) override;
};

class GuiResource : public Resource
{
public:
    GuiResource(const std::string &filename);
    ~GuiResource() override;

    void load(const std::string &basepath) override;

    //Paramètres
    sf::Color forCol;
    sf::Color bordCol;
    float bordW;

private:
    std::string m_filename;
    std::map<std::string, std::string> params;
};

class FontResource : public Resource
{
private:
   std::string Dir;
   std::string File;
   sf::Color Back;
   sf::Color Front;
   unsigned  Size;
   sf::Font  Font;

public:
   FontResource(const std::string & dir, const std::string & file);
   
   sf::Vector2f draw_string(sf::RenderTarget & drawer, const std::string & str
		    ,float dx = 0, float dy = 0, bool centered = true, float opacity = 1) const;

   const sf::Font & font() const;

   void load(const std::string & basepath) override;
};

class SoundResource : public Resource
{
private:
   static const unsigned SHORT_COUNT = 10;

   std::string Dir;
   std::string File;

   bool Is_long;
   // --
   unsigned Short_pos;
   sf::Sound Short_sounds[SHORT_COUNT];
   sf::Sound Short_sound;
   sf::SoundBuffer Short;
   // --
   sf::Music Long;
   // --

   float Pitch;
   float Volume;
   
public:
   SoundResource(const std::string & dir, const std::string & file);
   
   void play();
   void pause();
   void stop();

   // uniquement pour Long=false
   void play_new();

   void load(const std::string & basepath) override;
};
