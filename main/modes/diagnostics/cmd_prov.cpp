/*
 * cmd_prov.cpp
 *
 *  Created on: Sep 5, 2021
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
#include "cmd_prov.h"

#include "../../include/tasks/provisioning.h"
extern task_provisioning_class task_PROV;

/** Arguments used by "reset_prov" function: **/
static struct {
    struct arg_str *reset;
    struct arg_str *really;
    struct arg_end *end;
} reset_prov_args;

/**
 * prov_reset_wifi: Confirm the parameters twice to initiate a full provision reset of the WiFi/AP and security settings:
 * set the RTC on board clock to the given date.
 * Command: prov_resetWIFI
 * @param argc
 * @param argv
 * @return 0 on success or 1 on failure.
 */
static int prov_reset_wifi(int argc, char **argv) {
	/** First, validate the user input: **/
    int nerrors = arg_parse(argc, argv, (void **)&reset_prov_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, reset_prov_args.end, argv[0]);
        return 1;
    }
	/** Date first: **/
    String reset = reset_prov_args.reset->sval[0];
	if (reset.compareTo("really") != 0) {
		printf("--reset param must be set to 'really'\n");
		return 1;
	}
	String really = reset_prov_args.really->sval[0];
	if (really.compareTo("true") != 0) {
		printf("--really param must be set to 'true'\n");
		return 1;
	}
	task_PROV.prefs.clear();
	printf("WiFi provisioning deleted! Please restart.\n");
	return 0;
}

/** Arguments used by "reset_prov" function: **/
static struct {
    struct arg_str *usr;
    struct arg_str *pw;
    struct arg_end *end;
} set_auth_args;
/**
 * prov_set_auth: Reset the HTML Auth parameters
 * set the HTML auth to the specified user and password
 * Command: set_auth
 * @param argc
 * @param argv
 * @return 0 on success or 1 on failure.
 */
static int prov_set_auth(int argc, char **argv) {
	/** First, validate the user input: **/
    int nerrors = arg_parse(argc, argv, (void **)&set_auth_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, set_auth_args.end, argv[0]);
        return 1;
    }
	/** Date first: **/
    String usr = set_auth_args.usr->sval[0];
	String pw = set_auth_args.pw->sval[0];
	task_PROV.prefs.putString("fe_username",usr);
	task_PROV.prefs.putString("fe_pw",pw);
	printf("HTML Authentication updated.\n");
	return 0;
}
void register_prov(void) {
	/** Register the "prov_resetWIFI" command: **/
	reset_prov_args.reset = arg_str1(NULL, "reset", "really", "Must be set to 'really' to reset");
	reset_prov_args.really = arg_str1(NULL, "really", "true", "Must be set to 'true' to reset.");
	reset_prov_args.end = arg_end(2);

	    const esp_console_cmd_t command_reset_wifi = {
		        .command = "prov_resetWIFI",
		        .help = "Reset WiFi Provisioning",
		        .hint = NULL,
		        .func = &prov_reset_wifi,
				.argtable = &reset_prov_args
		    };

		    ESP_ERROR_CHECK( esp_console_cmd_register(&command_reset_wifi) );
			/** Register the "prov_setAUTH" command: **/
		    set_auth_args.usr = arg_str1(NULL, "usr", "user", "New HTML Auth Username.");
		    set_auth_args.pw = arg_str1(NULL, "pw", "password", "New HTML Auth Password.");
		    set_auth_args.end = arg_end(2);

			    const esp_console_cmd_t command_reset_html = {
				        .command = "prov_setAUTH",
				        .help = "Reset HTTP Auth Provisioning",
				        .hint = NULL,
				        .func = &prov_set_auth,
						.argtable = &set_auth_args
				    };

				    ESP_ERROR_CHECK( esp_console_cmd_register(&command_reset_html) );

}



