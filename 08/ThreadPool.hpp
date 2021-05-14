#pragma once

#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <thread>
#include <queue>
#include <functional>
#include <future>

class ThreadPool {
 private:
  std::vector<std::thread> threads;
  std::queue<std::function<void()> > tasks;
  std::atomic<bool> is_finish;
  std::mutex mutex;
  std::condition_variable new_task;
  size_t size;

 public:
  ThreadPool();
  ~ThreadPool();

  void run_thread();

  explicit ThreadPool(size_t pool_Size);

  template<class Func, class... Args>
  auto exec(Func func, Args...args) -> std::future<decltype(func(args...))>;
};

#include "ThreadPool.tpp"
