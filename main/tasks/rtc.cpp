/*
 * task_hw_rtc.cpp
 *
 *  Created on: Aug 28, 2021
 *      Author: rasheek
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "FreeRTOS.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "spiram.h"
#include "himem.h"
#include <Wire.h>
#include "Arduino.h"
#include "MCP7940.h"
#include "rtc.h"
#include "delta9FW-CONSTS.h"
extern task_RTC_class task_RTC;
extern SemaphoreHandle_t SEMA_i2c_bus;
void task_RTC_class::print_current_time() {
		// get the date and time from RTC
	  printf("**-> Current RTC Time is: (Y/M/D HH:MM:SS): %d/%d/%d, %d:%d:%d<-**\n",now.year(),now.month(),now.day(),now.hour(),now.minute(),now.second());

}

void task_RTC_class::update() {
	DateTime n_now = MCP7940.now();
	if (n_now.year() > 2000) {
		now = n_now;
	}
}

DateTime task_RTC_class::get_current_time() {
	  now = MCP7940.now(); // get the date and time from RTC
	  return now;

}
void task_RTC_class::set_time(int year, int month, int day, int hour=0, int min=0, int sec=0) {
	  DateTime adj = DateTime(year,month,day,hour,min,sec);
	  MCP7940.adjust(adj);
	  now = MCP7940.now();
	  printf("**-> Current RTC Time is NOW: (Y/M/D HH:MM:SS): %d/%d/%d, %d:%d:%d<-**\n",now.year(),now.month(),now.day(),now.hour(),now.minute(),now.second());

}

/** Function to be called every 60 seconds for clock/step update**/
void task_RTC_class::clk_act_task(void* parm) {
	uint current_tick = 0;
	uint delta = 0;
	for (;;) {
		current_tick = FreeRTOS::getTimeSinceStart();
		delta = current_tick - task_RTC.clk_rtc_tick;
		if (delta >= task_RTC.clk_rtc_heartbeat) {
			if( xSemaphoreTake( SEMA_i2c_bus, ( TickType_t ) 100 ) == pdTRUE ) {
				//task_RTC.MCP7940.begin();
				task_RTC.now = task_RTC.get_current_time();
				delta = 0;
				printf("**-> Current RTC Time is NOW: (Y/M/D HH:MM:SS): %d/%d/%d, %d:%d:%d<-**\n",task_RTC.now.year(),task_RTC.now.month(),task_RTC.now.day(),task_RTC.now.hour(),task_RTC.now.minute(),task_RTC.now.second());
				task_RTC.clk_rtc_tick = current_tick;
				xSemaphoreGive( SEMA_i2c_bus );
			}

		};
	};
};
/** And it's static wrapper for xTaskCreate **/
void rtc_clk_task(void* parm) {
	    static_cast<task_RTC_class *>(parm)->clk_act_task(parm);

};

void task_RTC_class::init() {
	  while (!MCP7940.begin()) { // Initialize RTC communications
	  printf("Unable to find MCP7940. Checking again in 1 second.\n");
	  delay(1000);
	  }
	  MCP7940.deviceStart();
	  MCP7940.setBattery(true);
	  if(!MCP7940.deviceStatus()) {
		  printf("ERROR: Unable to start MCP7940 device: RTC failure? (10 second pause)\n");
		  delay(10000);
	  } else {
		  printf("RTC oscillator init complete..\n");
	  };
	  now = MCP7940.now();
	  /** Start the Clock task ***/
	 // clk_rtc_tick = FreeRTOS::getTimeSinceStart();
	  //xTaskCreate(rtc_clk_task, "rtc_clk_task", STACK_SIZE, NULL, tskIDLE_PRIORITY,& _clk_rtc_handle );
	 // configASSERT( _clk_rtc_handle );
}


