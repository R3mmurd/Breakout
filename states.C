/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <states.H>
#include <audio.H>
#include <font.H>
#include <global.H>
#include <gamemain.H>
#include <spritesheet.H>
#include <random.H>
#include <levelmaker.H>
#include <util.H>

void StartState::enter(GameMain *)
{
  Player::get_instance().reset();
}

void StartState::key_pressed(GameMain * sm, QKeyEvent * event)
{
  if (event->isAutoRepeat())
    return;

  if (event->key() == Qt::Key_Up or event->key() == Qt::Key_Down)
    {
      highlighted = (highlighted == 1 ? 2 : 1);
      Audio::get_instance().play_paddle_hit();
    }
  else if (event->key() == Qt::Key_Return or event->key() == Qt::Key_Enter)
    {
      if (highlighted == 1)
        {
          Global::level = 1;
          Global::recover_points = 5000;
          LevelMaker::get_instance().create_map(Global::level);
          Global::num_live_bricks = BrickSet::get_instance().size();
          Paddle::get_instance().reset();
          sm->change_state(PaddleSelectState::get_ptr_instance());
        }
      else
        sm->change_state(HighScoreState::get_ptr_instance());
    }
}

void StartState::draw(GameMain *, QPainter & painter)
{
  painter.setFont(Font::get_instance().large_font());
  painter.drawText(0, 0, Global::VIRTUAL_WIDTH,
                   Global::VIRTUAL_HEIGHT, Qt::AlignCenter, "BREAKOUT");

  painter.setFont(Font::get_instance().medium_font());

  if (highlighted == 1)
    painter.setPen(QColor(103, 255, 255));

  painter.drawText(0, Global::VIRTUAL_HEIGHT/2 + 50,
                   Global::VIRTUAL_WIDTH,
                   Global::VIRTUAL_HEIGHT/2 - 50,
                   Qt::AlignHCenter, "START");
  painter.setPen(Qt::white);

  if (highlighted == 2)
    painter.setPen(QColor(103, 255, 255));

  painter.drawText(0, Global::VIRTUAL_HEIGHT/2 + 75,
                   Global::VIRTUAL_WIDTH,
                   Global::VIRTUAL_HEIGHT/2 - 75,
                   Qt::AlignHCenter, "HIGH SCORES");
  painter.setPen(Qt::white);
}

void ServeState::enter(GameMain *)
{
  balls.clear();
  balls.append(
        Ball(paddle.get_x() + paddle.get_width()/2.0 - Global::BALL_WIDTH/2.0,
             paddle.get_y() - Global::BALL_HEIGHT));
}

void ServeState::update(GameMain *, double dt)
{
  paddle.update(dt);
  balls.begin()->set_position(
    paddle.get_x() + paddle.get_width()/2.0 - Global::BALL_WIDTH/2.0,
    paddle.get_y() - Global::BALL_HEIGHT
  );
}

void ServeState::draw(GameMain *, QPainter & painter)
{
  Player::get_instance().draw(painter);
  paddle.draw(painter);

  for (const Ball & ball : balls)
    ball.draw(painter);

  for (const Brick & b : bricks)
    b.draw(painter);

  painter.setFont(Font::get_instance().large_font());
  painter.drawText(0, 0, Global::VIRTUAL_WIDTH, 2*Global::VIRTUAL_HEIGHT/3,
                   Qt::AlignCenter, QString("Level ")
                   + QString().setNum(Global::level)
                   );

  painter.setFont(Font::get_instance().medium_font());
  painter.drawText(0, 0,Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT,
                   Qt::AlignCenter, "Press Enter to serve!");
}

void ServeState::key_pressed(GameMain * sm, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Left)
    paddle.move_left();
  else if (event->key() == Qt::Key_Right)
    paddle.move_right();

  if (event->isAutoRepeat())
    return;

  if (event->key() == Qt::Key_Return or event->key() == Qt::Key_Enter)
    sm->change_state(PlayState::get_ptr_instance());
}

void ServeState::key_released(GameMain *, QKeyEvent *)
{
  paddle.stop();
}

void PlayState::enter(GameMain *)
{
  double dx = Random::get_instance().unif(100, 200);
  if (Random::get_instance().flip_coin())
    dx *= -1;
  Ball & ball = const_cast<Ball &>(*balls.begin());
  ball.set_velocity(dx, Random::get_instance().unif(-60, -50));
  hit_count = 0;
  powerups.clear();
}

