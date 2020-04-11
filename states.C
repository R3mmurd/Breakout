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
#include <global.H>
#include <gamemain.H>
#include <spritesheet.H>
#include <random.H>
#include <levelmaker.H>

#include <QDebug>

void StartState::key_pressed(GameMain * sm, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Up or event->key() == Qt::Key_Down)
    {
      highlighted = (highlighted == 1 ? 2 : 1);
      Audio::get_instance().play_paddle_hit();
    }
  else if (event->key() == Qt::Key_Return or event->key() == Qt::Key_Enter)
    {
      if (highlighted == 1)
        sm->change_state(PlayState::get_ptr_instance());
    }
}

void StartState::draw(GameMain *, QPainter & painter)
{
  painter.setFont(Font::get_instance().large_font());
  painter.drawText(0, 0, Global::VIRTUAL_WIDTH,
                   Global::VIRTUAL_HEIGHT, Qt::AlignCenter, "BREAKOUT");

  painter.setFont(Font::get_instance().medium_font());

  if (highlighted == 1)
    painter.setPen(QColor(103, 255, 255));

  painter.drawText(0, Global::VIRTUAL_HEIGHT/2 + 50,
                   Global::VIRTUAL_WIDTH,
                   Global::VIRTUAL_HEIGHT/2 - 50,
                   Qt::AlignHCenter, "START");
  painter.setPen(Qt::white);

  if (highlighted == 2)
    painter.setPen(QColor(103, 255, 255));

  painter.drawText(0, Global::VIRTUAL_HEIGHT/2 + 75,
                   Global::VIRTUAL_WIDTH,
                   Global::VIRTUAL_HEIGHT/2 - 75,
                   Qt::AlignHCenter, "HIGH SCORES");
  painter.setPen(Qt::white);
}

PlayState::PlayState()
  : ball(Random::get_instance().random(7)),
    bricks(LevelMaker::get_instance().create_map())
{
  ball.set_velocity(Random::get_instance().random(-200, 200),
                    Random::get_instance().random(-60, -50));

  ball.set_position(Global::VIRTUAL_WIDTH/2 - Global::BALL_WIDTH/2,
                    Global::VIRTUAL_HEIGHT - 42);
}

void PlayState::update(GameMain *, double dt)
{
  if (Global::paused)
    return;

  paddle.update(dt);
  ball.update(dt);

  QRectF paddle_collision_rect = paddle.get_collision_rect();

  if (ball.collides(paddle_collision_rect))
    {
      ball.set_y(paddle.get_collision_rect().top()-Global::BALL_HEIGHT);
      ball.set_dy(-ball.get_dy());
      Audio::get_instance().play_paddle_hit();
    }

  for (Brick & b : bricks)
    if (b.is_in_play() and ball.collides(b.get_collision_rect()))
      b.hit();

}

void PlayState::draw(GameMain *, QPainter & painter)
{
  if (Global::paused)
    {
      painter.setFont(Font::get_instance().large_font());
      painter.drawText(0, 0,
                       Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT,
                       Qt::AlignCenter, "PAUSED");
    }
  paddle.draw(painter);
  ball.draw(painter);

  for (const Brick & b : bricks)
    b.draw(painter);
}

void PlayState::key_pressed(GameMain *, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Space)
    {
      Global::paused = not Global::paused;
      Audio::get_instance().play_pause();
    }

  if (Global::paused)
    return;

  if (event->key() == Qt::Key_Left)
    paddle.move_left();
  else if (event->key() == Qt::Key_Right)
    paddle.move_right();
}

void PlayState::key_released(GameMain *, QKeyEvent *)
{
  paddle.stop();
}
