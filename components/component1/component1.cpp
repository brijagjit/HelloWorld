#include <iostream>

#include "component1.h"
#include "hello.h"

void run_component1(int& counter)
{
    sayHello(Component::COMPONENT1);
    counter++;
    std::cout << "    Counter: " << counter << "\n";
}
