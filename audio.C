/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
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
  brick_hit_1->stop();
  brick_hit_1->play();
}

void Audio::play_brick_hit_2()
{
  brick_hit_2->stop();
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
