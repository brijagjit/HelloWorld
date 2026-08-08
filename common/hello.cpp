#include <iostream>
#include "hello.h"

void sayHello(Component component)
{
    std::cout << "Hello from " << componentName(component) << "!" << std::endl;
}
