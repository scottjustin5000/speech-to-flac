#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <portaudio.h>
#include <stdbool.h>
#include <stdint.h>

#include "record.h"

AudioData* allocAudioData() {
  AudioData *data = malloc(sizeof(AudioData));
  data->formatType = paFloat32;
  data->numberOfChannels = 1; 
  data->sampleRate = 16000;
  data->size = 0;
  data->recordedSamples = NULL;
  return data;
}

int record(PaStream *stream, AudioData *data, AudioSnippet *sampleBlock, const char *fileName, bool *sampleComplete) {
  int err = 0;
  size_t len;
  while(err == 0 && *sampleComplete == false) {
    err = processStream(stream, data, sampleBlock, fileName, sampleComplete);
  }
  return err;
}

int run(const char *fileName) {
  AudioData *data = allocAudioData();
  AudioSnippet *sampleBlock = &((AudioSnippet){
                                  .size = 0,
                                  .snippet = NULL
                                });
  PaStream *stream = NULL;
  time_t talking = 0;
  time_t silence = 0;
   
  PaError err = paNoError;
  err = init(&stream, data, sampleBlock);
  if (err){
    fprintf(stderr, "%s\n", "error");
    return err;
  }
  bool sampleComplete = false;
  while (!err && !sampleComplete) {
    err = record(stream, data, sampleBlock, fileName, &sampleComplete);
  }
  return err;
}

int main(void) {
  char buffer[100];
  snprintf(buffer, 100, "file:%d.flac", rand());
  run(buffer);   
}