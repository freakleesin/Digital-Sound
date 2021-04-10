#include "soundio.h"
#include <iostream>
#include <fstream>

int SoundIO::OutputSound(SoundSamples *samples, std::string filename) {

    std::ofstream txtOut;
    txtOut.open(filename, std::ofstream::app);
    //txtOut.open(filename);
    for(int i=0; i<samples->getLength(); i++){
        txtOut << samples->operator[](i) << std::endl;
    }
    txtOut.close();
    return 0;
}
