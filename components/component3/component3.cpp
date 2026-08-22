#include <chrono>
#include <iostream>
#include <thread>

#include "component3.h"
#include "hello.h"

void run_component3(int& counter)
{
    while(true)
    {
        sayHello(Component::COMPONENT3);
        counter++;
        std::cout << "    Counter: " << counter << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}
