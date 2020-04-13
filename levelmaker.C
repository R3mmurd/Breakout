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

void LevelMaker::create_map(int level)
{
  Random & random = Random::get_instance();
  int num_rows = random.unif(1, 6);
  int num_cols = random.unif(7, 14);
  if (num_cols % 2 == 0)
    ++num_cols;

  int highest_tier = std::min(3, level/5);
  int highest_color = std::min(5, level % 5 + 3);

  BrickSet & bricks = BrickSet::get_instance();
  bricks.clear();

  while (bricks.empty())
    {
      for (int y = 1; y <= num_rows; ++y)
        {
          bool skip_pattern = random.flip_coin();
          bool skip_flag = random.flip_coin();
          bool alternate_pattern = random.flip_coin();
          bool alternate_flag = random.flip_coin();
          int alternate_color_1 = random.unif(0, highest_color);
          int alternate_color_2 = random.unif(0, highest_color);
          int alternate_tier_1 = random.unif(0, highest_tier + 1);
          int alternate_tier_2 = random.unif(0, highest_tier + 1);
          int solid_color = random.unif(0, highest_color);
          int solid_tier = random.unif(0, highest_tier + 1);
          for (int x = 0; x < num_cols; ++x)
            {
              if (skip_pattern and skip_flag)
                {
                  skip_flag = not skip_flag;
                  continue;
                }

              skip_flag = not skip_flag;
              Brick b(x * Global::BRICK_WIDTH + 8 + (13 - num_cols) * 16,
                      y * Global::ALL_SPRITES_HEIGHT);

              if (alternate_pattern and alternate_flag)
                {
                  b.set_color(alternate_color_1);
                  b.set_tier(alternate_tier_1);
                  alternate_flag = not alternate_flag;
                }
              else
                {
                  b.set_color(alternate_color_2);
                  b.set_tier(alternate_tier_2);
                  alternate_flag = not alternate_flag;
                }

              if (not alternate_pattern)
                {
                  b.set_color(solid_color);
                  b.set_tier(solid_tier);
                }

              bricks.append(b);

              if (Global::locked_brick_ptr == nullptr and random.flip_coin(0.1))
                {
                  bricks.last().lock();
                  Global::locked_brick_ptr = &bricks.last();
                }
            }
        }
    }
}
