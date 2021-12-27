#ifndef SRC_MNIST_RESULTREPORTER
#define SRC_MNIST_RESULTREPORTER

#include "ml/IMLCoreReporter.h"
#include "../base/json/json.h"

template<class T>
class ResultReporter : public IMLCoreReporter<T>
{
public:
    void reportStart() override;
    void reportProbabilities(std::vector<T> vecProbabilities) override;
    void reportMetaData(const MLCoreExecutionMetaData<T>& crMetaData) override;
    void reportEnd() override;
    void reportEndWithError() override;

    nlohmann::json getJsonReport() const;

private:
    nlohmann::json m_oJsonReport;
};

template class ResultReporter<float>;

#endif /* SRC_MNIST_RESULTREPORTER */
