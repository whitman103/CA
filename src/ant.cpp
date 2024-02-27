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
};

void HexAnt::move(RuleMessage inMessage)
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
};

void HexAnt::turnLeft()
{
    switch (this->curDirection)
    {
    case HexDirection::E:
        this->curDirection = HexDirection::NE;
        break;
    case HexDirection::NE:
        this->curDirection = HexDirection::NW;
        break;
    case HexDirection::NW:
        this->curDirection = HexDirection::W;
        break;
    case HexDirection::W:
        this->curDirection = HexDirection::SW;
        break;
    case HexDirection::SW:
        this->curDirection = HexDirection::SE;
        break;
    case HexDirection::SE:
        this->curDirection = HexDirection::E;
        break;
    }
}

void HexAnt::turnRight()
{
    switch (this->curDirection)
    {
    case HexDirection::E:
        this->curDirection = HexDirection::SE;
        break;
    case HexDirection::NE:
        this->curDirection = HexDirection::E;
        break;
    case HexDirection::NW:
        this->curDirection = HexDirection::NE;
        break;
    case HexDirection::W:
        this->curDirection = HexDirection::NW;
        break;
    case HexDirection::SW:
        this->curDirection = HexDirection::W;
        break;
    case HexDirection::SE:
        this->curDirection = HexDirection::SW;
        break;
    }
}

void HexAnt::moveForward()
{
    switch (this->curDirection)
    {
    case HexDirection::E:
        this->curX += 1;
        break;
    case HexDirection::NE:
        this->curX += 1;
        this->curY += 1;
        break;
    case HexDirection::NW:
        this->curX -= 1;
        this->curY += 1;
        break;
    case HexDirection::W:
        this->curX -= 1;
        break;
    case HexDirection::SW:
        this->curX -= 1;
        this->curY -= 1;
        break;
    case HexDirection::SE:
        this->curX += 1;
        this->curY -= 1;
        break;
    }
}