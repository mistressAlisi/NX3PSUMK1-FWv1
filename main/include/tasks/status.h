/*
 * status.h
 *
 *  Created on: Aug 29, 2021
 *      Author: rasheek
 */


#ifndef COMPONENTS_INCLUDE_STATUS_RTC_H_
#include <stdio.h>
#include "Arduino.h"  // Arduino data type definitions
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define COMPONENTS_INCLUDE_STATUS_RTC_H_
/** Definitions for convenience here: **/
#define STAT_LED_A 100
#define STAT_LED_C 101
#define STAT_LED_F 102
#define STAT_LED_R 200
#define STAT_LED_G 201
#define STAT_LED_B 202

class task_status_class {
private:

	/** HEARTBEAT (blink) functions for the WIFI Status (C)onnected LED: **/
	/** Status Indicator (flag): **/
	bool _hb_led_on;
	/** Handler for above task: **/
	 TaskHandle_t _hb_wifi_handle;
	/** Timeout for function and current counter values: **/
	uint led_stat_heartbeat = 500;
	uint led_stat_tick;

	/** HEARTBEAT (blink) functions for the System Status (A)ctivity LED: **/
	/** Status Indicator (flag): **/
	bool _hb_act_on;
	/** Handler for above task: **/
	 TaskHandle_t _hb_act_handle;
	/** Timeout for function and current counter values: **/
	uint led_act_heartbeat = 625;
	uint led_act_tick;


	/** Turn a status LED ON **/
	void _led_on(int led);
	/** Turn a status LED OFF **/
	void _led_off(int led);

	/** Set a status LED   to a given Dty cycle (0/4096)**/
	void _write_pwm(int led,int dty);

	/** Our status indicators use PWM for driving the LED brightness and patterns; PWM parameters below
	 */
	const int PWMFreq = 10000;
	const int PWMResolution = 13;
	const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1);
	/** STATUS LED IO pin and channels definitions: **/
	const int STATUS_LED_A = 12;
	const int PWMChannel_A = 0;
	const int STATUS_LED_FARRED = 22;
	const int PWMChannel_FR = 1;
	const int STATUS_LED_RED = 21;
	const int PWMChannel_RE = 2;
	const int STATUS_LED_C = 26;
	const int PWMChannel_C = 3;
	const int STATUS_LED_BLUE = 14;
	const int PWMChannel_BL = 4;
	const int STATUS_LED_GREEN = 23;
	const int PWMChannel_GR = 5;


public:
	/** Turn ALL LEDS off: **/
	void all_off();
	/** Turn ALL LEDS on: **/
	void all_on();
	/** Init and startup function (C++ standard): **/
	void init();

	/** Convenience function to turn  any given LED all the way on: **/
	void max_on(int LED);

	/** Convenience function to turn  any given LED off: **/
	void off(int LED);

	/** START the WiFi Heartbeat LED ("LED C" for connection) with the specified WIFI heartbeat delay **/
	void hb_wifi_en();

	/** STOP the WiFi heartbeat task: **/
	void hb_wifi_off();

	/** Heartbeat/blink function for the C(Connected) LED: **/
	void _hb_wifi_task(void* parm);

	/** START the System Heartbeat LED ("LED A" for Activity) with the specified Activity heartbeat delay **/
	void hb_act_en();

	/** STOP the Activity heartbeat task: **/
	void hb_act_off();

	/** Heartbeat/blink function for the A(ctivity) LED: **/
	void _hb_act_task(void* parm);

	/** Convenience function to PWM all RGBF leds: **/
	void pwm_output_status(int _b, int _r, int _g, int _f);

	int get_dty();
};


#endif /* COMPONENTS_INCLUDE_STATUS_RTC_H_ */
