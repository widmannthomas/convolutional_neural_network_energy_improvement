#include "core.h"

#include "pico/stdlib.h"
#include <vector>

#include "../base/log/log.h"
#include "train/model.h"

const uint LED_PIN = 25;

CoreStateMachine::CoreStateMachine()
    : m_pResultReporter(new ResultReporter<float>())
    , m_pMLCore(new MLCore<float>(m_pResultReporter))
{
}

bool CoreStateMachine::init()
{
    LOG_MANAGER::get().addSink(new LogSinkCommunicationHandler(m_oCommunicationHandler));

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    blinkSync(3);

    LOG_INFO << "Test environment.\n";
    LOG_INFO << "Thomas Widmann.\n";
    
    std::vector<SM::Trans> vecTransitions =
    {
        // from state                to state                  trigger                        guard       action
        { State::InitialState,       State::Initialize,        Transition::StartInitialization, nullptr,    nullptr },
        { State::Initialize,         State::WaitForCommand,    Transition::NewCommand,          nullptr,    nullptr },
        { State::WaitForCommand,     State::WaitForData,       Transition::WaitForData,         nullptr,    nullptr },
        { State::WaitForCommand,     State::Executing,         Transition::Execute,             nullptr,    nullptr },
        { State::WaitForData,        State::Executing,         Transition::Execute,             nullptr,    nullptr },
        { State::Executing,          State::WaitForCommand,    Transition::NewCommand,          nullptr,    nullptr },
        { State::Executing,          State::Reporting,         Transition::ReportResult,        nullptr,    nullptr },
        { State::Reporting,          State::WaitForCommand,    Transition::NewCommand,        nullptr,    nullptr },
    };

    m_oSM.add_transitions(vecTransitions);

    LOG_INFO << "Start state machine. Current state: " << std::to_string(int(m_oSM.state())) << "\n";

    Transition eNextTransition = Transition::StartInitialization;

    for(;;)
    {   
        const State ceCurrentState(m_oSM.state());
        LOG_INFO << "New state: " << std::to_string(int(ceCurrentState)) << "\n";

        switch(ceCurrentState)
        {
            case State::InitialState: eNextTransition = Transition::StartInitialization; break;
            case State::WaitForData: eNextTransition = stateWaitForData(); break;
            case State::WaitForCommand: eNextTransition = stateWaitForCommand(); break;
            case State::Initialize: eNextTransition = stateInitialize(); break;
            case State::Executing: eNextTransition = stateExecute(); break;
            case State::Reporting: eNextTransition = stateReportResult(); break;
            case State::Error:
            return false;
            break;
        }

        const FSM::Fsm_Errors ceError(m_oSM.execute(eNextTransition));
        switch(ceError)
        {
            case FSM::Fsm_Errors::Fsm_NoMatchingTrigger:
                LOG_WARNING << "Unable to trigger transition <" 
                            << std::to_string(int(eNextTransition)) 
                            << "> from state: " 
                            << std::to_string(int(ceCurrentState)) << "\n";
                break;
            case FSM::Fsm_Errors::Fsm_Success:
                break;
        }
    }
    

    return true;
}

Transition CoreStateMachine::stateInitialize() 
{
    if(!m_pMLCore->initModel(g_model))
    {
        return Transition::Error;
    }

    return Transition::NewCommand;
}

Transition CoreStateMachine::stateWaitForCommand()
{
    m_oCommunicationHandler.waitForCommand(m_oCommand);

    switch(m_oCommand.eType)
    {
        case CommandType::ClassifyExistingData: 
            return Transition::Execute;
        break;
        case CommandType::ReceiveDataAndClassify: 
            return Transition::WaitForData;
        break;
    }

    return Transition::Error;
}

Transition CoreStateMachine::stateWaitForData() 
{
    TfLiteTensor* pInput = m_pMLCore->getInputTensor();
    m_oCommunicationHandler.waitForData(m_oCommand, pInput->data.uint8);
    LOG_INFO << "Received data\n";

    /*
    for(int i = 0; i < 3; i++) {
        LOG_INFO << std::to_string(float(pInput->data.f[i]));
    }
    */

    return Transition::Execute;
}

Transition CoreStateMachine::stateExecute() 
{
    switch(m_oCommand.eType)
    {
        case CommandType::ReceiveDataAndClassify:
        case CommandType::ClassifyExistingData:
            break;
    }

    m_pResultReporter->reportStart();

    for(uint8_t n = 0; n < m_oCommand.unCount; n++)
    {
        MLCoreExecutionMetaData<float> oMetaData;
        std::vector<float> vecProbabilities;
        oMetaData.unCycle = n;

        if(!m_pMLCore->classify(oMetaData))
        {
            m_pResultReporter->reportEndWithError();
            return Transition::Error;
        }

        m_pResultReporter->reportMetaData(oMetaData);

        std::ostringstream oStringStream;
        std::copy(vecProbabilities.begin(), vecProbabilities.end(), std::ostream_iterator<float>(oStringStream, ","));

        //LOG_DEBUG << "Probabilities: " << oStringStream.str() << "\n";
    }

    m_pResultReporter->reportEnd();

    return Transition::ReportResult;
}

Transition CoreStateMachine::stateReportResult()
{
    const nlohmann::json coReport(m_pResultReporter->getJsonReport());
    m_oCommunicationHandler.sendJson(CommunicationHandler::MessageType::Report, coReport);

    return Transition::NewCommand;
}

void CoreStateMachine::blinkSync(const unsigned short cunTimes) const 
{
    for(unsigned short i = 0; i < cunTimes; i++) 
    {
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);
        sleep_ms(1000);
    }
}




