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

#include <font.H>

#include <QFontDatabase>

Font::Font()
{
  QFontDatabase font_db;
  int id = font_db.addApplicationFont(":/fonts/font");
  QString family = font_db.applicationFontFamilies(id).first();
  small.setFamily(family);
  small.setPointSize(8);
  medium.setFamily(family);
  medium.setPointSize(16);
  large.setFamily(family);
  large.setPixelSize(32);
}

QFont Font::small_font()
{
  return small;
}

QFont Font::medium_font()
{
  return medium;
}

QFont Font::large_font()
{
  return large;
}

