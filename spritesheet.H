/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <QPixmap>

#include <singleton.H>


class SpriteSheet : public Singleton<SpriteSheet>
{
  friend class Singleton<SpriteSheet>;

  QPixmap breakout;
  QPixmap arrows;
  QPixmap opaque_arrows;

protected:
  SpriteSheet();

public:
  const QPixmap & get_breakout() const;

  const QPixmap & get_arrows() const;

  const QPixmap & get_opaque_arrows() const;
};

#endif // SPRITESHEET_H
