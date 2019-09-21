#include "RemoteServer.hpp"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "esp_http_client.h"
#include "esp_log.h"

#define TAG "HttpStuff"

RemoteServer::RemoteServer(char * _user_name, char * _node_id)
{
   // Create JSON Objects
   settings = (char *)malloc(1024);
   state = (char *)malloc(1024);

   // Settings are initially invalid
   settingsValid = false;

   // Setup parameters
//   user_name = _user_name; // Still need to fix this copy thing
//   node_id = _node_id;

// We should sync with the server at least once to get a valid value for 'settings'
   syncWithRemoteServer();
}

bool RemoteServer::areSettingsValid()
{
   return settingsValid;
}

//float RemoteServer::getSetting_Float(String name)
//{
//   return (*settings)[name];
//}
//
//int RemoteServer::getSetting_Int(String name)
//{
//   return (*settings)[name];
//}
//
//bool RemoteServer::getSetting_Bool(String name)
//{
//   return (*settings)[name];
//}
//
//String RemoteServer::getSetting_String(String name)
//{
//   return (*settings)[name].as<String>();
//}
//
//void RemoteServer::setState(String name, float value)
//{
//   (*state)[name] = value;
//}
//
//void RemoteServer::setState(String name, int value)
//{
//   (*state)[name] = value;
//}
//
//void RemoteServer::setState(String name, bool value)
//{
//   (*state)[name] = value;
//}
//
//void RemoteServer::setState(String name, String value)
//{
//   (*state)[name] = value;
//}

esp_err_t _http_event_handle(esp_http_client_event_t *evt)
{
   switch(evt->event_id)
   {
      case HTTP_EVENT_ERROR:
         ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
         break;
      case HTTP_EVENT_ON_CONNECTED:
         ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
         break;
      case HTTP_EVENT_HEADER_SENT:
         ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
         break;
      case HTTP_EVENT_ON_HEADER:
         ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER");
         printf("%.*s", evt->data_len, (char*)evt->data);
         break;
      case HTTP_EVENT_ON_DATA:
         ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
         if(!esp_http_client_is_chunked_response(evt->client))
         {
            printf("%.*s", evt->data_len, (char*)evt->data);
         }

         break;
      case HTTP_EVENT_ON_FINISH:
         ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
         break;
      case HTTP_EVENT_DISCONNECTED:
         ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
         break;
   }
   return ESP_OK;
}

void RemoteServer::syncWithRemoteServer()
{
   ESP_LOGI(TAG, "Got into the sync");

   esp_err_t err;

   esp_http_client_config_t config = {};
   config.url = "http://marijauto.com/node/updateStatusNode/";
   config.method = HTTP_METHOD_POST;
   config.event_handler = _http_event_handle;

   ESP_LOGI(TAG, "Created the handler");

   char thingToPost[512];

   sprintf(thingToPost, "node_id=%s&user_name=%s&node_status=%s", "12345678123456781234567812345678", "admin", "\"status\":\"good\"");
   ESP_LOGI(TAG, "filled the tihing to post with \n%s\n", thingToPost);

   esp_http_client_handle_t client = esp_http_client_init(&config);
//   esp_http_client_set_url(client, "http://httpbin.org/anything");
//   esp_http_client_set_url(client, "http://marijauto.com/node/updateStatusNode");
   esp_http_client_set_method(client, HTTP_METHOD_POST);
   esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");
   esp_http_client_set_post_field(client, thingToPost, strlen(thingToPost));
   err = esp_http_client_perform(client);

   ESP_LOGI(TAG, "Attempted to post");

   if(err == ESP_OK)
   {
      int len = esp_http_client_get_content_length(client);
      ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d",
         esp_http_client_get_status_code(client),
         len);
   }
   else
   {
      ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
   }

   esp_http_client_cleanup(client);

//   // Precheck for WiFi connection
//   if(WiFi.status() == WL_CONNECTED)
//   {
   // Convert the state-JSON into a String
//   String stateString;
//   serializeJson(*state, stateString);
//
//   // Send a POST request to the server
//   // This sends the state JSON
//   // This receives the settings JSON
//   HTTPClient http;
//   http.begin("http://marijauto.com/node/updateStatusNode");
//   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//   int respCode = http.POST(
//      "node_id=" + node_id +
//         "&user_name=" + user_name +
//         "&node_status=" + stateString
//         );
//   String response = http.getString();
//   http.end();

   // Print debug information about the server's response

   //dbg->printL("[RemoteServer] Got HTTP " + String(respCode) + "={" + http.errorToString(respCode) + "} for status+settings POST.");

//
//
//   // Check that response exists
//   if(response == "")
//   {
//      printf("[RemoteServer] No settings received!\n");
//   }
//   else
//   {
//      // Decode the received settings JSON
//      DeserializationError err = deserializeJson(*settings, response);
//
//      // Print error and die if deserialization fails
//      if(err != DeserializationError::Ok)
//      {
//         printf("[RemoteServer] Deserialization error: %d\n", err);
//         assert(false);
//      }
//
//      // Mark that we have received at least one valid set of settings
//      settingsValid = true;
//   }

//   }
}
