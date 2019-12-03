#include "scpi.hpp"

int main()
{
    SCPI scpiObj("GPIB0::11::INSTR");
    scpiObj.identifyObject();
    return 0;
}