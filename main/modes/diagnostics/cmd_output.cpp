/*
 * cmd_files.cpp
 *
 *  Created on: Sep 1, 2021
 *      Author: rasheek
 */

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
#include "cmd_files.h"
#include <Arduino.h>
#include <Wire.h>
#include "provisioning.h"
#include "delta9FW-littlefs.h"
extern task_provisioning_class task_PROV;


/** Arguments used by "cmd_fs_ls" function: **/
static struct {
    struct arg_str *name;
    struct arg_int *user;
    struct arg_end *end;
} cmd_output_profile_args;

static int cmd_output_profile(int argc, char **argv) {
	/** First, validate the user input: **/
	int nerrors = arg_parse(argc, argv, (void **)&cmd_output_profile_args);
	if (nerrors != 0) {
	        arg_print_errors(stderr, cmd_output_profile_args.end, argv[0]);
	        return 1;
	    }
	 String profile = cmd_output_profile_args.name->sval[0];
	 int is_user = cmd_output_profile_args.user->ival[0];
	 if (is_user == 1) {
		 task_PROV.prefs.putBool("profile_user",true);
	 } else {
		 task_PROV.prefs.putBool("profile_user",false);
	 }
	 task_PROV.prefs.putString("current_profile",profile);
	 printf("**-> Output profile set. <-**\n");
	 return 0;
};

void register_out() {


	 /** Register the "fs_ls" command: **/
	cmd_output_profile_args.name = arg_str0(NULL, "name", "name", "Profile Name");
	cmd_output_profile_args.user = arg_int0(NULL, "user", "1/0", "Is this a User profile? (1 = true; 0 =false)");
	cmd_output_profile_args.end = arg_end(2);

			    const esp_console_cmd_t cmd_output_profile_cmd = {
				        .command = "output_profile",
				        .help = "Change Output Profile",
				        .hint = NULL,
				        .func = &cmd_output_profile,
						.argtable = &cmd_output_profile_args
				    };

				    ESP_ERROR_CHECK( esp_console_cmd_register(&cmd_output_profile_cmd) );
};

