// Copyright Wouter Dijk
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/// @file

#ifndef MPULIBRARY_HPP
#define MPULIBRARY_HPP

#include "hwlib.hpp"

/// \brief
/// mpu6050 accelerometer library
/// \details
/// This is a library for the accelerometer within the
/// mpu6050. In this library you can wake the chip up
/// and ask for the x,y and z axis of the accelerometer.

class mpulibrary{
private:
    int mpu_addr;
    hwlib::i2c_bus_bit_banged_scl_sda &bus;
public:
    /// \brief
    /// constructor of class
    /// \details
    /// This constructor initializes the mpu6050 address
    /// and the i2c bus so that they can be used in the function later on.
    mpulibrary(int mpu_addr, hwlib::i2c_bus_bit_banged_scl_sda &bus):
        mpu_addr(mpu_addr),
        bus(bus)
    {}

    /// \brief
    /// wakeup function
    /// \details
    /// This function wakes up the mpu6050 by writing 0 to the
    /// 0x6b address within the mpu6050.
    void wake_up(){
        const uint8_t data[] = {0x6b, 0};
        hwlib::i2c_write_transaction(bus, mpu_addr).write(data, 2);
    };

    /// \brief
    /// X axis function
    /// \details
    /// This function gives back the x axis integer that the mpu6050 gives back.
    /// It does this by reading out the correct addressess and changing those
    /// bytes back to an integer by pushing the first byte to the left so that there
    /// is an 16 bit number.
    int16_t numbers_x(){
        hwlib::i2c_write_transaction(bus , mpu_addr).write(0x3b);
        auto a1 = hwlib::i2c_read_transaction(bus , mpu_addr).read_byte();
        hwlib::i2c_write_transaction(bus , mpu_addr).write(0x3c);
        auto a2 = hwlib::i2c_read_transaction(bus , mpu_addr).read_byte();

        return a1<<8 | a2;
    };

    /// \brief
    /// Y axis function
    /// \details
    /// This function gives back the y axis integer that the mpu6050 gives back.
    /// It does this by reading out the correct addressess and changing those
    /// bytes back to an integer by pushing the first byte to the left so that there
    /// is an 16 bit number.
    int16_t numbers_y(){
        hwlib::i2c_write_transaction(bus , mpu_addr).write(0x3d);
        auto a1 = hwlib::i2c_read_transaction(bus , mpu_addr).read_byte();
        hwlib::i2c_write_transaction(bus , mpu_addr).write(0x3e);
        auto a2 = hwlib::i2c_read_transaction(bus , mpu_addr).read_byte();

        return a1<<8 | a2;
    };

    /// \brief
    /// Z axis function
    /// \details
    /// This function gives back the z axis integer that the mpu6050 gives back.
    /// It does this by reading out the correct addressess and changing those
    /// bytes back to an integer by pushing the first byte to the left so that there
    /// is an 16 bit number.
    int16_t numbers_z(){
        hwlib::i2c_write_transaction(bus , mpu_addr).write(0x3f);
        auto a1 = hwlib::i2c_read_transaction(bus , mpu_addr).read_byte();
        hwlib::i2c_write_transaction(bus , mpu_addr).write(0x40);
        auto a2 = hwlib::i2c_read_transaction(bus , mpu_addr).read_byte();

        return a1<<8 | a2;
    };

};

#endif

