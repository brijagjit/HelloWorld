#include <hello.h>
#include <component1.h>
#include <component2.h>
#include <component3.h>

int main()
{
    sayHello(Component::SYSTEM);
    run_component1();
    run_component2();
    run_component3();

    return 0;
}
