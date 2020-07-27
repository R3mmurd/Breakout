/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <spritesheet.H>

SpriteSheet::SpriteSheet()
  : breakout(":/images/breakout"), arrows(":/images/arrows"),
    opaque_arrows(":/images/opaque-arrows")
{
  // Empty
}

const QPixmap & SpriteSheet::get_breakout() const
{
  return breakout;
}

const QPixmap & SpriteSheet::get_arrows() const
{
  return arrows;
}

const QPixmap & SpriteSheet::get_opaque_arrows() const
{
  return opaque_arrows;
}
