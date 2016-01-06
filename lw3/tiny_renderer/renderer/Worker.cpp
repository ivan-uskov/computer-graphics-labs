#include "Worker.h"

Worker::Worker()
    : m_enabled(true)
    , m_functionQueue()
    , m_thread(&Worker::threadFn, this)
{}

Worker::~Worker()
{
    m_enabled = false;
    m_conditionView.notify_one();
    m_thread.join();
}

void Worker::appendFn(fn_type fn)
{
    std::unique_lock<std::mutex> locker(m_mutex);
    m_functionQueue.push(fn);
    m_conditionView.notify_one();
}

size_t Worker::getTaskCount()
{
    std::unique_lock<std::mutex> locker(m_mutex);
    return m_functionQueue.size();
}

bool Worker::isEmpty()
{
    std::unique_lock<std::mutex> locker(m_mutex);
    return m_functionQueue.empty();
}

void Worker::threadFn()
{
    while (m_enabled)
    {
        std::unique_lock<std::mutex> locker(m_mutex);

        m_conditionView.wait(locker, [&]()
        {
            return !m_functionQueue.empty() || !m_enabled; 
        });

        while (!m_functionQueue.empty())
        {
            auto fn = m_functionQueue.front();
            locker.unlock();
            fn();
            locker.lock();
            m_functionQueue.pop();
        }
    }
}