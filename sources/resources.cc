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
   const std::string bp = basepath + '/';
   for (Resource* r : Pool)
   {
      r -> load(bp);
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


FontResource::FontResource(const std::string & dir, const std::string & file)
   :Dir(dir + '/')
   ,File(file)
   ,Size(0)
{}

#define GET(str) std::stoi( f.at(str) )
void FontResource::load(const std::string & basepath)
{
   std::map<std::string, std::string> f;
   if ( not parseFile(f, basepath+Dir + File) )
      throw basepath+Dir + File;

   try
   {
      Back = sf::Color( GET("_R")
			,GET("_G")
			,GET("_B")
			,GET("_A") );

      Front = sf::Color( GET("R")
			 ,GET("G")
			 ,GET("B")
			 ,GET("A") );
      
      Size = GET("size");

      if (not Font.LoadFromFile(basepath+Dir + f.at("font")))
	 throw basepath+Dir + f.at("font");
      
   }
   catch(const std::out_of_range &oor)
   {
      throw basepath+Dir + File;
   }
   catch(const std::invalid_argument &ia)
   {
      throw basepath+Dir + File;
   }

}


void FontResource::draw_string(sf::RenderTarget & drawer, const std::string & str
			       ,float dx = 0, float dy = 0, float opacity = 1) const
{
   sf::Color back  = Back;
   sf::Color front = Front;

   if (opacity < 1)
   {
      back.a  *= opacity;
      front.a *= opacity;
   }

   sf::String s;
   s.SetFont(Font);
//   s.SetStyle(sf::String::Bold);
   s.SetText(str);
   s.SetSize(Size);
   
   s.SetColor(back);
   s.Move(dx,dy);
   drawer.Draw( s );
   
   s.SetColor(front);
   s.Move(2,2);
   drawer.Draw( s );
}
