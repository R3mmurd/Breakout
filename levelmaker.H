/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef LEVELMAKER_H
#define LEVELMAKER_H

#include <QVector>

#include <brickset.H>
#include <singleton.H>

class LevelMaker : public Singleton<LevelMaker>
{
  friend class Singleton<LevelMaker>;

protected:
    LevelMaker() = default;

public:
  enum class GlobalPatterns
  {
    NONE, SINGLE_PYRAMID, MULTI_PYRAMID
  };

  enum class PerRowPattern
  {
    SOLID,     // All color the same in this row
    ALTERNATE, // Alternate colors
    SKIP,      // Skip every other block
    NONE       // No block this row
  };

  void create_map(int);
};

#endif // LEVELMAKER_H
