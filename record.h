#ifndef RECORD_H_ 
#define RECORD_H_

#include <stdint.h>
#include <stdlib.h>
#include <portaudio.h>

typedef struct{
  uint16_t formatType;
  uint8_t numberOfChannels;
  uint32_t sampleRate;
  size_t size;
  float *recordedSamples;
} AudioData;

typedef struct{
  float *snippet;
  size_t size;
} AudioSnippet;


int init(PaStream **stream, AudioData *data, AudioSnippet *sampleBlock);
int processStream(PaStream *stream, AudioData *data, AudioSnippet *sampleBlock, const char *fileName, bool *sampleComplete);

#endif