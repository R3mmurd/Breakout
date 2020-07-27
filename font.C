/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <font.H>

#include <QFontDatabase>

Font::Font()
{
  QFontDatabase font_db;
  int id = font_db.addApplicationFont(":/fonts/font");
  QString family = font_db.applicationFontFamilies(id).first();
  small.setFamily(family);
  small.setPointSize(8);
  medium.setFamily(family);
  medium.setPointSize(16);
  large.setFamily(family);
  large.setPixelSize(32);
}

QFont Font::small_font()
{
  return small;
}

QFont Font::medium_font()
{
  return medium;
}

QFont Font::large_font()
{
  return large;
}

