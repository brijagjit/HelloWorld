#include <iostream>
#include "component2.h"
#include "hello.h"

void run_component2()
{
    sayHello();
    std::cout << "(called from Component2)" << std::endl;
}
