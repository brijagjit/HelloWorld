# HelloWorld — C++ Build, Components, Scheduling, and Threads

This project is a step-by-step exploration of building a small C++ application and gradually introducing concepts that are important in embedded and real-time software.

The project starts as a simple `HelloWorld` program and evolves into a multi-component application with:

* CMake-based builds
* Reusable libraries
* Multiple software components
* A cooperative scheduler
* Task priorities and periodic execution
* C++ threads
* Shared data between threads
* Race conditions
* Mutex-based synchronization

The project is intentionally divided into Git branches. Each branch builds on the previous one, allowing the development process to be followed as a story.

The goal is not to create a complicated application. The goal is to understand **how the architecture evolves** and why each new concept is useful.

---

# Project Progression

The branches follow this progression:

```text
helloCMake
    ↓
helloComponents
    ↓
helloScheduler
    ↓
helloThreads
```

Each branch introduces a new concept.

| Branch            | Main Concept                                                    |
| ----------------- | --------------------------------------------------------------- |
| `helloCMake`      | CMake and project structure                                     |
| `helloComponents` | Separating functionality into components                        |
| `helloScheduler`  | Cooperative scheduling, priorities, and periods                 |
| `helloThreads`    | Concurrent execution, shared data, race conditions, and mutexes |

The commits within each branch are also intended to be read in order.

---

# 1. `helloCMake` — Building the Project with CMake

The project begins with a very small C++ application.

The first goal is simply to establish a clean project structure and learn how CMake can be used to build the application.

## Starting Point

The project initially contains a basic `main.cpp` that prints:

```text
Hello World!
```

At this stage there is no scheduler, threading, or component architecture.

The focus is simply:

> How do we organize a C++ project and build it using CMake?

---

## Commit: `setting up folder structure and .gitignore`

This establishes the initial project layout and adds a `.gitignore`.

The purpose is to separate source files and build artifacts.

The important idea is that generated files should not become part of the source repository.

---

## Commit: `adding main.cpp with basic HelloWorld`

A basic C++ program is added.

The application has a single entry point:

```cpp
int main()
```

and simply prints a message.

This gives us the simplest possible application to build upon.

---

## Commit: `adding CMake`

CMake is introduced as the project's build system.

Instead of compiling the application manually with something such as:

```bash
g++ main.cpp -o hello
```

we describe the project to CMake and allow it to generate the build system.

The basic workflow becomes:

```bash
cmake ..
make
./hello
```

This introduces the distinction between:

* **Source code** — what we write
* **Build system** — how the source is compiled
* **Executable** — the resulting program

---

## Commit: `adding hello library and updating CMake`

A reusable library is introduced.

Instead of putting all functionality directly inside `main.cpp`, functionality can now be placed into a library and linked against the executable.

This introduces an important concept:

> `main.cpp` does not need to contain all of the application's functionality.

The project is beginning to separate **application logic** from the **entry point**.

---

## Commit: `updaing README`

The README is updated to document the project and its progression.

At this point, the `helloCMake` branch represents the foundation of the project.

### What to understand before moving on

By the end of `helloCMake`, you should understand:

* Basic C++ project structure
* The purpose of `main.cpp`
* What CMake does
* What a build directory is
* How libraries can be created
* How libraries are linked to an executable

Once this makes sense, move to:

```bash
git switch helloComponents
```

---

# 2. `helloComponents` — Breaking the Application into Components

The next step is to make the application more representative of a real system.

Instead of having one piece of functionality, we introduce multiple independent components.

The project now contains:

```text
components/
├── component1/
├── component2/
└── component3/
```

Each component has its own implementation and CMake configuration.

The goal is to answer:

> How can we divide a larger application into smaller pieces that can be built and managed independently?

---

## Commit: `adding component 1, setting up cmake, and calling from root`

The first component is introduced.

Component 1 has its own source files and CMake configuration.

The root CMake configuration adds the component and links it into the application.

This demonstrates that a CMake project can be hierarchical:

```text
Root CMake
    ↓
Component CMake
    ↓
Component source
```

---

## Commit: `using hello_library in component1`

Component 1 begins using the existing hello library.

This demonstrates that libraries can be shared between different parts of the application.

The dependency structure is becoming:

```text
hello executable
       |
       +--- component1
       |
       +--- hello library
```

---

## Commit: `adding components 2 and 3`

Two additional components are introduced.

The application now has three independently implemented pieces:

```text
Component 1
Component 2
Component 3
```

Each component can expose functionality through a header file while keeping its implementation in its `.cpp` file.

This introduces the idea of an interface:

```text
component1.h
     ↑
     |
main.cpp
```

