#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_console.h"
#include "argtable3/argtable3.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "cmd_rtc.h"

#include "../../include/tasks/wifi.h"
extern task_wifi_class task_WIFI;


/**
 * wifi_startAP: Start WIFI in STAtion/Client Mode using provisioned params
 * Command: time_now.
 * @param argc
 * @param argv
 * @return
 */
static int wifi_startSTA(int argc, char **argv) {
	task_WIFI.start_STA();
	return 0;
};
/**
 * wifi_startAP: Start WIFI in SoftAP Mode
 * Command: time_now.
 * @param argc
 * @param argv
 * @return
 */
static int wifi_startAP(int argc, char **argv) {
	task_WIFI.start_AP();
	return 0;
};

static int wifi_status(int argc, char **argv) {
	if (task_WIFI.is_active() == false) {
		printf("WiFi is not enabled.\n");
		return 0;
	}
	if (task_WIFI.is_AP() == true) {

		printf("WiFi is in AP Mode.\nSSID: '%s'.\nIP Address: %d.%d.%d.%d, Netmask: %d.%d.%d.%d\n",
				task_WIFI.ssid.c_str(),task_WIFI.ipaddr[0],task_WIFI.ipaddr[1],task_WIFI.ipaddr[2],task_WIFI.ipaddr[3],
				task_WIFI.subnet[0],task_WIFI.subnet[1],task_WIFI.subnet[2],task_WIFI.subnet[3]);
	} else {
		printf("**-> WiFi is in STA/Client Mode. \nSSID: '%s'.\nIP Address: %d.%d.%d.%d, Netmask: %d.%d.%d.%d. Gateway: %d.%d.%d.%d <-**\n",task_WIFI.ssid.c_str(),task_WIFI.ipaddr[0],task_WIFI.ipaddr[1],task_WIFI.ipaddr[2],task_WIFI.ipaddr[3],
				task_WIFI.subnet[0],task_WIFI.subnet[1],task_WIFI.subnet[2],task_WIFI.subnet[3],task_WIFI.gw[0],task_WIFI.gw[1],task_WIFI.gw[2],task_WIFI.gw[3]);
	}
	return 0;
};


static int wifi_scan(int argc, char **argv) {
	if (task_WIFI.is_active() == false) {
		printf("WiFi is not enabled.\n");
		return 0;
	}
	task_WIFI.scan();
	return 0;
};


void register_wifi() {
	/** Register the "scan" command: **/
	const esp_console_cmd_t command_scan = {
	        .command = "wifi_scan",
	        .help = "Scan Access Points in range",
	        .hint = NULL,
	        .func = &wifi_scan
	    };

	    ESP_ERROR_CHECK( esp_console_cmd_register(&command_scan) );


	/** Register the "start_AP" command: **/
	const esp_console_cmd_t command_startAP = {
	        .command = "wifi_startAP",
	        .help = "Start WiFi in AP mode with default parameters",
	        .hint = NULL,
	        .func = &wifi_startAP
	    };

	    ESP_ERROR_CHECK( esp_console_cmd_register(&command_startAP) );

		/** Register the "start_STA" command: **/
		const esp_console_cmd_t command_startSTA = {
		        .command = "wifi_startSTA",
		        .help = "Start WiFi in STAtion mode with provisioned parameters",
		        .hint = NULL,
		        .func = &wifi_startSTA
		    };

		    ESP_ERROR_CHECK( esp_console_cmd_register(&command_startSTA) );
		/** Register the "wifi_status" command: **/
	const esp_console_cmd_t command_wifistatus = {
		        .command = "wifi_status",
		        .help = "Query WiFi Parameters",
		        .hint = NULL,
		        .func = &wifi_status
		    };
 ESP_ERROR_CHECK( esp_console_cmd_register(&command_wifistatus) );
};



