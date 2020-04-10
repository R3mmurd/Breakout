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

#include <states.H>
#include <audio.H>
#include <font.H>
#include <constants.H>

void StartState::key_pressed(GameMain *, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Up or event->key() == Qt::Key_Down)
    {
      highlighted = (highlighted == 1 ? 2 : 1);
      Audio::get_instance().play_paddle_hit();
    }
}

void StartState::draw(GameMain *, QPainter & painter)
{
  painter.setFont(Font::get_instance().large_font());
  painter.drawText(0, 0, Constants::VIRTUAL_WIDTH,
                   Constants::VIRTUAL_HEIGHT, Qt::AlignCenter, "BREAKOUT");

  painter.setFont(Font::get_instance().medium_font());

  if (highlighted == 1)
    painter.setPen(QColor(103, 255, 255));

  painter.drawText(0, Constants::VIRTUAL_HEIGHT/2 + 50,
                   Constants::VIRTUAL_WIDTH,
                   Constants::VIRTUAL_HEIGHT/2 - 50,
                   Qt::AlignHCenter, "START");
  painter.setPen(Qt::white);

  if (highlighted == 2)
    painter.setPen(QColor(103, 255, 255));

  painter.drawText(0, Constants::VIRTUAL_HEIGHT/2 + 75,
                   Constants::VIRTUAL_WIDTH,
                   Constants::VIRTUAL_HEIGHT/2 - 75,
                   Qt::AlignHCenter, "HIGH SCORES");
  painter.setPen(Qt::white);
}