while the implementation remains in:

```text
component1.cpp
```

---

## Commit: `adding cmake to component directory`

Each component receives its own CMake configuration.

This makes the project more modular and allows components to be added without putting all of their build logic into the root `CMakeLists.txt`.

---

## Commit: `adding component name enum`

An enumeration is introduced to identify components.

Conceptually:

```cpp
enum class Component
{
    COMPONENT1,
    COMPONENT2,
    COMPONENT3
};
```

This gives the application a way to refer to components programmatically rather than relying on strings.

The project is now ready to introduce something that can decide **when** components should execute.

### What to understand before moving on

By the end of `helloComponents`, you should understand:

* How a project can be divided into components
* Header vs. implementation files
* Static libraries
* CMake subdirectories
* Component dependencies
* Enumerations
* Why modularity becomes important as a system grows

The application now has multiple pieces, but there is no mechanism controlling their execution.

That is the problem addressed by the next branch.

Move to:

```bash
git switch helloScheduler
```

---

# 3. `helloScheduler` — Cooperative Scheduling

The scheduler branch introduces a major architectural change.

Instead of simply calling the components from `main()`, we introduce a scheduler responsible for deciding when components should run.

The scheduler is **cooperative**.

That means the application itself is responsible for determining when tasks run. There is no operating-system thread scheduler involved yet.

The basic architecture becomes:

```text
                  main()
                    |
                    ↓
              run_scheduler()
                    |
             +------+------+
             |      |      |
             ↓      ↓      ↓
          Task 1  Task 2  Task 3
             |      |      |
             ↓      ↓      ↓
          Comp 1  Comp 2  Comp 3
```

---

## Commit: `integrating scheduler`

The scheduler is introduced into the project.

The scheduler becomes responsible for calling the component functions rather than having `main()` directly manage the components.

This introduces the separation between:

**What should run**

```text
Component 1
Component 2
Component 3
```

and:

**When it should run**

```text
Scheduler
```

This is an important architectural distinction.

---

## Commit: `adding while(1) loop and creating build/run/kill script for hello executable`

The application is changed from a program that runs once into a continuously running application.

The scheduler now continuously checks for work.

Conceptually:

```cpp
while(true)
{
    check_tasks();
    run_ready_task();
}
```

This is a **polling architecture**.

The scheduler repeatedly checks the state of the tasks rather than waiting for an event to notify it.

---

## Commit: `adding tasks with priority and time period`

The scheduler is expanded to manage task metadata.

Each task has:

* A component
* A priority
* A period
* A next execution time

Conceptually:

```text
Component 1 → Priority 3 → 1000 ms
Component 2 → Priority 2 → 2000 ms
Component 3 → Priority 1 → 3000 ms
```

The scheduler checks whether a task is ready to run.

If multiple tasks are ready at the same time, priority determines the order.

Higher priority values run first.

For example:

```text
Priority 3 → Component 1
Priority 2 → Component 2
Priority 1 → Component 3
```

The scheduler therefore performs two important jobs:

```text
Timing
  +
Priority
```

---

## Understanding the Periods

The task periods mean:

```text
Component 1 → every 1 second
Component 2 → every 2 seconds
Component 3 → every 3 seconds
```

The expected schedule looks approximately like:

```text
Time 0:
    Component 1
    Component 2
    Component 3

Time 1:
    Component 1

Time 2:
    Component 1
    Component 2

Time 3:
    Component 1
    Component 3

Time 4:
    Component 1
    Component 2

Time 5:
    Component 1

Time 6:
    Component 1
    Component 2
    Component 3
```

At time 6, all three tasks are ready, so priority determines their order:

```text
Component 1
Component 2
Component 3
```

This demonstrates the difference between:

**Period**

> How often should a task run?

and:

**Priority**

> Which ready task should run first?

---

## Shared Counter

The scheduler branch also introduces a shared counter.

The counter is passed into the component functions:

```cpp
run_component1(counter);
run_component2(counter);
run_component3(counter);
```

Each component increments the same counter.

This is important because it creates a shared resource that will later be used to demonstrate concurrency problems.

At this stage, execution is still controlled by the cooperative scheduler.

### What to understand before moving on

By the end of `helloScheduler`, you should understand:

* What a scheduler does
* Cooperative scheduling
* Polling
* Task periods
* Task priorities
* Ready tasks
* Scheduler ticks
* Shared data
* Why a scheduler needs to keep track of task timing

Most importantly, understand that the scheduler and threads are **not the same thing**.

The scheduler is application-level logic deciding what to execute.

The next branch removes that scheduler and lets the operating system manage multiple threads.

Move to:

