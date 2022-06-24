#ifndef DS3231_HPP
#define DS3231_HPP

#include "hwlib.hpp"
#include "TimerChip.hpp"

class ds3231 : public timerchip{
private:

	const static uint8_t default_address = 0x68; //Default I2C-address for the DS3231-chip (0x68)
	const uint8_t seconds_register = 0; //0 (00h) is the address for the seconds register of the DS3231-chip
	const uint8_t date_register = 3; //3 (03h) is the address for the date register of the DS3231-chip
	
public:

	//The constructor for a "ds3231" object.
	//It takes 1 or 2 argument(s):
	//The first is of the type "hwlib::i2c_bus_bit_banged_scl_sda &". This refers to the i2c channel that will be used to communicate with the ds3231.
	//The second is the i2c address of your ds3231 in "uint8_t" format. This parameter is 0x68 by default.
	ds3231(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t address = ds3231::default_address);
	
	//Member function to set the time of a ds3231 object.
	//This function will set/write the time-registers of your ds3231 object.
	//This function takes (up to) 3 arguments in the following order:
	//seconds, minutes, hours
	//All arguments should be of the type "int".
	//All arguments left empty will default to 0.
	void set_time(Time & time) override;
	
	//Member function to set the date of a ds3231 object.
	//This function will set/write the date-registers of your ds3231 object.
	//This function takes 3 or 4 arguments in the following order:
	//date, month, year, (day)
	//All arguments should be of the type "int".
	//The "day" argument is to specify the day: monday, tuesday, etc...
	//when left blank this will default to 1 (=monday).
	void set_date(Date & date) override;
	
	//Member function to get the time of a ds3231 object.
	//This function will get/read the time-registers of your ds3231 object.
	//This function takes a single argument of the type "int[3]".
	timerchip::Time get_time() override;
	
	//Member function to get the date of a ds3231 object.
	//This function will get/read the date-registers of your ds3231 object.
	//This function takes a single argument of the type "int[4]".
	timerchip::Date get_date() override;
};

#endif