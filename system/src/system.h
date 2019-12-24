#ifndef __system_h_INCLUDED__
#define __system_h_INCLUDED__

#include "data_type.h"

typedef struct 
{
  uint8_t taskStats;
} SystemConfig_t;


data_type({
  char taskName[32];
  uint32_t runtimeCounter;
  uint32_t deltaCount;
  uint32_t percent;
}, TaskStatusData_t);

data_type({
  uint32_t totalTime;
  uint32_t deltaCount;
  uint8_t taskCount;
  TaskStatusData_t tasks[32];
}, SystemTaskStatsData_t);

void systemInit(SystemConfig_t* config);
void systemGetTaskStats( SystemTaskStatsData_t* stats );
#endif