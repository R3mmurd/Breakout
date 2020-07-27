/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef STATES_H
#define STATES_H

#include <singleton.H>
#include <statemachine.H>
#include <paddle.H>
#include <ballset.H>
#include <brickset.H>
#include <player.H>
#include <powerup.H>

class GameMain;

class StartState :
    public State<GameMain>,
    public Singleton<StartState>
{
  friend class Singleton<StartState>;

  int highlighted = 1;

protected:
  StartState() = default;

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
  BallSet & balls = BallSet::get_instance();
  BrickSet & bricks = BrickSet::get_instance();

protected:
  ServeState() = default;

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
  BallSet & balls = BallSet::get_instance();
  BrickSet & bricks = BrickSet::get_instance();
  Player & player = Player::get_instance();
  QList<PowerUp> powerups;

  int hit_count = 0;

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
  friend class Singleton<PaddleSelectState>;

  int selected;
protected:
  PaddleSelectState() = default;

public:
  void enter(GameMain *) override;

  void key_pressed(GameMain *, QKeyEvent *) override;

  void draw(GameMain *, QPainter &) override;
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
  BallSet & balls = BallSet::get_instance();

protected:
  VictoryState() = default;
public:
  void update(GameMain *, double) override;

  void draw(GameMain *, QPainter &) override;

  void key_pressed(GameMain *, QKeyEvent *) override;

  void key_released(GameMain *, QKeyEvent *) override;
};

#endif // STATES_H
