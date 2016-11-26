#pragma once
#include "Worker.h"

typedef std::shared_ptr<Worker> WorkerPtr;

class ThreadPool
{
public:

    ThreadPool(size_t threads = 1);

    template<typename FnType, typename... ArgsType>
    void runAsync(FnType fn, ArgsType... args)
    {
        getFreeWorker()->appendFn(std::bind(fn, args...));
    }

    void joinAll();

private:
    bool isAllJoined();
    WorkerPtr getFreeWorker();

    std::vector<WorkerPtr> m_workers;

};
