#include "main.hpp"

// int main() { std::cout << "Hello depuis le projet Brick Breaker" << std::endl; }

// int main()
// {
//     // Create a window
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Hello SFML");

//     // Main loop
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear(sf::Color::Black);

//         // (we’ll draw text here soon)

//         window.display();
//     }

//     return 0;
// }



int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello SFML");

    sf::Font font;
    // if (!font.loadFromFile("./assets/ARIAL.TTF"))
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
    text.setPosition(200, 250);

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