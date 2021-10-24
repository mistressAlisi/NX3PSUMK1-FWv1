/*
 * adc.cpp
 *
 *  Created on: Sep 17, 2021
 *      Author: rasheek
 */



#include <Preferences.h>
#include "delta9FW-CONSTS.h"
#include "taskadc.h"
#include <Wire.h>
#include "ADS1X15.h"
#include "Arduino.h"



void task_adc_class::init(TwoWire *WireObj) {
	  bool status;
	  pinMode(A,OUTPUT);
	  pinMode(B,OUTPUT);
	  pinMode(C,OUTPUT);
	  ADS = ADS1113(0x48,WireObj);
	  status = ADS.begin();
	  if (status == false) {
		  printf("**->Error!! Unable to start ADC!! <-**\n");
		  return;
	  };
	 ADS.setGain(16);

};


bool task_adc_class::_set_channel(int chan) {
	/** Don't change channel if it's already set to chan: **/
	if (chan == current) {
		return true;
	}
	if (chan == Y0) {
		/** We're setting to Y0, so turn off all pins and return true: **/
		digitalWrite(A,LOW);
		digitalWrite(C,LOW);
		digitalWrite(B,LOW);
		current = Y0;
		return true;
	} else if (chan == Y1) {
		/** We're setting to Y1: */
		digitalWrite(A,HIGH);
		digitalWrite(C,LOW);
		digitalWrite(B,LOW);
		current = Y1;
		return true;
	} else if (chan == Y2) {
		/** We're setting to Y2: */
		digitalWrite(A,LOW);
		digitalWrite(C,HIGH);
		digitalWrite(B,LOW);
		current = Y2;
		return true;
	} else if (chan == Y3) {
		/** We're setting to Y3: */
		digitalWrite(C,LOW);
		digitalWrite(A,HIGH);
		digitalWrite(B,HIGH);
		current = Y3;
		return true;
	}  else if (chan == Y4) {
		/** We're setting to Y4: */
		digitalWrite(C,HIGH);
		digitalWrite(A,LOW);
		digitalWrite(B,LOW);
		current = Y4;
		return true;
	}  else if (chan == Y5) {
		/** We're setting to Y5: */
		digitalWrite(A,HIGH);
		digitalWrite(B,LOW);
		digitalWrite(C,HIGH);
		current = Y5;
		return true;
	}  else if (chan == Y6) {
		/** We're setting to Y6: */
		digitalWrite(C,HIGH);
		digitalWrite(B,HIGH);
		digitalWrite(A,LOW);
		current = Y6;
		return true;
	}  else if (chan == Y7) {
		/** We're setting to Y7: */
		digitalWrite(A,HIGH);
		digitalWrite(C,HIGH);
		digitalWrite(B,HIGH);
		current = Y7;
		return true;
	}
	return false;
}

int16_t task_adc_class::read_adc(int chan) {
	/** Wrong channel selected. **/
	if (_set_channel(chan) == false) {
		printf("ADC Error: Wrong channel selected!\n");
		return 0;
	}
	/** After setting the channel, go ahead and read the ADC value: **/
	ADS.requestADC(1);
	while (!ADS.isReady()) {};
	int16_t val = ADS.getValue();
	printf("ADC Read Value for channel %d is %d.\n",current,val);
	return val;

}
