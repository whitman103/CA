#include "ant.hpp"
#include "color.hpp"
#include "shape_array.hpp"
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

ColorMessage moveAnt(HexAnt &inAnt, std::vector<std::vector<State>> &simField, Rule &inRule)
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
    // Rule moveRule = HexRule("L1L2NUL2L1R2");
    Rule moveRule = SquareRule("LRRRRRLLR");
    const int colorDepth{4};
    void change_pixel(ColorMessage inMessage);
    SquareSystem system;
    SimWorld(int xSize, int ySize) : world_xSize{xSize}, world_ySize{ySize}
    {
        this->system = SquareSystem(this->world_xSize, this->world_ySize);
        this->system.init();
        this->simField.resize(this->world_xSize);
        for (uint xIndex{0}; xIndex < this->world_xSize; xIndex++)
        {
            this->simField[xIndex].resize(this->world_ySize, State{0});
        }
    };
};

void SimWorld::change_pixel(ColorMessage inMessage)
{
    this->system.update(inMessage.x, inMessage.y, inMessage.color);
};

bool calculateImage(Ant &inAnt, SimWorld &simWorld)
{
    ColorMessage turnPixel = moveAnt(inAnt, simWorld.simField, simWorld.moveRule);
    if (turnPixel.x < 0 || turnPixel.x > simWorld.world_xSize || turnPixel.y < 0 || turnPixel.y > simWorld.world_ySize)
    {
        return false;
    }
    simWorld.change_pixel(turnPixel);
    return true;
};

bool calculateImage(HexAnt &inAnt, SimWorld &simWorld)
{
    ColorMessage turnPixel = moveAnt(inAnt, simWorld.simField, simWorld.moveRule);
    if (turnPixel.x < 0 || turnPixel.x > simWorld.world_xSize || turnPixel.y < 0 || turnPixel.y > simWorld.world_ySize)
    {
        return false;
    }
    simWorld.change_pixel(turnPixel);
    return true;
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

    SimWorld simWorld(100, 100);

    // HexAnt useAnt{.curX = (int)(25), .curY = (int)(45), .curDirection = HexDirection::E};
    Ant useAnt{.curX = (int)(50), .curY = (int)(50), .curDirection = Direction::RIGHT};
    int frameCount(0);
    int frameNumber(0);
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
            if (!calculateImage(useAnt, simWorld))
            {
                return 0;
            };
            window.draw(simWorld.system);
            frameCount += 1;
            window.display();
        }
    }

    return 0;
}