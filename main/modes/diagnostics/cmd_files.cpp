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
#include "LittleFS.h"
#include "delta9FW-littlefs.h"

static int cmd_fs_mount(int argc, char **argv) {
	uint8_t maxfiles = 255;
	if (LittleFS.begin(false,"/littlefs",maxfiles,"root")) {
		printf("littleFS mounted.\n");
		return 0;
	} else {
		printf("Unable to mount littleFS!");
		return 1;
	}
};

static int cmd_fs_size(int argc, char **argv) {
	 unsigned int totalBytes = LittleFS.totalBytes();
	 unsigned int usedBytes = LittleFS.usedBytes();
	 printf("File System Information (bytes): \n Total Size: %d.\n Total Used: %d. \n",totalBytes,usedBytes);
	 return 0;
};

/** Reentrant print directory content function, will be used inside the wrapped command for fs_ls: **/
void _printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      /** No more files **/
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      printf("\t");
    }
   printf(entry.name());
    if (entry.isDirectory()) {
      printf("/\n");
      _printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      printf(" %d \t\t\n",entry.size());
    }
    entry.close();
  }
}

/** Arguments used by "cmd_fs_ls" function: **/
static struct {
    struct arg_str *fname;
    struct arg_end *end;
} cmd_fs_ls_args;

static int cmd_fs_ls(int argc, char **argv) {
	/** First, validate the user input: **/
	int nerrors = arg_parse(argc, argv, (void **)&cmd_fs_ls_args);
	if (nerrors != 0) {
	        arg_print_errors(stderr, cmd_fs_ls_args.end, argv[0]);
	        return 1;
	    }
	 File dir = LittleFS.open(cmd_fs_ls_args.fname->sval[0]);
	 _printDirectory(dir,0);
	 return 0;
};

void register_fs() {

	/** Register the "mount fs" command: **/
	const esp_console_cmd_t command_mount= {
	        .command = "fs_mount",
	        .help = "Mount Filesystem (MUST BE CALLED BEFORE FS OPS!)",
	        .hint = NULL,
	        .func = &cmd_fs_mount
	    };

	    ESP_ERROR_CHECK( esp_console_cmd_register(&command_mount) );


	/** Register the "fs_size command" command: **/
	const esp_console_cmd_t command_fssize = {
		        .command = "fs_size",
		        .help = "Report FS size and usage.",
		        .hint = NULL,
		        .func = &cmd_fs_size
		    };

		    ESP_ERROR_CHECK( esp_console_cmd_register(&command_fssize) );

	 /** Register the "fs_ls" command: **/
		    cmd_fs_ls_args.fname = arg_str0(NULL, "file", "file", "File/Dir Name");
		    cmd_fs_ls_args.end = arg_end(2);

			    const esp_console_cmd_t command_fs_ls = {
				        .command = "fs_ls",
				        .help = "List contents of directory",
				        .hint = NULL,
				        .func = &cmd_fs_ls,
						.argtable = &cmd_fs_ls_args
				    };

				    ESP_ERROR_CHECK( esp_console_cmd_register(&command_fs_ls) );
};
