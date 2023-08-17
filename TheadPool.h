#pragma once

#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <functional>
#include <iostream>

template<typename T>
class SyncQueue
{
public:
	SyncQueue(int maxSize)
		:m_needStop(0),
		m_maxSize(maxSize) {};

	void put(const T& task) {
		std::unique_lock<std::mutex> locker(m_mutex);
		//while (m_queue.size() == m_maxSize) {
		//	cout << "queue is full, waiting..." << endl;
		//	m_notFull.wait();
		//}
		m_notFull.wait(locker, [this] { return m_needStop || m_queue.size() != m_maxSize; });
		if (m_needStop) {
			return;
		}
		m_queue.push(task);
		m_notEmpty.notify_one();
	}

	void put(T&& task) {
		std::unique_lock<std::mutex> locker(m_mutex);
		//while (m_queue.size() == m_maxSize) {
		//	cout << "queue is full, waiting..." << endl;
		//	m_notFull.wait();
		//}
		m_notFull.wait(locker, [this] { return m_needStop || m_queue.size() != m_maxSize; });
		if (m_needStop) {
			return;
		}
		m_queue.push(std::forward<T>(task));
		m_notEmpty.notify_one();
	}

	void take(T& task) {
		std::unique_lock<std::mutex> locker(m_mutex);
		//while (m_queue.empty()) {
		//	cout << "queue is empty, waiting..." << endl;
		//	m_notEmpty.wait();
		//}
		m_notEmpty.wait(locker, [this] { return m_needStop || !m_queue.empty(); });
		if (m_needStop) {
			task = [] {};
			return;
		}
		task = m_queue.front();
		m_queue.pop();
		m_notFull.notify_one();
	}

	// 队列的终止函数，
	void stop() {
		{
			std::lock_guard<std::mutex> locker(m_mutex);
			m_needStop = 1;
		}// reset mutex
		m_notEmpty.notify_all();
		m_notFull.notify_all();
	}

	bool empty() const { return m_queue.empty(); };
	size_t size() const { return m_queue.size(); };


private:
	bool					m_needStop;
	int						m_maxSize;
	std::queue<T>			m_queue;
	std::mutex				m_mutex;
	std::condition_variable m_notFull;
	std::condition_variable m_notEmpty;
};


const int MaxTaskNum = 10;
using namespace std;
class ThreadPool {
public:
	using Task = std::function<void()>;
	ThreadPool(int numThreads = std::thread::hardware_concurrency())
		:m_queue(MaxTaskNum),
		m_planNum(0),
		m_complatedNum(0)
	{
		start(numThreads);
	}

	~ThreadPool() {
		stop();
	}

	// 终止函数，call_once 确保不同线程也只会被调用一次。
	void stop() {
		call_once(m_flag, [this] { stopThreadPool(); });
	}

	// 终止线程池， 清空任务队列，然后等待当前所有线程执行完毕
	void stopThreadPool() {
		m_queue.stop();
		m_running = 0;
		for (auto thre : m_threadPool) {
			if (thre) {
				thre->join();
			}
		}
		m_threadPool.clear();
	}

	// 根据线程数，开启对应数量的执行任务的线程
	void start(int numThreads) {
		m_running = 1;
		for (int i = 0; i < numThreads; i++) {
			m_threadPool.push_back(make_shared<thread>(&ThreadPool::runThread, this));
		}
	}

	// 运行线程，持续从任务队列中拿取任务，并执行
	void runThread() {
		while (m_running) {
			Task t;
			m_queue.take(t); // you wen ti
			t();
			m_complatedNum++;
		}
	}

	// 添加任务到同步队列，并计划任务量+1
	void addTask(const Task& t) {
		m_queue.put(t);
		m_planNum++;
	}
	void addTask(Task&& t) {
		m_queue.put(forward<Task>(t));
		m_planNum++;
	}

	// 检查计划任务量是否等于已完成任务量，如果等于则判定任务结束（需要保证所有任务都已添加）
	bool isAllFinished() {
		return m_planNum == m_complatedNum;
	}

private:
	SyncQueue<Task>		m_queue;
	std::list<std::shared_ptr<std::thread>>  m_threadPool;
	atomic_bool			m_running;
	once_flag			m_flag;
	atomic_int			m_planNum;
	atomic_int			m_complatedNum;
};
