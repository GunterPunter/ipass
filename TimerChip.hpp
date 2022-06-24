#ifndef TIMERCHIP_HPP
#define TIMERCHIP_HPP

#include "hwlib.hpp"

class timerchip{
protected:

	hwlib::i2c_bus_bit_banged_scl_sda & bus; //I2C-bus used for communication with the timer-chip
	uint8_t address; //I2C-address of the timer-chip
	
public:

	struct Time{
		int seconds;
		int minutes;
		int hours;
	};
	
	struct Date{
		int date;
		int month;
		int year;
		int day;
	};

	//constructor:
	timerchip(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t address);

	//operations:
	int make_int(uint8_t value); //convert a 0x number to an integer
	uint8_t make_0x(int value); //convert an integer to a 0x number

	virtual void set_time(Time & time)=0;
	virtual void set_date(Date & date)=0;
	virtual Time get_time()=0;
	virtual Date get_date()=0;
};


#endif