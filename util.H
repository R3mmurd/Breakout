/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef UTIL_H
#define UTIL_H

#include <QVector>
#include <QPixmap>
#include <QRectF>

QVector<QRectF> generate_drawing_rects(double, double, double, double);

QVector<QRectF> slice(const QVector<QRectF> &, int, int, int step=1);

QVector<QVector<QRectF> > generate_paddle_drawing_rects();

QVector<QRectF> generate_ball_drawing_rects();

QVector<QRectF> generate_brick_drawing_rects();

QVector<QRectF> generate_powerup_drawing_rects();

QStringList read_highscores();

void write_highscores(const QStringList &);

#endif // UTIL_H
