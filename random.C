/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <random.H>

Random::Random()
  : rng(clock_t::now().time_since_epoch().count())
{
  // Empty
}

void Random::set_seed(unsigned s)
{
  rng.seed(s);
}

double Random::unif()
{
  return std::generate_canonical<double, 64>(rng);
}

double Random::unif(double n)
{
  return unif(0.0, n);
}

double Random::unif(double a, double b)
{
  std::uniform_real_distribution<double> dist(a, b);
  return dist(rng);
}

int Random::unif(int n)
{
  return unif(0, n);
}

int Random::unif(int a, int b)
{
  std::uniform_int_distribution<int> dist(a, b - 1);
  return dist(rng);
}

bool Random::flip_coin(double p)
{
  return unif() < p;
}

double Random::normal(double mu, double sigma)
{
  std::normal_distribution<double> dist(mu, sigma);
  return dist(rng);
}
