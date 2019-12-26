#include "flashFS.h"

#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "esp_partition.h"
#include "esp_system.h"
#include "dirent.h"

#include "webserver.h"

static FlashFSConfig_t *config = NULL;
static const char *TAG = "flashFS";

void flashFSInit(FlashFSConfig_t *cfg)
{
  config = cfg;
  esp_vfs_spiffs_conf_t conf = {
      .base_path = config->root,
      .partition_label = config->partition,
      .max_files = config->maxOpenFiles,
      .format_if_mount_failed = false};

  esp_err_t ret = esp_vfs_spiffs_register(&conf);

  if (ret != ESP_OK)
  {
    if (ret == ESP_FAIL)
    {
      ESP_LOGE(TAG, "Failed to mount or format filesystem");
    }
    else if (ret == ESP_ERR_NOT_FOUND)
    {
      ESP_LOGE(TAG, "Failed to find SPIFFS partition");
    }
    else
    {
      ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
    }
    return;
  }

  size_t total = 0, used = 0;
  ret = esp_spiffs_info(config->partition, &total, &used);
  if (ret != ESP_OK)
  {
    ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
  }
  else
  {
    ESP_LOGI(TAG, "Partition %s, size: total: %d, used: %d", conf.partition_label, total, used);
  }
}

FILE *flashFSOpen(const char *filepath, const char *mode)
{
  return fopen(filepath, mode);
}

void flashFSInfo(size_t *total, size_t *used, size_t *totalFlashMem)
{
  if (!esp_spiffs_mounted(config->partition))
    return;

  *totalFlashMem = spi_flash_get_chip_size();

  esp_err_t ret = esp_spiffs_info(config->partition, total, used);
  if (ret != ESP_OK)
    ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
}
