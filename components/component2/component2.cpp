#include <iostream>

#include "component2.h"
#include "hello.h"

void run_component2(int& counter)
{
    sayHello(Component::COMPONENT2);
    counter++;
    std::cout << "    Counter: " << counter << "\n";
}
