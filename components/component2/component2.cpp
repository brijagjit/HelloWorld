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
        counter++;
        std::cout << "    Counter: " << counter << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
