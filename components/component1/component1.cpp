#include <iostream>
#include "component1.h"
#include "hello.h"

void run_component1()
{
    sayHello();
    std::cout << "(called from Component1)" << std::endl;
}
