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

#include <audio.H>

Audio::Audio()
{
   paddle_hit = new QSound(":/audio/paddle-hit");
   score = new QSound(":/audio/score");
   wall_hit = new QSound(":/audio/wall-hit");
   confirm = new QSound(":/audio/confirm");
   select = new QSound(":/audio/select");
   no_select = new QSound(":/audio/no-select");
   brick_hit_1 = new QSound(":/audio/brick-hit-1");
   brick_hit_2 = new QSound(":/audio/brick-hit-2");
   hurt = new QSound(":/audio/hurt");
   victory = new QSound(":/audio/victory");
   recover = new QSound(":/audio/recover");
   high_score = new QSound(":/audio/high-score");
   pause = new QSound(":/audio/pause");
   music = new QSound(":/audio/music");
}

void Audio::play_paddle_hit()
{
  paddle_hit->play();
}

void Audio::play_score()
{
  score->play();
}

void Audio::play_wall_hit()
{
  wall_hit->play();
}

void Audio::play_confirm()
{
  confirm->play();
}

void Audio::play_select()
{
  select->play();
}

void Audio::play_no_select()
{
  no_select->play();
}

void Audio::play_brick_hit_1()
{
  brick_hit_1->play();
}

void Audio::play_brick_hit_2()
{
  brick_hit_2->play();
}

void Audio::play_hurt()
{
  hurt->play();
}

void Audio::play_victory()
{
  victory->play();
}

void Audio::play_recover()
{
  recover->play();
}

void Audio::play_high_score()
{
  high_score->play();
}

void Audio::play_pause()
{
  pause->play();
}

void Audio::play_music()
{
  music->setLoops(QSound::Infinite);
  music->play();
}

void Audio::stop_music()
{
  music->stop();
}
