/*
  This file contains a reusable and generic implementation of the State
  Machine Pattern.
  Copyright (C) 2017 Alejandro J. Mujica.

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

/** State .
 *
 *  Base state in which could be a state machine in a given time.
 *
 *  @param ConcreteStateMachine: is the class that will be the state machine.
 *
 *  @author: Alejandro J. Mujica
 */
template <class ConcreteStateMachine>
class State
{
public:
  virtual void enter(ConcreteStateMachine *) = 0;

  virtual void exec(ConcreteStateMachine *, double) = 0;

  virtual void exit(ConcreteStateMachine *) = 0;

  virtual void draw(ConcreteStateMachine *, QPainter &) = 0;

  virtual void key_pressed(ConcreteStateMachine *, QKeyEvent *) = 0;
};

/** State machine.
 *
 *  This class was designed in order to be reused for any class that can be
 *  in exactly one of a finite number of states at any given time. It was
 *  adapted to be used with Qt's QKeyEvent and QPainter.
 *
 *  @param ConcreteStateMachine: is the class that will be the state machine.
 *
 *  @author: Alejandro J. Mujica
 */
template <class ConcreteStateMachine>
class StateMachine 
{
  State<ConcreteStateMachine> * current_state;
  State<ConcreteStateMachine> * last_state;

public:
  StateMachine(State<ConcreteStateMachine> * initial_state)
    : current_state(initial_state), last_state(nullptr)
  {
    if (current_state == nullptr)
      throw std::logic_error("The state machine needs an initial state");

    current_state->enter(me());
  }

  ConcreteStateMachine * me()
  {
    return static_cast<ConcreteStateMachine *>(this);
  }

  const ConcreteStateMachine * const_me() const
  {
    return static_cast<const ConcreteStateMachine *>(this);
  }

  operator ConcreteStateMachine & ()
  {
    return *me();
  }

  void update(double dt)
  {
    assert(current_state != nullptr);
    current_state->exec(me(), dt);
  }

  void change_state(State<ConcreteStateMachine> * new_state)
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
