enum DataEncoding {
    DATA_ENCODING_ASCII,
    DATA_ENCODING_FASTEST,
    DATA_ENCODING_RIB,
    DATA_ENCODING_RPB,
    DATA_ENCODING_FPB,
    DATA_ENCODING_SRI,
    DATA_ENCODING_SRP,
    DATA_ENCODING_SFP,
    DATA_ENCODING_INVALID
};

enum ChannelSource {
    CHANNEL_SRC_CH1,
    CHANNEL_SRC_CH2,
    CHANNEL_SRC_CH3,
    CHANNEL_SRC_CH4,
    CHANNEL_SRC_INVALID
};

enum DataWidth {
    DATA_WIDTH_1,
    DATA_WIDTH_2,
    DATA_WIDTH_INVALID
};



namespace EnumMap {

    static const std::map<std::string, DataEncoding> EncodingMap = 
    {
        {"ASCII",     DATA_ENCODING_ASCII},
        {"FASTEST",   DATA_ENCODING_FASTEST},
        {"RIBINARY",  DATA_ENCODING_RIB},
        {"RPBINARY",  DATA_ENCODING_RPB},
        {"FPBINARY",  DATA_ENCODING_FPB},
        {"SRIBINARY", DATA_ENCODING_SRI},
        {"SRPBINARY", DATA_ENCODING_SRP},
        {"SFPBINARY", DATA_ENCODING_SFP}
    };

    static const std::map<std::string, ChannelSource> ChannelSrcMap = 
    {
        {"CH1", CHANNEL_SRC_CH1},
        {"CH2", CHANNEL_SRC_CH2},
        {"CH3", CHANNEL_SRC_CH3},
        {"CH4", CHANNEL_SRC_CH4}
    };

    static const std::map<std::string, DataWidth> DataWidthMap = 
    {
        {"1", DATA_WIDTH_1},
        {"2", DATA_WIDTH_2}
    };
};
