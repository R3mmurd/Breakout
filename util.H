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

#ifndef UTIL_H
#define UTIL_H

#include <QVector>
#include <QPixmap>
#include <QRectF>

QVector<QRectF> generate_drawing_rects(double, double, double, double);

QVector<QRectF> slice(const QVector<QRectF> &, int, int, int step=1);

QVector<QVector<QRectF> > generate_paddle_drawing_rects();

QVector<QRectF> generate_ball_drawing_rects();

QVector<QRectF> generate_brick_drawing_rects();

QStringList read_highscores();

void write_highscores(const QStringList &);

#endif // UTIL_H
