#include "main.hpp"

int main()
{
    int width{800};
    int height{600};
    sf::RenderWindow window(sf::VideoMode(width, height), "Hello SFML");

    sf::Font font;
    if (!font.loadFromFile("./src/assets/ARIAL.TTF"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Hello World");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setPosition(width/2, height/2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }

    return 0;
}