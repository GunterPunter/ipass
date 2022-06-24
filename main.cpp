#include "hwlib.hpp"
#include "TimerChip.hpp"
#include "DS3231.hpp"

int main(void){
	
	hwlib::wait_ms( 500 );  
	namespace target = hwlib::target;
	auto scl     = target::pin_oc( target::pins::scl );
	auto sda     = target::pin_oc( target::pins::sda );
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
	
	ds3231 klok(i2c_bus);
	
	timerchip::Time tijd;
	tijd.seconds = 12;
	tijd.minutes = 12;
	tijd.hours = 12;

	klok.set_time(tijd);
	
	
	for(;;){
		hwlib::wait_ms(1000);
	
		tijd = klok.get_time();
	
		hwlib::cout << tijd.seconds << "|" << tijd.minutes << "|" << tijd.hours << "\n";
	}
}