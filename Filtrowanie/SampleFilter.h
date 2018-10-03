#ifndef SAMPLEFILTER_H_
#define SAMPLEFILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 500 Hz

fixed point precision: 16 bits

* 0 Hz - 20 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 50 Hz - 250 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/

#define SAMPLEFILTER_TAP_NUM 19

typedef struct {
  int history[SAMPLEFILTER_TAP_NUM];
  unsigned int last_index;
} SampleFilter;

void SampleFilter_init(SampleFilter* f);
void SampleFilter_put(SampleFilter* f, int input);
int SampleFilter_get(SampleFilter* f);

#endif