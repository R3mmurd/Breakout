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

#include <ball.H>
#include <global.H>
#include <audio.H>
#include <spritesheet.H>

void Ball::set_x(double value)
{
  x = value;
}

void Ball::set_y(double value)
{
  y = value;
}

Ball::Ball(int _skin)
  : skin(_skin)
{
  // Empty
}

double Ball::get_dx() const
{
  return dx;
}

void Ball::set_dx(double value)
{
  dx = value;
}

double Ball::get_dy() const
{
  return dy;
}

void Ball::set_dy(double value)
{
  dy = value;
}

double Ball::get_x() const
{
  return x;
}

double Ball::get_y() const
{
  return y;
}

bool Ball::collides(const QRectF & target)
{
  QRectF collision_rectangle(x, y, Global::BALL_WIDTH, Global::BALL_HEIGHT);
  return collision_rectangle.intersects(target);
}

void Ball::set_position(double _x, double _y)
{
  x = _x;
  y = _y;
}

void Ball::set_velocity(double _dx, double _dy)
{
  dx = _dx;
  dy = _dy;
}

void Ball::reset()
{
  x = Global::VIRTUAL_WIDTH / 2.0 - 2;
  y = Global::VIRTUAL_HEIGHT / 2.0 - 2;
  dy = dx = 0;
}

void Ball::update(double dt)
{
  x += dx*dt;
  y += dy*dt;

  if (x <= 0)
    {
      x = 0;
      dx *= -1;
      Audio::get_instance().play_wall_hit();
    }

  if (x >= Global::VIRTUAL_WIDTH - Global::BALL_WIDTH)
    {
      x = Global::VIRTUAL_WIDTH - Global::BALL_WIDTH;
      dx *= -1;
      Audio::get_instance().play_wall_hit();
    }

  if (y <= 0)
    {
      y = 0;
      dy *= -1;
      Audio::get_instance().play_wall_hit();
    }
}

void Ball::draw(QPainter & painter) const
{
  painter.drawPixmap(QPoint(x, y), SpriteSheet::get_instance().get(),
                     Global::all_balls[skin]);
}
