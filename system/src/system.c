#include "system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



uint32_t delta(uint32_t last, uint32_t next)
{
  if(last >= next)
  {
    // overflow
    return last - next;
  }

  return next + (UINT32_MAX - last);
}


void systemGetTaskStats( SystemTaskStatsData_t* stats )
{
  TaskStatus_t pxTaskStatusArray[64];
  volatile UBaseType_t uxArraySize, x;
  uint32_t ulTotalRunTime, ulStatsAsPercentage;

  // Take a snapshot of the number of tasks in case it changes while this
  // function is executing.
  uxArraySize = uxTaskGetNumberOfTasks();

  if( pxTaskStatusArray == NULL )
    return;

  // Generate raw status information about each task.
  uxArraySize = uxTaskGetSystemState( pxTaskStatusArray, uxArraySize, &ulTotalRunTime );
  stats->taskCount = uxArraySize;  
  
  uint32_t totald = delta(stats->totalTime, ulTotalRunTime);
  stats->deltaCount = totald;
  stats->totalTime = ulTotalRunTime;

  // Avoid divide by zero errors.
  if( totald <= 0 )
    return;

  // For each populated position in the pxTaskStatusArray array,
  // format the raw data as human readable ASCII data
  for( x = 0; x < uxArraySize && x < 32; x++ )
  {
      TaskStatus_t* task = &pxTaskStatusArray[x];
      uint32_t d = delta(stats->tasks[x].runtimeCounter, task->ulRunTimeCounter);
      stats->tasks[x].deltaCount = d;
      stats->tasks[x].runtimeCounter = task->ulRunTimeCounter;

      // What percentage of the total run time has the task used?
      // This will always be rounded down to the nearest integer.
      // ulTotalRunTimeDiv100 has already been divided by 100.
      ulStatsAsPercentage = d / (totald / 100UL);

      stats->tasks[x].percent = ulStatsAsPercentage;
      strncpy(stats->tasks[x].taskName, task->pcTaskName, sizeof(stats->tasks[x].taskName));
  } 
}


// TaskStatusData_t
//
data_type_write_decl(TaskStatusData_t)
{
  data_set_number(percent);
  data_set_number(deltaCount);
  data_set_number(runtimeCounter);
  data_set_string(taskName);
}

data_type_read_decl(TaskStatusData_t)
{
  data_get_number(uint32_t, percent);
  data_get_number(uint32_t, runtimeCounter);
  data_get_number(uint32_t, deltaCount);
  data_get_string(taskName);
}

// SystemTaskStatsData_t
//
data_type_write_decl(SystemTaskStatsData_t)
{
  data_set_array_of(TaskStatusData_t, tasks, taskCount, 32);
  data_set_number(totalTime);
  data_set_number(deltaCount);
}

data_type_read_decl(SystemTaskStatsData_t)
{
  data_get_array_of(TaskStatusData_t, tasks, taskCount, 32);
  data_get_number(uint32_t, totalTime);
  data_get_number(uint32_t, deltaCount);
}
