#include "player.hpp"

player::player(int points):
    points(points)
{}

void player::points_plus(){
    points++;
}

int player::points_amount(){
    return points;
}