#include "hwlib.hpp"
#include "mpulibrary.hpp"
#include <array>
#include "ball.hpp"
#include "line.hpp"
#include "player.hpp"

int main(){
    const int mpu = 0x68;
    const int mpu2 = 0x69;

    namespace target = hwlib::target;
    auto scl     = target::pin_oc( target::pins::scl );
    auto sda     = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

    //display gedeelte
    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c ); 

    player p1(0);
    player p2(0);

    line l1(oled, hwlib::xy(10,10), hwlib::xy(10, 30) ,hwlib::xy(-1,1));
    line l2(oled, hwlib::xy(110,10), hwlib::xy(110, 30) ,hwlib::xy(-1,1));
    line top(oled, hwlib::xy(0,1), hwlib::xy(128, 1) ,hwlib::xy(1,-1));
    line bottom(oled, hwlib::xy(0,63), hwlib::xy(128, 63) ,hwlib::xy(1,-1));
    line left(oled, hwlib::xy(0,1), hwlib::xy(0, 64) ,hwlib::xy(0,0));
    line right(oled, hwlib::xy(127, 0), hwlib::xy(127, 63) ,hwlib::xy(0,0));
    ball b1(oled, hwlib::xy( 20, 20 ), 3, hwlib::xy( 5, 2 ) );
   
    std::array< drawable *, 7 > objects = { &l1, &l2, &top, &bottom, &left, &right, &b1};

    mpulibrary one(mpu2, i2c_bus);
    mpulibrary two(mpu, i2c_bus); 

    one.wake_up();
    two.wake_up();



    for(;;){   
        if(p2.points_amount() < 5 && p1.points_amount() < 5){
            if(b1.overlaps(left)){
                p2.points_plus();
                b1.reset(hwlib::xy( 20, 20 ));
            }else if(b1.overlaps(right)){
                p1.points_plus();
                b1.reset(hwlib::xy( 20, 20 ));
            }
        }else{
            auto f1 = hwlib::font_default_8x8();
            auto d1 = hwlib::terminal_from( oled, f1 ); 
            
            if(p1.points_amount() == 5 ){
                oled.clear();
                d1 << "PLAYER 1\nheeft\ngewonnen\n<-----" << hwlib::flush;

            }else{
                oled.clear();
                d1 << "PLAYER 2\nheeft\ngewonnen\n----->" << hwlib::flush;
            }
            break;
        }
        
        if(one.numbers_y() < -8000){
            l1.down(3);
        }else if(one.numbers_y() > -8000 && one.numbers_y() < -4000){
            l1.down(2);
        }else if(one.numbers_y() > 8000){
            l1.up(3);
        }else if(one.numbers_y() < 8000 && one.numbers_y() > 4000){
            l1.up(2);
        }

        if(two.numbers_y() < -8000){
            l2.down(3);
        }else if(two.numbers_y() > -8000 && two.numbers_y() < -4000){
            l2.down(2);
        }else if(two.numbers_y() > 8000){
            l2.up(3);
        }else if(two.numbers_y() < 8000 && two.numbers_y() > 4000){
            l2.up(2);
        }


        oled.clear();
        for( auto & p : objects ){
            p->draw();
        }
        oled.flush();
        for( auto & p : objects ){
            p->update();
        }
        for( auto & p : objects ){
            for( auto & other : objects ){
                p->interact( *other );
            } 
        }
    }
}
