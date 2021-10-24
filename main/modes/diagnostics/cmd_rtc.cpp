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

#include "rtc.h"
extern task_RTC_class task_RTC;



/** Arguments used by "set_date" function: **/
static struct {
    struct arg_int *year;
    struct arg_int *month;
    struct arg_int *day;
    struct arg_int *hour;
    struct arg_int *minute;
    struct arg_int *second;
    struct arg_end *end;
} set_time_args;

/**
 * rtc_set_date: Using the arguments below as parameters,
 * set the RTC on board clock to the given date.
 * Command: set_date YYYY MM DD HH MM SS
 * @param argc
 * @param argv
 * @return 0 on success or 1 on failure.
 */
static int rtc_set_time(int argc, char **argv) {
	/** First, validate the user input: **/
    int nerrors = arg_parse(argc, argv, (void **)&set_time_args);
    if (nerrors != 0) {
        arg_print_errors(stderr, set_time_args.end, argv[0]);
        return 1;
    }
	/** Date first: **/
	if (set_time_args.year->ival[0] <= 2000) {
		printf("Invalid Year. Calendar starts in the year 2000.");
		return 1;
	}
if ((set_time_args.month->ival[0] < 1)||(set_time_args.month->ival[0] > 12)) {
			printf("Invalid entry for Month (1 to 12).");
			return 1;
	}
	if ((set_time_args.day->ival[0] < 1)||(set_time_args.day->ival[0] > 31)) {
			printf("Invalid entry for Day (1 to 31).");
			return 1;
	}
	/** Now time: **/
	if ((set_time_args.hour->ival[0] < 0)||(set_time_args.hour->ival[0] > 23)) {
			printf("Invalid entry for Hour (0 to 23).");
			return 1;
	}
	if ((set_time_args.minute->ival[0] < 0)||(set_time_args.minute->ival[0] > 59)) {
			printf("Invalid entry for Minute (0 to 59).");
			return 1;
	}
	if ((set_time_args.second->ival[0] < 0)||(set_time_args.second->ival[0] > 59)) {
			printf("Invalid entry for Second (0 to 59).");
			return 1;
	}
	task_RTC.set_time(set_time_args.year->ival[0],set_time_args.month->ival[0],set_time_args.day->ival[0],set_time_args.hour->ival[0],set_time_args.minute->ival[0],set_time_args.second->ival[0]);
	return 0;
}
/**
 * rtc_get_time: Print out current RTC time.
 * Command: time_now.
 * @param argc
 * @param argv
 * @return
 */
static int rtc_get_time(int argc, char **argv) {
	task_RTC.print_current_time();
	return 0;
};


void register_rtc() {

	/** Register the "get_now" command: **/
	const esp_console_cmd_t command_now = {
	        .command = "time_now",
	        .help = "Get current RTC Time",
	        .hint = NULL,
	        .func = &rtc_get_time
	    };

	    ESP_ERROR_CHECK( esp_console_cmd_register(&command_now) );

	/** Register the "set_date" command: **/
	    set_time_args.year = arg_int1(NULL, "year", "YYYY", "Current Year");
	    set_time_args.month = arg_int1(NULL, "month", "MM", "Current Month");
	    set_time_args.day = arg_int1(NULL, "day", "DD", "Current Day");
	    set_time_args.hour = arg_int1(NULL, "hour", "HH", "Current Hour");
	    set_time_args.minute = arg_int1(NULL, "minute", "mm", "Current Minute");
	    set_time_args.second = arg_int1(0, "second", "SS", "Current Second (default 0)");
	    set_time_args.end = arg_end(2);

	    const esp_console_cmd_t command_settime = {
		        .command = "set_time",
		        .help = "Set current RTC Date and Time (24H format)",
		        .hint = NULL,
		        .func = &rtc_set_time,
				.argtable = &set_time_args
		    };

		    ESP_ERROR_CHECK( esp_console_cmd_register(&command_settime) );
};
