#include <QPainter>

#include <gamemain.H>
#include <constants.H>

#include <states.H>

#include <QDebug>

GameMain::GameMain(QWidget * parent)
  : QWidget(parent), StateMachine<GameMain>(StartState::get_ptr_instance()),
    background(":/images/background"), background_width(background.width()),
    background_height(background.height())
{
  setFixedSize(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
  connect(&timer, SIGNAL(timeout()), this, SLOT(update_loop()));
  timer.setInterval(60);
  time.start();
  timer.start();
}

void GameMain::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.scale(Constants::H_SCALE, Constants::V_SCALE);
  painter.setPen(Qt::white);
  painter.drawPixmap(0, 0, Constants::VIRTUAL_WIDTH,
                     Constants::VIRTUAL_HEIGHT, background);
  StateMachine::draw(painter);
}

void GameMain::keyPressEvent(QKeyEvent * event)
{
  StateMachine::key_pressed(event);
}

void GameMain::update_loop()
{
  double dt = time.elapsed()/1000.0;
  time.restart();
  StateMachine::update(dt);
  repaint();
}
