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

#include <levelmaker.H>
#include <random.H>
#include <global.H>

LevelMaker::LevelMaker()
{

}

QVector<Brick> LevelMaker::create_map()
{
  int num_rows = Random::get_instance().random(1, 5);
  int num_cols = Random::get_instance().random(7, 13);

  QVector<Brick> bricks;

  for (int y = 1; y <= num_rows; ++y)
    for (int x = 0; x < num_cols; ++x)
      {
        Brick b(x * Global::BRICK_WIDTH + 8 + (13 - num_cols) * 16,
                y * Global::ALL_SPRITES_HEIGHT);
        bricks.append(b);
      }

  return bricks;
}
