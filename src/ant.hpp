#ifndef ANT_HPP
#define ANT_HPP

#include "color.hpp"

enum class Direction
{
    RIGHT = 0,
    UP = 1,
    LEFT = 2,
    DOWN = 3
};

enum class HexDirection
{
    E = 0,
    NE = 1,
    NW = 2,
    W = 3,
    SW = 4,
    SE = 5
};

struct Ant
{
    int curX, curY;
    Direction curDirection;
    void turnRight();
    void turnLeft();
    void moveForward();
    void move(RuleMessage inMessage);
};

struct HexAnt
{
    int curX, curY;
    HexDirection curDirection;
    void turnLeft();
    void turnRight();
    void moveForward();
    void move(RuleMessage inMessage);
};

#endif