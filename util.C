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

#include <util.H>
#include <global.H>
#include <spritesheet.H>

QVector<QRectF> generate_drawing_rects(double width, double height,
                                       double tile_width, double tile_height)
{
  QVector<QRectF> spritesheet;

  double sheet_width = width / tile_width;
  double sheet_height = height / tile_height;

  for (double y = 0; y < sheet_height; y += 1)
    for (double x = 0; x < sheet_width; x += 1)
      spritesheet.append(QRectF(x*tile_width, y*tile_height,
                                tile_width, tile_height));

  return spritesheet;
}

QVector<QRectF> slice(const QVector<QRectF> & v, int first, int last, int step)
{
  QVector<QRectF> result;

  for (int i = first; i < last; i += step)
    result.append(v.at(i));

  return result;
}

QVector<QVector<QRectF>> generate_paddle_drawing_rects()
{
  QVector<QVector<QRectF>> spritsheet;

  double x = 0;
  double y = Global::ALL_SPRITES_HEIGHT*4;

  for (int i = 0; i < 4; ++i)
    {
      QVector<QRectF> paddle_collection;
      // small
      paddle_collection.append(QRectF(x, y,
                                      Global::PADDLE_WIDTH_FACTOR,
                                      Global::ALL_SPRITES_HEIGHT));
      // medium
      paddle_collection.append(QRectF(x + Global::PADDLE_WIDTH_FACTOR, y,
                                      Global::PADDLE_WIDTH_FACTOR*2,
                                      Global::ALL_SPRITES_HEIGHT));
      // large
      paddle_collection.append(QRectF(x + Global::PADDLE_WIDTH_FACTOR*3, y,
                                      Global::PADDLE_WIDTH_FACTOR*3,
                                      Global::ALL_SPRITES_HEIGHT));
      // huge
      paddle_collection.append(QRectF(x, y + Global::ALL_SPRITES_HEIGHT,
                                      Global::PADDLE_WIDTH_FACTOR*4,
                                      Global::ALL_SPRITES_HEIGHT));

      spritsheet.append(paddle_collection);
      y += Global::ALL_SPRITES_HEIGHT*2;
    }

  return spritsheet;
}

QVector<QRectF> generate_ball_drawing_rects()
{
  QVector<QRectF> spritesheet;

  double y = Global::ALL_SPRITES_HEIGHT*3;

  for (int row = 0; row < 2; ++row)
    {
      double x = Global::BRICK_WIDTH*3;

      for (int col = 0; col < 4-row; ++col)
        {
          spritesheet.append(QRectF(x, y,
                                    Global::BALL_WIDTH, Global::BALL_HEIGHT));
          x += Global::BALL_WIDTH;
        }
      y += Global::BALL_HEIGHT;
    }

  return spritesheet;
}


QVector<QRectF> generate_brick_drawing_rects()
{
  return slice(generate_drawing_rects(Global::BRICK_WIDTH*6,
                                      Global::ALL_SPRITES_HEIGHT*4,
                                      Global::BRICK_WIDTH,
                                      Global::ALL_SPRITES_HEIGHT), 0, 21);

}
