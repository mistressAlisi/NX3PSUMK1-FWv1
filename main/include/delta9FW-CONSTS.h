/*
 * delta9FW-VER.h
 *
 *  Created on: Aug 28, 2021
 *      Author: rasheek
 */

#ifndef MAIN_INCLUDE_DELTA9FW_CONSTS_H_
#define MAIN_INCLUDE_DELTA9FW_CONSTS_H_

/** d9 FW Version information: **/
#define D9FW_VERSION_STRING "0.1.0B"
#define D9FW_VERSION_DATE "Oct 17, 2021"

#define STACK_SIZE 2048

/** d9 FW PIN definitions - based on NX3 PDU Schm Mark 1: **/
/** LED indicators: **/
static const int STATUS_LED_GREEN = 23;
static const int STATUS_LED_FARRED = 22;
static const int STATUS_LED_RED = 21;
static const int STATUS_LED_C = 26;
static const int STATUS_LED_BLUE = 14;
static const int STATUS_LED_A = 12;
/** FAN pin: **/
static const int FAN_PIN = 27;
/** I2c/Wire bus: **/
static const int I2C_SDA = 19;
static const int I2C_SCL = 18;

/** INPUT buttons: **/
static const int BTN_BTNb = 35;
static const int BTN_WIRb = 32;


/** Configuration for WiFi AP mode **/
/** IP configuration in octets, most significant first: **/
static const int WIFI_IPO1 = 10;
static const int WIFI_IPO2 = 100;
static const int WIFI_IPO3 = 200;
static const int WIFI_IPO4 = 1;

/** NETMASK configuration in octets, most significant first: **/
static const int WIFI_NMO1 = 255;
static const int WIFI_NMO2 = 255;
static const int WIFI_NMO3 = 255;
static const int WIFI_NMO4 = 0;





#endif /* MAIN_INCLUDE_DELTA9FW_CONSTS_H_ */
