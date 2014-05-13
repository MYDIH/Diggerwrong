#pragma once

#include "resources.hh"

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

class AnimationResource : public Resource
{
private:
  sf::Image Image;
  std::vector<sf::Drawable *> Frames;
  std::string Dir = "No Dir";
  float Fps;
  bool Loop;

public:
  AnimationResource(std::string dir);
  AnimationResource(unsigned frame_count, float fps, bool loop); // constructeur de test (triangle qui tourne)
  ~AnimationResource() override;

  const sf::Drawable & frame(float elapsed_time, float stopping_since) const;
  float remaining_time(float elapsed_time, float stopping_since) const;

  void dealloc();

  void load(const std::string & basepath) override;
  void createErrorImg();
};

class Animation
{
private:
  const AnimationResource * Resource;

  float Start_at;
  float Stop_after;

public:
  Animation(const AnimationResource * r);
  Animation(const Animation &);

  void start(float at);
  void stop(float at);

  bool running(float at) const;

  float remaining_time(float at) const;

  void draw(sf::RenderTarget & drawer, float now) const;
};
