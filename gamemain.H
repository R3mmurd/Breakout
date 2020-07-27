/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPixmap>

#include <statemachine.H>

class GameMain :
    public QWidget,
    public StateMachine<GameMain>
{
  Q_OBJECT
  QTime time;
  QTimer timer;

  QPixmap background;
  double background_width;
  double background_height;
public:
  explicit GameMain(QWidget *parent = nullptr);

  void paintEvent(QPaintEvent *) override;

  void keyPressEvent(QKeyEvent *) override;

  void keyReleaseEvent(QKeyEvent *) override;

public slots:
  void update_loop();

};

#endif // GAMEMAIN_H
