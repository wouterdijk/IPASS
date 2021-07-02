#ifndef BALL_HPP
#define BALL_HPP

#include "ball.hpp"
#include "drawable.hpp"

class ball : public drawable{
private:
    int radius;
    hwlib::xy speed;


public:
    ball(hwlib::window & w, const hwlib::xy & midpoint, int radius, const hwlib::xy & speed);

    void draw() override;
    void update() override;
    void interact( drawable & other ) override;
    void reset(hwlib::xy l); 
};

#endif