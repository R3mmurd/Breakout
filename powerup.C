/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <powerup.H>
#include <global.H>
#include <spritesheet.H>

PowerUp::PowerUp(double _x, double _y, PowerUp::Type t)
  : x(_x), y(_y), dy(50), type(t)
{
  // Empty
}

double PowerUp::get_x() const
{
  return x;
}

double PowerUp::get_y() const
{
  return y;
}

PowerUp::Type PowerUp::get_type() const
{
  return type;
}

QRectF PowerUp::get_collision_rect() const
{
  return QRectF(x, y, Global::POWERUP_WIDTH, Global::POWERUP_HEIGHT);
}

void PowerUp::update(double dt)
{
  y += dy*dt;
}

void PowerUp::draw(QPainter & painter) const
{
  painter.drawPixmap(QPoint(x, y), SpriteSheet::get_instance().get_breakout(),
                     Global::all_powerups[int(type)]);
}
