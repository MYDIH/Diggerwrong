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
protected:
    float Start_at;
    float Stop_after;

public:
    Animation(float start, float stop);

    virtual void start(float at) = 0;
    virtual void stop(float at) = 0;
    virtual bool running(float at) const = 0;
    virtual float remaining_time(float at) const = 0;
};

class ValueAnimation : public Animation
{
private:
    float m_startValue;
    float m_endValue;
    float m_duration;
    bool m_loop;

public:
    ValueAnimation(float endValue, float startValue = 0, float duration = 10, bool loop = false);

    void start(float at) override;
    void stop(float at) override;
    bool running(float at) const override;
    float remaining_time(float at) const override;

    float getValue(float now);
};

class SpriteAnimation : public Animation
{
private:
  const AnimationResource * Resource;

public:
  SpriteAnimation(const AnimationResource * r);
  SpriteAnimation(const SpriteAnimation &);

  void start(float at) override;
  void stop(float at) override;

  bool running(float at) const override;

  float remaining_time(float at) const override;

  void draw(sf::RenderTarget & drawer, float now) const;
};
