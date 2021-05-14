ThreadPool::ThreadPool() {
  is_finish = false;
  size = std::thread::hardware_concurrency();
  for (size_t i = 0; i < size; ++i) {
    threads.emplace_back(std::thread([this] { this->run_thread(); }));
  }
}

ThreadPool::ThreadPool(size_t pool_Size) {
  is_finish = false;
  size = pool_Size;
  for (size_t i = 0; i < size; ++i) {
    threads.emplace_back(std::thread([this] { this->run_thread(); }));
  }

}

ThreadPool::~ThreadPool() {
  is_finish = true;
  new_task.notify_all();
  for (size_t i = 0; i < size; ++i) {
    threads[i].join();
  }

}

void ThreadPool::run_thread() {
  std::unique_lock<std::mutex> lock(mutex);
  while (!is_finish || tasks.size() != 0) {
    if (tasks.size() != 0) {
      auto task = std::move(tasks.front());
      tasks.pop();
      lock.unlock();
      task();
      lock.lock();
    } else {
      new_task.wait(lock);
    }
  }
}

template<class Func, class... Args>
auto ThreadPool::exec(Func func, Args...args) -> std::future<decltype(func(args...))> {
  auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>
      (std::packaged_task<decltype(func(args...))()>(std::move(std::bind(func, args...))));
  auto res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(mutex);
    tasks.emplace([task]() {
      (*task)();
    });
  }
  new_task.notify_one();
  return res;
}