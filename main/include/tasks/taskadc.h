/*
 * adc.h
 *
 *  Created on: Sep 17, 2021
 *      Author: rasheek
 */

#include <ADS1X15.h>
#include <Wire.h>
#ifndef MAIN_INCLUDE_TASKS_ADC_H_
#define MAIN_INCLUDE_TASKS_ADC_H_
/** d9NX3 FW ADC Driver Class **/
class task_adc_class {
private:
	/** This is the actual ADS driver: **/
	ADS1113 ADS;
	/** Currently listening to channel: **/
	int current = 0;
	/** PIN numbers for set channel (A,B,C for Mux): **/
	const int A = 25;
	const int B = 33;
	const int C = 5;
	/** This function actually sets the channel, it must be private so nothing can call it mid-conversion. **/
	bool _set_channel(int chan);
public:
	void init(TwoWire *WireObj);
	int16_t read_adc(int chan);
	const int Y0 = 0;
	const int Y1 = 1;
	const int Y2 = 2;
	const int Y3 = 3;
	const int Y4 = 4;
	const int Y5 = 5;
	const int Y6 = 6;
	const int Y7 = 7;

};



#endif /* MAIN_INCLUDE_TASKS_ADC_H_ */
