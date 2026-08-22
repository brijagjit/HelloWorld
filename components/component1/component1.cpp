#include <chrono>
#include <iostream>
#include <thread>

#include "component1.h"
#include "hello.h"

void run_component1(int& counter)
{
    while(true)
    {
        sayHello(Component::COMPONENT1);
        counter++;
        std::cout << "    Counter: " << counter << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
