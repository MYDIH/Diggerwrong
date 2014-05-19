#include "resources.hh"

Resource::~Resource()
{}

void ResourcesPool::add(Resource* r)
{
   Pool.push_back(r);
}

void ResourcesPool::load(const std::string & basepath)
{
   for (Resource* r : Pool)
      r -> load(basepath);
}


GuiResource::GuiResource(const std::string &filename) :
    m_filename(filename)
{}

GuiResource::~GuiResource()
{}

void GuiResource::load(const std::string &basepath)
{

    parseFile(params, basepath + m_filename);
    if(params.size() >= 1)
        try
        {
            envColor = sf::Color(stoi(params.at("R")), stoi(params.at("V")), stoi(params.at("B")), stoi(params.at("A")));
        }
        catch(const std::out_of_range &oor)
        {
            std::cout << "Paramètre inconnu" << std::endl;
        }
    else
        std::cout << "Parse Error on file : " << basepath + m_filename << std::endl;
}
