#include "resources.hh"

Resource::~Resource()
{}

/////////////////////////Ressource Pool/////////////////////////////

void ResourcesPool::add(Resource* r)
{
   Pool.push_back(r);
}

void ResourcesPool::load(const std::string & basepath)
{
   for (Resource* r : Pool)
   {
      r -> load(basepath);
   }
}

///////////////////////////GuiResource/////////////////////////////

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
            forCol = sf::Color(stoi(params.at("forColR")), stoi(params.at("forColV")), stoi(params.at("forColB")), stoi(params.at("forColA")));
            bordCol = sf::Color(stoi(params.at("bordColR")), stoi(params.at("bordColV")), stoi(params.at("bordColB")), stoi(params.at("bordColA")));
            bordW = stof(params.at("bordW"));
        }
        catch(const std::out_of_range &oor)
        {
            std::cout << "Paramètre inconnu" << std::endl;
        }
    else
        std::cout << "Parse Error on file : " << basepath + m_filename << std::endl;
}
