/*
 * production_main.cpp
 *
 *  Created on: Sep 5, 2021
 *      Author: rasheek
 */

#include <Arduino.h>
#include "ESPAsyncWebServer.h"
#include "LittleFS.h"
#include "ArduinoJson.h"
#include "esp_event.h"

#include "json.hpp"
#include <stdio.h>
#include <string.h>
#include <Preferences.h>
#include "../include/diagnostics_main.h"
#include "../../include/delta9FW-CONSTS.h"
#include "../../include/tasks/rtc.h"
#include "../../include/tasks/status.h"
#include "../../include/tasks/wifi.h"
#include "../../include/tasks/provisioning.h"
#include "../../include/tasks/output.h"
#include "../../include/tasks/worker.h"
#include "../../include/delta9FW-CONSTS.h"
#include "../include/production_main.h"

extern task_RTC_class task_RTC;
extern task_status_class task_STATUS;
extern task_wifi_class task_WIFI;
extern task_provisioning_class task_PROV;
extern task_output_class task_OUT;
extern task_worker_class task_WORKER;

// JSON parser object:
using json = nlohmann::json;

/** Async HTTP server instance: **/
extern AsyncWebServer server;

/** Configuration for Production server must match output driver: **/
/** filesystem path for profiles: **/

/** User-provided: **/
char P_PROF_USR_PATH[] = "/pr_user/";

/** Extension for profile files: **/
char P_PROF_EXT[] = ".json";



/** Helper function to Authenticate calls: **/
bool _reqIsAuth(AsyncWebServerRequest *request) {
	const char *usr;
	const char *pw;
	String us = task_PROV.prefs.getString("fe_username");
	usr = us.c_str();
	String pwd = task_PROV.prefs.getString("fe_pw");
	pw = pwd.c_str();
  	if(!request->authenticate(usr,pw)) {
  		return false;
  	} else {
  		return true;
  	}
};

