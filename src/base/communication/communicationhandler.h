#ifndef SRC_BASE_COMMUNICATION_COMMUNICATIONHANDLER
#define SRC_BASE_COMMUNICATION_COMMUNICATIONHANDLER

#include "command.h"
#include "pico/stdlib.h"
#include <string>

#include "../json/json.h"
#include "../log/log.h"

class CommunicationHandler
{
public:
    enum class MessageType
    {
        Log,
        Report
    };

    void waitForCommand(Command& rCommand);
    void waitForData(const Command& crCommand, uint8_t* pData);

    void sendString(const MessageType ceType, const std::string& str);

    void sendJson(const MessageType ceType, const nlohmann::json& crJson);

private:
    unsigned int m_unBufferSize = 2048;
    char m_arrBuffer[2048];
};

struct LogSinkCommunicationHandler : public ILogSink
{
    LogSinkCommunicationHandler(CommunicationHandler& rCommunicationHandler)
        : m_rCommunicationHandler(rCommunicationHandler)
    {
    }
    
    void log(const std::string& strMsg) final;

private:
    CommunicationHandler& m_rCommunicationHandler;
};

#endif /* SRC_BASE_COMMUNICATION_COMMUNICATIONHANDLER */
