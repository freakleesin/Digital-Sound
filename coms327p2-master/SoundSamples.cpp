#include <iostream>
#include "vector"
#include "SoundSamples.h"
#include <cstring>
using namespace std;
/*
 * Constructor
 */
SoundSamples::SoundSamples():sample_rate(8000), sampleLength(0){}

SoundSamples::~SoundSamples(){
    delete samples;
}
/*
 * specific constructor
 */
SoundSamples::SoundSamples(float *sample, int number, float sampleRate):
//samples(sample),
sampleLength(number), sample_rate(sampleRate)
{
    samples = (float*)new float[number];
    for(int i=0; i<number; i++){
        samples[i] = sample[i];
    }
}

/*
 *  copy constructor that deep copies the object.
 */
SoundSamples::SoundSamples(const SoundSamples & origObj)
        :samples(origObj.samples), sampleLength(origObj.sampleLength), sample_rate(origObj.sample_rate)
{
}

/*
 * Creates a sequence of samples of the specified length that are all zeros
 */
SoundSamples::SoundSamples(int num, float sampleRate):sampleLength(num), sample_rate(sampleRate)
{
    samples = (float*)new float[num];
    float val = 0; //makes sure the value is the float type.
    for(int i=0; i<num; i++){
        samples[i] = val;
    }
}

/*
 * delete and copy all the data. ---Deep Copy
 */
const SoundSamples & SoundSamples::operator=(const SoundSamples & origObj){
    if(this != &origObj){
        *samples = * origObj.samples;
    }
    return *this;
}

float& SoundSamples::operator[](unsigned int index){
    float& ref = samples[index];
    return ref;
}

SoundSamples SoundSamples::operator+(SoundSamples rhs){
    SoundSamples s;
    for(int i=0; i<sampleLength-1; i++){
        s.samples[i] = samples[i];
    }
    int k=0;
    for(int j=sampleLength; j<sampleLength*2; j++){
        s.samples[j] = rhs.samples[k++];
    }
    return s;
}

/*
 * returns the number of samples
 */
int SoundSamples::getLength() {
    return sampleLength;
}

void SoundSamples::reverb2(float delay, float attenuation){
    float array[sampleLength];
    for(int i=0; i<sampleLength; i++){
        int temp = (int)(i-delay*sample_rate) ;
        if(temp < 0) {
            array[i] = samples[i];
            //samples[i] = samples[temp] * attenuation + samples[i];
        }else{
            array[i] = samples[i] + array[temp]*attenuation;
        }

    }
    for(int j=0; j<sampleLength; j++){
        samples[j] = array[j];
        //printf("%f\n", samples[j]);
    }
}

void SoundSamples::adsr(float atime, float alevel, float dtime, float slevel, float rtime){
    float duration = sampleLength/sample_rate;
    int aSamples = (int)(atime * sample_rate); // number of samples during atime
    int dSamples = (int)(dtime * sample_rate); // number of samples during dtime
    int rSamples = (int)(rtime * sample_rate); // number of samples during rtime
    int stableSamples = (int)((duration-atime-dtime-rtime)*sample_rate); // number of samples with the constant value

    int curSamples = 0;
    float temp1 = 0;
    float temp2 = alevel;
    float temp3 = slevel;
    float arr[sampleLength];
    for(int a=0; a<aSamples; a++){
        arr[curSamples] = temp1;
        temp1 += alevel/aSamples;
        curSamples++;
    }
    for(int d=0; d<dSamples; d++){
        arr[curSamples] = temp2;
        temp2 -= (alevel-slevel)/dSamples;
        curSamples++;
    }
    for(int s=0; s<stableSamples; s++){
        arr[curSamples] = slevel;
        curSamples++;
    }
    for(int r=0; r<rSamples; r++){
        temp3 -= slevel/rSamples;
        arr[curSamples] = temp3;
        curSamples++;
    }

    /*
     * multiple the samples by the float array
     */
    for(int i=0; i<sampleLength; i++){
        samples[i] = arr[i] * samples[i];
    }

}
