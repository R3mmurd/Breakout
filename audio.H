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

#ifndef AUDIO_H
#define AUDIO_H

#include <QSound>

#include <singleton.H>

class Audio : public Singleton<Audio>
{
  QSound * paddle_hit;
  QSound * score;
  QSound * wall_hit;
  QSound * confirm;
  QSound * select;
  QSound * no_select;
  QSound * brick_hit_1;
  QSound * brick_hit_2;
  QSound * hurt;
  QSound * victory;
  QSound * recover;
  QSound * high_score;
  QSound * pause;
  QSound * music;
public:
  Audio();

  void play_paddle_hit();

  void play_score();

  void play_wall_hit();

  void play_confirm();

  void play_select();

  void play_no_select();

  void play_brick_hit_1();

  void play_brick_hit_2();

  void play_hurt();

  void play_victory();

  void play_recover();

  void play_high_score();

  void play_pause();

  void play_music();

  void stop_music();
};

#endif // AUDIO_H
