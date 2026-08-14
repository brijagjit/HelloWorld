#pragma once

#include <chrono>

#include "component.h"

struct Task
{
  Component component;
  int priority;
  int period_ms;
  std::chrono::steady_clock::time_point next_run;
};

void run_scheduler();
