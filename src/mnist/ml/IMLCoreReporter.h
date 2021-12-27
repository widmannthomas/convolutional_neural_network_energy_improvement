#ifndef SRC_MNIST_ML_MLCOREREPORTER
#define SRC_MNIST_ML_MLCOREREPORTER

#include "pico/stdlib.h"
#include <vector>

template <class T>
struct MLCoreExecutionMetaData
{
    std::vector<T> vecProbabilities;
    uint64_t unTime_us;
    uint8_t unCycle = 1;
};

template<class T>
class IMLCoreReporter
{
public:
    virtual void reportStart() = 0;
    virtual void reportProbabilities(std::vector<T> vecProbabilities) = 0;
    virtual void reportMetaData(const MLCoreExecutionMetaData<T>& crMetaData) = 0;
    virtual void reportEnd() = 0;
    virtual void reportEndWithError() = 0;
};

#endif /* SRC_MNIST_ML_MLCOREREPORTER */