/** Function to actually start the Async HTTP server in setup mode: **/
void p_setup_httpserver_init() {
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
				if (!_reqIsAuth(request)) return request->requestAuthentication();
			    String output;
			    String ip;
			    ip = WiFi.localIP().toString();
			    output = "{\"sys\":{\"ip\":\""+ip;
			    ip = WiFi.macAddress();
			    String hr = String(task_RTC.now.hour());
			    String min = String(task_RTC.now.minute());
			    output = output+"\",\"mac\":\""+ip+"\",\"time\":\""+hr+":"+min+"\"}}";
			    request->send(200,"text/json",output);
		   });
		 /** REBOOT call: ***/
		server.on("/api/reboot.json", HTTP_GET , [](AsyncWebServerRequest *request) {
			if (!_reqIsAuth(request)) return request->requestAuthentication();
			request->send(200,"text/json","{\"stat\":\"ok\"}");
			LittleFS.end();
			ESP.restart();
		});

	  /** Spectrum functions: **/

	   /** Get Available Spectrum options: **/
	  server.on("/api/spec/profiles.json",HTTP_GET,[](AsyncWebServerRequest *request) {
		  if (!_reqIsAuth(request)) return request->requestAuthentication();
		  json prof;
		  prof["s"] = json::array();
		  prof["u"] = json::array();
		  /** Will use it later: **/
		   String en_profile = task_PROV.prefs.getString("current_profile");
		   bool profile_user = task_PROV.prefs.getBool("profile_user");
		  /** Iterate through system profiles: **/
		  File dir = LittleFS.open("/pr_builtIn/");
		  String contents;
		  json profile;
		  while (true) {
			    File entry =  dir.openNextFile();
			    if (! entry) {
			      /** No more files **/
			      break;
			    }
			    contents = entry.readString();
			    profile = json::parse(contents.c_str());
			    std::string name = profile.value("name","string");
			    //prof["s"] +=
			    // Select the active profile:
			    bool sel = false;
			    if ((en_profile.compareTo(name.c_str()) ==0)&&(profile_user == false)) {
			    	sel = true;
			    } else {
			    	sel = false;
			    }
			    json step = json::object({ {"l", profile["name"]}, {"i", profile["id"]}, {"s",sel} });
			    prof["s"].insert(prof["s"].end(),step);
		  };
		  /** Iterate through user profiles: **/
		  dir = LittleFS.open("/pr_user/");
		  while (true) {
			    File entry =  dir.openNextFile();
			    if (! entry) {
			      /** No more files **/
			      break;
			    }
			    contents = entry.readString();
			    profile = json::parse(contents.c_str());
			    std::string name = profile.value("name","string");
			    //prof["s"] +=
			    // Select the active profile:
			    bool sel = false;
			    if ((en_profile.compareTo(name.c_str()) ==0)&&(profile_user == true)) {
			    	sel = true;
			    } else {
			    	sel = false;
			    }
			    json step = json::object({ {"l", profile["name"]}, {"i", profile["id"]}, {"s",sel} });
			    prof["u"].insert(prof["u"].end(),step);
		  };
		  std::string output = prof.dump();
		  request->send(200,"text/json",output.c_str());


	  });
	  /** Set Spectrum profile function: **/
	  server.on("/api/spec/set.json", HTTP_POST, [](AsyncWebServerRequest *request) {
			if (!_reqIsAuth(request)) return request->requestAuthentication();
			if(request->hasParam("load",true)) {
			 AsyncWebParameter* load = request->getParam("load",true);
			 String profile = load->value();
			 String p_name = profile.substring(2);
			 task_PROV.prefs.putString("current_profile",p_name);
			 /** Determine if it's a system or user profile: **/
			 if (profile.charAt(0) == *"s") {
				 printf("**-> Setting Profile to System Profile: %s<-**\n",p_name.c_str());
				 task_PROV.prefs.putBool("profile_user",false);

			 } else if (profile.charAt(0) == *"u") {
				 printf("**-> Setting Profile to User Profile: %s<-**\n",p_name.c_str());
				 task_PROV.prefs.putBool("profile_user",true);
			 }
			 task_OUT.load();
			 task_OUT.setStep();
			 request->send(200,"text/json","{\"res\":\"ok\"}");
			};
	  });

	  /** Serve Output Profile CSV function: **/
	  server.on("/api/spec/profile.csv", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (!_reqIsAuth(request)) return request->requestAuthentication();

			String return_str = task_OUT.get_csv();
			 request->send(200,"text/plain",return_str.c_str());
	  });

	  /** SAVE a  USER profile uploaded as a JSON string: if the PID exists in the user profiles, overwrite. if it doesn't, create a new profile: ***/
	  server.on("/api/spec/create.json", HTTP_POST, [](AsyncWebServerRequest *request) {
		  if (!_reqIsAuth(request)) return request->requestAuthentication();
		  if((request->hasParam("pid",true))&&(request->hasParam("pdata",true))) {
			  	 /** Get the parameters from the HTTP request and save them: **/
				 AsyncWebParameter* pid = request->getParam("pid",true);
				 AsyncWebParameter* pdata = request->getParam("pdata",true);
				 /** In case the User profile dir is empty: **/
				 if (!LittleFS.exists(P_PROF_USR_PATH)) {
					 LittleFS.mkdir(P_PROF_USR_PATH);
				 }
				 String path = String(P_PROF_USR_PATH);
				 path += pid->value();
				 path += String(P_PROF_EXT);
				 File file = LittleFS.open(path,FILE_WRITE);
				     if(!file || file.isDirectory()){
						printf("**-> ERROR: Unable to open file for writing: %s<-**\n",path.c_str());
				    	request->send(500,"text/plain","{\"stat\":\"write-denied\"}");
				        return;
				     }
				String data = pdata->value();
				file.print(data);
				file.close();
				printf("**-> SUCCESS: Profile: '%s' Stored!<-**\n",path.c_str());
				request->send(200,"text/plain","ok");
		  } else {
			  request->send(500,"text/plain","{\"stat\":\"missing-data\"}");
		  };

	  });
	  /** Finally, connect and serve static directories: **/
	    /**User and Password protection: */
		const char *usr;
		const char *pw;
		String us = task_PROV.prefs.getString("fe_username");
		usr = us.c_str();
		String pwd = task_PROV.prefs.getString("fe_pw");
		pw = pwd.c_str();

	    server.serveStatic("/prb/", LittleFS, "/pr_builtIn/").setAuthentication(usr,pw);
	    server.serveStatic("/pru/", LittleFS, "/pr_user/").setAuthentication(usr,pw);
	    server.serveStatic("/", LittleFS, "/www/").setDefaultFile("dashboard.html").setAuthentication(usr,pw);





	  server.begin();
	  printf("Production server started, ready for connections.\n");
};

void production_main() {
		/** This is the main Production File that does all the magick once the d9NX3 is provisioned :) **/
		/** As always.. Diagnostics mode:) **/
		if (digitalRead(BTN_WIRb) == HIGH) {
			task_STATUS.all_off();
			task_STATUS.max_on(STATUS_LED_RED);
			task_STATUS.max_on(STATUS_LED_FARRED);
			task_STATUS.max_on(STATUS_LED_GREEN);
			task_STATUS.max_on(STATUS_LED_A);
			printf("**-> Device is Provisioned; In production Mode. <-**\n");
			printf("**-> Entering Diagnostics Mode <-**\n");
			diagnostics_main();
		}


		if (digitalRead(BTN_WIRb) == LOW) {
			task_STATUS.all_off();
			task_STATUS.max_on(STAT_LED_C);
			//task_STATUS.max_on(STATUS_LED_A);
			task_STATUS.max_on(STAT_LED_B);
			printf("**-> Production Mode starting. <-**\n");

			/** Start the Wireless task in production mode.. **/
			task_WIFI.start_STA();

			p_setup_httpserver_init();

			/** Now start the output: **/
			task_OUT.init();

			task_WORKER.init();
		}
};
