#ifndef SOUNDSAMPLES_H
#define SOUNDSAMPLES_H
#include <iostream>
#include "vector"


class SoundSamples {
private:
    float sample_rate;
    float *samples;
    int sampleLength;

public:
    SoundSamples();
    ~SoundSamples();
    SoundSamples(float *, int, float); //Specific Constructor
    SoundSamples(const SoundSamples & origObj); // copy constructor
    SoundSamples(int, float);
    const SoundSamples & operator=(const SoundSamples & origObj);
    float & operator[](unsigned int index);
    SoundSamples operator+(SoundSamples rhs);
    void setSampleRate(float sampleRate){ sample_rate = sampleRate; }
    float getSampleRate(){ return sample_rate; }
    void setLength(int len){ sampleLength = len; }
    int getLength();
    void reverb2(float delay, float attenuation);
    void adsr(float atime, float alevel, float dtime, float slevel, float rtime);
};


#endif //SOUNDSAMPLES_H
