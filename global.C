/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <global.H>
#include <util.H>

Brick * Global::locked_brick_ptr = nullptr;

bool Global::paused = false;

int Global::level = 0;

int Global::recover_points = 0;

int Global::num_live_bricks = 0;

const QString Global::high_scores_filename = "highscores.txt";

QVector<QVector<QRectF>> Global::all_paddles = generate_paddle_drawing_rects();

QVector<QRectF> Global::all_balls = generate_ball_drawing_rects();

QVector<QRectF> Global::all_bricks = generate_brick_drawing_rects();

QVector<QRectF> Global::all_arrows = {
  QRectF(0, 0, Global::ARROW_WIDTH, Global::ARROW_HEIGHT),
  QRectF(Global::ARROW_WIDTH, 0, Global::ARROW_WIDTH, Global::ARROW_HEIGHT)
};

QVector<QRectF> Global::all_powerups = generate_powerup_drawing_rects();

QRectF Global::locked_brick =
    QRectF(Global::BRICK_WIDTH*5, Global::ALL_SPRITES_HEIGHT*3,
           Global::BRICK_WIDTH, Global::ALL_SPRITES_HEIGHT);
