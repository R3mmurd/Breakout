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
