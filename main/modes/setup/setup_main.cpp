/*
 * setup_main.cpp
 *
 *  Created on: Aug 28, 2021
 *      Author: rasheek
 */

#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include "LittleFS.h"
#include "ArduinoJson.h"
#include <stdio.h>
#include <string.h>
#include <Preferences.h>
#include "../include/setup_main.h"
#include "../include/diagnostics_main.h"
#include "../../include/delta9FW-CONSTS.h"
#include "../../include/tasks/rtc.h"
#include "../../include/tasks/status.h"
#include "../../include/tasks/wifi.h"
#include "../../include/tasks/provisioning.h"
#include "../../include/delta9FW-CONSTS.h"

extern task_RTC_class task_RTC;
extern task_status_class task_STATUS;
extern task_wifi_class task_WIFI;
extern task_provisioning_class task_PROV;


/** Async HTTP server instance: **/
AsyncWebServer server(80);

/** Function to actually start the Async HTTP server in setup mode: **/
void setup_httpserver_init() {
		uint8_t maxfiles = 255;
	    if (!LittleFS.begin(false,"/littlefs",maxfiles,"root")) {
	        printf("An Error has occurred while mounting LittleFS!! ABORT!");

	        while (1) {};
	  	}

	  /** Spin up the HTML server! **/
      /** API calls first! **/
	  /** Generic CALLs **/
	  /** HEADER (hdr) API call, get IP and MAC: **/
	    /** URL: /api/hdr.json. **/
		  server.on("/api/hdr.json", HTTP_GET, [](AsyncWebServerRequest *request){
			    String output;
			    String ip;
			    ip = WiFi.softAPIP().toString();
			    output = "{\"sys\":{\"ip\":\""+ip;
			    ip = WiFi.macAddress();
			    output = output+"\",\"mac\":\""+ip+"\"}}";
			    request->send(200,"text/json",output);
		   });
		 /** REBOOT call: ***/
		server.on("/api/setup/reboot.json", HTTP_GET , [](AsyncWebServerRequest *request) {
				request->send(200,"text/json","{\"stat\":\"ok\"}");
				LittleFS.end();
				ESP.restart();
		});
		/** USER SETUP call: **/
		server.on("/api/setup/commit_user.json", HTTP_POST , [](AsyncWebServerRequest *request) {
				if(request->hasParam("username",true)) {
					 /** Get the User/Password from the request and store it in Prefs: **/
					 AsyncWebParameter* username = request->getParam("username",true);
					 AsyncWebParameter* upw = request->getParam("upw",true);
					 task_PROV.prefs.putString("fe_username",username->value());
					 task_PROV.prefs.putString("fe_pw",upw->value());
					 /** Set provisioned to true :) **/
					 task_PROV.prefs.putBool("prov",true);
					 printf("!!!User Provisioning Succeded!!!\n");
					 request->send(200,"text/json","{\"stat\":\"ok\"}");
				} else {
					 request->send(500,"text/json","Missing Parameters.");
				}
			});
	   /** SET RTC CAll: **/
		server.on("/api/setup/commit_datetime.json", HTTP_POST , [](AsyncWebServerRequest *request) {
			if(request->hasParam("datetime",true)) {
				 /** Get the time from the client and store it in RTC **/
				 AsyncWebParameter* day = request->getParam("DD",true);
				 AsyncWebParameter* mon = request->getParam("MM",true);
				 AsyncWebParameter* yer = request->getParam("YYYY",true);
				 AsyncWebParameter* hr = request->getParam("HH",true);
				 AsyncWebParameter* mi = request->getParam("m",true);
				 AsyncWebParameter* sec = request->getParam("ss",true);
				 int v_day = day->value().toInt();
				 int v_yr = yer->value().toInt();
				 int v_mo = mon->value().toInt();
				 int v_hr = hr->value().toInt();
				 int v_mi = mi->value().toInt();
				 int v_sec = sec->value().toInt();
				 task_RTC.set_time(v_yr,v_mo,v_day,v_hr,v_mi,v_sec);
				 printf("!!!Clock Provisioning Succeded!!!\n");
				 request->send(200,"text/json","{\"stat\":\"ok\"}");
			} else {
				 request->send(500,"text/json","Missing Parameters.");
			}
		});
	  /** WIFI API calls: **/
	  /** SETUP NETWORK: SET AP/DHCP mode and parameters : **/
		 server.on("/api/setup/commit_apssid.json", HTTP_POST , [](AsyncWebServerRequest *request) {
			 if (request->hasParam("mode",true)) {

				 /** Mode is present, good, we can continue: **/
				 AsyncWebParameter* p = request->getParam("mode",true);
				 String mode = p->value();
				 printf("Got Mode: %s\n",mode.c_str());

				 if (mode.compareTo("sta")  == 0) {
					 /** Configure for STAtion mode: **/
					 AsyncWebParameter* ssid = request->getParam("wifi_ap_ssid",true);
					 AsyncWebParameter* pw = request->getParam("wifi_ap_pw",true);
					 task_PROV.prefs.putString("sta_ssid",ssid->value());
					 task_PROV.prefs.putString("sta_pw",pw->value());
					 task_PROV.prefs.putBool("sta",true);
					 task_PROV.prefs.putBool("softAP",false);
					 printf("STA Mode Enabled.\n");
					 /** DHCP mode or static mode? **/
					 if (request->hasParam("dhcp",true)) {
						 /** DHCP mode. **/
						 /** Save preferences for dhcp mode **/
						 task_PROV.prefs.putBool("dhcp",true);
					 } else {
						 /** Static mode.. */
						 task_PROV.prefs.putBool("dhcp",false);

						 /** IP octets: **/
						 AsyncWebParameter* ip1 = request->getParam("ip1",true);
						 AsyncWebParameter* ip2 = request->getParam("ip2",true);
						 AsyncWebParameter* ip3 = request->getParam("ip3",true);
						 AsyncWebParameter* ip4 = request->getParam("ip4",true);
						 task_PROV.prefs.putUChar("ip1",ip1->value().toInt());
						 task_PROV.prefs.putUChar("ip2",ip2->value().toInt());
						 task_PROV.prefs.putUChar("ip3",ip3->value().toInt());
						 task_PROV.prefs.putUChar("ip4",ip4->value().toInt());
						 /** Network Mask octets: **/
						 AsyncWebParameter* nm1 = request->getParam("nm1",true);
						 AsyncWebParameter* nm2 = request->getParam("nm2",true);
						 AsyncWebParameter* nm3 = request->getParam("nm3",true);
						 AsyncWebParameter* nm4 = request->getParam("nm4",true);
						 task_PROV.prefs.putUChar("nm1",nm1->value().toInt());
						 task_PROV.prefs.putUChar("nm2",nm2->value().toInt());
						 task_PROV.prefs.putUChar("nm3",nm3->value().toInt());
						 task_PROV.prefs.putUChar("nm4",nm4->value().toInt());

						 /** Gateway octets: **/
						 AsyncWebParameter* gw1 = request->getParam("gw1");
						 AsyncWebParameter* gw2 = request->getParam("gw2");
						 AsyncWebParameter* gw3 = request->getParam("gw3");
						 AsyncWebParameter* gw4 = request->getParam("gw4");
						 task_PROV.prefs.putUChar("gw1",gw1->value().toInt());
						 task_PROV.prefs.putUChar("gw2",gw2->value().toInt());
						 task_PROV.prefs.putUChar("gw3",gw3->value().toInt());
						 task_PROV.prefs.putUChar("gw4",gw4->value().toInt());

						 /** DNS octets: **/
						 AsyncWebParameter* dn1 = request->getParam("dn1");
						 AsyncWebParameter* dn2 = request->getParam("dn2");
						 AsyncWebParameter* dn3 = request->getParam("dn3");
						 AsyncWebParameter* dn4 = request->getParam("dn4");
						 task_PROV.prefs.putUChar("dn1",dn1->value().toInt());
						 task_PROV.prefs.putUChar("dn2",dn2->value().toInt());
						 task_PROV.prefs.putUChar("dn3",dn3->value().toInt());
						 task_PROV.prefs.putUChar("dn4",dn4->value().toInt());


					 }
				 } else if (mode.compareTo("ap") == 0) {
					 /** Configure in softAP mode **/
					 AsyncWebParameter* ssid = request->getParam("wifi_ap_ssid",true);
					 AsyncWebParameter* pw = request->getParam("wifi_ap_pw",true);
					 task_PROV.prefs.putString("softAP_ssid",ssid->value());
					 task_PROV.prefs.putString("softAP_pw",pw->value());
					 task_PROV.prefs.putBool("sta",false);
					 task_PROV.prefs.putBool("softAP",true);
					 printf("Soft AP Mode Enabled");


				 } else {
					 request->send(500,"text/json","Unknown mode.");
				 }
				 printf("!!!Network Provisioning Succeded!!!\n");
				 request->send(200,"text/json","{\"stat\":\"ok\"}");
			 } else {
				 request->send(500,"text/json","Missing Parameters.");
			 }
		 });
	  /** SETUP Networks: SCAN for APs: **/
	 /** URL: /api/setup/networks.json **/
		  server.on("/api/setup/networks.json", HTTP_GET, [](AsyncWebServerRequest *request){
			  	/** SCAN for wifi APs in range and print it out in json. **/
			    String output;
			    output = "{\"sys\":{\"ssids\":\[";
			    char 	ssid_buf[100];
			    int n = WiFi.scanNetworks();
			   	    if (n == 0) {
			   	    	snprintf(ssid_buf,sizeof(ssid_buf)," {\"i\":\"%s\",\"n\":\"%s\",\"s\":\"-%d dBm\"},","none","none",0);
			   	    } else {

			   	        for (int i = 0; i < n; ++i) {
			   	            // Print SSID and RSSI for each network found and store it in our pointers:
			   	        	snprintf(ssid_buf,sizeof(ssid_buf)," {\"i\":\"%s\",\"n\":\"%s\",\"s\":\"%d dBm\"}",WiFi.SSID(i).c_str(),WiFi.SSID(i).c_str(),WiFi.RSSI(i));
			   	           output = output+ssid_buf;
			   	        	if (i < n-1) {
			   	        		output = output+",\n";
			   	        	} else {
			   	        		output = output+"\n";
			   	        	}

			   	        }
			   	    };
			    output = output+"]}}";
			    request->send(200,"text/json",output);
		   });
	  /** Finally, connect and serve static directories: **/
	    server.serveStatic("/res", LittleFS, "/www/res");
	    server.serveStatic("/setup/", LittleFS, "/www/setup").setDefaultFile("index.html");
	    server.serveStatic("/", LittleFS, "/www/setup").setDefaultFile("index.html");





	  server.begin();
	  printf("Provisioning server started, ready for connections.\n");
};

void setup_main() {

	/** This is the factory default / after reset SETUP mode which helps users provision their d9 device. **/

	if (digitalRead(BTN_WIRb) == HIGH) {
	task_STATUS.all_off();
	task_STATUS.max_on(STATUS_LED_RED);
	task_STATUS.max_on(STATUS_LED_FARRED);
	task_STATUS.max_on(STATUS_LED_GREEN);
	task_STATUS.max_on(STATUS_LED_A);
	printf("**-> Entering Diagnostics Mode <-**\n");
	diagnostics_main();
	}


	if (digitalRead(BTN_WIRb) == LOW) {
		task_STATUS.all_off();
		task_STATUS.max_on(STAT_LED_C);
		//task_STATUS.max_on(STATUS_LED_A);
		task_STATUS.max_on(STAT_LED_B);
		printf("**-> Device Setup Mode starting. <-**\n");
		/** Let's actually start the setup mode, start in AP mode so we can be provisioned: **/
		task_WIFI.start_AP();
		setup_httpserver_init();

	}


}

void loop() {

};

