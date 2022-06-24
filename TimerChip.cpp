#include "TimerChip.hpp"

timerchip::timerchip(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t address):
	bus(bus), address(address)
{}

int timerchip::make_int(uint8_t value){
	return((value/16*10) + (value%16));
}

uint8_t timerchip::make_0x(int value){
	return((value/10*16) + (value%10));
}