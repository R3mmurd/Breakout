/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
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
  virtual void enter(ConcreteStateMachine *)
  {
    // Empty
  }

  virtual void update(ConcreteStateMachine *, double)
  {
    // Empty
  }

  virtual void exit(ConcreteStateMachine *)
  {
    // Empty
  }

  virtual void draw(ConcreteStateMachine *, QPainter &)
  {
    // Empty
  }

  virtual void key_pressed(ConcreteStateMachine *, QKeyEvent *)
  {
    // Empty
  }

  virtual void key_released(ConcreteStateMachine *, QKeyEvent *)
  {
    // Empty
  }
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
    current_state->update(me(), dt);
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

  void key_released(QKeyEvent * event)
  {
    current_state->key_released(me(), event);
  }
};

# endif // STATEMACHINE_H
