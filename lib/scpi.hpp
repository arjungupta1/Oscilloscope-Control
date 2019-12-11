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
#include <algorithm>
#include <map>
#include <sstream>
#include "enums.hpp"


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

    //handles queries for the data encoding type
    DataEncoding queryDataEncodingType();
    int setDataEncodingType(DataEncoding enc);

    ChannelSource queryChannelSource();
    int setChannelSource(ChannelSource src);

    DataWidth queryDataWidth();
    int setDataWidth(DataWidth width);

    float queryYMult();
    float queryYZero();
    float queryYOff();
    float queryXIncr();


private:

    ViSession defaultRM;
    ViSession instr;
    ViStatus status;

    float yMult;
    float yZero;
    float yOff;

    float xIncr;


    void* returnBuff; 
    uint32_t returnSz;

    char stringInput[512];
    unsigned char returnString[100];

    int handleFailures(std::string errorMessage);
    int writeString(const char* strInput);
    
    std::string queryString(const char* strInput, uint32_t &retCount);
    float strToFloat(std::string query);
    double strToDouble(std::string query);


    int readString(uint32_t &retCount);
    void cleanup();
    
    bool iequals(const std::string &a, const std::string &b) 
    {
        //lambda function to iterate across string A and B, applying the binary predicate toupper() on the implict objects c_a and c_b
        return (
            (a.size() == b.size()) && 
            (std::equal(
                a.begin(), 
                a.end(), 
                b.begin(),
                [](const char &c_a, const char &c_b) { return (std::toupper(c_a) == std::toupper(c_b)); }
            ))
        );
    }

    std::string getQueryVal(std::string queryReturn)
    {

        std::string queryVal = queryReturn.substr(queryReturn.find(' ') + 1);
        queryVal.erase(std::remove(queryVal.begin(), queryVal.end(), '\n'), queryVal.end());
        return queryVal;
    }
};


