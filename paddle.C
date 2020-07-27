/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <paddle.H>
#include <global.H>
#include <spritesheet.H>

void Paddle::set_skin(int value)
{
    skin = value;
}

double Paddle::get_width() const
{
    return Global::all_paddles[skin][size].width();
}

double Paddle::get_height() const
{
  return Global::all_paddles[skin][size].height();
}

double Paddle::get_x() const
{
  return x;
}

double Paddle::get_y() const
{
  return y;
}

double Paddle::get_dx() const
{
  return dx;
}

void Paddle::reset()
{
  size = 1;
  x = Global::VIRTUAL_WIDTH/2 - get_width()/2;
  y = Global::VIRTUAL_HEIGHT - 32;
}

QRectF Paddle::get_collision_rect() const
{
  return QRectF(x, y, get_width(), get_height());
}

void Paddle::move_left()
{
  dx = -Global::PADDLE_SPEED;
}

void Paddle::move_right()
{
  dx = Global::PADDLE_SPEED;
}

void Paddle::stop()
{
  dx = 0;
}

void Paddle::update(double dt)
{
  double nx = x + dx*dt;

  if (dx < 0)
    x = std::max<double>(0, nx);
  else if (dx > 0)
    x = std::min<double>(Global::VIRTUAL_WIDTH - get_width(), nx);
}

void Paddle::draw(QPainter & painter) const
{
  painter.drawPixmap(QPoint(x, y), SpriteSheet::get_instance().get_breakout(),
                     Global::all_paddles[skin][size]);
}
