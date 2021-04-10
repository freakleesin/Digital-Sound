//
// Created by Rundi Liu on 2020/10/4.
//
#include <stdio.h>
#include <stdlib.h>
#include "process.h"

sound * mix(sound *s[], float w[], int c){
    float CurSamples = 0;
    float maxLength = 0; //longest length of an array
    for(int i=0; i<c; i++){
        if(s[i]->length > maxLength){
            maxLength = s[i]->length;
        }
    }
    sound *p = malloc(sizeof(struct sound_t));
    p->samples = malloc(maxLength*sizeof(float));
    p->length = maxLength;
    //p->rate =
    while(CurSamples < maxLength){
        float sum=0;
        for(int n=0; n<c; n++){
            sum += s[n]->samples[(int)CurSamples] * w[n];
        }
        (p->samples)[(int)CurSamples] = sum;
        CurSamples++;
    }

    return p;
}

sound * modulate(sound *s1, sound *s2){
    sound *p = malloc(sizeof(struct sound_t));
    p->samples = malloc(sizeof(float)*s1->length);
    if(s1->length != s2->length){
        return NULL;
    }else{
        for(int i=0; i<s1->length; i++) {
            (p->samples)[i] = (s1->samples)[i] * (s2->samples)[i];
        }
    }
    return p;
}

sound * filter(sound *s, float fir[], int c){
    sound *p = malloc(sizeof(struct sound_t));
    p->samples = malloc(sizeof(float)*s->length);
    p->length = s->length;
    p->rate = s->rate;
    p->samples[0] = fir[0] * s->samples[0];
    p->samples[1] = fir[1] * s->samples[0] + fir[0] * s->samples[1];
    p->samples[2] = fir[0] * s->samples[2] + fir[1] * s->samples[1] + fir[2] * s->samples[0];
    float CurSamples = 3;
    while(CurSamples < s->length){
        float sum=0;
        float n = CurSamples;
        for(int i=0; i<c; i++){
            sum += fir[i] * s->samples[(int)n];
            n--;
        }
        p->samples[(int)CurSamples++] = sum;
    }
    return p;
}

sound * reverb(sound *s, float delay, float attenuation){
    int length = (int)(s->rate*delay);
    float fir[length];
    fir[0] = 1;
    for(int i=1; i<length-1; i++){
        fir[i] = 0;
    }
    fir[length-1] = attenuation;
    if((attenuation>=1 & attenuation <=0) | (delay>=0.1 & delay <=0) | s == NULL){
        printf("Error. Incorrect Parameter\n");
        exit(0);
    }
    return filter(s, fir, length);
}

sound * echo(sound *s, float delay, float attenuation){
    int length = (int)(s->rate*delay);
    float fir[length];
    fir[0] = 1;
    for(int i=1; i<length-1; i++){
        fir[i] = 0;
    }
    fir[length-1] = attenuation;
    if((attenuation>=1 & attenuation <=0) | (delay>=1 & delay<=0.1) | s == NULL){
        printf("Error. Incorrect Parameter\n");
        exit(0);
    }
    return filter(s, fir, length);
}
