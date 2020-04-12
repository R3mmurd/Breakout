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

#ifndef STATES_H
#define STATES_H

#include <singleton.H>
#include <statemachine.H>
#include <paddle.H>
#include <ball.H>
#include <bricks.H>
#include <player.H>

class GameMain;

class StartState :
    public State<GameMain>,
    public Singleton<StartState>
{
  friend class Singleton<StartState>;

  int highlighted = 1;

protected:
  StartState();

public:
  void enter(GameMain *) override;

  void key_pressed(GameMain *, QKeyEvent *) override;

  void draw(GameMain *, QPainter &) override;
};

class ServeState :
    public State<GameMain>,
    public Singleton<ServeState>
{
  friend class Singleton<ServeState>;

  Paddle & paddle = Paddle::get_instance();
  Ball & ball = Ball::get_instance();
  Bricks & bricks = Bricks::get_instance();

protected:
  ServeState();

public:
  void enter(GameMain *) override;

  void update(GameMain *, double) override;

  void draw(GameMain *, QPainter &) override;

  void key_pressed(GameMain *, QKeyEvent *) override;

  void key_released(GameMain *, QKeyEvent *) override;
};

class PlayState :
    public State<GameMain>,
    public Singleton<PlayState>
{
  friend class Singleton<PlayState>;

  Paddle & paddle = Paddle::get_instance();
  Ball & ball = Ball::get_instance();
  Bricks & bricks = Bricks::get_instance();
  Player & player = Player::get_instance();

protected:
  PlayState() = default;
public:
  void enter(GameMain *) override;

  void update(GameMain *, double) override;

  void draw(GameMain *, QPainter &) override;

  void key_pressed(GameMain *, QKeyEvent *) override;

  void key_released(GameMain *, QKeyEvent *) override;
};

class HighScoreState :
    public State<GameMain>,
    public Singleton<HighScoreState>
{
  friend class Singleton<HighScoreState>;

  QStringList highscores;

protected:
  HighScoreState() = default;

public:
  void enter(GameMain *) override;

  void exit(GameMain *) override;

  void key_pressed(GameMain *, QKeyEvent *) override;

  void draw(GameMain *, QPainter &) override;
};

class PaddleSelectState :
    public State<GameMain>,
    public Singleton<PaddleSelectState>
{

};

class EnterHighScoreState :
    public State<GameMain>,
    public Singleton<EnterHighScoreState>
{
  friend class Singleton<EnterHighScoreState>;

  char chars[3] = {'A', 'A', 'A'};
  int highlighted = 0;
  QStringList highscores;

protected:
  EnterHighScoreState() = default;

public:
  void enter(GameMain *) override;

  void exit(GameMain *) override;

  void key_pressed(GameMain *, QKeyEvent *) override;

  void draw(GameMain *, QPainter &) override;
};

class GameOverState  :
    public State<GameMain>,
    public Singleton<GameOverState>
{
  void key_pressed(GameMain *, QKeyEvent *) override;

  void draw(GameMain *, QPainter &) override;
};

class VictoryState :
    public State<GameMain>,
    public Singleton<VictoryState>
{
  friend class Singleton<VictoryState>;

  Paddle & paddle = Paddle::get_instance();
  Ball & ball = Ball::get_instance();

protected:
  VictoryState() = default;
public:
  void update(GameMain *, double) override;

  void draw(GameMain *, QPainter &) override;

  void key_pressed(GameMain *, QKeyEvent *) override;

  void key_released(GameMain *, QKeyEvent *) override;
};

#endif // STATES_H
