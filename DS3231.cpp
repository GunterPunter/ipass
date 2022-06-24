#include "DS3231.hpp"

ds3231::ds3231(hwlib::i2c_bus_bit_banged_scl_sda & bus, uint8_t address):
	timerchip(bus, address)
{}

void ds3231::set_time(Time & time){
	uint8_t data[4] = {seconds_register, timerchip::make_0x(time.seconds), timerchip::make_0x(time.minutes), timerchip::make_0x(time.hours)}; //convert values from int to 0x numbers and combine into data array (the 0 at the start points the ds3231 to the 00h register)
	hwlib::i2c_write_transaction(bus, address).write(data, 4); //start and perform hwlib i2c write transaction
}

void ds3231::set_date(Date & dates){
	uint8_t data[5] = {date_register, timerchip::make_0x(dates.day), timerchip::make_0x(dates.date), timerchip::make_0x(dates.month), timerchip::make_0x(dates.year-2000)}; //convert values from int to 0x numbers and combine into data array (the 3 at the start points the ds3231 to the 03h register)
	hwlib::i2c_write_transaction(bus, address).write(data, 5); //start and perform hwlib i2c write transaction
}

timerchip::Time ds3231::get_time(){
	hwlib::i2c_write_transaction(bus, address).write(seconds_register); //point to the seconds registers of the ds3231
	uint8_t tmp[3]; //make a temporary array
	hwlib::i2c_read_transaction(bus, address).read(tmp, 3); //start and perform hwlib i2c read transaction
	Time rtw;
	rtw.seconds = timerchip::make_int(tmp[0]);
	rtw.minutes = timerchip::make_int(tmp[1]);
	rtw.hours = timerchip::make_int(tmp[2]);
	return rtw;
}

timerchip::Date ds3231::get_date(){
	hwlib::i2c_write_transaction(bus, address).write(date_register); //point to the date registers of the ds3231
	uint8_t tmp[4]; //make a temporary array
	hwlib::i2c_read_transaction(bus, address).read(tmp, 4); //start and perform hwlib i2c read transaction
	Date rtw;
	rtw.date = ds3231::make_int(tmp[0]); //set the tmp values in rtw as integers
	rtw.month = ds3231::make_int(tmp[1]);
	rtw.year = ds3231::make_int(tmp[2]);
	rtw.day	 = ds3231::make_int(tmp[3]);
	return rtw;
}