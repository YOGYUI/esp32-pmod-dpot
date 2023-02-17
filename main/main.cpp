#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "logger.h"
#include "dpotctrl.h"
#include "network.h"
#include "webserver.h"

extern "C" void app_main(void)
{
    esp_err_t err;

    err = esp_netif_init();
    if (err != ESP_OK) {
        GetLogger(eLogType::Error)->Log("Failed to initialize network interface (ret: %d)", err);
    }

    err = esp_event_loop_create_default();
    if (err != ESP_OK) {
        GetLogger(eLogType::Error)->Log("Failed to create event loop (ret: %d)", err);
    }

    activate_wifi_softap();
    GetWebServer()->start();
    GetDPotCtrl()->initialize();
}
