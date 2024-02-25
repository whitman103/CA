#include "ant.hpp"

void Ant::moveForward()
{
    switch (this->curDirection)
    {
    case Direction::RIGHT:
        this->curX += 1;
        break;
    case Direction::LEFT:
        this->curX -= 1;
        break;
    case Direction::UP:
        this->curY += 1;
        break;
    case Direction::DOWN:
        this->curY -= 1;
        break;
    }
}

void Ant::turnRight()
{
    switch (this->curDirection)
    {
    case Direction::RIGHT:
        this->curDirection = Direction::DOWN;
        break;
    case Direction::LEFT:
        this->curDirection = Direction::UP;
        break;
    case Direction::UP:
        this->curDirection = Direction::RIGHT;
        break;
    case Direction::DOWN:
        this->curDirection = Direction::LEFT;
        break;
    }
}

void Ant::turnLeft()
{
    switch (this->curDirection)
    {
    case Direction::LEFT:
        this->curDirection = Direction::DOWN;
        break;
    case Direction::DOWN:
        this->curDirection = Direction::RIGHT;
        break;
    case Direction::RIGHT:
        this->curDirection = Direction::UP;
        break;
    case Direction::UP:
        this->curDirection = Direction::LEFT;
        break;
    }
}

void Ant::move(RuleMessage inMessage)
{
    for (MovementDirections movement : inMessage.movement_commands)
    {
        switch (movement)
        {
        case MovementDirections::LEFT:
            this->turnLeft();
            break;
        case MovementDirections::RIGHT:
            this->turnRight();
            break;
        case MovementDirections::FORWARD:
            this->moveForward();
            break;
        default:
            break;
        }
    }
}