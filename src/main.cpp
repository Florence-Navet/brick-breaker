#include "main.hpp"


int main() {
  std::setlocale(LC_ALL, ".utf8");
  // Create Font
  sf::Font font;
  if (!font.loadFromFile("src/assets/fonts/ARIAL.TTF")) {
    std::cerr << "Failed to load font!" << std::endl;
    return -1;
  }
  const float width{Values::WINDOW_WIDTH};
  const float height{Values::WINDOW_HEIGHT};
  gameManager game;

  sf::RenderWindow window(sf::VideoMode(width, height), "Casse-Brique SFML");
  window.setFramerateLimit(120);
  window.setVerticalSyncEnabled(true);

  Ball ball(Values::BALL_RADIUS, width, height);
  Paddle paddle(width, height);

  // Music backgroundMusic;
  // std::string musicPath = "assets/musics/boogie.mp3";

  // if (backgroundMusic.load(musicPath))
  // {
  //   backgroundMusic.play(true, 40.f);
  // }

  // Create Bricks Layer
  std::vector<std::unique_ptr<Brick>> bricks =
      BrickFactory::createBricksUnique(width);

  std::unique_ptr<sf::RenderTexture> brickLayer =
      Utils::createTexture(width, height, sf::Color::Transparent);

  for (std::unique_ptr<Brick>& brick : bricks) {
    brick->draw(*brickLayer);
  }
  brickLayer->display();
  sf::Sprite brickLayerSprite(brickLayer->getTexture());

  // Create GameOver Layer
  std::unique_ptr<sf::RenderTexture> gameOverLayer =
      Utils::createTexture(width, height, sf::Color(0, 0, 0, 128));

  std::unique_ptr<sf::Text> gameOverText =
      Utils::createText("Vous avez perdu.", 50, font);
  gameOverText->setPosition(
      (width - gameOverText->getLocalBounds().width) / 2.f,
      (height / 3.f * 1 - (gameOverText->getLocalBounds().height) / 2.f));

  std::unique_ptr<sf::Text> reloadText =
      Utils::createText("Appuyez sur espace pour relancer", 50, font);
  reloadText->setPosition(
      (width - reloadText->getLocalBounds().width) / 2.f,
      ((gameOverText->getPosition().y + gameOverText->getLocalBounds().height) +
       (reloadText->getLocalBounds().height) / 2.f));

  gameOverLayer->draw(*gameOverText);
  gameOverLayer->draw(*reloadText);
  gameOverLayer->display();
  sf::Sprite gameOverSprite(gameOverLayer->getTexture());
  window.draw(gameOverSprite);

  // Create Win Layer
  std::unique_ptr<sf::RenderTexture> winLayer =
      Utils::createTexture(width, height, sf::Color(255, 255, 255, 128));
  std::unique_ptr<sf::Text> winText =
      Utils::createText("Vous avez gagné.", 50, font);
  winText->setPosition(
      (width - gameOverText->getLocalBounds().width) / 2.f,
      (height / 3.f * 1 - (gameOverText->getLocalBounds().height) / 2.f));

  winLayer->draw(*winText);
  winLayer->draw(*reloadText);
  winLayer->display();
  sf::Sprite winSprite(winLayer->getTexture());
  window.draw(winSprite);

  while (window.isOpen()) {
    sf::Event evenement;

    while (window.pollEvent(evenement)) {
      if (evenement.type == sf::Event::Closed) window.close();
    }

    if (game.getLife() > 0) {
      // Launch Ball!
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
          !ball.getIsMoving()) {
        std::cout << "space pressed " << std::endl;
        ball.launch();
      }

      float previousPositionX = paddle.getGlobalBounds().left;
      paddle.update();
      float newPositionX = paddle.getGlobalBounds().left;

      paddle.handleBallCollision(ball);

      ball.update(paddle.getGlobalBounds());
      game.ballInWindow(ball, paddle, window);
      if (game.getLife() < 0) {
        std::cout << "on est décédé" << std::endl;
      }

      window.clear(Colors::background);

      bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
                                  [](std::unique_ptr<Brick>& b) {
                                    return b->isDestroyed();
                                  }),
                   bricks.end());

      for (std::unique_ptr<Brick>& brick : bricks) {
        if (!brick->isDestroyed()) {
          brick->collision(ball);
          if (brick->changeState) {
            brickLayer->draw(brick->getShape());
            brickLayer->display();
            brick->changeState = false;
          }
        }
      }
    }
    window.clear(Colors::background);
    window.draw(brickLayerSprite);
    ball.draw(window);
    paddle.draw(window);

    if (game.getLife() <= 0) {
      window.draw(gameOverSprite);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        bricks = game.resetBricks(width);
        game.resetLife();
      }
    }

    if (bricks.size() <= 0) {
      ball.setIsMoving(false);
      window.draw(winSprite);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        bricks = game.resetBricks(width);
        game.resetLife();
      }
    }
    window.display();
  }

  return 0;
}
