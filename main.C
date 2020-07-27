/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <QApplication>
#include <gamemain.H>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  GameMain canvas;
  canvas.show();
  return app.exec();
}
