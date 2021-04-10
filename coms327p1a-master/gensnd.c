//
// Created by Rundi Liu on 2020/9/4.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gensnd.h"

/*
 * Returns a pointer to the structure
 */
sound *gensine(float hertz, float sample_rate, float duration){
    sound *p = malloc(sizeof(struct sound_t));
    p->samples = malloc(sample_rate*duration*sizeof(float));

    int CurSample =0;
    int numSamples = sample_rate*duration;

    while(CurSample<numSamples){
        float val = sin(2*M_PI*hertz*CurSample/sample_rate);
        (p->samples)[CurSample] = val;
        CurSample += 1;
    }
    p->rate = sample_rate;
    p->length = numSamples;

    return p;
}

/*
 * Creates the dual tones
 * at the specified sample rate and duration given in the parameters.
 */
sound * genDTMF(char key, float sample_rate, float duration){
    char p = key;
    int input1, input2;
    if(p == '0'){
        input1 = 941;
        input2 = 1336;
    }
    else if(p == '1'){
        input1 = 697;
        input2 = 1209;
    }
    else if(p == '2'){
        input1 = 697;
        input2 = 1336;
    }
    else if(p == '3'){
        input1 = 697;
        input2 = 1477;
    }
    else if(p == '4'){
        input1 = 770;
        input2 = 1209;
    }
    else if(p == '5'){
        input1 = 770;
        input2 = 1336;
    }
    else if(p == '6'){
        input1 = 770;
        input2 = 1477;
    }
    else if(p == '7'){
        input1 = 852;
        input2 = 1209;
    }
    else if(p == '8'){
        input1 = 852;
        input2 = 1336;
    }
    else if(p == '9'){
        input1 = 852;
        input2 = 1477;
    }
    else if((p == 'A') | (p == 'a')){
        input1 = 697;
        input2 = 1633;
    }
    else if((p == 'B') | (p == 'b')){
        input1 = 770;
        input2 = 1633;
    }
    else if((p == 'C') | (p == 'c')){
        input1 = 852;
        input2 = 1633;
    }
    else if((p == 'D') | (p == 'd')){
        input1 = 941;
        input2 = 1633;
    }
    else if(p == '*'){
        input1 = 941;
        input2 = 1209;
    }
    else if(p == '#'){
        input1 = 941;
        input2 = 1477;
    }
    int CurrentSample=0;
    int length=sample_rate*duration;

    sound *soundStruct = malloc(sizeof(sound));
    sound *soundStruct1 = malloc(sizeof(struct sound_t));
    sound *soundStruct2 = malloc(sizeof(struct sound_t));
    soundStruct->samples = malloc(sample_rate*duration*sizeof(float));
    soundStruct1->samples = malloc(sample_rate*duration*sizeof(float));
    soundStruct2->samples = malloc(sample_rate*duration*sizeof(float));
    while(CurrentSample < sample_rate*duration){
        soundStruct1 = gensine(input1,sample_rate,duration);
        soundStruct2 = gensine(input2,sample_rate,duration);
        float value = (soundStruct1->samples[CurrentSample]+soundStruct2->samples[CurrentSample])/2;
        if(value<1 & value>-1){
            soundStruct->samples[CurrentSample] = value;
        }else{
            soundStruct->samples[CurrentSample] = value/2;
        }
        CurrentSample += 1;
    }

    soundStruct->length = length;
    soundStruct->rate = sample_rate;

    free(soundStruct->samples);
    //free(soundStruct);

    return soundStruct;
}

/*
 * generates silence
 * The samples are returned in the structure
 */
sound *genSilence(float sample_rate, float duration) {
    float fre = 0;
    int numSamples = sample_rate * duration;
    sound *soundStruct = malloc(sizeof(sound));
    soundStruct->samples = malloc(sizeof(float) * numSamples);
    for (int f = 0; f < sample_rate * duration; f += 1) {
        (soundStruct->samples)[f] = fre;
    }
    soundStruct->length = numSamples;
    soundStruct->rate = sample_rate;

    //free(soundStruct->samples);
    //free(soundStruct);
    return soundStruct;
}

sound *genSquare(float hertz, float sample_rate, float duration){
    sound *p = malloc(sizeof(struct sound_t));
    p->samples = malloc(sample_rate*duration*sizeof(float));

    int CurSample = 1;
    int numSamples = sample_rate*duration;
    float f = 1;
    (p->samples)[0] = f; // // make sure start with 1 instead of -1;
    while(CurSample < numSamples){
        float val = sin(2*M_PI*hertz*CurSample/sample_rate);
        if(val > 0){
            (p->samples)[CurSample] = 1;
        }else{
            (p->samples)[CurSample] = -1;
        }
        CurSample += 1;
    }
    p->rate = sample_rate;
    p->length = numSamples;

    return p;
}

sound *genTriangle(float hertz, float sample_rate, float duration){
    sound *p = malloc(sizeof(sound));
    p->samples = malloc(sample_rate*duration*sizeof(float));
    float CurSample = 0;
    float numSamples = sample_rate*duration;
    float OneCycleSamples = sample_rate/hertz;
    float Quarter = OneCycleSamples/4;
    float fre = 1/Quarter;
    float value = 0;

    while(CurSample < numSamples){
        if(CurSample < Quarter-fre){
            (p->samples)[(int)CurSample] = value;
            value += fre;
            CurSample++;
        }else{
            value = 1;
            while(value > -1+fre){
                (p->samples)[(int)CurSample] = value;
                value -= fre;
                CurSample++;
            }
            value = -1;
            while(value < 1-fre){
                p->samples[(int)CurSample] = value;
                value += fre;
                CurSample++;
            }
        }
    }

    p->length = numSamples;
    p->rate = sample_rate;

    return p;
}

sound *genSawtooth(float hertz, float sample_rate, float duration){
    sound *p = malloc(sizeof(sound));
    p->samples = malloc(sample_rate*duration*sizeof(float));
    float CurSample = 0;
    float numSamples = sample_rate*duration;
    float OneCycleSamples = sample_rate/hertz;
    float half = OneCycleSamples/2;
    float fre = 1/half;
    float value = 0;

    while(CurSample < numSamples){
        if(CurSample < half+fre){
            (p->samples)[(int)CurSample] = value;
            value += fre;
            CurSample++;
        }else{
            value = -1;
            while(value < 1+fre){
                (p->samples)[(int)CurSample] = value;
                value += fre;
                CurSample++;
            }
        }
    }
    p->rate = sample_rate;
    p->length = sample_rate*duration;
    return p;
}
