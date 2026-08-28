#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "component1.h"
#include "hello.h"

void run_component1(int& counter, std::mutex& counter_mutex)
{
    while(true)
    {
        sayHello(Component::COMPONENT1);
        {
            std::lock_guard<std::mutex> lock(counter_mutex);
            int temp = counter;
            std::this_thread::yield();
            counter = temp + 1;
            std::cout << "    Counter: " << counter << " - (from Component 1)\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
