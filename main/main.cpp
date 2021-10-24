
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "spiram.h"
#include "himem.h"
#include <Wire.h>
#include "Arduino.h"
#include "LittleFS.h"
#include "delta9FW-CONSTS.h"
#include "d9-semaphore.h"
#include "rtc.h"
#include "status.h"
#include "provisioning.h"
#include "wifi.h"
#include "output.h"
#include "taskadc.h"
#include "worker.h"
#include "setup_main.h"
#include "production_main.h"

/** RTC Task/Driver Object: **/
task_RTC_class task_RTC;

/** Provisioning Task Object: **/
task_provisioning_class task_PROV;

/** Status Task Object: **/
task_status_class task_STATUS;

/** Wifi Task Object: **/
task_wifi_class task_WIFI;

/** Output Driver Task Object: **/
task_output_class task_OUT;

/** ADC Driver Task Object: **/
task_adc_class task_ADC;


/** Worker class: **/
task_worker_class task_WORKER;

/** Semaphores: **/

extern "C" void app_main(void)
{
  initArduino();
  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  /** Print HW information before we launch all tasks: **/
  printf("**-> HW: %s chip with %d CPU core(s), WiFi%s%s. <-**\n",
              CONFIG_IDF_TARGET,
              chip_info.cores,
              (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
              (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");
  printf("*%dMB %s flash initialised.\n", spi_flash_get_chip_size() / (1024 * 1024),(chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
  printf("HIMEM Total: (%d) %dMB . Free: %d KB.\n",esp_himem_get_phys_size(), esp_himem_get_phys_size() / (1024 * 1024), esp_himem_get_free_size() / 1024);
  printf("SPIRAM Total: (%d) %dMB. \n",esp_spiram_get_size(), esp_spiram_get_size() / (1024 * 1024));
  /** Start default event loops: **/
  ESP_ERROR_CHECK(esp_event_loop_create_default());
  /** Init Semaphores **/
  SEMA_i2c_bus = xSemaphoreCreateBinary();
  xSemaphoreGive( SEMA_i2c_bus );

  /**Start hardware drivers: **/
  /** Status GPIO driver: **/
  task_STATUS.init();
  /** FAN OUTPUT: **/
  pinMode(FAN_PIN,OUTPUT);
  /** I2C bus: **/
  Wire.begin (I2C_SDA,I2C_SCL);
  /** Button INPUTS: **/
  pinMode(BTN_BTNb,INPUT_PULLDOWN);
  pinMode(BTN_WIRb,INPUT_PULLDOWN);
  printf("I2C bus initialised on SDA: %d, SCL: %d.\n",I2C_SDA,I2C_SCL);
  /** HARDWARE start below **/

  /** FIRST TASK: RTC startup: **/
  task_RTC.init();
  task_RTC.print_current_time();

  /** SECOND TASK: WiFi init (); */
  task_WIFI.init();

  /** turn on ALL STATUS LEDS: **/
  task_STATUS.all_on();




  /** start ADC task: **/
  task_ADC.init(&Wire);

  /** Now Print Welcome Text and wait two seconds: **/
  printf("**-> Delta9 SmartPDU MK3 FWMK1 Rev: %s, Date (%s) <-**\n",D9FW_VERSION_STRING,D9FW_VERSION_DATE);
  printf("**-> (c) 2018 ~ 2021 Delta9 / Ardent Lighting LLC <-**\n");
  printf("**-> Open Source Software: https://osi.del9.biz <-**\n");
  printf("**-> Waiting two seconds before starting tasks... <-**\n");
  delay(2000);

  /** turn off ALL STATUS LEDS: **/
  task_STATUS.all_off();
  /** Now turn on the Green "A"ctivity LED all the way on: **/
  task_STATUS.max_on(STAT_LED_A);

  /** Based on Provisioning status, determine which mode to go into next: **/
  task_PROV.init();
  if (task_PROV.is_provisioned() == false) {
	  /** Not provisioned, turn on STATUS_FARRED to turn LED 2 Yellow as indicator: **/
	  task_STATUS.max_on(STAT_LED_F);
	  /** Jump to SETUP mode: **/
	  setup_main();


  } else {
	  if (!LittleFS.begin(false,"/littlefs",255,"root")) {
		  printf("**-> ALARM: UNABLE to mount LittleFS partition!!! <-**\n");
	  }
	  task_STATUS.off(STAT_LED_F);
	  task_STATUS.max_on(STAT_LED_B);
	  production_main();
  }
 

   
}
