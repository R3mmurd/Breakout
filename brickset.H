/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef BRICKS_H
#define BRICKS_H

#include <QList>

#include <brick.H>
#include <singleton.H>

class BrickSet :
    public QList<Brick>,
    public Singleton<BrickSet>
{
  friend class Singleton<BrickSet>;

protected:
  BrickSet() = default;
};

#endif // BRICKS_H
