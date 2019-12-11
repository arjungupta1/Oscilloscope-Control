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
    //SCPI reader constructor 
    SCPI(const char *instrAddr);

    //SCPI destructor 
    ~SCPI();
    
    //gets Default Resource Manager Session, handles opening and closing of instrument resources
    const ViSession getDefaultRMSession();
    
    //gets Instrument session, handles writing functions to instrument
    const ViSession getInstrSession();

    //handles *IDN? queries.
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
    int writeString(const char* strInput);
    
    std::string queryString(const char* strInput, uint32_t &retCount);

    int readString(uint32_t &retCount);
};


