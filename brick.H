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

  ParticleSystem ps;

public:
  Brick();

  Brick(double, double);

  void set_color(int value);

  void set_tier(int value);

  int score() const;

  void hit();

  QRectF get_collision_rect() const;

  void update(double);

  void draw(QPainter &) const;

  bool is_in_play() const;
};

#endif // BRICK_H
