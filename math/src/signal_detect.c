#include <stdio.h>
#include <math.h>
#include <string.h>

#include "filters.h"
#include "signal_detect.h"

// # for a new value newValue, compute the new count, new mean, the new M2.
// # mean accumulates the mean of the entire dataset
// # M2 aggregates the squared distance from the mean
// # count aggregates the number of samples seen so far
// def update(existingAggregate, newValue):
//     (count, mean, M2) = existingAggregate
//     count += 1 
//     delta = newValue - mean
//     mean += delta / count
//     delta2 = newValue - mean
//     M2 += delta * delta2

//     return (count, mean, M2)

// # retrieve the mean, variance and sample variance from an aggregate
// def finalize(existingAggregate):
//     (count, mean, M2) = existingAggregate
//     (mean, variance, sampleVariance) = (mean, M2/count, M2/(count - 1)) 
//     if count < 2:
//         return float('nan')
//     else:
//         return (mean, variance, sampleVariance)

int signal_detect(signal_data_t* data, float sample)
{
  float filtered = data->avg;
  //lowPassFilter(data->avg, sample, data->alpha);
  float delta = sample - data->avg;
  data->avg = sample;
  data->variance += ((delta*delta)-data->variance) * data->alpha;

  data->signal = 0;

  if( fabs(delta) > data->threshold * data->variance)
  {
    data->avg = data->influence * sample + (1 - data->influence) * filtered;
    data->signal += (delta > 0 ) ? 1 : -1;
  }

  return data->signal;
}
