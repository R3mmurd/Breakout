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

#include <paddle.H>
#include <global.H>
#include <spritesheet.H>

Paddle::Paddle()
{

}

void Paddle::move_left()
{
  dx = -Global::PADDLE_SPEED;
}

void Paddle::move_right()
{
  dx = Global::PADDLE_SPEED;
}

void Paddle::stop()
{
  dx = 0;
}

void Paddle::update(double dt)
{
  double nx = x + dx*dt;

  if (dx < 0)
    x = std::max<double>(0, nx);
  else if (dx > 0)
    x = std::min<double>(Global::VIRTUAL_WIDTH - width, nx);
}

void Paddle::draw(QPainter & painter) const
{
  painter.drawPixmap(QPoint(x, y), SpriteSheet::get_instance().get(),
                     Global::all_paddles[skin][size]);
}

QRectF Paddle::get_collision_rect() const
{
  return QRectF(x, y, width, height);
}
