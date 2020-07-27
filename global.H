/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef GLOBAL_H
#define GLOBAL_H

#include <QVector>
#include <QRectF>

class Brick;

class Global
{
public:
  static constexpr double WINDOW_WIDTH = 1280;
  static constexpr double WINDOW_HEIGHT = 720;

  static constexpr double VIRTUAL_WIDTH = 432;
  static constexpr double VIRTUAL_HEIGHT = 243;

  static constexpr double H_SCALE = WINDOW_WIDTH/VIRTUAL_WIDTH;
  static constexpr double V_SCALE = WINDOW_HEIGHT/VIRTUAL_HEIGHT;

  static constexpr double PADDLE_SPEED = 200;

  static constexpr double BALL_WIDTH = 8;
  static constexpr double BALL_HEIGHT = 8;
  static constexpr double POWERUP_WIDTH = 16;
  static constexpr double POWERUP_HEIGHT = 16;
  static constexpr double HEART_WIDTH = 10;
  static constexpr double HEART_HEIGHT = 10;
  static constexpr double ALL_SPRITES_HEIGHT = 16;
  static constexpr double SMALL_SPRITE_WIDTH = 16;
  static constexpr double BRICK_WIDTH = 32;
  static constexpr double PADDLE_WIDTH_FACTOR = 32;
  static constexpr double ARROW_WIDTH = 24;
  static constexpr double ARROW_HEIGHT = 24;

  static constexpr double DEFAULT_PADDLE_SIZE = 1;

  static Brick * locked_brick_ptr;
  static bool paused;
  static int level;
  static int recover_points;
  static int num_live_bricks;

  static const QString high_scores_filename;

  static QVector<QVector<QRectF>> all_paddles;
  static QVector<QRectF> all_balls;
  static QVector<QRectF> all_bricks;
  static QVector<QRectF> all_arrows;
  static QVector<QRectF> all_powerups;
  static QRectF locked_brick;
};

#endif // GLOBAL_H
