/*
 * output.cpp
 *
 *  Created on: Sep 5, 2021
 *      Author: rasheek
 */
/** PCA9633 CHANNEL TO D9NX3 OUTPUT MAPPING: **/
/*
 * PCA9633/R -> D9NX3/DEEP RED
 * PCA9633/G -> D9NX3/LIME GREEN
 * PCA9633/B -> D9NX3/DEEP BLUE
 * PCA9633/W -> D9NX3/FAR RED
 */
/** END TABLE **/
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
#include "profile_settings.h"
#include <iostream>
#include "json.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../include/FreeRTOS.h"
extern task_RTC_class task_RTC;
extern task_status_class task_STATUS;
extern task_provisioning_class task_PROV;
extern task_output_class task_OUT;
extern SemaphoreHandle_t SEMA_i2c_bus;
// JSON parser object:
using json = nlohmann::json;

/**
 * With a loaded and validated profile,  this function is called to iterate through the profile steps,
 * find the correct one and assign output values to the drivers and status LEDs:
 * it should be called every minute ;)
 */
/** Helper class that calculates and sets output levels for both PWM and LEDs: **/
void task_output_class::_set(float _b, float _r, float _g, float _f) {
	/** Set Status LED output: **/
	int bo;
	int ro;
	int go;
	int fo;
	int dty = task_STATUS.get_dty();
	float ratio = 0;
	ratio = _b/100;
	bo = ratio * dty;
	ratio = _r/100;
	ro = ratio * dty;
	ratio = _g/100;
	go = ratio * dty;
	ratio = _f/100;
	fo = ratio * dty;
	task_STATUS.pwm_output_status(bo,ro,go,fo);

	dty = 256;
	ratio = _b/100;
	bo = ratio * dty;
	ratio = _r/100;
	ro = ratio * dty;
	ratio = _g/100;
	go = ratio * dty;
	ratio = _f/100;
	fo = ratio * dty;

//	if( xSemaphoreTake( SEMA_i2c_bus, ( TickType_t ) 100 ) == pdTRUE ) {
	output_driver.setrgbw(bo,ro,go,fo);
//		printf("Took semaphore\n");
//		xSemaphoreGive( SEMA_i2c_bus );
//	};
};

void task_output_class::setStep() {
	if(loaded == false) {
		printf("** LOAD a profile first! **\n");
		return;
	}
	//DateTime now = task_RTC.now;
	printf("**-> Setting output step for time: %d:%d <-**\n",task_RTC.now.hour(),task_RTC.now.minute());
	/** Let's step through the profile and find the right step: **/

	std::string start;
	std::string end;
	std::string buf;
	int hour;
	int min;
	int shour;
	int smin;
	auto steps = json_config.at("steps");
	bool found = false;
	bool write = false;
	for (auto it = steps.begin(); it != steps.end();  ++it)
	{

		if ( found == false) {
		start =  it.value()["start"].get<std::string>();
		end =  it.value()["end"].get<std::string>();
		//printf("Value for IT: %s, %s",start.c_str(),end.c_str());
		/** Make sure we're not over the end: **/
		/** convert hour first: **/
		buf = end.substr(0,2);
		hour = std::stoi(buf);
		/** Now Minute: **/
		buf = end.substr(3,6);
		min = std::stoi(buf);
		/** Store them in integer format for comparisons: **/
		int time_now = (task_RTC.now.hour()* 60)+task_RTC.now.minute();
		int time_end = (hour* 60)+min;
		//printf("Time now: %d, time end: %d",time_now,time_end);
		//printf("**-> Current Step: begins at %s and ends at %s. <-**\n",start.c_str(),end.c_str());
		//printf("END condition: hour: %d, min: %d\n",hour,min);
		/** Since we're checking we're not PAST the profile step first, now.hour() must be <= hour and then now.minute() must be < min for this to be true: **/
		if (time_now <= time_end) {
				/** Ok, we are not in the future, now check that we're in the right step: **/
				/** So we check the start time: **/
				/** convert hour first: **/
				buf = start.substr(0,2);
				shour = std::stoi(buf);
				/** Now Minute: **/
				buf = start.substr(3,6);
				smin = std::stoi(buf);

				//printf("START condition: hour: %d, min: %d\n",shour,smin);
				int time_start = (shour* 60)+smin;


				/** Now do the reverse check for now.hour() and now.minute() vis a vis hour and min: **/
				if (time_now >= time_start) {
					//printf("hr min: %d\,%d\n",smin,task_RTC.now.minute());
						//printf("min\n");
						/** We found our step!! **/
						printf("**-> Selected Step: begins at %s and ends at %s. <-**\n",start.c_str(),end.c_str());
						found = true;
						_b = it.value()["b"].get<int>();
						if (_b != b) {
							b = _b;
							write = true;
						}
						_r = it.value()["r"].get<int>();
						if (_r != r) {
							r = _r;
							write = true;
						}
						_g = it.value()["g"].get<int>();
						if (_g != g) {
							g = _g;
							write = true;
						}
						_f = it.value()["f"].get<int>();
						if (_f != f) {
							f = _f;
							write = true;
						}
						printf("**-> Output Set points: B[%d],R[%d],G[%d],F[%d] <-**\n",b,r,g,f);

				}


		}
		} else {

		}

	}
	if (found == true) {
		/** Everything went well, write to hardware: **/
		if (write == true) {
		_set(b,r,g,f);
	}}

};
void task_output_class::load() {
	/** Now, lets load the default, or user provided, profile: **/
	String en_profile = task_PROV.prefs.getString("current_profile");
	bool profile_user = task_PROV.prefs.getBool("profile_user");
	String full_path;
	/** if Empty string, then set to default: **/
	if (en_profile.compareTo("")==0) {
		en_profile = String(PROF_DEF);
	}
	/** now build a full path: **/
	if (profile_user == true) {
		/** User supplied profile: **/
		full_path = PROF_USR_PATH;
		full_path.concat(en_profile);
		full_path.concat(PROF_EXT);
	} else {
		/** Default/Factory supplied profile: **/
		full_path = PROF_DEF_PATH;
		full_path.concat(en_profile);
		full_path.concat(PROF_EXT);
	}
	printf("**-> Output Profile path: %s <-**\n",full_path.c_str());
	/** Try and open the file: **/
    File file = LittleFS.open(full_path.c_str());
    if(!file || file.isDirectory()){
    	printf("**-> Failed to open file: %s for reading!! <-**\n",full_path.c_str());
        return;
    }
    /** Read and load contents: **/
    String contents = file.readString();
    json_config = json::parse(contents.c_str());
    std::string name = json_config.value("name","string");
    loaded = true;
    printf("**-> Profile loaded \"%s\": and ready! <-**\n",name.c_str());

};

