#ifndef SRC_BASE_LOG_LOG
#define SRC_BASE_LOG_LOG

#include "pico/stdlib.h"
#include <ostream>
#include <vector>

class LOG;
class TAG;

enum class LogLevel : uint8_t
{
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    NOTICE = 3,
    WARNING = 4,
    ERROR = 5,
    FATAL = 6
};


struct ILogSink
{
    virtual void log(const std::string& strMsg) = 0;
};

struct LOG_MANAGER
{
    static LOG_MANAGER& get()
    {
        static LOG_MANAGER s_oDefault;
        return s_oDefault;
    }

    LOG_MANAGER& addSink(ILogSink* pSink)
    {
        m_vecSinks.push_back(pSink);
        return *this;
    }

    void log(const std::string& strMsg)
    {
        for(auto it = std::begin(m_vecSinks); it != std::end(m_vecSinks); ++it) 
        {
            (*it)->log(strMsg);
        }
    }

private:
    LOG_MANAGER() {};
    LOG_MANAGER(const LOG_MANAGER&) = delete;
    LOG_MANAGER(LOG_MANAGER&&) = delete;
    void operator=(const LOG_MANAGER&) = delete;

    std::vector<ILogSink*> m_vecSinks;
};


struct TAG
{
    TAG(const LogLevel ceLevel)
    {
        m_strMsg += "[";
        m_strMsg += std::to_string(static_cast<int>(ceLevel));
        m_strMsg += "] ";
    }

    TAG(const char* szMsg) 
        : m_strMsg(szMsg)
    {
    }

    TAG(std::string&& strMsg) 
        : m_strMsg(std::move(strMsg))
    {
    }

    TAG(const std::string& strMsg) 
        : m_strMsg(strMsg)
    {
    }

    bool operator+(const TAG& other) const
    {
        return m_strMsg < other.m_strMsg;
    }

    const std::string& getMsg() const
    {
        return m_strMsg;
    }

private:
    std::string m_strMsg;
};

struct LOG
{
    LOG(const LogLevel ceLevel)
        : m_ceLevel(ceLevel)
    {
        operator<<(TAG(ceLevel));
    }

    ~LOG()
    {
        LOG_MANAGER::get().log(m_strMsg);
    }

    LOG& operator<<(const TAG& crTag)
    {
        m_strMsg += crTag.getMsg();
        return *this;
    }

private:
    std::string m_strMsg;
    const LogLevel m_ceLevel;
};



struct LogSinkStdOut : public ILogSink
{
    void log(const std::string& strMsg) final
    {
        printf("%s", strMsg.data());
    }
};


#define LOG_TRACE LOG(LogLevel::TRACE)
#define LOG_DEBUG LOG(LogLevel::DEBUG)
#define LOG_INFO LOG(LogLevel::INFO)
#define LOG_NOTICE LOG(LogLevel::NOTICE)
#define LOG_WARNING LOG(LogLevel::WARNING)
#define LOG_ERROR LOG(LogLevel::ERROR)
#define LOG_FATAL LOG(LogLevel::FATAL)

#endif /* SRC_BASE_LOG_LOG */