void PlayState::update(GameMain * sm, double dt)
{
  if (Global::paused)
    return;

  paddle.update(dt);
  QRectF paddle_collision_rect = paddle.get_collision_rect();

  QMutableListIterator<Ball> it(balls);

  while (it.hasNext())
    {
      Ball & ball = it.next();
      ball.update(dt);

      if (ball.collides(paddle_collision_rect))
        {
          Audio::get_instance().play_paddle_hit();
          QRectF intersection =
              ball.get_collision_rect().intersected(paddle_collision_rect);
          ball.rebound(intersection);
          double dx = ball.get_dx();
          double dy = ball.get_dy();
          double center_delta = paddle_collision_rect.x()
              + paddle_collision_rect.width()/2 - ball.get_x();
          if (center_delta > 0 and paddle.get_dx() < 0)
            dx = -50 - 8*center_delta;
          else if (center_delta < 0 and paddle.get_dx() > 0)
            dx = 50 - 8*center_delta;

          ball.set_velocity(dx, dy);
        }

      if (ball.get_y() > Global::VIRTUAL_HEIGHT)
        it.remove();
    }

  if (balls.size() == 0)
    {
      player.dec_health();
      Audio::get_instance().play_hurt();

      if (player.get_health() == 0)
        sm->change_state(GameOverState::get_ptr_instance());
      else
        sm->change_state(ServeState::get_ptr_instance());
    }

  QMutableListIterator<PowerUp> pit(powerups);

  while (pit.hasNext())
    {
      PowerUp & powerup = pit.next();
      powerup.update(dt);

      QRectF collision_rect = powerup.get_collision_rect();

      if (collision_rect.intersects(paddle_collision_rect))
        {
          if (powerup.get_type() == PowerUp::Type::BALL)
            {
              Ball ball1(paddle.get_x() + paddle.get_width()/2.0
                          - Global::BALL_WIDTH/2.0,
                          paddle.get_y() - Global::BALL_HEIGHT);
              double dx = Random::get_instance().unif(100, 200);
              if (Random::get_instance().flip_coin())
                dx *= -1;
              ball1.set_velocity(dx, Random::get_instance().unif(-60, -50));
              balls.append(ball1);
              Ball ball2(paddle.get_x() + paddle.get_width()/2.0
                          - Global::BALL_WIDTH/2.0,
                          paddle.get_y() - Global::BALL_HEIGHT);
              dx = Random::get_instance().unif(100, 200);
              if (Random::get_instance().flip_coin())
                dx *= -1;
              ball2.set_velocity(dx, Random::get_instance().unif(-60, -50));
              balls.append(ball2);
            }
          else if (powerup.get_type() == PowerUp::Type::KEY
                   and Global::locked_brick_ptr != nullptr)
            {
              Global::locked_brick_ptr->unlock();
              Global::locked_brick_ptr = nullptr;
            }
          pit.remove();
        }

      if (collision_rect.y() > Global::VIRTUAL_WIDTH)
        pit.remove();
    }

  for (Ball & ball : balls)
    {
      bool victory = true;

      for (Brick & b : bricks)
          {
            b.update(dt);
            QRectF brick_collision_rect = b.get_collision_rect();
            if (b.is_in_play() and ball.collides(brick_collision_rect))
              {
                player.add_score(b.score());
                b.hit();
                ++hit_count;

                if (not b.is_in_play())
                  --Global::num_live_bricks;

                if (Global::locked_brick_ptr != nullptr
                    and Random::get_instance().unif(Global::num_live_bricks) == 1)
                  powerups.append(PowerUp(brick_collision_rect.center().x()
                                          - Global::POWERUP_WIDTH/2,
                                          brick_collision_rect.y()
                                          +Global::ALL_SPRITES_HEIGHT,
                                          PowerUp::Type::KEY));
                else
                  {
                    int p = 10 + std::pow(10, powerups.size())
                        + std::pow(10, balls.size());
                    if (Random::get_instance().unif(p) < hit_count)
                      {
                        powerups.append(PowerUp(
                                          brick_collision_rect.center().x()
                                          - Global::POWERUP_WIDTH/2,
                                          brick_collision_rect.y()
                                          + Global::ALL_SPRITES_HEIGHT,
                                          PowerUp::Type::BALL));
                        hit_count = 0;
                      }
                  }

                if (player.get_score() > Global::recover_points)
                  {
                    player.inc_health();
                    Global::recover_points *= 2;
                    Audio::get_instance().play_recover();
                  }

                QRectF intersection =
                    ball.get_collision_rect().intersected(brick_collision_rect);
                ball.rebound(intersection);
              }
            victory = victory and not b.is_in_play();
          }
      if (victory)
        {
          Audio::get_instance().play_victory();
          sm->change_state(VictoryState::get_ptr_instance());
        }
    }
}

void PlayState::draw(GameMain *, QPainter & painter)
{
  if (Global::paused)
    {
      painter.setFont(Font::get_instance().large_font());
      painter.drawText(0, 0,
                       Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT,
                       Qt::AlignCenter, "PAUSED");
    }

  player.draw(painter);

  for (const PowerUp & powerup : powerups)
    powerup.draw(painter);

  for (const Ball & ball : balls)
    ball.draw(painter);

  for (const Brick & b : bricks)
    b.draw(painter);

  paddle.draw(painter);
}

