#include "SoundSamples.h"
#include <string>
#include "math.h"
#include "wave.h"

Wave::Wave(std::string a):name(a) {}
SoundSamples * Wave::generateSamples(float frequency, float sampleRate, float duration) {
    int length = (int)(duration * sampleRate);
    float *samples = new float[length];

    for(int i=0; i<length; i++){
        float value = (2*M_PI*frequency*i)/sampleRate;
        samples[i] = generateFunction(value);
    }

    SoundSamples *ss = new SoundSamples(samples, length, sampleRate);
    ss->setLength(length);
    ss->setSampleRate(sampleRate);
    return ss;
}

SineWave::SineWave(std::string a):Wave(a){}
float SineWave::generateFunction(float time) {
    return sin(time);
}

SquareWave::SquareWave(std::string a):Wave(a) {}
float SquareWave::generateFunction(float time) {
    if(sin(time) > 0)
        return 1;
    else
        return -1;
}

TriangleWave::TriangleWave(std::string a):Wave(a) {}
float TriangleWave::generateFunction(float time) {
    return 2*asin(sin(time))/M_PI;
}


SawtoothWave::SawtoothWave(std::string a):Wave(a) {}
float SawtoothWave::generateFunction(float time) {
    return -2*atan(1/(tan(time/2)))/M_PI;
}
