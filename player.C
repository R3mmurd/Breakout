#include <player.H>
#include <spritesheet.H>
#include <global.H>
#include <font.H>

QRectF Player::fill_heart_drawing_rect =
    QRect(Global::BRICK_WIDTH*3 + Global::BALL_WIDTH*4,
          Global::ALL_SPRITES_HEIGHT*3,
          Global::HEART_WIDTH, Global::HEART_HEIGHT);
QRectF Player::empty_heart_drawing_rect =
    QRect(Global::BRICK_WIDTH*3 + Global::BALL_WIDTH*4 + Global::HEART_WIDTH,
          Global::ALL_SPRITES_HEIGHT*3,
          Global::HEART_WIDTH, Global::HEART_HEIGHT);

int Player::get_score() const
{
  return score;
}

int Player::get_health() const
{
  return health;
}

void Player::reset()
{
  health = 3;
  score = 0;
}

void Player::dec_health()
{
  if (health == 0)
    return;
  --health;
}

void Player::add_score(int value)
{
  score += value;
}

void Player::draw(QPainter & painter) const
{
  double x = Global::VIRTUAL_WIDTH - 140;

  int i = 0;

  while (i < health)
    {
      painter.drawPixmap(QPoint(x, 3), SpriteSheet::get_instance().get_breakout(),
                         fill_heart_drawing_rect);
      x += 11;
      ++i;
    }

  while (i < 3)
    {
      painter.drawPixmap(QPoint(x, 3), SpriteSheet::get_instance().get_breakout(),
                         empty_heart_drawing_rect);
      x += 11;
      ++i;
    }

  painter.setFont(Font::get_instance().small_font());
  painter.drawText(Global::VIRTUAL_WIDTH - 100, 3, 40, 10,
                   Qt::AlignLeft, "Score:");
  painter.drawText(Global::VIRTUAL_WIDTH - 60, 3, 40, 10,
                   Qt::AlignRight, QString().setNum(score));
}
