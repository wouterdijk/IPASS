#include "hwlib.hpp"
//Opdracht 7/8

//Deze functie is er om eerst alle leds donker te maken dus eigenlijk te flushen.
//En daarna te zorgen dat het goede ledje aan gaat.
void write(hwlib::i2c_bus_bit_banged_scl_sda& i2c_bus , uint8_t x){
    hwlib::i2c_write_transaction(i2c_bus, 0x38).write(0x0f);
    hwlib::i2c_write_transaction(i2c_bus, 0x38).write(x);
    hwlib::wait_ms(100);
}

//Deze functie leest de byte uit van de chip.
uint8_t read(hwlib::i2c_bus_bit_banged_scl_sda& i2c_bus){
    return hwlib::i2c_read_transaction(i2c_bus , 0x38).read_byte();
}

int main(){

    //Dit gedeelte is er om de scl en sda pins te initieren en er een bus van te maken.
    namespace target = hwlib::target;
    auto scl     = target::pin_oc( target::pins::scl );
    auto sda     = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda ); 

    //Dit is er voor om te checken of de knop is ingedrukt. En als de knop is ingedrukt
    //gaan alle 4 de ledjes aan. Als de knop niet is ingedrukt gaan alle ledjes op donker.
    while(1){
        if(read(i2c_bus) & 0x10){
            write(i2c_bus, 0x00);            
        }else{
            write(i2c_bus, 0x0f);
        }
    }
}