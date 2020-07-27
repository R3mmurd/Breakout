/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef PADDLE_H
#define PADDLE_H

#include <QPainter>

#include <singleton.H>
#include <global.H>

class Paddle : public Singleton<Paddle>
{
  friend class Singleton<Paddle>;

  int skin = 0;
  int size = Global::DEFAULT_PADDLE_SIZE;
  double x = 0;
  double y = 0;
  double dx = 0;

protected:
  Paddle() = default;

public:
  void set_skin(int);

  double get_width() const;

  double get_height() const;

  double get_x() const;

  double get_y() const;

  double get_dx() const;

  void reset();

  QRectF get_collision_rect() const;

  void move_left();

  void move_right();

  void stop();

  void update(double);

  void draw(QPainter &) const;
};

#endif // PADDLE_H
