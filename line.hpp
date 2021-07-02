#ifndef LINE_HPP
#define LINE_HPP

#include "hwlib.hpp"
#include "drawable.hpp"

class line: public drawable {
private:
    hwlib::xy end;
public:
    line(hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end, const hwlib::xy & bounce);

    void draw() override;
    void up(int x);
    void down(int x);
};


#endif