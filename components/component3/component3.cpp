#include <iostream>
#include "component3.h"
#include "hello.h"

void run_component3()
{
    sayHello();
    std::cout << "(called from Component3)" << std::endl;
}
