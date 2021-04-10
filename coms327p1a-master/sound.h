#ifndef SOUND_H
#define SOUND_H

typedef struct sound_t sound;
struct sound_t {
    int length; // number of the samples in the array
    float *samples; //the samples pointer.
    float rate; // sample rate for the sequence of samples.
};

#endif
