#ifndef __signal_detect_h_INCLUDED__
#define __signal_detect_h_INCLUDED__

typedef struct {
  float avg;
  float alpha;
  float variance;
  float threshold;
  float influence;
  float signal;
} signal_data_t;

int signal_detect(signal_data_t* data, float sample);

#endif