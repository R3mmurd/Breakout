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

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <QPainter>

class Particle
{
  double x;
  double y;
  double vx;
  double vy;
  double ax;
  double ay;
  double life_time;  // in seconds
  QColor color;

public:
  Particle() = default;

  Particle(double, double, double, double, double, QColor);

  void update(double);

  void draw(QPainter &) const;

  double get_life_time() const;
};

class ParticleSystem
{
  double x_mean;
  double y_mean;
  int size;
  double min_life_time = 0;
  double max_life_time = 0;
  double timer = 0;
  double ax1 = 0;
  double ay1 = 0;
  double ax2 = 0;
  double ay2 = 0;
  double x_desv = 1;
  double y_desv = 1;

  QVector<QColor> colors;
  QVector<Particle> particles;

public:
  ParticleSystem(double, double, int);

  void set_life_time(double, double);

  void set_linear_acceleration(double, double, double, double);

  void set_colors(const QVector<QColor> &);

  void set_area_spread(double, double);

  void generate();

  void update(double);

  void draw(QPainter &) const;
};

#endif // PARTICLESYSTEM_H
