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

class GameMain;

class StartState :
    public State<GameMain>,
    public Singleton<StartState>
{
  int highlighted = 1;

public:
  void key_pressed(GameMain *, QKeyEvent *) override;

  void draw(GameMain *, QPainter &) override;
};

class HighScoreState :
    public State<GameMain>,
    public Singleton<HighScoreState>
{

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

};

class GameOverState  :
    public State<GameMain>,
    public Singleton<GameOverState>
{

};

class ServeState :
    public State<GameMain>,
    public Singleton<ServeState>
{

};

class PlayState :
    public State<GameMain>,
    public Singleton<PlayState>
{

};

class VictoryState :
    public State<GameMain>,
    public Singleton<VictoryState>
{

};

#endif // STATES_H
