#include "ball.hpp"

ball::ball( 
    hwlib::window & w, 
    const hwlib::xy & midpoint, 
    int radius, 
    const hwlib::xy & speed 
):
    drawable( w, midpoint - hwlib::xy( radius, radius ), hwlib::xy( radius * 2, radius * 2 ) ),
    radius( radius ),
    speed( speed )  
{}

void ball::draw(){
    hwlib::circle c( location + hwlib::xy( radius, radius ), radius );
    c.draw( w );
}

   
void ball::update(){
    location = location + speed; 
}
   
void ball::interact( drawable & other ){
    if( this != & other){
        if( overlaps( other )){
            speed.x *= other.bounce.x;
            speed.y *= other.bounce.y;
            update();
        }
    }
}

void ball::reset(hwlib::xy l){
    location = l;
    update();
    hwlib::wait_ms(3000);
    speed = hwlib::xy(5,2);
};
   
