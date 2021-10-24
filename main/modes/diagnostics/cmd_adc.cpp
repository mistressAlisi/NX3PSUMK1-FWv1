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
#include <Arduino.h>
#include <Wire.h>
#include "LittleFS.h"
#include "cmd_adc.h"
#include <taskadc.h>

extern task_adc_class task_ADC;

/** Arguments used by "cmd_read_Adc" function: **/
static struct {
    struct arg_int *chan;
    struct arg_end *end;
} cmd_read_adc_args;
static int cmd_read_adc(int argc, char **argv) {
	/** First, validate the user input: **/
	int nerrors = arg_parse(argc, argv, (void **)&cmd_read_adc_args);
	if (nerrors != 0) {
	        arg_print_errors(stderr, cmd_read_adc_args.end, argv[0]);
	        return 1;
	    }
	 int chan = cmd_read_adc_args.chan->ival[0];
	 int16_t adc_val = task_ADC.read_adc(chan);
	 return 0;
};
void register_adc() {
	 /** Register the "read_adc" command: **/
	cmd_read_adc_args.chan = arg_int0(NULL, "chan", "Channel #", "Channel # 0...7");
	cmd_read_adc_args.end = arg_end(2);

			    const esp_console_cmd_t command_fs_ls = {
				        .command = "read_adc",
				        .help = "Set ADC to channel and read it.",
				        .hint = NULL,
				        .func = &cmd_read_adc,
						.argtable = &cmd_read_adc_args
				    };

				    ESP_ERROR_CHECK( esp_console_cmd_register(&command_fs_ls) );
}