```bash
git switch helloThreads
```

---

# 4. `helloThreads` — Concurrent Execution

The `helloThreads` branch takes the components from the scheduler branch and changes how they execute.

The scheduler is removed.

Instead, each component runs in its own C++ thread.

The architecture becomes:

```text
                    main()
                      |
          +-----------+-----------+
          |           |           |
          ↓           ↓           ↓
      Thread 1    Thread 2    Thread 3
          |           |           |
          ↓           ↓           ↓
      Component 1 Component 2 Component 3
```

This is fundamentally different from the cooperative scheduler.

With the scheduler:

```text
Application controls execution
```

With threads:

```text
The operating system schedules the threads
```

---

## Commit: `replacing scheduler with components thread`

The scheduler is removed.

`main.cpp` creates three threads:

```cpp
std::thread thread1(run_component1, ...);
std::thread thread2(run_component2, ...);
std::thread thread3(run_component3, ...);
```

Each thread begins executing its component function independently.

This is the first point where the components can actually execute concurrently.

---

## Understanding `std::thread`

When this is executed:

```cpp
std::thread thread1(run_component1, ...);
```

the program creates a thread and tells it:

> Start executing `run_component1` using these arguments.

The main thread continues executing and creates the other threads.

Therefore, execution can look like:

```text
Main
 |
 +--- create Thread 1
 |
 +--- create Thread 2
 |
 +--- create Thread 3
 |
 +--- wait
```

while the three component threads execute independently.

---

## `join()`

The main thread calls:

```cpp
thread1.join();
thread2.join();
thread3.join();
```

`join()` means:

> Wait for this thread to finish.

Since the component threads contain infinite loops, they do not normally finish.

Therefore, `main()` waits for the threads indefinitely.

---

# Commit: `adding periodic thread execution`

Each component thread is given its own sleep period.

For example:

```text
Component 1 → 1 second
Component 2 → 2 seconds
Component 3 → 3 seconds
```

Instead of a central scheduler determining when each component executes, each thread now controls its own periodic behavior.

Conceptually:

```text
Thread 1:
    run component
    sleep 1 second
    repeat

Thread 2:
    run component
    sleep 2 seconds
    repeat

Thread 3:
    run component
    sleep 3 seconds
    repeat
```

This demonstrates an important difference from the scheduler.

The scheduler previously had one central loop:

```text
                 Scheduler
                     |
          +----------+----------+
          |          |          |
        Comp 1     Comp 2     Comp 3
```

Now each thread has its own execution loop:

```text
Thread 1 → Component 1 → sleep
Thread 2 → Component 2 → sleep
Thread 3 → Component 3 → sleep
```

---

# Shared Data and the Counter

The next step is to have all three threads access the same counter.

The counter lives in `main()`:

```cpp
int counter = 0;
```

A reference to that counter is passed to each thread:

```cpp
std::ref(counter)
```

This is important.

The threads are not receiving three separate counters.

They are all receiving a reference to the **same variable**.

Conceptually:

```text
                  counter
                     |
          +----------+----------+
          |          |          |
          ↓          ↓          ↓
       Thread 1   Thread 2   Thread 3
```

This creates our first shared resource.

---

# Commit: `adding yield and separating counter read and write to demonstrate race condition`

The counter increment is intentionally changed from:

```cpp
counter++;
```

to something conceptually equivalent to:

```cpp
int temp = counter;

std::this_thread::yield();

counter = temp + 1;
```

Why?

Because `counter++` is a **read-modify-write operation**.

Conceptually:

```text
read counter
     ↓
add 1
     ↓
write counter
```

The simplified code makes those steps visible.

`yield()` gives another runnable thread an opportunity to execute between the read and write.

This creates a race-condition window.

For example:

```text
Thread 1                 Thread 2

read counter = 10
                         read counter = 10

write counter = 11
                         write counter = 11
```

Two increments occurred, but the final value is:

```text
11
```

instead of:

```text
12
```

The update from one thread was lost.

This is a **race condition**.

---

# Why This Matters

The important lesson is that:

```cpp
counter++;
```

does not automatically mean:

> "Nobody else can touch counter while I increment it."

Multiple threads can access the same memory concurrently.

The problem is therefore not simply that the operations are separated in the source code.

The problem is:

> Multiple threads are accessing shared data without synchronization.

---

# Commit: `adding mutex lock to fix counter race condition`

A mutex is introduced to protect the shared counter.

A mutex provides mutual exclusion.

Only one thread can hold the mutex at a time.

The counter update is placed inside a protected section:

```cpp
{
    std::lock_guard<std::mutex> lock(counter_mutex);

    int temp = counter;
    std::this_thread::yield();
    counter = temp + 1;
}
```