void PlayState::key_pressed(GameMain *, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Space)
    {
      Global::paused = not Global::paused;
      Audio::get_instance().play_pause();
    }

  if (Global::paused)
    return;

  if (event->key() == Qt::Key_Left)
    paddle.move_left();
  else if (event->key() == Qt::Key_Right)
    paddle.move_right();
}

void PlayState::key_released(GameMain *, QKeyEvent *)
{
  paddle.stop();
}


void GameOverState::key_pressed(GameMain * sm, QKeyEvent * event)
{
  if (event->isAutoRepeat())
    return;

  if (event->key() == Qt::Key_Enter or event->key() == Qt::Key_Return)
    sm->change_state(EnterHighScoreState::get_ptr_instance());
}

void GameOverState::draw(GameMain *, QPainter & painter)
{
  painter.setFont(Font::get_instance().large_font());
  painter.drawText(0, 0, Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT,
                   Qt::AlignCenter, "GAME OVER");
  painter.setFont(Font::get_instance().medium_font());
  painter.drawText(0, 30, Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT,
                   Qt::AlignCenter, QString("Final Score: ")
                   + QString().setNum(Player::get_instance().get_score()));
  painter.drawText(0, 60, Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT,
                   Qt::AlignCenter, "Press Enter!");

}

void VictoryState::update(GameMain *, double dt)
{
  paddle.update(dt);
  balls.first().set_position(
        paddle.get_x() + paddle.get_width()/2.0 - Global::BALL_WIDTH/2.0,
        paddle.get_y() - Global::BALL_HEIGHT
  );
}

void VictoryState::draw(GameMain *, QPainter & painter)
{
  Player::get_instance().draw(painter);
  paddle.draw(painter);
  balls.first().draw(painter);

  painter.setFont(Font::get_instance().large_font());
  painter.drawText(0, 0, Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT/2,
                   Qt::AlignCenter, QString("Level ")
                   + QString().setNum(Global::level) + QString(" complete!"));
  painter.setFont(Font::get_instance().medium_font());
  painter.drawText(0, 0,Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT,
                   Qt::AlignCenter, "Press Enter to serve!");
}

void VictoryState::key_pressed(GameMain * sm, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Left)
    paddle.move_left();
  else if (event->key() == Qt::Key_Right)
    paddle.move_right();

  if (event->isAutoRepeat())
    return;

  if (event->key() == Qt::Key_Return or event->key() == Qt::Key_Enter)
    {
      ++Global::level;
      LevelMaker::get_instance().create_map(Global::level);
      Global::num_live_bricks = BrickSet::get_instance().size();
      sm->change_state(ServeState::get_ptr_instance());
    }
}

void VictoryState::key_released(GameMain *, QKeyEvent *)
{
  paddle.stop();
}

void HighScoreState::enter(GameMain *)
{
  highscores = read_highscores();
}

void HighScoreState::exit(GameMain *)
{
  highscores.clear();
}

void HighScoreState::key_pressed(GameMain * sm, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape)
    sm->change_state(StartState::get_ptr_instance());
}

void HighScoreState::draw(GameMain *, QPainter & painter)
{
  painter.setFont(Font::get_instance().large_font());
  painter.drawText(0, 0, Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT/4,
                   Qt::AlignCenter, "High Scores");


  painter.setFont(Font::get_instance().medium_font());

  QStringListIterator it(highscores);

  for (int i = 0; i < 10; ++i)
    {
      QString place;
      place.setNum(i + 1);
      place.append(".");
      QString name = "---";
      QString score = "---";

      if (it.hasNext())
        {
          QStringList p = it.next().split(":");
          name = p.first();
          score = p.last();
        }

      painter.drawText(Global::VIRTUAL_WIDTH/4, 65+i*17, place);
      painter.drawText(Global::VIRTUAL_WIDTH/4 + 58, 65+i*17, name);
      painter.drawText(Global::VIRTUAL_WIDTH/2 + 38, 65+i*17, score);

    }
}

void EnterHighScoreState::enter(GameMain *)
{
  highscores = read_highscores();
  chars[0] = 'A';
  chars[1] = 'A';
  chars[2] = 'A';
  highlighted = 0;
}

void EnterHighScoreState::exit(GameMain *)
{
  highscores.clear();
}

