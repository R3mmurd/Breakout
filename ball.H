/*
  This file is part of Breakout game.
  Copyright (C) 2020 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to

  Alejandro Mujica

  aledrums@gmail.com
*/

#ifndef BALL_H
#define BALL_H

#include <QRectF>
#include <QPainter>

class Ball
{
  double x;
  double y;
  double dx = 0;
  double dy = 0;

  int skin = 0;
public:
  Ball(int);

  bool collides(const QRectF &);

  void set_position(double, double);

  void set_velocity(double, double);

  void reset();

  void update(double);

  void draw(QPainter &) const;

  double get_dx() const;

  void set_dx(double);

  double get_dy() const;

  void set_dy(double);

  double get_x() const;

  double get_y() const;

  void set_x(double);

  void set_y(double);
};

#endif // BALL_H
