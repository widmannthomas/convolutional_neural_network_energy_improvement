#include "MLCore.h"

#include <iostream>
#include "pico/stdlib.h"

#include "../base/log/log.h"

#define PIN_TRIGGER 22

template<class T>
MLCore<T>::MLCore(IMLCoreReporter<T>* pReporter)
    : m_pReporter(pReporter)
{
    gpio_init(PIN_TRIGGER);
    gpio_set_dir(PIN_TRIGGER, GPIO_OUT);
}

template<class T>
bool MLCore<T>::initModel(const unsigned char *cpModel)
{
    m_pModel = tflite::GetModel(cpModel);

    if (m_pModel->version() != TFLITE_SCHEMA_VERSION)
    {
        LOG_ERROR << "Version " << std::to_string(m_pModel->version()) << " is not supported!\n";
        return false;
    }

    m_pTensorArena = new uint8_t[m_unTensorArenaSize];

    tflite::AllOpsResolver oResolver;
    m_pInterpreter = new tflite::MicroInterpreter(m_pModel, oResolver, m_pTensorArena, m_unTensorArenaSize, &m_oErrorReporter);

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = m_pInterpreter->AllocateTensors();
    if (allocate_status != kTfLiteOk)
    {
        LOG_ERROR << "Unable to allocate tensors!\n";
        return false;
    }

    m_pInput = m_pInterpreter->input(0);
    m_pOutput = m_pInterpreter->output(0);

    LOG_DEBUG << "Input type: " << std::to_string(int(m_pInput->type)) << "\n";
    LOG_DEBUG << "Input dims size: " << std::to_string(int(m_pInput->dims->size)) << "\n";
    for(short i = 0; i < m_pInput->dims->size; i++)
    {
        LOG_DEBUG << "Input dim (" << std::to_string(int(i)) << ") = " << std::to_string(int(m_pInput->dims->data[i])) << "\n";
    }

    /*
    printf("Input dims: (");
    for (int n = 0; n < m_pInput->dims->size; n++)
    {
        printf("%d ", m_pInput->dims->data[n]);
    }
    printf(")\n");
    */

    LOG_DEBUG << "Output type: " << std::to_string(int(m_pOutput->type)) << "\n";
    LOG_DEBUG << "Output dims size: " << std::to_string(int(m_pOutput->dims->size)) << "\n";
    for(short i = 0; i < m_pOutput->dims->size; i++)
    {
        LOG_DEBUG << "Output dim (" << std::to_string(int(i)) << ") = " << std::to_string(int(m_pOutput->dims->data[i])) << "\n";
    }
    
    /*
    printf("Output dims: (");
    for (int n = 0; n < m_pOutput->dims->size; n++)
    {
        printf("%d ", m_pOutput->dims->data[n]);
    }
    printf(")\n");
    */

    return true;
}

template<class T>
bool MLCore<T>::classify(MLCoreExecutionMetaData<T>& rMetaData)
{
    assert(rMetaData.vecProbabilities.size() == 0);

    const absolute_time_t coTimeStart = get_absolute_time();

    gpio_put(PIN_TRIGGER, 1);
    const TfLiteStatus coStatus = m_pInterpreter->Invoke();
    if(coStatus != kTfLiteOk)
    {
        gpio_put(PIN_TRIGGER, 0);
        return false;
    }

    gpio_put(PIN_TRIGGER, 0);

    const absolute_time_t coTimeStop = get_absolute_time();
    rMetaData.unTime_us = absolute_time_diff_us(coTimeStart, coTimeStop);

    for (int n = 0; n < m_pOutput->dims->data[1]; n++)
    {
        const float cdValue(m_pOutput->data.f[n]);
        rMetaData.vecProbabilities.push_back(cdValue);
    }

    return true;
}

template<class T>
TfLiteTensor *MLCore<T>::getInputTensor()
{
    return m_pInput;
}

template<class T>
TfLiteTensor *MLCore<T>::getOutputTensor()
{
    return m_pOutput;
}
