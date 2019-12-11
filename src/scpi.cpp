#include "scpi.hpp"

/**
 * Constructs SCPI object based on instrument address.
 * Opens the default RM manager and instrument session.
 * Sets the timeout attribute to 5s.
 **/
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

    if (!this->identifyObject())
    {
        printf("Unable to read the device Identification.\n");
        this->status = viClose(this->instr);
        this->status = viClose(this->defaultRM);
        exit(EXIT_FAILURE);
    }

}

/**
 * Closes the instrument and resource manager session. 
 * This is important to do before the object goes out of scope and for garbage collection purposes. 
 **/
SCPI::~SCPI()
{
    this->status = viClose(this->instr);
    this->status = viClose(this->defaultRM);
}

/**
 * Queries the instrument using the *IDN? query. 
 **/
int SCPI::identifyObject()
{
    int ret = 1;
    strcpy(this->stringInput, "*IDN?");
    ViUInt32 retCount;
    std::string query_return = this->queryString(this->stringInput, retCount);    
    return ret;
}

int SCPI::writeString(const char* strInput)
{
    int ret = 1;
    ViUInt32 retCount;
    this->status = viWrite(this->instr, (ViBuf) strInput, (ViUInt32) strlen(strInput), &retCount);
    printf("Wrote %d bytes\n", retCount);
    std::string err_msg("Unable to write the string: ");
    err_msg += strInput;
    ret = this->handleFailures(err_msg);
    return ret;
}

std::string SCPI::queryString(const char* strInput, uint32_t &retCount)
{

    if (!this->writeString(strInput))
    {
        return "";
    }

    this->readString(retCount);

    if ((retCount == 0) || (!this->returnString))
    {
        return "";
    }

    std::string query_return(this->returnString, this->returnString + retCount);
    std::cout << "Data read from queryString(): " << query_return << std::endl;
    return query_return;
}

int SCPI::readString(uint32_t &retCount)
{
    this->status = viRead(this->instr, this->returnString, sizeof(this->returnString), &retCount);
    std::string err_msg("Unable to read the requested string.");
    int ret = this->handleFailures(err_msg);
    printf("Read %d bytes\n", retCount);
    printf("Data read from readString(): %s\n", this->returnString);
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