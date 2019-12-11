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

void SCPI::cleanup()
{
    memset(this->returnString, 0, sizeof(this->returnString));
    memset(this->stringInput, 0, sizeof(this->stringInput));
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
    this->cleanup();
    return ret;
}

DataEncoding SCPI::queryDataEncodingType()
{
    strcpy(this->stringInput, "DATA:ENCDG?");
    ViUInt32 retCount;
    std::string query_return = this->queryString(this->stringInput, retCount);
    if (retCount == 0)
    {
        std::cout << "Unable to query encoding type?" << std::endl;
        //larger error handling? 
    }

    std::string queryVal = this->getQueryVal(query_return);

    DataEncoding ret;

    auto itr = EnumMap::EncodingMap.find(queryVal);

    if (itr == EnumMap::EncodingMap.end()) {
        return DATA_ENCODING_INVALID;
    }

    std::cout << "Iterator Value is: " << itr->first << "\tMap value is " << itr->second <<  std::endl;
    
    ret = itr->second;

    this->cleanup();

    return ret;
}


int SCPI::setDataEncodingType(DataEncoding enc)
{
    int ret = 1;
    auto itr = std::find_if(EnumMap::EncodingMap.begin(), EnumMap::EncodingMap.end(), 
                            [&enc](const std::pair<std::string, DataEncoding> &p)
                            {
                                return (enc == p.second);
                            });

    if (itr == EnumMap::EncodingMap.end()) 
    {
        std::cout << "Unable to set encoding type to an invalid value." << std::endl;
        return 0;
    }

    //val falls out of scope once dataStr falls out of scope
    std::string dataStr = itr->first;

    strcpy(this->stringInput, "DATA:ENCDG ");
    strcat(this->stringInput, dataStr.c_str());

    std::cout << "writing the string: " << this->stringInput << std::endl;

    ret = this->writeString(this->stringInput);
    this->cleanup();

    return ret;

}

ChannelSource SCPI::queryChannelSource()
{
    strcpy(this->stringInput, "DATA:SOURCE?");
    ViUInt32 retCount;
    std::string query_return = this->queryString(this->stringInput, retCount);
    if (retCount == 0)
    {
        std::cout << "Unable to query channel source?" << std::endl;
        //larger error handling? 
    }

    std::string queryVal = this->getQueryVal(query_return);

    ChannelSource ret;

    auto itr = EnumMap::ChannelSrcMap.find(queryVal);

    if (itr == EnumMap::ChannelSrcMap.end()) {
        return CHANNEL_SRC_INVALID;
    }

    std::cout << "Iterator Value is: " << itr->first << "\tMap value is " << itr->second <<  std::endl;
    
    ret = itr->second;

    this->cleanup();

    return ret;
}


int SCPI::setChannelSource(ChannelSource src)
{
    int ret = 1;
    //since we are using C++11, can't use generic templates :( 
    auto itr = std::find_if(EnumMap::ChannelSrcMap.begin(), EnumMap::ChannelSrcMap.end(), 
                            [&src](const std::pair<std::string, ChannelSource> &p)
                            {
                                return (src == p.second);
                            });

    if (itr == EnumMap::ChannelSrcMap.end()) 
    {
        std::cout << "Unable to set encoding type to an invalid value." << std::endl;
        return 0;
    }

    //val falls out of scope once dataStr falls out of scope
    std::string dataStr = itr->first;

    strcpy(this->stringInput, "DATA:SOURCE ");
    strcat(this->stringInput, dataStr.c_str());
    
    std::cout << "writing the string: " << this->stringInput << std::endl;

    ret = this->writeString(this->stringInput);
    this->cleanup();

    return ret;

}

DataWidth SCPI::queryDataWidth()
{
    strcpy(this->stringInput, "DATA:WIDTH?");
    ViUInt32 retCount;
    std::string query_return = this->queryString(this->stringInput, retCount);
    if (retCount == 0)
    {
        std::cout << "Unable to query data width?" << std::endl;
        //larger error handling? 
    }

    std::string queryVal = this->getQueryVal(query_return);

    DataWidth ret;

    auto itr = EnumMap::DataWidthMap.find(queryVal);

    if (itr == EnumMap::DataWidthMap.end()) {
        return DATA_WIDTH_INVALID;
    }

    std::cout << "Iterator Value is: " << itr->first << "\tMap value is " << itr->second <<  std::endl;
    
    ret = itr->second;

    this->cleanup();

    return ret;

}

