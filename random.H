/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <chrono>

#include <singleton.H>

class Random : public Singleton<Random>
{
  using clock_t = std::chrono::high_resolution_clock;
  std::mt19937_64 rng;

public:
  Random();

  void set_seed(unsigned);

  double unif();

  double unif(double);

  double unif(double, double);

  int unif(int);

  int unif(int, int);

  bool flip_coin(double p = 0.5);

  double normal(double mu = 0, double sigma = 1);
};

#endif // RANDOM_H
