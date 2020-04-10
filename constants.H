#ifndef CONSTANTS_H
#define CONSTANTS_H


class Constants
{
public:
  static constexpr double WINDOW_WIDTH = 1280;
  static constexpr double WINDOW_HEIGHT = 720;

  static constexpr double VIRTUAL_WIDTH = 432;
  static constexpr double VIRTUAL_HEIGHT = 243;

  static constexpr double H_SCALE = WINDOW_WIDTH/VIRTUAL_WIDTH;
  static constexpr double V_SCALE = WINDOW_HEIGHT/VIRTUAL_HEIGHT;
};

#endif // CONSTANTS_H
