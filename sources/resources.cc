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
      try
      {
	 r -> load(bp);
      }
      catch (const std::string &e )
      {
	 std::cout << "\n_______________\nERREUR concernant le fichier resource:\n" << e << "\n" << std::endl;
      }
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

      if (not Font.LoadFromFile(basepath+Dir + f.at("font"), Size))
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

sf::Vector2f FontResource::draw_string(sf::RenderTarget & drawer, const std::string & str
			       ,float dx, float dy, bool centered, float opacity) const
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

   float x = dx;
   float y = dy;
   if (centered)
   {
      x -= s.GetRect().GetWidth()/2;
      y -= s.GetRect().GetHeight()/2;
   }

   s.SetColor(back);
   s.Move(x,y);
   drawer.Draw( s );

   s.SetColor(front);
   s.Move(2,2);
   drawer.Draw( s );

   return { s.GetRect().GetWidth(), s.GetRect().GetHeight() };
}

const sf::Font & FontResource::font() const
{ return Font; }


SoundResource::SoundResource(const std::string & dir, const std::string & file)
   :Dir(dir+'/')
   ,File(file)
   ,Is_long(false)
   ,Short_pos(0)
   ,Pitch(1)
   ,Volume(100)
{
//   for (unsigned i = 0; i<SHORT_COUNT; i++)
//      Short_sounds[i].SetBuffer(Short);
}

void SoundResource::play()
{
   if (Is_long)
      Long.Play();
   else
      Short_sound.Play();
}
void SoundResource::pause()
{
   if (Is_long)
      Long.Pause();
   else
      Short_sound.Pause();
}
void SoundResource::stop()
{
   if (Is_long)
      Long.Stop();
   else
      Short_sound.Stop();
}

// uniquement pour Long=false
// permet de lancer plusieurs son en parallèle
void SoundResource::play_new()
{
   if (not Is_long)
   {
      Short_sounds[Short_pos].Play();
      Short_pos = (Short_pos+1) % SHORT_COUNT;
   }
}

void SoundResource::load(const std::string & basepath)
{
   const std::string base = basepath+Dir;

   std::map<std::string, std::string> f;
   if ( not parseFile(f, base+File) )
      throw base+File;

   try
   {
      Pitch  = std::stof( f.at("pitch") );
      Volume = std::stof( f.at("volume") );

      if ( f.at("long") == "true" )
      {
	 Is_long = true;

	 if (not Long.OpenFromFile( base + f.at("sound") ))
	    throw base + f.at("sound");

	 Long.SetPitch(Pitch);
	 Long.SetVolume(Volume);
      }
      else
      {
	 Is_long = false;

	 if (not Short.LoadFromFile( base + f.at("sound") ))
	    throw base + f.at("sound");

	 for (unsigned i = 0; i<SHORT_COUNT; i++)
	 {
	    Short_sounds[i].SetBuffer(Short);
	    Short_sounds[i].SetPitch(Pitch);
	    Short_sounds[i].SetVolume(Volume);
	 }

	 Short_sound.SetBuffer(Short);
	 Short_sound.SetPitch(Pitch);
	 Short_sound.SetVolume(Volume);


      }

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
