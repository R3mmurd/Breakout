#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QPainter>
#include <QRectF>

#include <singleton.H>

class Player : public Singleton<Player>
{
  friend class Singleton<Player>;

  static QRectF fill_heart_drawing_rect;
  static QRectF empty_heart_drawing_rect;

  int health = 3;
  int score = 0;

protected:
  Player() = default;

public:
  int get_score() const;

  int get_health() const;

  void reset();

  void dec_health();

  void inc_health();

  void add_score(int value = 1);

  void draw(QPainter &) const;

};

#endif // PLAYERINFO_H
