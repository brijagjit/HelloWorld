#include <chrono>
#include <iostream>
#include <thread>

#include "component2.h"
#include "hello.h"

void run_component2(int& counter)
{
    while(true)
    {
        sayHello(Component::COMPONENT2);

        int temp = counter;
        std::this_thread::yield();
        counter = temp + 1;
        std::cout << "    Counter: " << counter << " - (from Component 2)\n";

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
