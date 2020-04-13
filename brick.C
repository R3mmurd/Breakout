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


const std::tuple<int, int, int> Brick::color_palette[5] = {
  std::make_tuple(99, 155, 255),  // blue
  std::make_tuple(106, 190, 47),  // green
  std::make_tuple(217, 87, 99),   // red
  std::make_tuple(215, 123, 186), // purple
  std::make_tuple(251, 242, 54)   // gold
};

Brick::Brick()
  : ps(x, y, 64)
{
  // Empty
}

Brick::Brick(double _x, double _y)
  : x(_x), y(_y),
    ps(x + Global::BRICK_WIDTH/2, y + Global::ALL_SPRITES_HEIGHT/2, 64)
{
  ps.set_life_time(0.5, 1);
  ps.set_linear_acceleration(-1.5, 0, 1.5, 4);
  ps.set_area_spread(7, 7);
}

void Brick::set_color(int value)
{
  color = value;
}

void Brick::set_tier(int value)
{
  tier = value;
}

int Brick::score() const
{
  if (locked)
    return 0;
  return tier*200 + color*25;
}

bool Brick::is_locked() const
{
  return locked;
}

void Brick::lock()
{
  locked = true;
}

void Brick::unlock()
{
  locked = false;
}

bool Brick::is_in_play() const
{
  return in_play;
}

void Brick::hit()
{
  Audio::get_instance().play_brick_hit_2();

  if (locked)
    return;

  auto t = color_palette[color];
  ps.set_colors({
                  QColor(std::get<0>(t), std::get<1>(t), std::get<2>(t),
                  55*(tier+1)),
                  QColor(std::get<0>(t), std::get<1>(t), std::get<2>(t), 0)
                });
  ps.generate();
  if (tier > 0)
    {
      if (color == 0)
        {
          tier -= 1;
          color = 4;
        }
      else
        --color;
    }
  else
    {
      if (color == 0)
        {
          in_play = false;
          Audio::get_instance().play_brick_hit_1();
        }
      else
        --color;
    }
}

QRectF Brick::get_collision_rect() const
{
  return QRectF(x, y, Global::BRICK_WIDTH, Global::ALL_SPRITES_HEIGHT);
}

void Brick::update(double dt)
{
  ps.update(dt);
}

void Brick::draw(QPainter & painter) const
{
  if (in_play)
    {
      if (locked)
        painter.drawPixmap(QPoint(x, y), SpriteSheet::get_instance().get_breakout(),
                         Global::locked_brick);
      else
        painter.drawPixmap(QPoint(x, y), SpriteSheet::get_instance().get_breakout(),
                            Global::all_bricks[color*4+tier]);
    }
  ps.draw(painter);
}
