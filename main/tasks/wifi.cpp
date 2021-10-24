/*
 * cpp
 *
 *  Created on: Aug 29, 2021
 *      Author: rasheek
 */

#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "spiram.h"
#include "himem.h"
#include "Arduino.h"
#include "WiFi.h"
#include "esp_wifi.h"
#include "delta9FW-CONSTS.h"
#include "rtc.h"
#include "status.h"
#include "wifi.h"
#include "provisioning.h"
#include "delta9FW-CONSTS.h"

extern task_RTC_class task_RTC;
extern task_status_class task_STATUS;
extern task_wifi_class task_WIFI;
extern task_provisioning_class task_PROV;


void task_wifi_class::init() {
	active = false;
	String macaddr = WiFi.macAddress();
	printf("WiFi interface mac: %s, ready.\n",macaddr.c_str());
};

void task_wifi_class::start_AP() {
	/** Don't try to start the WiFi interface more than once without reset...*/
	if (active == false) {
	printf("Starting in AP mode...");
	ssid = "d9 NX3 ["+WiFi.macAddress()+"]";
	ipaddr = IPAddress(WIFI_IPO1,WIFI_IPO2,WIFI_IPO3,WIFI_IPO4);
	subnet = IPAddress(WIFI_NMO1,WIFI_NMO2,WIFI_NMO3,WIFI_NMO4);
	isAP = true;
	WiFi.softAPConfig(ipaddr, ipaddr, subnet);
	WiFi.softAP(ssid.c_str(),"");
	printf("**->WiFi has started in AP Mode: SSID: %s, IP Addr: %d.%d.%d.%d <-**\n",ssid.c_str(),WIFI_IPO1,WIFI_IPO2,WIFI_IPO3,WIFI_IPO4);
	/** Store our IP address for later use. **/

	active = true;
	};
};

void task_wifi_class::scan() {
	if (active == true) {
	  int n = WiFi.scanNetworks();
	    Serial.println("scan done");
	    if (n == 0) {
	        printf("no networks found!\n");
	    } else {

	        printf("%d networks found!\n",n);
	        for (int i = 0; i < n; ++i) {
	            // Print SSID and RSSI for each network found:
	        	printf("#%d:  SSID: (%s) Signal: %d (dBm)\n",i+1,WiFi.SSID(i).c_str(),WiFi.RSSI(i));
	        }
	    };
	};
}

/** PRIVATE function: Event handle: STA connected: **/
void task_wifi_class::_eConnected() {
	active = true;
	ipaddr = WiFi.localIP();
	char hostname[40];
	snprintf(hostname,40,"d9 NX3 [%s]",WiFi.macAddress().c_str());
	WiFi.setHostname(hostname);
	printf("**-> WiFi is connected in STA/Client Mode to SSID: '%s' <-**\n",ssid.c_str());
};

/** PRIVATE function: Event handle: STA Disconnected: **/
void task_wifi_class::_eDisconnected() {
	printf("**-> WiFi is disconnected! Reconnecting to: '%s' <-**\n",ssid.c_str());
	active = false;
	task_STATUS.hb_wifi_off();
	_connect_AP();



};

/** PRIVATE function: Event handle: STA got IP: **/
void task_wifi_class::_eSTAIP() {
	ipaddr = WiFi.localIP();
	subnet = WiFi.subnetMask();
	gw = WiFi.gatewayIP();
	printf("**-> WiFi Got IP Address: %d.%d.%d.%d, Netmask: %d.%d.%d.%d. Gateway: %d.%d.%d.%d <-**\n",ipaddr[0],ipaddr[1],ipaddr[2],ipaddr[3],
			subnet[0],subnet[1],subnet[2],subnet[3],gw[0],gw[1],gw[2],gw[3]);
	task_STATUS.off(STATUS_LED_A);
	task_STATUS.hb_wifi_en();
};

/**
 * PRIVATE function that handles WiFi Driver Events:
 */
