#ifndef SRC_MNIST_MLCORE
#define SRC_MNIST_MLCORE

#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/version.h"

#include "IMLCoreReporter.h"

template<class T>
class MLCore
{
public:
    MLCore(IMLCoreReporter<T>* pReporter);

    bool initModel(const unsigned char* cpModel);

    bool classify(MLCoreExecutionMetaData<T>& rMetaData);

    TfLiteTensor* getInputTensor();
    TfLiteTensor* getOutputTensor();

private:
    const tflite::Model* m_pModel;
    IMLCoreReporter<T>* m_pReporter;
    tflite::MicroInterpreter* m_pInterpreter;
    tflite::MicroErrorReporter m_oErrorReporter;
    TfLiteTensor* m_pInput = nullptr;
    TfLiteTensor* m_pOutput = nullptr;
    unsigned int m_unTensorArenaSize = 50000;
    uint8_t* m_pTensorArena = nullptr;
};

template class MLCore<float>;

#endif /* SRC_MNIST_MLCORE */
