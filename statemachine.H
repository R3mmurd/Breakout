/*
  This file is part of Fatty Bird game.
  Copyright (C) 2020 by Alejandro J. Mujica

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

  Any user request of this software, write to

  Alejandro Mujica

  aledrums@gmail.com
*/

# ifndef STATEMACHINE_H
# define STATEMACHINE_H

#include <cassert>
#include <stdexcept>

#include <QPainter>
#include <QKeyEvent>

template <class GameEntityType>
class State
{
public:
  virtual void enter(GameEntityType *) = 0;

  virtual void exec(GameEntityType *, double) = 0;

  virtual void exit(GameEntityType *) = 0;

  virtual void draw(GameEntityType *, QPainter &) = 0;

  virtual void key_pressed(GameEntityType *, QKeyEvent *) = 0;
};

template <class GameEntityType>
class StateMachine 
{
  State<GameEntityType> * current_state;
  State<GameEntityType> * last_state;

public:
  StateMachine(State<GameEntityType> * initial_state)
    : current_state(initial_state), last_state(nullptr)
  {
    if (current_state == nullptr)
      throw std::logic_error("The state machine needs an initial state");

    current_state->enter(me());
  }

  GameEntityType * me()
  {
    return static_cast<GameEntityType *>(this);
  }

  const GameEntityType * const_me() const
  {
    return static_cast<const GameEntityType *>(this);
  }

  operator GameEntityType & ()
  {
    return *me();
  }

  void update(double dt)
  {
    assert(current_state != nullptr);
    current_state->exec(me(), dt);
  }

  void change_state(State<GameEntityType> * new_state)
  {
    assert(new_state != nullptr);
    
    current_state->exit(me());
    last_state = current_state;
    current_state = new_state;
    current_state->enter(me());
  }

  void set_last_state()
  {
    if (last_state == nullptr)
      return;
    
    change_state(last_state);
  }

  void draw(QPainter & painter)
  {
    current_state->draw(me(), painter);
  }

  void key_pressed(QKeyEvent * event)
  {
    current_state->key_pressed(me(), event);
  }
};

# endif // STATEMACHINE_H
