#ifndef COLOR_HPP
#define COLOR_HPP

#include <map>
#include <string>
#include <tuple>

#include <vivid/vivid.h>

typedef std::array<int, 4> RGBA;
typedef unsigned int uint;

struct ColorMessage
{
    const int x, y;
    RGBA color;
};

struct State
{
    uint currentState = 0;
    static vivid::ColorMap colorMap;
    RGBA get_color(double state);
    State(const uint state) : currentState{state} {};
};

typedef void (*AntMove)();

enum class MovementDirections
{
    NONE = -1,
    LEFT = 0,
    RIGHT = 1,
    FORWARD = 2
};

struct RuleMessage
{
    std::vector<MovementDirections> movement_commands;
    uint newState;
};

struct Rule
{
    std::vector<std::string> ruleString;
    std::unordered_map<std::string, std::vector<MovementDirections>> ruleToMovementMap;
    RuleMessage get_next_move(State inState);
};

struct SquareRule : public Rule
{

    SquareRule(std::string inRule)
    {
        for (char a : inRule)
        {
            this->ruleString.push_back(std::string(1, a));
        }
        this->ruleToMovementMap.insert({"L", {MovementDirections::LEFT}});
        this->ruleToMovementMap.insert({"R", {MovementDirections::RIGHT}});
    };
};

struct HexRule : public Rule
{
    HexRule(std::string inRule)
    {
        this->ruleString = {};
        for (int charIndex{0}; charIndex < inRule.length(); charIndex++)
        {
            if (inRule[charIndex] == 'N' || inRule[charIndex] == 'U')
            {
                this->ruleString.push_back(std::string(1, inRule[charIndex]));
            }
            else
            {
                this->ruleString.push_back(inRule.substr(charIndex, 2));
                charIndex += 1;
            }
        }
        this->ruleToMovementMap.insert({"N", {MovementDirections::NONE}});
        this->ruleToMovementMap.insert(
            {"U", {MovementDirections::LEFT, MovementDirections::LEFT, MovementDirections::LEFT}});
        this->ruleToMovementMap.insert({"L2", {MovementDirections::LEFT, MovementDirections::LEFT}});
        this->ruleToMovementMap.insert({"L1", {MovementDirections::LEFT}});
        this->ruleToMovementMap.insert({"R1", {MovementDirections::RIGHT}});
        this->ruleToMovementMap.insert({"R2", {MovementDirections::RIGHT, MovementDirections::RIGHT}});
    };
};

#endif