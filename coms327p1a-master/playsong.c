//
// Created by Rundi Liu on 2020/10/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "process.c"
#include "gensnd.c"
#include <math.h>
#include "iosnd.c"

int main(int argc, char* argv[]) {

    FILE * fRead = fopen(argv[1], "r");
    FILE * fWrite = fopen(argv[2], "w");

    sound *s[1];
    //int sLength = 0;
    const char space[] = " ";
    char singleLine[100];
    float sampleRate;
    float freq[200];
    float duration[200];
    float start[200];
    int freqLength = 0;
    int durationANDstartANDfreqLength = 0;
    float delay;
    float attenuation;
    int c = 0;
    float w[1];
    //int wLength = 0;
    char waveNameUnderWAVE[100];
    char waveType[100];
    char parameters[100];
    char *arrayOfParameter[100];
    int lengthOfParameter = 0;
    char soundNameInSOUND[100];
    fgets(singleLine, 100, fRead);
    fgets(singleLine, 100, fRead);
    sampleRate = atof(singleLine);

    rewind(fRead);

    while(!feof(fRead)){
        fgets(singleLine, 100, fRead);
        if(strstr(singleLine, "WAVE")){
            fgets(waveNameUnderWAVE, 100, fRead);
            fgets(waveType, 100, fRead);
            fgets(parameters, 100 ,fRead);
            char * token1 = strtok(parameters, space);
            while(token1 != NULL){
                arrayOfParameter[lengthOfParameter++] = token1;
                token1 = strtok(NULL, space);
            }
            delay = atof(arrayOfParameter[0]);
            attenuation = atof(arrayOfParameter[1]);
        }

        //freq = powf((powf(2,1.0/12)), (atof(arrayOfParameter[1])-49)) * 440;
        //duration = atof(lengthOfParameter[3]);
        if(strstr(singleLine, "SOUND")){
            char underSOUND[100];
            char *arrUnderSOUND[100];
            int arrUnderSOUNDlength = 0;
            fgets(soundNameInSOUND, 100, fRead);
            while(fgets(underSOUND, 100, fRead)){
                if(strcmp(underSOUND, "\n") == 0 || strcmp(underSOUND,"\r\n") == 0)
                    break;
                c++;
                char * token2 = strtok(underSOUND, space);
                while(token2 != NULL){
                    arrUnderSOUND[arrUnderSOUNDlength++] = token2;
                    token2 = strtok(NULL, space);
                }
                w[0] = atof(arrUnderSOUND[1]);



            }
            //printf("%d\n", c);
        }
        if(strstr(singleLine, "SONG")){
            char underSONG[100];
            char *arrUnderSONG[100];
            int arrUnderSONGlength = 0;
            while(fgets(underSONG, 100, fRead)){
                //float freq;
                //float duration;

                if(strcmp(underSONG, "\n") == 0 || strcmp(underSONG,"\r\n") == 0)
                    break;
                char * token3 = strtok(underSONG, space);
                while(token3 != NULL){
                    arrUnderSONG[arrUnderSONGlength++] = token3;
                    token3 = strtok(NULL, space);
                }
                freq[freqLength++] = powf((powf(2,1.0/12)), (atof(arrUnderSONG[1])-49)) * 440;
                duration[durationANDstartANDfreqLength] = atof(arrUnderSONG[3]);
                start[durationANDstartANDfreqLength] = atof(arrUnderSONG[2]);
                durationANDstartANDfreqLength++;
            }
        }

    }

    for(int i=0; i<durationANDstartANDfreqLength; i++){
        float silenceDuration = 0;
        sound *soundP;
        sound *s1;
        sound *s2;
        sound *s3;

        if((start[i] == start[i+1]) & (start[i] != start[i+2])){ // only two same start time
            if(strstr(waveType, "sine")){
                s1 = gensine(freq[i], sampleRate, duration[i]);
                s2 = gensine(freq[i+1], sampleRate, duration[i+1]);
            }
            else if(strstr(waveType, "square")){
                s1 = genSquare(freq[i], sampleRate, duration[i]);
                s2 = genSquare(freq[i+1], sampleRate, duration[i+1]);
            }
            else if(strstr(waveType, "triangle")){
                s1 = genTriangle(freq[i], sampleRate, duration[i]);
                s2 = genTriangle(freq[i+1], sampleRate, duration[i+1]);
            }
            else{
                s1 = genSawtooth(freq[i], sampleRate, duration[i]);
                s2 = genSawtooth(freq[i+1], sampleRate, duration[i+1]);
            }

            soundP = malloc(sizeof(struct sound_t));
            //soundP->rate = sampleRate;
            //soundP->length = s1->length;
            soundP->samples = malloc(s1->length*sizeof(float));

            for(int n=0; n<sampleRate*duration[i]; n++){
                soundP->samples[n] = s1->samples[n] + s2->samples[n];
            }
            if(start[i] + duration[i] != start[i+2])
                silenceDuration = start[i+1] - start[i] - duration[i];
        }
        else if((start[i] == start[i+1]) & (start[i] == start[i+2])){ // three start time overlap
            if(strstr(waveType, "sine")){
                s1 = gensine(freq[i], sampleRate, duration[i]);
                s2 = gensine(freq[i+1], sampleRate, duration[i+1]);
                s3 = gensine(freq[i+2], sampleRate, duration[i+2]);
            }
            else if(strstr(waveType, "square")){
                s1 = genSquare(freq[i], sampleRate, duration[i]);
                s2 = genSquare(freq[i+1], sampleRate, duration[i+1]);
                s3 = genSquare(freq[i+2], sampleRate, duration[i+2]);
            }
            else if(strstr(waveType, "triangle")){
                s1 = genTriangle(freq[i], sampleRate, duration[i]);
                s2 = genTriangle(freq[i+1], sampleRate, duration[i+1]);
                s3 = genTriangle(freq[i+2], sampleRate, duration[i+2]);
            }
            else{
                s1 = genSawtooth(freq[i], sampleRate, duration[i]);
                s2 = genSawtooth(freq[i+1], sampleRate, duration[i+1]);
                s3 = genSawtooth(freq[i+2], sampleRate, duration[i+2]);
            }

            soundP = malloc(sizeof(struct sound_t));
            soundP->rate = sampleRate;
            soundP->length = s1->length;
            soundP->samples = malloc(s1->length*sizeof(float));
            for(int n=0; n<sampleRate*duration[i]; n++)
                soundP->samples[n] = s1->samples[n] + s2->samples[n] + s3->samples[n];
            if(start[i] + duration[i] != start[i+3])
                silenceDuration = start[i+1] - start[i] - duration[i];
        }else{ // no overlap
            if(strstr(waveType, "sine"))
                soundP = gensine(freq[i], sampleRate, duration[i]);
            else if(strstr(waveType, "square"))
                soundP = genSquare(freq[i], sampleRate, duration[i]);
            else if(strstr(waveType, "triangle"))
                soundP = genTriangle(freq[i], sampleRate, duration[i]);
            else
                soundP = genSawtooth(freq[i], sampleRate, duration[i]);

            if(start[i] + duration[i] != start[i+1])
                silenceDuration = start[i+1] - start[i] - duration[i];
        }
        s[0] = reverb(soundP, delay, attenuation);
        sound * result;
        result = mix(s, w, c);
        outputSound(result, fWrite);
        if(silenceDuration > 0)
            outputSound(genSilence(sampleRate, silenceDuration),fWrite);
    }


    fclose(fRead);
    fclose(fWrite);
    return 0;
}
