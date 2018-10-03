#include "SampleFilter.h"

static int filter_taps[SAMPLEFILTER_TAP_NUM] = {
  191,
  598,
  856,
  1418,
  1953,
  2563,
  3110,
  3570,
  3867,
  3972,
  3867,
  3570,
  3110,
  2563,
  1953,
  1418,
  856,
  598,
  191
};

void SampleFilter_init(SampleFilter* f) {
  int i;
  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i)
    f->history[i] = 0;
  f->last_index = 0;
}

void SampleFilter_put(SampleFilter* f, int input) {
  f->history[f->last_index++] = input;
  if(f->last_index == SAMPLEFILTER_TAP_NUM)
    f->last_index = 0;
}

int SampleFilter_get(SampleFilter* f) {
  long long acc = 0;
  int index = f->last_index, i;
  for(i = 0; i < SAMPLEFILTER_TAP_NUM; ++i) {
    index = index != 0 ? index-1 : SAMPLEFILTER_TAP_NUM-1;
    acc += (long long)f->history[index] * filter_taps[i];
  };
  return acc >> 16;
}