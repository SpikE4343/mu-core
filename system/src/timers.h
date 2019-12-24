#ifndef __timers_h_INCLUDED__
#define __timers_h_INCLUDED__

#include "driver/timer.h"
#include "freertos/queue.h"

#define TIMER_DIVIDER   16               /*!< Hardware timer clock divider */
#define TIMER_SCALE    (TIMER_BASE_CLK / TIMER_DIVIDER)  /*!< used to calculate counter value */

unsigned long IRAM_ATTR millis();

void timerInit(
    timer_idx_t timer_idx, 
    timer_group_t timer_group_idx, 
    QueueHandle_t locks, 
    bool auto_reload, 
    double timer_interval_sec);

void IRAM_ATTR timerUpdateIttr(void* para);
#endif