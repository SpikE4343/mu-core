//

#ifndef __wifi_controller_h__INCLUDED__
#define __wifi_controller_h__INCLUDED__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "data_type.h"

#define WIFI_AP 0

data_type(
    {
      char ssid[32];
      char password[64];
      uint8_t maxConnections;
      uint8_t retryCount;
    },
    WifiConfig_t);

void wifiInit(WifiConfig_t *config);
EventGroupHandle_t *wifiGetEventGroup();

#endif