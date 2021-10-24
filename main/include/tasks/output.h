/*
 * system_settings.h
 *
 *  Created on: Aug 28, 2021
 *      Author: rasheek
 */

#ifndef MAIN_INCLUDE_OUTPUT_H_
#define MAIN_INCLUDE_OUTPUT_H_


#include "../../components/pca9633/pca9633.h"
#include <iostream>
#include "json.hpp"
#include "Arduino.h"
using json = nlohmann::json;
/** d9NX3 FW Output Control, management and interacction class. **/
class task_output_class {
private:
	PCA9633 output_driver;
	json json_config;
	bool loaded = false;
	/** Actual output levels in PCT we will write to PWM and LED status: **/
	int b = 0;
	int r = 0;
	int g = 0;
	int f = 0;
	int _b = 0;
	int _r = 0;
	int _g = 0;
	int _f = 0;
	/** Handler for clock task: **/
	 TaskHandle_t _clk_act_handle;
	 /** and ticks **/
	uint clk_act_heartbeat = 30000;



	void _set(float _b, float _r, float _g, float _f);
public:
	void init();
	void load();
	void setStep();
	// Enable the 60 second update clock
	void clk_act_en();
	void clk_act_task(void *parm);
	/** tick will be updated in runtime **/
	uint clk_act_tick;

	String get_csv();
};

#endif


