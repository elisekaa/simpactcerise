#include "State.h"
#include "mutex.h"

using namespace std;

State::State()
{
        m_time        = 0;
        m_abort       = false;
        m_pAbortMutex = new Mutex();
}

State::~State() { delete m_pAbortMutex; }

void State::setAbortAlgorithm(const std::string& reason) const
{
        m_pAbortMutex->lock();
        if (!m_abort) // Keep the first abort reason
        {
                m_abort       = true;
                m_abortReason = reason;
        }
        m_pAbortMutex->unlock();
}

void State::clearAbort()
{
        m_abort       = false;
        m_abortReason = "";
}

std::string State::getAbortReason() const { return m_abortReason; }
