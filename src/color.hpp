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
    std::vector<char> ruleString;
    Rule(std::string inRule)
    {
        this->ruleString = std::vector<char>(inRule.begin(), inRule.end());
    };
    RuleMessage get_next_move(State inState);
};

#endif