/*
 * task_wifi.cpp
 *
 *  Created on: Aug 29, 2021
 *      Author: rasheek
 */

#ifndef MAIN_INCLUDE_TASKS_TASK_WIFI_CPP_
#define MAIN_INCLUDE_TASKS_TASK_WIFI_CPP_

// How many WIFI nets to include in the storage arrays below?
#define MAX_WIFI_NET_SCANNETS 31

#include <stdio.h>
#include "Arduino.h"  // Arduino data type definitions
#include "WiFi.h"
#include "esp_event.h"
class task_wifi_class {
private:


	void static _evHandle(void* handler_args, esp_event_base_t base, int32_t id, void* event_data);

	void  _connect_AP();

	bool  active;

	bool  isAP;

	void _eConnected();

	void _eSTAIP();

	void _eDisconnected();

public:
	void init();

	void start_AP();

	void start_STA();

	bool is_AP();

	bool is_active();

	void scan();



	String ssid;

	IPAddress ipaddr;
	IPAddress subnet;
	IPAddress gw;
	IPAddress dns;



};

#endif /* MAIN_INCLUDE_TASKS_TASK_WIFI_CPP_ */
