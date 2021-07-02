#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "hwlib.hpp"

class player{
private:
    int points;
public:
    player(int points);

    void points_plus();
    int points_amount();
};

#endif