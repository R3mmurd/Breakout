/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef BALLSET_H
#define BALLSET_H

#include <QList>

#include <singleton.H>
#include <ball.H>

class BallSet :
    public QList<Ball>,
    public Singleton<BallSet>
{
  friend class Singleton<BallSet>;

protected:
  BallSet() = default;
};

#endif // BALLSET_H
