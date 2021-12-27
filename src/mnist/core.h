#ifndef SRC_MNIST_CORE
#define SRC_MNIST_CORE

#include "../base/statemachine/finitestatemachine.h"
#include "../base/communication/communicationhandler.h"

#include "ml/MLCore.h"
#include "ml/IMLCoreReporter.h"

#include "ResultReporter.h"

enum class State
{
    InitialState,
    Initialize,
    WaitForCommand,
    WaitForData,
    Executing,
    Reporting,
    Error
};

enum class Transition
{
    StartInitialization,
    NewCommand,
    WaitForData,
    Execute,
    ReportResult,
    Error
};

class CoreStateMachine
{
public:
    CoreStateMachine();

    bool init();

private:
    Transition stateInitialize();
    Transition stateWaitForCommand();
    Transition stateWaitForData();
    Transition stateExecute();
    Transition stateReportResult();

    void blinkSync(const unsigned short cunTimes) const;

    using SM = FSM::Fsm<State, State::InitialState, Transition>;
    SM m_oSM;

    ResultReporter<float>* m_pResultReporter;
    MLCore<float>* m_pMLCore;
    CommunicationHandler m_oCommunicationHandler;

    Command m_oCommand;
};

#endif /* SRC_MNIST_CORE */
