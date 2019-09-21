/* Hello World Example

 This example code is in the Public Domain (or CC0 licensed, at your option.)

 Unless required by applicable law or agreed to in writing, this
 software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 CONDITIONS OF ANY KIND, either express or implied.
 */
#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "WifiSystems.h"
#include "RemoteServer.hpp"

extern "C"
{
void app_main(void);
}

RemoteServer* remoteServer;
int changingNumber = 0;

char user_name[] = "CharlieBetaDemo";
char node_id[] = "12345678123456781234567812345679";

void app_main()
{
   printf("Setting up WiFi\n");

   InitWifi();

   printf("Creating server and starting application!\n");

   remoteServer = new RemoteServer(user_name, node_id);

// Update settings & send last loop's state
//   remoteServer->syncWithRemoteServer();

//// Demo settings
//   printf("Light State:");
//   printf("%s\n", (remoteServer->getSetting_Bool("ligh") ? "true" : "false")); // Light State
//   printf("Light State:" "Water State:");
//   printf("%s\n", (remoteServer->getSetting_Bool("wate") ? "true" : "false")); // Water State
//
//// Demo state values
//   changingNumber > 10 ?
//      changingNumber = 0 : changingNumber = changingNumber + 1;
//   remoteServer->setState("humi", changingNumber); // Humidity sensor reported value
//   remoteServer->setState("lise", changingNumber); // Light sensor reported value

// Log that this loop completed and send out any buffered log data
   printf("\n\r//////////////////////////// Loop Complete ////////////////////////////\n\r");

}

