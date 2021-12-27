#ifndef SRC_BASE_COMMUNICATION_COMMAND
#define SRC_BASE_COMMUNICATION_COMMAND

enum class CommandType
{
    ReceiveDataAndClassify,
    ClassifyExistingData
};

struct Command
{
    CommandType eType;
    unsigned short unCount = 1;
    unsigned int unDataSize = 0;
};

#endif /* SRC_BASE_COMMUNICATION_COMMAND */
