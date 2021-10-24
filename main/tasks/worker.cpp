#include <Preferences.h>
#include <Arduino.h>
#include <LittleFS.h>
#include "output.h"
#include "rtc.h"
#include "status.h"
#include "wifi.h"
#include "provisioning.h"
#include "output.h"
#include "delta9FW-CONSTS.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/FreeRTOS.h"
#include "worker.h"

extern task_worker_class task_WORKER;
extern task_RTC_class task_RTC;
extern task_output_class task_OUT;

void task_worker_class::_doWork() {

};


void task_worker_class::task(void *parm) {
	    uint current_tick = 0;
		uint delta = 0;
		const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
		for (;;) {
			current_tick = FreeRTOS::getTimeSinceStart();
			delta = current_tick - task_WORKER.clk_act_tick;
			if (delta >= task_WORKER.clk_act_heartbeat) {
				task_RTC.update();
			    vTaskDelay( xDelay );
				task_OUT.setStep();
				delta = 0;
				task_WORKER.clk_act_tick = current_tick;

			};
		};
};

/** And it's static wrapper for xTaskCreate **/
void worker_task(void* parm) {
	    static_cast<task_worker_class *>(parm)->task(parm);

};

/** Function to enable Output timer heartbeat: **/
void task_worker_class::init() {

	clk_act_tick = FreeRTOS::getTimeSinceStart();
	  xTaskCreate(worker_task, "WORKER_CLK_TASK", 3100, NULL, tskIDLE_PRIORITY,& _task_handle );
	  configASSERT( _task_handle );

};

