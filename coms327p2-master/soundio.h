#ifndef SOUNDIO_H
#define SOUNDIO_H
#include "SoundSamples.h"
#include <string>
#include <fstream>



class SoundIO {
public:
    static int OutputSound(SoundSamples *, std::string);
};


#endif //SOUNDIO_H
