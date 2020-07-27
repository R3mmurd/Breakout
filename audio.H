/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
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
