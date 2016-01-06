#pragma once
#include <functional>
#include <thread>
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

typedef std::function<void()> fn_type;

class Worker
{
public:
    Worker();
    ~Worker();

    void appendFn(fn_type fn);
    size_t getTaskCount();

    bool isEmpty();
private:
    void threadFn();

    bool m_enabled;
    std::condition_variable m_conditionView;
    std::queue<fn_type> m_functionQueue;
    std::mutex m_mutex;
    std::thread m_thread;
};
