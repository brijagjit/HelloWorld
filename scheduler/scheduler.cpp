#include "scheduler.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "component1.h"
#include "component2.h"
#include "component3.h"

int counter = 0;

// Define the tasks managed by the scheduler.
// Higher priority values run first when multiple tasks are ready.
Task tasks[] =
{
    {Component::COMPONENT1, 3, 1000, {}},
    {Component::COMPONENT2, 2, 2000, {}},
    {Component::COMPONENT3, 1, 3000, {}}
};


// Run the component associated with the task.
void run_component(Component component, int& counter)
{
    switch (component)
    {
        case Component::COMPONENT1:
            run_component1(counter);
            break;

        case Component::COMPONENT2:
            run_component2(counter);
            break;

        case Component::COMPONENT3:
            run_component3(counter);
            break;
    }
}


// Run the cooperative scheduler.
//
// The scheduler checks task timing, selects the highest-priority
// ready task, runs it, and waits for the next scheduler tick.
void run_scheduler()
{
    auto start_time = std::chrono::steady_clock::now();

    // Start all tasks immediately.
    for (auto& task : tasks)
    {
        task.next_run = start_time;
    }

    while (true)
    {
        auto now = std::chrono::steady_clock::now();

        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                now - start_time
            ).count();

        Task* highest_priority_task = nullptr;

        // Find the highest-priority ready task.
        for (auto& task : tasks)
        {
            if (now >= task.next_run)
            {
                if (highest_priority_task == nullptr ||
                    task.priority > highest_priority_task->priority)
                {
                    highest_priority_task = &task;
                }
            }
        }

        if (highest_priority_task != nullptr)
        {
            std::cout << "\nTime: " << elapsed  << " ms " << "\n";
            std::cout << "-----------------------\n";

            // Run all tasks that are ready, in priority order.
            while (highest_priority_task != nullptr)
            {
                run_component(highest_priority_task->component, counter);
            
	            highest_priority_task->next_run +=
                    std::chrono::milliseconds(
                        highest_priority_task->period_ms
                    );

                highest_priority_task = nullptr;

                for (auto& task : tasks)
                {
                    if (now >= task.next_run)
                    {
                        if (highest_priority_task == nullptr ||
                            task.priority > highest_priority_task->priority)
                        {
                            highest_priority_task = &task;
                        }
                    }
                }
            }
        }

        // Scheduler tick.
        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );
    }
}
