#include "color.hpp"

vivid::ColorMap State::colorMap;

RGBA State::get_color(double inValue)
{
    vivid::srgb_t color = this->colorMap.at(inValue);
    return {(int)(color.r * 255), (int)(color.g * 255), (int)(color.b * 255), 255};
}

RuleMessage Rule::get_next_move(State inState)
{
    uint nextState(0);
    if (inState.currentState == this->ruleString.size() - 1)
    {
        nextState = 0;
    }
    else
    {
        nextState = inState.currentState + 1;
    }
    std::string turnDirection = this->ruleString[inState.currentState];
    std::vector<MovementDirections> turnEnum = this->ruleToMovementMap.at(turnDirection);
    turnEnum.push_back(MovementDirections::FORWARD);
    return RuleMessage{.newState = nextState, .movement_commands = turnEnum};
};
