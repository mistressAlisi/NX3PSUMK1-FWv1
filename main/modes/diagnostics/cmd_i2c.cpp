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
#include "cmd_i2c.h"
#include <Arduino.h>
#include <Wire.h>


/**
 * i2c_scan: I2c Boundary Scan Tool
 * Command: i2c_scan.
 * @param argc
 * @param argv
 * @return
 */
static int cmd_i2c_scan(int argc, char **argv) {
	printf("I2C Bus Scan:\n");
	byte count = 0;
	  for (byte i = 8; i < 120; i++)
	  {
	    Wire.beginTransmission (i);          // Begin I2C transmission Address (i)
	    if (Wire.endTransmission () == 0)  // Receive 0 = success (ACK response)
	    {
	      printf ("Found Device at address DEC: %d (HEX: 0x%02X).\n",i,i);
	      count++;
	    }
	  }
	  printf("Found %d devices.\nI2C Scan Complete!\n ",count);

	return 0;
};


void register_i2c() {

	/** Register the "i2c_scan" command: **/
	const esp_console_cmd_t command_i2cscan = {
	        .command = "i2c_scan",
	        .help = "Scan I2C bus",
	        .hint = NULL,
	        .func = &cmd_i2c_scan
	    };

	    ESP_ERROR_CHECK( esp_console_cmd_register(&command_i2cscan) );


};
