#include <iostream>
#include <string>
#include "SoundSamples.cpp"
#include "soundio.cpp"
#include "wave.cpp"



using namespace std;

int main(){
    float SAMPLERATE = 44100;
    float duration = 1;
    int WaveType;
    printf("Wave Type (1-4):\n");
    cin>>WaveType;

    float delay, attenuation;
    printf("Delay & Attenuation (ONE parameter in a line):\n");
    cin>>delay;
    cin>>attenuation;

    float atime, alevel, dtime, slevel, rtime;
    printf("5 parameters for adsr (ONE parameter in a line):\n");
    cin>>atime;
    cin>>alevel;
    cin>>dtime;
    cin>>slevel;
    cin>>rtime;

    std::string filename;
    printf("File Name:\n");
    cin>>filename;


    float key;
    printf("Piano key (all parameters in one line, separate with spaces and end with a negative number):\n");
    while(cin>>key){
        if(key < 0)
            break;

        float fre = powf(powf(2,1.0/12), (key-49)) * 440;
        SoundSamples *ss;
        Wave *w;
        if(WaveType == 1){
            w = new SineWave("MySineWave");
        }
        else if(WaveType == 2){
            w = new SquareWave("MySquareWave");
        }
        else if(WaveType == 3){
            w = new TriangleWave("MyTriangleWave");
        }else{
            w = new SawtoothWave("MySawtoothWave");
        }
        ss = w->generateSamples(fre, SAMPLERATE, duration);
        ss->adsr(atime,alevel,dtime,slevel,rtime);
        ss->reverb2(delay,attenuation);
        SoundIO::OutputSound(ss, filename);
        SoundSamples *silence = new SoundSamples((int)(SAMPLERATE*0.25),SAMPLERATE);
        SoundIO::OutputSound(silence, filename);
    }


    return 0;
}

