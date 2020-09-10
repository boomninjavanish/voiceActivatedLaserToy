/* 
	sample_config.h

	Change this file to match your Wifi configuration and
	the Adaftui IO user name and password. When finish editing,
	save the file as "config.h" within the same directory 
	before compiling the code.

*/

// point AdafruitIO to ESP8266 
#define ESP8266

// wifi network
#define WIFI_SSID "ENTER_SSID_HERE"
#define WIFI_PASS "ENTER_WIFI_PASSWORD_HERE"

// Adafruit IO
#define AIO_USERNAME "ENTER_ADAFRUIT_IO_USERNAME_HERE"
#define AIO_KEY "ENTER_ADAFRUIT_IO_PASSWORD_HERE"

#include "AdafruitIO_WiFi.h"

// setup Adafruit IO
AdafruitIO_WiFi io(AIO_USERNAME, AIO_KEY, WIFI_SSID, WIFI_PASS);