/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <QPainter>

#include <gamemain.H>
#include <global.H>

#include <states.H>
#include <audio.H>

#include <QDebug>

GameMain::GameMain(QWidget * parent)
  : QWidget(parent), StateMachine<GameMain>(StartState::get_ptr_instance()),
    background(":/images/background"), background_width(background.width()),
    background_height(background.height())
{
  Audio::get_instance().play_music();
  setFixedSize(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update_loop()));
  timer.setInterval(33);
  time.start();
  timer.start();
}

void GameMain::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.scale(Global::H_SCALE, Global::V_SCALE);
  painter.setPen(Qt::white);
  painter.drawPixmap(0, 0, Global::VIRTUAL_WIDTH,
                     Global::VIRTUAL_HEIGHT, background);
  StateMachine::draw(painter);
}

void GameMain::keyPressEvent(QKeyEvent * event)
{
  StateMachine::key_pressed(event);
}

void GameMain::keyReleaseEvent(QKeyEvent * event)
{
  StateMachine::key_released(event);
}

void GameMain::update_loop()
{
  double dt = time.elapsed()/1000.0;
  time.restart();
  StateMachine::update(dt);
  repaint();
}
