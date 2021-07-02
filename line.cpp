#include "line.hpp"

line::line( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & end , const hwlib::xy & bounce):
    drawable( w, location, end - location , bounce),
    end( end )
{}

void line::draw(){
    hwlib::line x( location, end );
    x.draw( w );
}

void line::up(int x){
    if(end.y < 64){
        location = location + hwlib::xy(0,x);
        end = end + hwlib::xy(0,x);
    }
}

void line::down(int x){
    if(location.y > 1){
        location = location - hwlib::xy(0,x);
        end = end - hwlib::xy(0,x);
    }
}