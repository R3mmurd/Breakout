/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

# ifndef SINGLETON_H
# define SINGLETON_H

# include <memory>

/** Generic Singleton.
 *
 *  This class was designed in order to be reused for any class that
 *  requires only one instance.
 *
 *  @param T Base class.
 *
 *  Usage example:
 *
 *  \code{.cpp}
 *  class MySingletonClass : public Singleton<MySingletonClass>
 *  {
 *    friend class Singleton<MySingletonClass>;
 *
 *    // If you need default constructor, make it protected.
 *  protected:
 *    MySingletonClass() { }
 *
 *    // Any attributes or methods;
 *  };
 *
 *  MySingletonClass * ptr_instance = MySingletonClass::get_ptr_instance();
 *
 *  MySingletonClass & instance = MySingletonClass::get_instance();
 *  \endcode
 *
 *  @author: Alejandro J. Mujica
 */         
template <typename T>
class Singleton
{
  static std::unique_ptr<Singleton<T>> instance;

protected:
  Singleton()
  {
    // Empty
  }

  Singleton(const Singleton<T> &) = delete;

  Singleton & operator = (const Singleton<T> &) = delete;

public:

  virtual ~Singleton()
  {
    // Empty
  }

  /** Get a pointer to instance.
   *
   *  @return A pointer to instance.
   */
  static T * get_ptr_instance()
  {
    if (instance.get() == nullptr)
      instance = std::unique_ptr<Singleton<T>>(new T());

    return static_cast<T *>(instance.get());
  }

  /** Get a reference to instance.
   *
   *  @return A reference to instance.
   */
  static T & get_instance()
  {
    return *get_ptr_instance();
  }
};

template <typename T>
std::unique_ptr<Singleton<T>> Singleton<T>::instance =
std::unique_ptr<Singleton<T>>(nullptr);

# endif // SINGLETON_H