void EnterHighScoreState::key_pressed(GameMain * sm, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Enter or event->key() == Qt::Key_Return)
    {
      int score = Player::get_instance().get_score();
      QString entry;
      for (char c : chars)
        entry.append(c);

      entry.append(":");
      entry.append(QString().setNum(score));

      highscores.append(entry);

      int i = highscores.size() - 1;

      while (i > 0)
        {
          QString s = highscores.at(i - 1);
          int ss = s.split(":").last().toInt();

          if (ss > score)
            break;

          highscores.swap(i, i - 1);
          --i;
        }

      write_highscores(highscores);
      sm->change_state(HighScoreState::get_ptr_instance());
    }
  else if (event->key() == Qt::Key_Left)
    highlighted = std::max(0, highlighted - 1);
  else if (event->key() == Qt::Key_Right)
    highlighted = std::min(2, highlighted + 1);
  else if (event->key() == Qt::Key_Up)
    {
      chars[highlighted] = chars[highlighted] + 1;
      if (chars[highlighted] > 'Z')
        chars[highlighted] = 'A';
    }
  else if (event->key() == Qt::Key_Down)
    {
      chars[highlighted] = chars[highlighted] - 1;
      if (chars[highlighted] < 'A')
        chars[highlighted] = 'Z';
    }
}

void EnterHighScoreState::draw(GameMain *, QPainter & painter)
{
  painter.setFont(Font::get_instance().medium_font());
  painter.drawText(0, 0, Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT/6,
                   Qt::AlignCenter, QString("Your score: ")
                   + QString().setNum(Player::get_instance().get_score()));

  if (highlighted == 0)
    painter.setPen(QColor(103, 255, 255));
  painter.drawText(Global::VIRTUAL_WIDTH/2-28, Global::VIRTUAL_HEIGHT/2,
                   QString(chars[0]));
  painter.setPen(Qt::white);
  if (highlighted == 1)
    painter.setPen(QColor(103, 255, 255));
  painter.drawText(Global::VIRTUAL_WIDTH/2-4, Global::VIRTUAL_HEIGHT/2,
                   QString(chars[1]));
  painter.setPen(Qt::white);
  if (highlighted == 2)
    painter.setPen(QColor(103, 255, 255));
  painter.drawText(Global::VIRTUAL_WIDTH/2+20, Global::VIRTUAL_HEIGHT/2,
                   QString(chars[2]));
  painter.setPen(Qt::white);
}

void PaddleSelectState::enter(GameMain *)
{
  selected = 0;
}

void PaddleSelectState::key_pressed(GameMain * sm, QKeyEvent * event)
{
  if (event->key() == Qt::Key_Enter or event->key() == Qt::Key_Return)
    {
      Paddle::get_instance().set_skin(selected);
      Audio::get_instance().play_confirm();
      sm->change_state(ServeState::get_ptr_instance());
    }

  if (event->key() == Qt::Key_Left)
    selected = std::max(0, selected - 1);
  else if (event->key() == Qt::Key_Right)
    selected = std::min(3, selected + 1);
}

void PaddleSelectState::draw(GameMain *, QPainter & painter)
{
  painter.setFont(Font::get_instance().small_font());
  painter.drawText(0, 0, Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT/4,
                   Qt::AlignCenter, "Select your paddle with left and right!");
  painter.drawText(0, 10, Global::VIRTUAL_WIDTH, Global::VIRTUAL_HEIGHT/3,
                   Qt::AlignCenter, "(Press Enter to continue!)");

  if (selected == 0)
    painter.drawPixmap(QPoint(Global::VIRTUAL_WIDTH/4 - 24,
                              Global::VIRTUAL_HEIGHT-Global::VIRTUAL_HEIGHT/3),
                       SpriteSheet::get_instance().get_opaque_arrows(),
                       Global::all_arrows[0]);
  else
    painter.drawPixmap(QPoint(Global::VIRTUAL_WIDTH/4 - 24,
                              Global::VIRTUAL_HEIGHT-Global::VIRTUAL_HEIGHT/3),
                       SpriteSheet::get_instance().get_arrows(),
                       Global::all_arrows[0]);

  if (selected == 3)
    painter.drawPixmap(QPoint(Global::VIRTUAL_WIDTH - Global::VIRTUAL_WIDTH/4,
                              Global::VIRTUAL_HEIGHT-Global::VIRTUAL_HEIGHT/3),
                       SpriteSheet::get_instance().get_opaque_arrows(),
                       Global::all_arrows[1]);
  else
    painter.drawPixmap(QPoint(Global::VIRTUAL_WIDTH - Global::VIRTUAL_WIDTH/4,
                              Global::VIRTUAL_HEIGHT-Global::VIRTUAL_HEIGHT/3),
                       SpriteSheet::get_instance().get_arrows(),
                       Global::all_arrows[1]);

  painter.drawPixmap(QPoint(Global::VIRTUAL_WIDTH/2-Global::PADDLE_WIDTH_FACTOR,
                            Global::VIRTUAL_HEIGHT-Global::VIRTUAL_HEIGHT/3),
                     SpriteSheet::get_instance().get_breakout(),
                     Global::all_paddles[selected]
                     [Global::DEFAULT_PADDLE_SIZE]);
}
