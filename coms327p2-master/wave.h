#ifndef WAVE_H
#define WAVE_H
#include "SoundSamples.h"
#include <string>
#include "math.h"

class Wave {
public:
    Wave(std::string a);
    virtual float generateFunction(float time)=0;
    SoundSamples * generateSamples(float, float, float);
    std::string name;
    SoundSamples *s;
};

class SineWave : public Wave{
public:
    SineWave(std::string a);
    float generateFunction(float time);
};

class SquareWave : public Wave{
public:
    SquareWave(std::string a);
    float generateFunction(float time);
};

class TriangleWave : public Wave{
public:
    TriangleWave(std::string a);
    float generateFunction(float time);
};

class SawtoothWave : public Wave{
public:
    SawtoothWave(std::string a);
    float generateFunction(float time);
};


#endif //WAVE_H
