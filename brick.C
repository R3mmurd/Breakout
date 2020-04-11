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

#include <brick.H>
#include <spritesheet.H>
#include <audio.H>


Brick::Brick(double _x, double _y)
  : x(_x), y(_y)
{

}

bool Brick::is_in_play() const
{
  return in_play;
}

void Brick::hit()
{
  Audio::get_instance().play_brick_hit_2();
  in_play = false;
}

QRectF Brick::get_collision_rect() const
{
  return QRectF(x, y, Global::BRICK_WIDTH, Global::ALL_SPRITES_HEIGHT);
}

void Brick::draw(QPainter & painter) const
{
  if (not in_play)
    return;
  painter.drawPixmap(QPoint(x, y), SpriteSheet::get_instance().get(),
                     Global::all_bricks[color*4+tier]);
}
