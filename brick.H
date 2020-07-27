/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef BRICK_H
#define BRICK_H

#include <QRectF>
#include <QPainter>

#include <global.H>
#include <particlesystem.H>

#include <tuple>

class Brick
{
  static const std::tuple<int, int, int> color_palette[5];
  int color = 0;
  int tier = 0;

  double x = 0;
  double y = 0;

  bool in_play = true;
  bool locked = false;

  ParticleSystem ps;

public:
  Brick();

  Brick(double, double);

  void set_color(int value);

  void set_tier(int value);

  int score() const;

  bool is_locked() const;

  void lock();

  void unlock();

  void hit();

  QRectF get_collision_rect() const;

  void update(double);

  void draw(QPainter &) const;

  bool is_in_play() const;
};

#endif // BRICK_H
