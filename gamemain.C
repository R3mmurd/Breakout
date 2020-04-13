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

#include <QPainter>

#include <gamemain.H>
#include <global.H>

#include <states.H>
#include <audio.H>

#include <QDebug>

GameMain::GameMain(QWidget * parent)
  : QWidget(parent), StateMachine<GameMain>(StartState::get_ptr_instance()),
    background(":/images/background"), background_width(background.width()),
    background_height(background.height())
{
  Audio::get_instance().play_music();
  setFixedSize(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update_loop()));
  timer.setInterval(33);
  time.start();
  timer.start();
}

void GameMain::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.scale(Global::H_SCALE, Global::V_SCALE);
  painter.setPen(Qt::white);
  painter.drawPixmap(0, 0, Global::VIRTUAL_WIDTH,
                     Global::VIRTUAL_HEIGHT, background);
  StateMachine::draw(painter);
}

void GameMain::keyPressEvent(QKeyEvent * event)
{
  StateMachine::key_pressed(event);
}

void GameMain::keyReleaseEvent(QKeyEvent * event)
{
  StateMachine::key_released(event);
}

void GameMain::update_loop()
{
  double dt = time.elapsed()/1000.0;
  time.restart();
  StateMachine::update(dt);
  repaint();
}
