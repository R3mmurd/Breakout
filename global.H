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

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QVector>
#include <QRectF>

class Global
{
public:
  static constexpr double WINDOW_WIDTH = 1280;
  static constexpr double WINDOW_HEIGHT = 720;

  static constexpr double VIRTUAL_WIDTH = 432;
  static constexpr double VIRTUAL_HEIGHT = 243;

  static constexpr double H_SCALE = WINDOW_WIDTH/VIRTUAL_WIDTH;
  static constexpr double V_SCALE = WINDOW_HEIGHT/VIRTUAL_HEIGHT;

  static constexpr double PADDLE_SPEED = 200;

  static constexpr double BALL_WIDTH = 8;
  static constexpr double BALL_HEIGHT = 8;
  static constexpr double ALL_SPRITES_HEIGHT = 16;
  static constexpr double SMALL_SPRITE_WIDTH = 16;
  static constexpr double BRICK_WIDTH = 32;
  static constexpr double PADDLE_WIDTH_FACTOR = 32;

  static bool paused;

  static QVector<QVector<QRectF>> all_paddles;
  static QVector<QRectF> all_balls;
  static QVector<QRectF> all_bricks;
};

#endif // GLOBAL_H
