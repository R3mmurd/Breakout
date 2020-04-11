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

#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPixmap>

#include <statemachine.H>

class GameMain :
    public QWidget,
    public StateMachine<GameMain>
{
  Q_OBJECT
  QTime time;
  QTimer timer;

  QPixmap background;
  double background_width;
  double background_height;
public:
  explicit GameMain(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *) override;

  void keyPressEvent(QKeyEvent *) override;

  void keyReleaseEvent(QKeyEvent *) override;

public slots:
  void update_loop();

};

#endif // GAMEMAIN_H
