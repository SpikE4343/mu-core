/* SPI Slave example, sender (uses SPI master driver)

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"

#include "soc/timer_group_struct.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"
#include "timers.h"

#define TIMER_DIVIDER   16               /*!< Hardware timer clock divider */
#define TIMER_SCALE    (TIMER_BASE_CLK / TIMER_DIVIDER)  /*!< used to calculate counter value */

typedef struct
{
    int timer_idx;
    int timer_group_idx;
    QueueHandle_t lock;
} TimerInterruptArgs_t;

#define MAX_TIMERS 4

typedef struct
{
    uint8_t timerCount;
    TimerInterruptArgs_t timerArgs[MAX_TIMERS];
} TimerState_t;

static TimerState_t state;

void IRAM_ATTR timerAlarmIttr(void* para)
{
    //printf("interrupt\n\n");
    TimerInterruptArgs_t* args = (TimerInterruptArgs_t*)para;
    int timer_idx = args->timer_idx;

    timg_dev_t* timegroup = args->timer_group_idx ? &TIMERG1 : &TIMERG0;

    /* Retrieve the interrupt status and the counter value
       from the timer that reported the interrupt */
    uint32_t intr_status = timegroup->int_st_timers.val;
    timegroup->hw_timer[timer_idx].update = 1;

    /* Clear the interrupt
       and update the alarm time for the timer with without reload */
    if ((intr_status & BIT(timer_idx)))
    {   
        timegroup->int_clr_timers.t1 = 1;
    }

    /* After the alarm has been triggered
      we need enable it again, so it is triggered the next time */
    timegroup->hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN;

    int xHigherPriorityTaskWoken = false;
    
        /* Unblock the task by releasing the semaphore. */
    xSemaphoreGiveFromISR( args->lock, &xHigherPriorityTaskWoken );
    
    /* If xHigherPriorityTaskWoken was set to true you
    we should yield.  The actual macro used here is
    port specific. */
}

void timerInit(
    timer_idx_t timer_idx, 
    timer_group_t timer_group_idx, 
    QueueHandle_t lock, 
    bool auto_reload, 
    double timer_interval_sec)
{
    uint8_t id =  (1 << timer_idx) | timer_group_idx;
    TimerInterruptArgs_t* args = &state.timerArgs[id];

    /* Select and initialize basic parameters of the timer */
    timer_config_t tconfig;
    tconfig.divider = TIMER_DIVIDER;
    tconfig.counter_dir = TIMER_COUNT_UP;
    tconfig.counter_en = TIMER_PAUSE;
    tconfig.alarm_en = TIMER_ALARM_EN;
    tconfig.intr_type = TIMER_INTR_LEVEL;
    tconfig.auto_reload = auto_reload;
    timer_init(timer_group_idx, timer_idx, &tconfig);

    /* Timer's counter will initially start from value below.
       Also, if auto_reload is set, this value will be automatically reload on alarm */
    timer_set_counter_value(timer_group_idx, timer_idx, 0x00000000ULL);

    args->timer_idx = timer_idx;
    args->timer_group_idx = timer_group_idx;
    args->lock = lock;

    /* Configure the alarm value and the interrupt on alarm. */
    timer_set_alarm_value(timer_group_idx, timer_idx, timer_interval_sec * TIMER_SCALE);
    timer_enable_intr(timer_group_idx, timer_idx);

    timer_isr_register(timer_group_idx, timer_idx, timerAlarmIttr,
        args, ESP_INTR_FLAG_IRAM, NULL);

    timer_start(timer_group_idx, timer_idx);
}

unsigned long IRAM_ATTR millis()
{
    return xTaskGetTickCount() * portTICK_PERIOD_MS;
}

