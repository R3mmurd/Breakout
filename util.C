/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <QDir>
#include <QTextStream>

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

QVector<QRectF> generate_powerup_drawing_rects()
{
  double x = 0;
  double y = Global::ALL_SPRITES_HEIGHT*12;

  QVector<QRectF> spritesheet;

  for (int i = 0; i < 10; ++i)
    {
      spritesheet.append(QRectF(x, y, Global::POWERUP_WIDTH,
                              Global::POWERUP_HEIGHT));
      x += Global::POWERUP_WIDTH;
    }

  return spritesheet;
}

QStringList read_highscores()
{
  QString path = QDir::homePath() + QDir::separator() + QString(".breakout");
  QDir dir(path);
  if (not dir.exists())
    dir.mkdir(path);
  QString filename = path + QDir::separator() + Global::high_scores_filename;

  QFile file(filename);

  if (not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      file.open(QIODevice::WriteOnly | QIODevice::Text);
      file.close();
      file.open(QIODevice::ReadOnly | QIODevice::Text);
    }

  QStringList highscores;
  QTextStream in(&file);
  while (not in.atEnd())
    highscores.append(in.readLine());
  file.close();
  return highscores;
}

void write_highscores(const QStringList & highscores)
{
  QString path = QDir::homePath() + QDir::separator() + QString(".breakout");
  QDir dir(path);
  if (not dir.exists())
    dir.mkdir(path);
  QString filename = path + QDir::separator() + Global::high_scores_filename;

  QFile file(filename);
  file.open(QIODevice::WriteOnly | QIODevice::Text);

  QTextStream out(&file);

  for (const QString s : highscores)
    out << s << "\n";

  file.close();
}
