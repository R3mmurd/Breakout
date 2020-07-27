/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef FONT_H
#define FONT_H

#include <QFont>

#include <singleton.H>

class Font : public Singleton<Font>
{
  QFont small;
  QFont medium;
  QFont large;

public:
  Font();

  QFont small_font();

  QFont medium_font();

  QFont large_font();
};

#endif // FONT_H