/** Function to be called every 60 seconds for clock/step update**/
void task_output_class::clk_act_task(void* parm) {
	uint current_tick = 0;
	uint delta = 0;
	for (;;) {
		current_tick = FreeRTOS::getTimeSinceStart();
		delta = current_tick - task_OUT.clk_act_tick;
		if (delta >= task_OUT.clk_act_heartbeat) {

			delta = 0;
			task_OUT.clk_act_tick = current_tick;

		};
	};
};
/** And it's static wrapper for xTaskCreate **/
void output_clk_task(void* parm) {
	    static_cast<task_output_class *>(parm)->clk_act_task(parm);

};

/** Function to enable Output timer heartbeat: **/
void task_output_class::clk_act_en() {

	clk_act_tick = FreeRTOS::getTimeSinceStart();
	  xTaskCreate(output_clk_task, "OUT_CLK_TASK", 3100, NULL, tskIDLE_PRIORITY,& _clk_act_handle );
	  configASSERT( _clk_act_handle );
};



void task_output_class::init() {
	/** In case LittleFS is not initialised: **/
  /**  if (!LittleFS.begin(false,"/littlefs",255,"root")) {
        printf("An Error has occurred while mounting LittleFS!! ABORT!");
        while (1) {};
  	}**/
	task_STATUS.all_off();
	output_driver.begin(PCA9633_ADDR);
	printf("**-> Output Task / Drivers ready @ I2c Addr: 0x%02X<-**\n",PCA9633_ADDR);
	task_STATUS.hb_act_en();
	/** Turn all channels off... just in case we left them on from a reboot: **/
	output_driver.setrgbw(0,0,0,0);
	/** let's get some fun Wire.begin();   going: Load the current profile: **/
	load();
	/** and set the step! **/
	setStep();
	/** Finally... start the clock/heartbeat task. **/
	//clk_act_en();
}

String task_output_class::get_csv() {
	std::string name = json_config.value("name","string");
	String return_str = String(name.c_str());
	bool profile_user = task_PROV.prefs.getBool("profile_user");
	if (profile_user == true) {
		return_str += ",u,";
	} else {
		return_str += ",s,";
	}
	return_str += String(b);
	return_str += ",";
	return_str += String(r);
	return_str += ",";
	return_str += String(g);
	return_str += ",";
	return_str += String(f);
	return return_str;
}










