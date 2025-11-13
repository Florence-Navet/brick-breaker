#ifndef VALUES_HPP
#define VALUES_HPP

namespace Values {
constexpr float WINDOW_WIDTH = 870.f;
constexpr float WINDOW_HEIGHT = 600.f;

constexpr float PADDLE_WIDTH = 100.f;
constexpr float PADDLE_HEIGHT = 20.f;

constexpr float BALL_RADIUS = 10.f;

constexpr float BRICK_WIDTH = 68.f;
constexpr float BRICK_HEIGHT = 25.f;

constexpr float PADDING = 10.f;
constexpr float MARGIN = 50.f;

constexpr float BALL_SPEED = 9.f;
constexpr float PADDLE_SPEED =
    Values::BALL_SPEED + (Values::BALL_SPEED / 3) * 2;

}  // namespace Values

#endif