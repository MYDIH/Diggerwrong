#pragma once

#include "utils.hh"

#include <SFML/Graphics.hpp>
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
private:
    std::string m_filename;
    std::map<std::string, std::string> params;
    sf::Color envColor;

public:
    GuiResource(const std::string &filename);
    ~GuiResource() override;

    void load(const std::string &basepath) override;
};
