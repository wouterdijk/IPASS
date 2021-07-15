#include "hwlib.hpp"
//Opdracht 2
//Een open collector device kan meerdere apparaten ontvangen met verschillende
//voltage groottes. Dit is handig want daarmee kan je dus elk apparaat eraan doen
//en maakt het dus niet uit hoe groot de voltage is die het apparaat gebruikt.

//Opdracht 6

//Deze functie is er om eerst alle leds donker te maken dus eigenlijk te flushen.
//En daarna te zorgen dat het goede ledje aan gaat.
void write(hwlib::i2c_bus_bit_banged_scl_sda& i2c_bus , uint16_t x){
    hwlib::i2c_write_transaction(i2c_bus, 0x38).write(0x0f);
    hwlib::i2c_write_transaction(i2c_bus, 0x38).write(x);
    hwlib::wait_ms(100);
}

int main(){

    //Dit gedeelte is er om de scl en sda pins te initieren en er een bus van te maken.
    namespace target = hwlib::target;
    auto scl     = target::pin_oc( target::pins::scl );
    auto sda     = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

    //Dit is om het kitt patroontje heen continue heen en weer te laten gaan.
    //Dit wordt gedaan door middel van de write functie die ik zelf heb gemaakt.
    while(1){
        write(i2c_bus, 0x0e);
        write(i2c_bus, 0x0d);
        write(i2c_bus, 0x0b);
        write(i2c_bus, 0x07);
        write(i2c_bus, 0x0b);
        write(i2c_bus, 0x0d);
    }
}
