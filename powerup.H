#ifndef POWERUP_H
#define POWERUP_H

#include <QPainter>
#include <QRectF>

class PowerUp
{
public:
  enum class Type {
    BALL = 8,  // Two more balls will be added
    KEY = 9    // Unlock the locked brick
  };

private:
  double x;
  double y;
  double dy;

  Type type;

public:
  PowerUp() = default;

  PowerUp(double, double, Type);

  double get_x() const;

  double get_y() const;

  Type get_type() const;

  QRectF get_collision_rect() const;

  void update(double);

  void draw(QPainter &) const;
};

#endif // POWERUP_H
