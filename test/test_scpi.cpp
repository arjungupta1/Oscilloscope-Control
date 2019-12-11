#include "scpi.hpp"

int main()
{
    SCPI scpiObj("GPIB0::11::INSTR");
    if (scpiObj.queryDataEncodingType() == DATA_ENCODING_RIB) 
    {
        printf("Encoding is RIB\n");
    }
    else 
    {
        printf("encoding is not RIB\n");
    }
    int success = scpiObj.setDataEncodingType(DATA_ENCODING_RPB);
    if (scpiObj.queryDataEncodingType() == DATA_ENCODING_RPB)
    {
        printf("Encoding is RPB\n");
    }
    else 
    {
        printf("encoding is not RPB\n");
    }

    success = scpiObj.setChannelSource(CHANNEL_SRC_CH1);
    if (scpiObj.queryChannelSource() == CHANNEL_SRC_CH1)
    {
        printf("Channel source is CH1\n");
    }
    else 
    {
        printf("Channel source is not CH1\n");
    }

    success = scpiObj.setDataWidth(DATA_WIDTH_1);
    if (scpiObj.queryDataWidth() == DATA_WIDTH_1)
    {
        printf("Data width is 1.\n");
    }
    else
    {
        printf("Data width is not 1.\n");
    }

    float ymult = scpiObj.queryYMult();
    float yzero = scpiObj.queryYZero();
    float yoff = scpiObj.queryYOff();
    double xIncr = scpiObj.queryXIncr();
    
    return 0;
}