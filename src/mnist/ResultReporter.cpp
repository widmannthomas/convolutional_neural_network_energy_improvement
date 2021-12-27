#include "ResultReporter.h"

template<class T>
void ResultReporter<T>::reportProbabilities(std::vector<T> vecProbabilities)
{
    m_oJsonReport["probabilities"] = vecProbabilities;
}

template<class T>
void ResultReporter<T>::reportMetaData(const MLCoreExecutionMetaData<T>& crMetaData)
{
    if(!m_oJsonReport.contains("data"))
    {
        m_oJsonReport["data"] = nlohmann::json::array();
    }

    nlohmann::json oJsonMetaData = nlohmann::json::object();
    oJsonMetaData["time_us"] = crMetaData.unTime_us;
    oJsonMetaData["probabilities"] = crMetaData.vecProbabilities;
    m_oJsonReport["data"].push_back(oJsonMetaData);
}

template<class T>
nlohmann::json ResultReporter<T>::getJsonReport() const
{
    return m_oJsonReport;
}

template<class T>
void ResultReporter<T>::reportStart()
{
    m_oJsonReport.clear();
}

template<class T>
void ResultReporter<T>::reportEnd()
{

}

template<class T>
void ResultReporter<T>::reportEndWithError()
{

}