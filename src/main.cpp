#include <functional>
#include <mutex>
#include <thread>

#include "component1.h"
#include "component2.h"
#include "component3.h"

int main()
{
  int counter = 0;
  std::mutex counter_mutex;

  std::thread thread1(run_component1, std::ref(counter), std::ref(counter_mutex));
  std::thread thread2(run_component2, std::ref(counter), std::ref(counter_mutex));
  std::thread thread3(run_component3, std::ref(counter), std::ref(counter_mutex));

  thread1.join();
  thread2.join();
  thread3.join();

  return 0;
}
