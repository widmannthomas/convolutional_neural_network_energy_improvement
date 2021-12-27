#include "communicationhandler.h"
#include "uart_helper.h"
#include "../json/json.h"
#include "../log/log.h"

#include "pico/stdlib.h"

void CommunicationHandler::waitForCommand(Command& rCommand) 
{
    uart_read_line(m_arrBuffer, m_unBufferSize);

    LOG_DEBUG << "Received " << m_arrBuffer << "\n";

    nlohmann::json oJsonPayload = nlohmann::json::parse(m_arrBuffer);
    if(oJsonPayload.contains("command"))
    {
        rCommand.eType = oJsonPayload["command"];
    }

    if(oJsonPayload.contains("ds"))
    {
        rCommand.unDataSize = oJsonPayload["ds"];
    }

    if(oJsonPayload.contains("repeat"))
    {
        rCommand.unCount = oJsonPayload["repeat"];
    }

    LOG_INFO << "Received command with type: " << std::to_string(int(rCommand.eType)) << "\n";
}

void CommunicationHandler::waitForData(const Command& crCommand, uint8_t* pData) 
{
    unsigned int unReceived = 0; 
    int nBuffer = 0;

    for(; unReceived < crCommand.unDataSize; unReceived++)
    {
        while((nBuffer = getchar_timeout_us(0)) == PICO_ERROR_TIMEOUT) { }

        pData[unReceived] = nBuffer;
    }
}

void CommunicationHandler::sendString(const MessageType ceType, const std::string& str) 
{
    nlohmann::json oJson;
    oJson["type"] = ceType;
    oJson["payload"] = str;

    printf("%s\n", oJson.dump().data());
}

void CommunicationHandler::sendJson(const MessageType ceType, const nlohmann::json& crJson) 
{
    nlohmann::json oJsonPayload;
    oJsonPayload["type"] = ceType;
    oJsonPayload["payload"] = crJson;

    printf("%s\n", oJsonPayload.dump().data());
}


void LogSinkCommunicationHandler::log(const std::string& strMsg) 
{
    m_rCommunicationHandler.sendString(CommunicationHandler::MessageType::Log, strMsg);
}
