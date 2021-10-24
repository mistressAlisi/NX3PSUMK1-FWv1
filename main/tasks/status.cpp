/*
 * task_status.cpp
 *
 *  Created on: Aug 29, 2021
 *      Author: rasheek
 */

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/FreeRTOS.h"
#include "status.h"
#include "delta9FW-CONSTS.h"
#include "rtc.h"
#include "wifi.h"
#include "provisioning.h"

extern task_RTC_class task_RTC;
extern task_wifi_class task_WIFI;
extern task_provisioning_class task_PROV;
extern task_status_class task_STATUS;

void task_status_class::_led_on(int channel) {
	ledcWrite(channel, MAX_DUTY_CYCLE);
};
void task_status_class::_led_off(int channel) {
	ledcWrite(channel, 0);
};

void task_status_class::_write_pwm(int channel, int dty) {
	if (dty > MAX_DUTY_CYCLE) dty = MAX_DUTY_CYCLE;
	  ledcWrite(channel, dty);
};

void task_status_class::init() {
	/** Set pins to output :**/
	  pinMode(STATUS_LED_GREEN,OUTPUT);
	  pinMode(STATUS_LED_FARRED,OUTPUT);
	  pinMode(STATUS_LED_RED,OUTPUT);
	  pinMode(STATUS_LED_C,OUTPUT);
	  pinMode(STATUS_LED_A,OUTPUT);
	  pinMode(STATUS_LED_BLUE,OUTPUT);
	 /** Now start the PWM channels: **/

	 ledcSetup(PWMChannel_GR,PWMFreq,PWMResolution);
	 ledcAttachPin(STATUS_LED_GREEN,PWMChannel_GR);

	 ledcSetup(PWMChannel_FR,PWMFreq,PWMResolution);
	 ledcAttachPin(STATUS_LED_FARRED,PWMChannel_FR);

	 ledcSetup(PWMChannel_RE,PWMFreq,PWMResolution);
	 ledcAttachPin(STATUS_LED_RED,PWMChannel_RE);

	 ledcSetup(PWMChannel_BL,PWMFreq,PWMResolution);
	 ledcAttachPin(STATUS_LED_BLUE,PWMChannel_BL);

	 ledcSetup(PWMChannel_A,PWMFreq,PWMResolution);
	 ledcAttachPin(STATUS_LED_A,PWMChannel_A);

	 ledcSetup(PWMChannel_C,PWMFreq,PWMResolution);
	 ledcAttachPin(STATUS_LED_C,PWMChannel_C);

//	printf("Preferences loaded");
}


/** Functions for WIFI heartbeat: **/
/** Disable WiFi Heartbeat / destroy task: **/
void task_status_class::hb_wifi_off() {
	if( _hb_wifi_handle != NULL )
		  {
		vTaskDelete( _hb_wifi_handle );
	};
	off(STATUS_LED_C);
}

/** Actual function that performs Wifi heartbeat **/
void task_status_class::_hb_wifi_task(void* parm) {
	uint current_tick = 0;
	uint delta = 0;
	for (;;) {
		current_tick = FreeRTOS::getTimeSinceStart();
		delta = current_tick - task_STATUS.led_stat_tick;
		if (delta >= task_STATUS.led_stat_heartbeat) {
			if (task_STATUS._hb_led_on == true) {
				task_STATUS.off(STAT_LED_C);
				task_STATUS._hb_led_on = false;
			} else {
				task_STATUS.max_on(STAT_LED_C);
				task_STATUS._hb_led_on = true;
			}
			task_STATUS.led_stat_tick = current_tick;
			delta = 0;
		};
	};
};
/** And it's static wrapper for xTaskCreate **/
void status_hwifi_task(void* parm) {
	    static_cast<task_status_class *>(parm)->_hb_wifi_task(parm);
};

/** Function to enable WiFi Heartbeat: **/
void task_status_class::hb_wifi_en() {
	 led_stat_tick = FreeRTOS::getTimeSinceStart();
	  xTaskCreate(status_hwifi_task, "STA_HB_WIFI", STACK_SIZE, NULL, tskIDLE_PRIORITY,& _hb_wifi_handle );
	  configASSERT( _hb_wifi_handle );
};

/** Functions for System heartbeat: **/
/** Disable System Heartbeat / destroy task: **/
void task_status_class::hb_act_off() {
	if( _hb_wifi_handle != NULL )
		  {
		vTaskDelete( _hb_act_handle );
	};
	off(STAT_LED_A);
}

