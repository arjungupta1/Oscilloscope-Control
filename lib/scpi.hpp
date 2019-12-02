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
    SCPI(const char *instrAddrs);
    ~SCPI();
    std::string createSCPIString(std::vector<std::string> args);

    const ViSession getDefaultRMSession();
    const ViSession getInstrSession();

    int identifyObject();


private:

    ViSession defaultRM;
    ViSession instr;
    ViStatus status;
    char stringInput[512];

    int handleFailures(std::string errorMessage);
    int writeSCPI(char* strInput, int len);



};


