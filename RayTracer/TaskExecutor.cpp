#include "TaskExecutor.h"

using namespace RayTracer;

TaskExecutor::TaskExecutor()
{

}

TaskExecutor::TaskExecutor(int nThreadCount)
{
	CreateThreads(nThreadCount);
}

TaskExecutor::~TaskExecutor()
{
	m_requestEndAll = true;
	m_condVar.notify_all();

	for (auto& curThread : m_threadPool)
	{
		if (curThread.joinable())
		{
			curThread.join();
		}
	}
}

void TaskExecutor::AddTask(std::function<void(void)> f)
{
	std::lock_guard<std::mutex> taskPullLock(m_taskPullMutex);
	m_taskList.push(f);
	m_condVar.notify_one();
}

void TaskExecutor::Check()
{
	m_condVar.notify_one();
}

int TaskExecutor::GetQueuedTaskCount()
{
	std::lock_guard<std::mutex> taskPullLock(m_taskPullMutex);
	return (int)m_taskList.size();
}

void TaskExecutor::CreateThreads(int threadCount)
{
	for (int i = 0; i < threadCount; i++)
	{
		m_threadPool.emplace_back(&TaskExecutor::_threadMain, this);
	}
}

void TaskExecutor::_threadMain()
{
	bool done = false;

	while (!done)
	{
		std::unique_lock<std::mutex> waitLock(m_waitMutex);
		m_condVar.wait_for(waitLock, std::chrono::milliseconds(500));

		{
			std::lock_guard<std::mutex> taskPullLock(m_taskPullMutex);

			while (!m_taskList.empty())
			{
				auto nextTask = m_taskList.front();
				m_taskList.pop();

				if (nextTask)
				{
					nextTask();
				}
			}
		}

		if (m_requestEndAll)
		{
			done = true;
		}
	}
}
