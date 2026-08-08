#include "scheduler.h"

#include "component1.h"
#include "component2.h"
#include "component3.h"

void run_scheduler()
{
    while(1)
    {
        run_component1();
        run_component2();
        run_component3();
    }
}
