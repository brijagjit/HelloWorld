#include <iostream>

#include "component3.h"
#include "hello.h"

void run_component3(int& counter)
{
    sayHello(Component::COMPONENT3);
    counter++;
    std::cout << "    Counter: " << counter << "\n";
}
