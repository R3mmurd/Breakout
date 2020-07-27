/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef BALL_H
#define BALL_H

#include <QRectF>
#include <QPainter>

#include <singleton.H>

class Ball
{
  double x;
  double y;
  double dx = 0;
  double dy = 0;

  int skin = 0;
public:
  Ball(double, double);

  double get_dx() const;

  double get_dy() const;

  double get_x() const;

  double get_y() const;

  void set_position(double, double);

  void set_velocity(double, double);

  void set_skin(int);

  void reset();

  QRectF get_collision_rect() const;

  bool collides(const QRectF &);

  void rebound(const QRectF &);

  void update(double);

  void draw(QPainter &) const;
};

#endif // BALL_H
