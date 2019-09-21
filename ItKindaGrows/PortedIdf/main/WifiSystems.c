#include "string.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "WifiSystems.h"

static const char *TAG = "WiFiSetup";

#define CONNECTED_BIT 1
static EventGroupHandle_t wifiConnectedHandle;

////////////// WiFi Specific Tasks Below ////////////////

static esp_err_t WifiEventHandler(void *context, system_event_t *event) {
	switch (event->event_id) {
	case SYSTEM_EVENT_STA_START:
		ESP_LOGI(TAG, "Station started...");
		esp_wifi_connect();
		break;

	case SYSTEM_EVENT_STA_GOT_IP:
		ESP_LOGI(TAG, "Station got ip: %s\n",
				ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
		xEventGroupSetBits(wifiConnectedHandle, CONNECTED_BIT);
		break;

	case SYSTEM_EVENT_STA_DISCONNECTED:
		ESP_LOGI(TAG, "Station disconnected...");
		esp_wifi_connect(); // Force reconnect since idf doesn't support it auto yet
		break;

	case SYSTEM_EVENT_STA_CONNECTED:
		ESP_LOGI(TAG, "Station connected...");

		break;

	default:
		break;
	}
	return ESP_OK;
}

void InitWifi() {
	ESP_LOGI(TAG, "Establishing WiFi Configuration");

	wifiConnectedHandle = xEventGroupCreate();

	ESP_ERROR_CHECK(nvs_flash_init());
	tcpip_adapter_init();

	ESP_ERROR_CHECK(esp_event_loop_init(WifiEventHandler, NULL));
	wifi_init_config_t wifiConfiguration = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&wifiConfiguration));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

	// Setup WiFi config parameters.
    wifi_config_t wifi_sta_config = {
        .sta = {
            .ssid = "KAOS",
            .password = "3fdeaf2052",
            .bssid_set = false
        }
    };
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_sta_config));
	ESP_ERROR_CHECK(esp_wifi_start());

	xEventGroupWaitBits(wifiConnectedHandle, CONNECTED_BIT, true, true,
			portMAX_DELAY);
}
