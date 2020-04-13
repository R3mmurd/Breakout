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
