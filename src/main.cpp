#include "main.hpp"

#include <memory>
#include <vector>

#include "ball.hpp"
#include "brick.hpp"
#include "brickFactory.hpp"
#include "colors.hpp"
#include "gameManager.hpp"
#include "music.hpp"
#include "paddle.hpp"
#include "values.hpp"

int main() {
  const float width{Values::WINDOW_WIDTH};
  const float height{Values::WINDOW_HEIGHT};
  gameManager game;

  sf::RenderWindow window(sf::VideoMode(width, height), "Casse-Brique SFML");
  window.setFramerateLimit(120);
  window.setVerticalSyncEnabled(true);

  Ball ball(Values::BALL_RADIUS, width, height);
  Paddle paddle(width, height);

  Music musiqueFond;
  std::string cheminMusique = "src/musics/bougie.mp3";

  if (musiqueFond.load(cheminMusique))

  {
    musiqueFond.play(true, 40.f);
  }

  std::vector<std::unique_ptr<Brick>> bricks =
      BrickFactory::createBricksUnique(width);

  sf::RenderTexture brickLayer;
  brickLayer.create(width, height);
  brickLayer.clear(sf::Color::Transparent);

  for (std::unique_ptr<Brick>& brick : bricks) {
    brick->draw(brickLayer);
  }

  brickLayer.display();
  sf::Sprite brickLayerSprite(brickLayer.getTexture());

  // CLEAN UP
  sf::Clock cleanupClock;             // démarre automatiquement
  const float cleanupInterval = 2.f;  // toutes les 2 secondes

  while (window.isOpen()) {
    sf::Event evenement;

    while (window.pollEvent(evenement)) {
      if (evenement.type == sf::Event::Closed) window.close();
    }

    float previousPositionX = paddle.getGlobalBounds().left;
    paddle.update();
    float newPositionX = paddle.getGlobalBounds().left;

    if (!ball.getIsMoving() && newPositionX != previousPositionX) ball.launch();

    // Paddle collision logic with region-based bounce
    paddle.handleBallCollision(ball);

    ball.update(paddle.getGlobalBounds());
    game.ballInWindow(ball, paddle, window);

    // window.clear(sf::Color(200, 200, 200));
    window.clear(Colors::background);

    bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
                                [](std::unique_ptr<Brick>& b) {
                                  return b->isDestroyed();
                                }),
                 bricks.end());
    if (cleanupClock.getElapsedTime().asSeconds() >= cleanupInterval) {
      std::cout << "ça nettoie en principe" << std::endl;
      cleanupClock.restart();
    }

    window.clear(sf::Color(200, 200, 200));

    for (std::unique_ptr<Brick>& brick : bricks) {
      if (!brick->isDestroyed()) {
        brick->collision(ball);
        if (brick->changeState) {
          // Redraw only this brick on the render texture
          brickLayer.draw(brick->getShape());
          brickLayer.display();
          brick->changeState = false;
          std::cout << "vector lenght : " << bricks.size() << std::endl;
          std::cout << "vie de la brick : " << brick->durability << std::endl;
        }
      }
    }

    window.draw(brickLayerSprite);
    // window.clear(sf::Color(0, 98, 255));
    ball.draw(window);
    paddle.draw(window);

    window.display();
  }

  return 0;
}
