#include "shape_array.hpp"

#include <SFML/Graphics.hpp>

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    const int window_xSize(1000), window_ySize(1000);
    sf::RenderWindow window(sf::VideoMode(window_xSize, window_ySize), "Ant Render", sf::Style::Default, settings);

    bool wait = false;

    sf::View view;

    HexSystem system = HexSystem(100, 100);
    system.init();
    sf::Clock clock;
    int frameCount(0);
    int colorValue(0);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.capture().saveToFile("testWrite.png");
                window.close();
            }
            /*             else if (event.type == sf::Event::KeyPressed)
                            wait = false; */
        }
        if (!wait)
        {
            window.clear();
            sf::Time elapsed = clock.restart();
            system.update(rand() % window_xSize, rand() % window_ySize,
                          RGBA({rand() % 255, rand() % 255, rand() % 255, 255}));
            colorValue += 1;
            window.draw(system);
            window.display();
        }
    }

    return 0;
}