The mutex protects the entire read-modify-write operation.

The execution now becomes:

```text
Thread 1                    Thread 2

LOCK
 |
read counter
 |
yield
 |
write counter
 |
UNLOCK
                            LOCK
                             |
                            read counter
                             |
                            yield
                             |
                            write counter
                             |
                            UNLOCK
```

Even though `yield()` still exists, Thread 2 cannot enter the protected section until Thread 1 releases the mutex.

---

# Why the Extra `{ }`?

The braces create a scope for the `lock_guard`.

```cpp
{
    std::lock_guard<std::mutex> lock(counter_mutex);

    // critical section
}
```

When the scope ends, the `lock_guard` is destroyed and automatically unlocks the mutex.

This is preferable to manually calling:

```cpp
counter_mutex.lock();
...
counter_mutex.unlock();
```

because `lock_guard` follows the C++ RAII pattern.

The mutex is automatically released when the object leaves scope.

The braces also ensure that the mutex is not held while the thread performs unrelated work such as sleeping.

---

# The Final Thread Architecture

At the end of `helloThreads`, the application has three independent threads:

```text
                           main()
                             |
                 +-----------+-----------+
                 |           |           |
                 ↓           ↓           ↓
              Thread 1    Thread 2    Thread 3
                 |           |           |
                 ↓           ↓           ↓
              Comp 1      Comp 2      Comp 3
                 |           |           |
                 +-----------+-----------+
                             |
                      shared counter
                             |
                       counter_mutex
```

Each component:

1. Runs independently in its own thread
2. Executes periodically
3. Accesses the shared counter
4. Uses the mutex when modifying the counter

---

# Scheduler vs. Threads

The two branches demonstrate two different ways of structuring concurrent-looking work.

## Cooperative Scheduler

```text
             Scheduler
                 |
       +---------+---------+
       |         |         |
     Task 1    Task 2    Task 3
       |         |         |
     Comp 1    Comp 2    Comp 3
```

The scheduler:

* Runs in one execution context
* Polls tasks
* Determines when tasks are ready
* Uses task priorities
* Controls the execution order

## Threads

```text
Thread 1 → Component 1
Thread 2 → Component 2
Thread 3 → Component 3
```

The threads:

* Execute independently
* Are scheduled by the operating system
* Can execute concurrently
* Require synchronization when sharing data

The two approaches are therefore **not mutually exclusive in general**.

A real system can use:

```text
Operating System
       |
   Threads
       |
   Scheduler
       |
    Tasks
```

However, this project intentionally separates the concepts into different branches so they can be understood individually.

---

# How to Follow the Project

The recommended way to study the project is to start from the beginning and move through the branches.

## Step 1 — Start with `helloCMake`

```bash
git switch helloCMake
```

Read the commits in order.

Focus on:

* Project structure
* CMake
* Libraries
* Build process

Ask:

> How does source code become an executable?

---

## Step 2 — Move to `helloComponents`

```bash
git switch helloComponents
```

Look at the commits added after `helloCMake`.

Focus on:

* Component organization
* Header files
* Source files
* Libraries
* CMake subdirectories

Ask:

> How can a larger application be divided into independent pieces?

---

## Step 3 — Move to `helloScheduler`

```bash
git switch helloScheduler
```

Focus on:

* Tasks
* Scheduling
* Polling
* Periods
* Priorities
* Ready tasks
* Shared data

Ask:

> How can we control when each component executes?

---

## Step 4 — Move to `helloThreads`

```bash
git switch helloThreads
```

Focus on:

* `std::thread`
* `join()`
* Concurrent execution
* Thread arguments
* Shared references
* Race conditions
* Mutexes
* `lock_guard`

Ask:

> What changes when multiple execution contexts can access the same data?

---

# Overall Story

The project can be viewed as one continuous progression:

```text
Simple Program
      ↓
CMake Build System
      ↓
Reusable Libraries
      ↓
Multiple Components
      ↓
Cooperative Scheduler
      ↓
Task Periods
      ↓
Task Priorities
      ↓
Multiple Threads
      ↓
Shared Data
      ↓
Race Condition
      ↓
Mutex Synchronization
```

Each stage introduces a problem that motivates the next stage.

We start with:

> How do I build this program?

Then:

> How do I organize it?

Then:

> How do I control when things run?

Then:

> What happens if multiple things run at the same time?

Finally:

> How do I safely share data between concurrent execution contexts?

The purpose of the project is therefore not the `HelloWorld` application itself.

The purpose is to use a small application to progressively demonstrate the architecture and problems that appear in larger systems.

