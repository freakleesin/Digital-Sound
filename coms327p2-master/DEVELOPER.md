Possible regrade part for PART A: 
misunderstood the piazza post about input format. After running the executable file, the
first input is meaningless (I thought wave type should be second command). 
Now, it's FIXED.

-----------------------------------------PART A-----------------------------------------

SoundSamples.cpp/SoundSamples.h
has a constructor, specific constructors, a copy constructor with deep copies the object
three overloaded operators: =, +, []
and some getter functions.

wave.cpp/wave.h
contains four subclasses: sine waves, square waves, triangle waves, and sawtooth waves

soundio.cpp/soundio.h
outputs the float numbers to a file

main.cpp
can compile this projec


-----------------------------------------PART B-----------------------------------------

Implemented two more functions in SoundSamples
reverb2: generate the sound you hear inside a large room, like the short echo.
adsr: multiplethe samples of sound sequence by the corresponding value of the ADSR graph

TestMain.cpp: main function to generate the executable file "main"
