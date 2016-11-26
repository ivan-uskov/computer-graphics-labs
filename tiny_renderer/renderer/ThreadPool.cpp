#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threads)
{
    if (threads == 0)
    {
        threads = 1;
    }

    for (size_t i = 0; i < threads; ++i)
    {
        WorkerPtr pWorker(new Worker);
        m_workers.push_back(pWorker);
    }
}

void ThreadPool::joinAll()
{
    while (!isAllJoined())
    {
        // wait for workers
    }
}

bool ThreadPool::isAllJoined()
{
    auto working = std::find_if(m_workers.begin(), m_workers.end(), [](WorkerPtr & worker) {
        return !worker->isEmpty();
    });

    return working == m_workers.end();
}

WorkerPtr ThreadPool::getFreeWorker()
{
    WorkerPtr pWorker;
    size_t minTasks = UINT32_MAX;

    for (auto & it : m_workers)
    {
        if (it->isEmpty())
        {
            return it;
        }

        else if (minTasks > it->getTaskCount())
        {
            minTasks = it->getTaskCount();
            pWorker = it;
        }
    }
    return pWorker;
}