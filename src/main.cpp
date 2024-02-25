#include "ant.hpp"
#include "color.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include <vivid/vivid.h>

ColorMessage moveAnt(Ant &inAnt, std::vector<std::vector<State>> &simField, Rule &inRule)
{
    RuleMessage changes = inRule.get_next_move(simField[inAnt.curX][inAnt.curY]);
    simField[inAnt.curX][inAnt.curY].currentState = changes.newState;
    inAnt.move(changes);
    return ColorMessage{
        .x = inAnt.curX,
        .y = inAnt.curY,
        .color = (simField[inAnt.curX][inAnt.curY].get_color((double)changes.newState / inRule.ruleString.size()))};
}

struct DisplayStruct
{
    int xSize, ySize;
    sf::RenderWindow *window;
    sf::Texture *texture;
    sf::Sprite *sprite;
    sf::View view;
    DisplayStruct() : xSize{0}, ySize{0} {};
    DisplayStruct(sf::RenderWindow *inWindow, sf::Texture *texture, sf::Sprite *sprite)
        : window(inWindow), sprite(sprite), texture(texture){};
};

struct SimWorld
{
    const int world_xSize, world_ySize;
    std::vector<std::vector<State>> simField;
    Rule moveRule = SquareRule("LRRRRLLR");
    const int colorDepth{4};
    void change_pixel(ColorMessage inMessage);
    sf::Uint8 *pixelDraw;
    SimWorld(int xSize, int ySize) : world_xSize{xSize}, world_ySize{ySize}
    {
        this->pixelDraw = (sf::Uint8 *)calloc(world_xSize * world_ySize * 4, sizeof(sf::Uint8));
        this->simField.resize(this->world_xSize);
        for (uint xIndex{0}; xIndex < this->world_xSize; xIndex++)
        {
            this->simField[xIndex].resize(this->world_ySize, State{0});
        }
    };
};

void SimWorld::change_pixel(ColorMessage inMessage)
{
    for (uint colorIndex{0}; colorIndex < this->colorDepth; colorIndex++)
    {
        this->pixelDraw[this->colorDepth * (inMessage.x * this->world_xSize + inMessage.y) + colorIndex] =
            inMessage.color[colorIndex];
    }
};

void calculateImage(Ant &inAnt, SimWorld &simWorld)
{
    ColorMessage turnPixel = moveAnt(inAnt, simWorld.simField, simWorld.moveRule);
    simWorld.change_pixel(turnPixel);
};

int main()
{

    const int window_xSize(1000), window_ySize(1000);
    sf::RenderWindow window(sf::VideoMode(window_xSize, window_ySize), "Ant Render");

    sf::Sprite sprite;
    sf::Texture texture;
    texture.create(window_xSize, window_ySize);

    sprite.setTexture(texture);
    sprite.setOrigin(0, 0);
    DisplayStruct displayStruct(&window, &texture, &sprite);

    bool wait = false;

    State::colorMap = vivid::ColorMap(vivid::ColorMap::Preset::Plasma);

    SimWorld simWorld(500, 500);

    sf::View view;

    view.setSize({.25f * window_xSize, .25f * window_ySize});
    view.setCenter(100, 50);
    window.setView(view);

    Ant useAnt{.curX = (int)(100), .curY = (int)(100), .curDirection = Direction::RIGHT};
    int frameCount(0);
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
            calculateImage(useAnt, simWorld);
            // calculateImage(&passArray, secondAnt, simField, moveRule);
            texture.update(simWorld.pixelDraw);
            window.draw(sprite);
            window.display();
            /* if (frameCount > 500)
            {
                frameCount = 0;
                wait = true;
            }
            else
            {
                frameCount += 1;
            } */
        }
    }
    free(simWorld.pixelDraw);

    return 0;
}