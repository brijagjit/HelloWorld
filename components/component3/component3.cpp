#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "component3.h"
#include "hello.h"

void run_component3(int& counter, std::mutex& counter_mutex)
{
    while(true)
    {
        sayHello(Component::COMPONENT3);
        {
            std::lock_guard<std::mutex> lock(counter_mutex);
            int temp = counter;
            std::this_thread::yield();
            counter = temp + 1;
            std::cout << "    Counter: " << counter << " - (from Component 3)\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}