int SCPI::setDataWidth(DataWidth width)
{
    int ret = 1;
    //since we are using C++11, can't use generic templates :( 
    auto itr = std::find_if(EnumMap::DataWidthMap.begin(), EnumMap::DataWidthMap.end(), 
                            [&width](const std::pair<std::string, DataWidth> &p)
                            {
                                return (width == p.second);
                            });

    if (itr == EnumMap::DataWidthMap.end()) 
    {
        std::cout << "Unable to set encoding type to an invalid value." << std::endl;
        return 0;
    }

    //val falls out of scope once dataStr falls out of scope
    std::string dataStr = itr->first;

    strcpy(this->stringInput, "DATA:WIDTH ");
    strcat(this->stringInput, dataStr.c_str());
    
    std::cout << "writing the string: " << this->stringInput << std::endl;

    ret = this->writeString(this->stringInput);
    this->cleanup();

    return ret;

}

float SCPI::queryYMult()
{
    strcpy(this->stringInput, "WFMOUTPRE:YMULT?");
    ViUInt32 retCount;
    std::string query_return = this->queryString(this->stringInput, retCount);
    if (retCount == 0)
    {
        std::cout << "Unable to query y mult?" << std::endl;
        //larger error handling? 
    }

    std::string queryStrVal = this->getQueryVal(query_return);
    float ret = this->strToFloat(queryStrVal);
    printf("The queried ymult value is %0.5f\n", ret);

    this->yMult = ret;

    return ret;

}

float SCPI::queryYZero()
{
    strcpy(this->stringInput, "WFMOUTPRE:YZERO?");
    ViUInt32 retCount;
    std::string query_return = this->queryString(this->stringInput, retCount);
    if (retCount == 0)
    {
        std::cout << "Unable to query y zero?" << std::endl;
        //larger error handling? 
    }

    std::string queryStrVal = this->getQueryVal(query_return);
    float ret = this->strToFloat(queryStrVal);
    printf("The queried yzero value is %0.5f\n", ret);
    
    this->yZero = ret;

    return ret;

}

float SCPI::queryYOff()
{
    strcpy(this->stringInput, "WFMOUTPRE:YOFF?");
    ViUInt32 retCount;
    std::string query_return = this->queryString(this->stringInput, retCount);
    if (retCount == 0)
    {
        std::cout << "Unable to query y off?" << std::endl;
        //larger error handling? 
    }

    std::string queryStrVal = this->getQueryVal(query_return);
    float ret = this->strToFloat(queryStrVal);
    printf("The queried off value is %0.5f\n", ret);
    
    this->yOff = ret;

    return ret;

}

float SCPI::queryXIncr()
{
    strcpy(this->stringInput, "WFMOUTPRE:XINCR?");
    ViUInt32 retCount;
    std::string query_return = this->queryString(this->stringInput, retCount);
    if (retCount == 0)
    {
        std::cout << "Unable to query x Incr?" << std::endl;
        //larger error handling? 
    }

    std::string queryStrVal = this->getQueryVal(query_return);
    float ret = this->strToFloat(queryStrVal);
    printf("The queried xIncr value is %0.12f\n", ret);
    
    this->xIncr = ret;

    return ret;
}


float SCPI::strToFloat(std::string query)
{
    std::cout << "QueryStrVal is: " << query << std::endl;\
    std::stringstream ss;
    float f;
    ss << query;
    ss >> f;

    if (ss.fail())
    {
        printf("String stream failed\n");
    }
    return f;

}

double SCPI::strToDouble(std::string query)
{
    std::cout << "QueryStrVal is: " << query << std::endl;\
    std::stringstream ss;
    double d;
    ss << query;
    ss >> d;

    if (ss.fail())
    {
        printf("String stream failed\n");
    }
    return d;

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