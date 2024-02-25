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

struct Ant
{
    int curX, curY;
    Direction curDirection;
    void turnRight();
    void turnLeft();
    void moveForward();
    void move(RuleMessage inMessage);
};

#endif