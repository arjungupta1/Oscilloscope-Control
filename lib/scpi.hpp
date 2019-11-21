/**



**/
#ifdef __cplusplus
extern "C" {
    #include "visa.h"
}
#endif 

#include <iostream>


namespace SCPI_COMMANDS
{
    namespace ACQUIRE {


    }

    namespace ALIAS {

    }

    namespace CAL {

    }

    namespace CURSOR {

    }


    typedef enum {

        DIAG,
        DISPLAY,
        FILESYSTEM,
        HARDCOPY,
        HISTOGRAM,
        HORIZONTAL,
        MATH,
        MEASUREMENT,
        MISC,
        TRIGGER,
        VERTICAL,
        WAVEFORM
    } CMD_GROUPS;


    namespace CURSOR {

        typedef enum {
            FUNCTION,
            HBARS,
            MODE,
            PAIRED,
            SOURCE,
            SPLIT,
            STATE,
            VBARS
        } CMDS;

        typedef enum {
            DELTA,
            POSITION,
            UNITS
        } HBAR;

        typedef enum {
            HDELTA,
            HPOS,
            POSITION,
            UNITS,
            VDELTA
        } PAIRED;

        typedef enum {
            HDELTA,
            HPOS,
            POSITION,
            SOURCE2,
            UNITS,
            VDELTA
        } SPLIT;
    }
}

class SCPI {

public:
    SCPI();
    ~SCPI();
    std::string createSCPIString(std::vector<std::string> args);


private:


}