void task_wifi_class::_evHandle(void* handler_args, esp_event_base_t base, int32_t id, void* event_data) {
	if (id == WIFI_EVENT_STA_CONNECTED) {
		/** Connected as STA: **/
		task_WIFI._eConnected();
	} else if ( id == IP_EVENT_STA_GOT_IP) {
		/** Got IP Address: **/
		task_WIFI._eSTAIP();
	} else if (id == WIFI_EVENT_STA_DISCONNECTED) {
		/** Disconnected! **/
		task_WIFI._eDisconnected();
	}
};
/**
 * PRIVATE function that actually initiates connections:
 */
void task_wifi_class::_connect_AP() {
	bool dhcp = task_PROV.prefs.putBool("dhcp",true);
		ssid = task_PROV.prefs.getString("sta_ssid");
		String pw = task_PROV.prefs.getString("sta_pw");
		if (ssid.compareTo("") == 0) {
			printf("No SSID! Is device provisioned?\n");
			return;

		};
		char hostname[40];
		snprintf(hostname,40,"d9 NX3 [%s]",WiFi.macAddress().c_str());
		WiFi.setHostname(hostname);
		if (dhcp == true) {
			/** Start in DHCP mode: **/
			printf("**-> Connecting in DHCP mode. <-**\n");
			WiFi.begin(ssid.c_str(),pw.c_str());
		} else {
			/** Start in Static IP mode: **/
			/** We're going to need some bytes: **/
			uint8_t ip1;
			uint8_t ip2;
			uint8_t ip3;
			uint8_t ip4;

			/** Assemble IP Addr: **/
			ip1 = task_PROV.prefs.getUChar("dn1");
			ip2 = task_PROV.prefs.getUChar("dn2");
			ip3 = task_PROV.prefs.getUChar("dn3");
			ip4 = task_PROV.prefs.getUChar("dn4");
			ipaddr = IPAddress(ip1,ip2,ip3,ip4);

			/** Assemble NM IP Addr: **/
			ip1 = task_PROV.prefs.getUChar("nm1");
			ip2 = task_PROV.prefs.getUChar("nm2");
			ip3 = task_PROV.prefs.getUChar("nm3");
			ip4 = task_PROV.prefs.getUChar("nm4");
			subnet = IPAddress(ip1,ip2,ip3,ip4);

			/** Assemble GW  IP Addr: **/
			ip1 = task_PROV.prefs.getUChar("nm1");
			ip2 = task_PROV.prefs.getUChar("nm2");
			ip3 = task_PROV.prefs.getUChar("nm3");
			ip4 = task_PROV.prefs.getUChar("nm4");
			gw = IPAddress(ip1,ip2,ip3,ip4);

			/** Assemble DNS IP Addr: **/
			ip1 = task_PROV.prefs.getUChar("nm1");
			ip2 = task_PROV.prefs.getUChar("nm2");
			ip3 = task_PROV.prefs.getUChar("nm3");
			ip4 = task_PROV.prefs.getUChar("nm4");
			dns = IPAddress(ip1,ip2,ip3,ip4);

			/** Now Configure the WiFi mode with static IP: **/
			WiFi.config(ipaddr,dns, gw, subnet);
			printf("**-> Connecting in Static IP mode. <-**\n");
			WiFi.begin(ssid.c_str(),pw.c_str());
		};

};



void task_wifi_class::start_STA() {
	/** Reset WIFI and start in STAtion (client) mode with the provisioned data from Provisioning. **/
	/** Will also install a handler for disconnect events to trigger re-connections. **/
	if (active == false) {
		/** Reset everything: **/
		WiFi.disconnect(true);
		/** Connect the WiFi and IP events to the right handlers: **/
		 ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID,_evHandle,NULL,NULL));
		 ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, ESP_EVENT_ANY_ID,_evHandle,NULL,NULL));
		 /** Now actually connect: **/
		_connect_AP();
		isAP  = false;
	};
};

bool task_wifi_class::is_AP() {
	return isAP;
};

bool task_wifi_class::is_active() {
	return active;
};


