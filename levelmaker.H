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

#ifndef LEVELMAKER_H
#define LEVELMAKER_H

#include <QVector>

#include <brickset.H>
#include <singleton.H>

class LevelMaker : public Singleton<LevelMaker>
{
  friend class Singleton<LevelMaker>;

protected:
    LevelMaker() = default;

public:
  enum class GlobalPatterns
  {
    NONE, SINGLE_PYRAMID, MULTI_PYRAMID
  };

  enum class PerRowPattern
  {
    SOLID,     // All color the same in this row
    ALTERNATE, // Alternate colors
    SKIP,      // Skip every other block
    NONE       // No block this row
  };

  void create_map(int);
};

#endif // LEVELMAKER_H
