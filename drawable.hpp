#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "hwlib.hpp"

class drawable {
protected:

   hwlib::window & w;
   hwlib::xy location;
   hwlib::xy size;

   
public:
   hwlib::xy bounce = { 1, 1 };

   drawable( hwlib::window & w, const hwlib::xy & location, const hwlib::xy & size, const hwlib::xy & bounce = hwlib::xy(1,1));     

   virtual void draw() = 0;
   virtual void update(){};
   bool overlaps( const drawable & other );   
   virtual void interact( drawable & other ){};
    
};

#endif