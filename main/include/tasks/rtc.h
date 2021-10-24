/*
 * rtc.h
 *
 *  Created on: Aug 28, 2021
 *      Author: rasheek
 */

#include "MCP7940.h"
#ifndef COMPONENTS_MCP7940_INCLUDE_TASKS_RTC_H_
#define COMPONENTS_MCP7940_INCLUDE_TASKS_RTC_H_
class task_RTC_class {
private:
	/**This is the actual MCP7940 driver Object we wrap around: **/
	MCP7940_Class MCP7940;
	uint clk_rtc_heartbeat = 20000;
	TaskHandle_t _clk_rtc_handle;
public:
	/** Set the current time and date: **/
	void set_time(int year, int month, int day, int hour, int min, int sec);
	/** Print Current Time to Printf for debug. **/
	void print_current_time();
	/** Init and startup function (C++ standard): **/
	void init();
	/** FreeRTOS thread task **/
	void clk_act_task(void* parm);


	void update();

	/** Get current time	 */
	DateTime get_current_time();
	DateTime now;
	uint clk_rtc_tick = 0;

};


#endif /* COMPONENTS_MCP7940_INCLUDE_TASKS_RTC_H_ */
