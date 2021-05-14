#include <iostream>
#include "ThreadPool.hpp"
#include <cassert>

struct A {
  int a = 0;
};

int fooI(const int i) {
  return i;
}

void test_vector() {
  ThreadPool pool(2);
  std::vector<int> log;
  for (int i = 0; i < 10; i++) {
    auto task = pool.exec(fooI, i);
    log.push_back(task.get());
  }
  std::vector res({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
  for (size_t i = 0; i < res.size(); i++)
    assert(log[i] == res[i]);
}

void test_threads() {
  ThreadPool pool(4);
  std::vector<std::future<std::string>> results;

  for (int i = 0; i < 10; i++) {
    results.emplace_back(
        pool.exec([i] {
          std::cout << "start task N " << i << ", thread id=" << std::this_thread::get_id() << std::endl;
          std::this_thread::sleep_for(std::chrono::milliseconds(rand()%100));
          std::cout << " end  task N " << i << ", thread id=" << std::this_thread::get_id() << std::endl;
          return std::string("\n");
        })
    );
  }
}

void foo0() {
  std::cout << "TEST_1.0 RESULT: TEST WITHOUT ARGUMENTS IS COMPLETED" << std::endl;
}

void foo1(int temp) {
  std::cout << "TEST_1.1 RESULT: TEST WITH ARGUMENTS IS COMPLETED. Get argument: " << temp << std::endl;
}

void foo2(const A &value, int num, std::string str) {
  int temp1 = num;
  std::string temp2 = str;
  std::cout << "TEST_1.2 RESULT: TEST WITH ARGUMENTS IS COMPLETED. Get arguments: " << value.a << " " << temp1 << " "
            << temp2 << std::endl;
}

int foo4() {
  return 0;
}

int foo5(int num) {
  return num;
}

std::thread::id foo6() {
  return std::this_thread::get_id();
}

void test_different_arguments() {
  ThreadPool pool(4);

  auto task0 = pool.exec(foo0);
  task0.get();

  auto task1 = pool.exec(foo1, 100);
  task1.get();

  auto task2 = pool.exec(foo2, A(), 100, "100");
  task2.get();

  auto task3 = pool.exec([]() {
    std::cout << "TEST_1.3 RESULT: TEST WITH LAMBDA-FUNCTION IS COMPLETED" << std::endl;;
  });
  task3.get();

  auto task4 = pool.exec(foo4);
  assert(task4.get() == 0);
  std::cout << "TEST_1.4 RESULT: TEST WITH INT FUNCTION IS COMPLETED" << std::endl;

  auto task5 = pool.exec(foo5, 5);
  std::cout << "TEST_1.5 RESULT: TEST WITH INT FUNC<<TION IS COMPLETED. GET VALUE: " << task5.get() << std::endl;

  auto task6 = pool.exec(foo6);
  assert(task6.get() != std::this_thread::get_id());
  std::cout << "TEST_1.6 RESULT: TEST THREAD ID IS COMPLETED" << std::endl;

  std::cout << "TEST_1 RESULT: ALL TESTS ARE COMPLETED" << std::endl;
}

void one_thread_test() {
  ThreadPool pool(1);
  std::vector<int> temp;
  for (int i = 0; i < 1500; i++)
    temp.push_back(i);
  for (int i = 0; i < 1500; i++)
    assert(temp[i] == i);

  std::cout << "TEST_3 RESULT: ONE THREAD TEST IS COMPLETED" << std::endl;
}

int main() {
  test_vector();
  test_different_arguments();
  test_threads();
  std::cout << "TEST_2 RESULT: THREADS TEST IS COMPLETED" << std::endl;
  one_thread_test();

  return 0;
}
