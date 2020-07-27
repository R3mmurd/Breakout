/*
  Breakout remake.
  
  Author: Alejandro Mujica (aledrums@gmail.com)
*/

#include <particlesystem.H>
#include <random.H>

Particle::Particle(double _x, double _y, double _ax, double _ay, double lt,
                   QColor c)
  : x(_x), y(_y), vx(0), vy(0), ax(_ax), ay(_ay), life_time(lt), color(c)
{
  // Empty
}

double Particle::get_life_time() const
{
  return life_time;
}

void Particle::update(double dt)
{
  vx += ax*dt;
  vy += ay*dt;
  x += vx;
  y += vy;
}

void Particle::draw(QPainter & painter) const
{
  QPen pen = painter.pen();
  QBrush brush = painter.brush();

  painter.setPen(Qt::transparent);
  painter.setBrush(color);
  painter.drawEllipse(QPoint(x, y), 2, 2);

  painter.setPen(pen);
  painter.setBrush(brush);
}


ParticleSystem::ParticleSystem(double x, double y, int n)
  : x_mean(x), y_mean(y), size(n)
{
  // Empty
}

void ParticleSystem::set_life_time(double minimum, double maximum)
{
  min_life_time = minimum;
  max_life_time = maximum;
}

void ParticleSystem::set_linear_acceleration(double x1, double y1,
                                             double x2, double y2)
{
  ax1 = x1;
  ay1 = y1;
  ax2 = x2;
  ay2 = y2;
}

void ParticleSystem::set_colors(const QVector<QColor> & cs)
{
  colors = cs;
}

void ParticleSystem::set_area_spread(double rx, double ry)
{
  x_desv = rx;
  y_desv = ry;
}

void ParticleSystem::generate()
{
  particles.clear();
  for (int i = 0; i < size; ++i)
    {
      Random & random = Random::get_instance();
      double ax = random.unif(ax1, ax2);
      double ay = random.unif(ay1, ay2);
      double px = random.normal(x_mean, x_desv);
      double py = random.normal(y_mean, y_desv);
      int cp = random.unif(colors.size());
      double life_time = random.unif(min_life_time, max_life_time);
      particles.append(Particle(px, py, ax, ay, life_time, colors.at(cp)));
    }

  timer = 0;
}

void ParticleSystem::update(double dt)
{
  timer += dt;

  if (timer > max_life_time)
    particles.clear();

  for (Particle & p : particles)
    {
      if (timer < p.get_life_time())
        p.update(dt);
    }
}

void ParticleSystem::draw(QPainter & painter) const
{
  for (const Particle & p : particles)
    {
      if (timer < p.get_life_time())
        p.draw(painter);
    }
}

