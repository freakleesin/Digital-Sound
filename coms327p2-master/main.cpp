#include <iostream>
#include <string>
#include "SoundSamples.cpp"
#include "soundio.cpp"
#include "wave.cpp"


using namespace std;

int main(){
    cout<<"Your input:"<<endl;

    /*
     * fix part a
     */
    //string singleLine;
    //cin>>singleLine; // main

    int type;
    cin>>type; // 1/2/3/4

    float sampleRate;
    cin>>sampleRate;

    float frequency;
    cin>>frequency;

    float duration;
    cin>>duration;

    string fileName;
    cin>>fileName;

    SoundSamples *ss;
    Wave *w;
    if(type == 1){
        w = new SineWave("MySineWave");
    }
    else if(type == 2){
        w = new SquareWave("MySquareWave");
    }
    else if(type == 3){
        w = new TriangleWave("MyTriangleWave");
    }
    else{
        w = new SawtoothWave("MySawWave");
    }
    ss = w->generateSamples(frequency,sampleRate,duration);
    SoundIO::OutputSound(ss,fileName);

    return 0;
}