/** Actual function that performs Wifi heartbeat **/
void task_status_class::_hb_act_task(void* parm) {
	uint current_tick = 0;
	uint delta = 0;
	for (;;) {
		current_tick = FreeRTOS::getTimeSinceStart();
		delta = current_tick - task_STATUS.led_act_tick;
		if (delta >= task_STATUS.led_act_heartbeat) {
			if (task_STATUS._hb_act_on == true) {
				task_STATUS.off(STAT_LED_A);
				task_STATUS._hb_act_on = false;
			} else {
				task_STATUS.max_on(STAT_LED_A);
				task_STATUS._hb_act_on = true;
			}
			task_STATUS.led_act_tick = current_tick;
			delta = 0;
		};
	};
};
/** And it's static wrapper for xTaskCreate **/
void status_sysa_task(void* parm) {
	    static_cast<task_status_class *>(parm)->_hb_act_task(parm);
};

/** Function to enable System Heartbeat: **/
void task_status_class::hb_act_en() {
	led_act_tick = FreeRTOS::getTimeSinceStart();
	  xTaskCreate(status_sysa_task, "STA_HB_ACT", STACK_SIZE, NULL, tskIDLE_PRIORITY,& _hb_act_handle );
	  configASSERT( _hb_act_handle );
};


void task_status_class::all_off() {
	task_status_class::_write_pwm(PWMChannel_GR,0);
	task_status_class::_write_pwm(PWMChannel_FR,0);
	task_status_class::_write_pwm(PWMChannel_RE,0);
	task_status_class::_write_pwm(PWMChannel_BL,0);
	task_status_class::_write_pwm(PWMChannel_A,0);
	task_status_class::_write_pwm(PWMChannel_C,0);
};

void task_status_class::all_on() {
	task_status_class::_write_pwm(PWMChannel_GR,MAX_DUTY_CYCLE);
	task_status_class::_write_pwm(PWMChannel_FR,MAX_DUTY_CYCLE);
	task_status_class::_write_pwm(PWMChannel_RE,MAX_DUTY_CYCLE);
	task_status_class::_write_pwm(PWMChannel_BL,MAX_DUTY_CYCLE);
	task_status_class::_write_pwm(PWMChannel_A,MAX_DUTY_CYCLE);
	task_status_class::_write_pwm(PWMChannel_C,MAX_DUTY_CYCLE);
};

void task_status_class::max_on(int led) {
	if (led == STAT_LED_R) {
		task_status_class::_write_pwm(PWMChannel_RE,MAX_DUTY_CYCLE);
	} else if (led == STAT_LED_F) {
		task_status_class::_write_pwm(PWMChannel_FR,MAX_DUTY_CYCLE);
	}  else if (led == STAT_LED_G) {
		task_status_class::_write_pwm(PWMChannel_GR,MAX_DUTY_CYCLE);
	} else if (led == STAT_LED_B) {
		task_status_class::_write_pwm(PWMChannel_BL,MAX_DUTY_CYCLE);
	} else if (led == STAT_LED_A) {
		task_status_class::_write_pwm(PWMChannel_A,MAX_DUTY_CYCLE);
	} else if (led == STAT_LED_C) {
		task_status_class::_write_pwm(PWMChannel_C,MAX_DUTY_CYCLE);
	}
}

void task_status_class::off(int led) {
    if (led == STAT_LED_R) {
		task_status_class::_write_pwm(PWMChannel_RE,0);
	} else if (led == STAT_LED_F) {
		task_status_class::_write_pwm(PWMChannel_FR,0);
	}  else if (led == STAT_LED_G) {
		task_status_class::_write_pwm(PWMChannel_GR,0);
	} else if (led == STAT_LED_B) {
		task_status_class::_write_pwm(PWMChannel_BL,0);
	} else if (led == STAT_LED_A) {
		task_status_class::_write_pwm(PWMChannel_A,0);
	} else if (led == STAT_LED_C) {
		task_status_class::_write_pwm(PWMChannel_C,0);
	}
}

int task_status_class::get_dty() {
	return MAX_DUTY_CYCLE;
}

void task_status_class::pwm_output_status(int _b, int _r, int _g, int _f) {
	task_status_class::_write_pwm(PWMChannel_BL,_b);
	task_status_class::_write_pwm(PWMChannel_RE,_r);
	task_status_class::_write_pwm(PWMChannel_GR,_g);
	task_status_class::_write_pwm(PWMChannel_FR,_f);
}


