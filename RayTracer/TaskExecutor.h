#pragma once

#include <atomic>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>

namespace RayTracer
{

	class TaskExecutor
	{
	public:
		TaskExecutor();
		TaskExecutor(int nThreadCount);
		~TaskExecutor();

		void AddTask(std::function<void(void)> f);
		void Check();

		int GetQueuedTaskCount();

	private:
		static int m_threadCount;

		std::atomic<bool> m_requestEndAll;
		std::vector<std::thread> m_threadPool;
		std::mutex m_waitMutex;
		std::condition_variable m_condVar;

		std::mutex m_taskPullMutex;
		std::queue<std::function<void(void)>> m_taskList;

		void CreateThreads(int threadCount);

		void _threadMain();

	};

}