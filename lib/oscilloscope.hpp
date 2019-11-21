#include "scpi.hpp"
#include <iostream>


class Oscilloscope
{
public:

    Oscilloscope();
    ~Oscilloscope();




private:

    int numChannels; //obtained by running through a "CH1?" .. "CH4?" and seeing what actually returns
    

}


