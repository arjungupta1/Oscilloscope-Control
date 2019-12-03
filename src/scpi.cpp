#include "scpi.hpp"

SCPI::SCPI(const char *instrAddr)
{
    memset(this->returnString, 0, sizeof(this->returnString));
    memset(this->stringInput, 0, sizeof(this->stringInput));
    if (strlen(instrAddr) == 0)
    {
        std::cout << "Unable to open address with 0 length" << std::endl;
        exit (EXIT_FAILURE);
    }
    this->status = viOpenDefaultRM(&this->defaultRM);
    if (this->status < VI_SUCCESS)
    {
        printf("Could not open a session to the VISA Resource Manager!\n");
        this->status = viClose(this->defaultRM);
        exit (EXIT_FAILURE);
    } 

    this->status = viOpen(this->defaultRM, (ViRsrc) instrAddr, VI_NULL, VI_NULL, &this->instr);
    if (this->status < VI_SUCCESS)  
    {
        printf ("Cannot open a session to the device.\n");
        this->status = viClose(this->instr);
        this->status = viClose(this->defaultRM);
        exit (EXIT_FAILURE);
    }

    this->status = viSetAttribute(this->instr, VI_ATTR_TMO_VALUE, 5000);

}

SCPI::~SCPI()
{
    this->status = viClose(this->instr);
    this->status = viClose(this->defaultRM);
}

int SCPI::identifyObject()
{
    int ret = 1;
    strcpy(this->stringInput, "*IDN?");
    ViUInt32 retCount;
    this->status = viWrite(this->instr, (ViBuf) this->stringInput, (ViUInt32)strlen(this->stringInput), &retCount);
    printf("Wrote %d bytes\n", retCount);
    ret = this->handleFailures("Unable to write *IDN.");

    this->status = viRead(this->instr, this->returnString, 100, &retCount);
    printf("Read %d bytes\n", retCount);
    printf("Data read %s\n", this->returnString);
    ret = this->handleFailures("Unable to read *IDN");

    
    return ret;
}

int SCPI::writeString(const char* strInput, int len)
{
    int ret = 1;
    ViUInt32 retCount;
    this->status = viWrite(this->instr, (ViBuf) strInput, (ViUInt32) len, &retCount);
    std::string err_msg("Unable to write the string: ");
    err_msg += strInput;
    ret = this->handleFailures(err_msg);
    return ret;
}


int SCPI::handleFailures(std::string errorMessage)
{
    int ret = 1;
    if (this->status < VI_SUCCESS)
    {
        std::cout << errorMessage << std::endl;
        ret = (viClose(this->instr) < VI_SUCCESS) ? 0 : 1;
        ret = (viClose(this->defaultRM) < VI_SUCCESS) ? 0 : 1;
    }
    return ret; 
}
const ViSession SCPI::getDefaultRMSession()
{
    return this->defaultRM;
}

const ViSession SCPI::getInstrSession()
{
    return this->instr;
}