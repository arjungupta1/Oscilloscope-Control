/**



**/
#ifdef __cplusplus
extern "C" {
    #include "visa.h"
}
#endif 

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>

class SCPI {

public:
    SCPI(const char *instrAddr);
    ~SCPI();
    std::string createSCPIString(std::vector<std::string> args);

    const ViSession getDefaultRMSession();
    const ViSession getInstrSession();

    int identifyObject();


private:

    ViSession defaultRM;
    ViSession instr;
    ViStatus status;

    void* returnBuff; 
    uint32_t returnSz;

    char stringInput[512];
    unsigned char returnString[100];

    int handleFailures(std::string errorMessage);
    int writeString(const char* strInput, int len);
};


