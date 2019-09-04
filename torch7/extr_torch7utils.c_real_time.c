#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timeval {double tv_sec; double tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static double real_time()
{
#ifdef _WIN32
  if (ticksPerSecond.QuadPart == 0)
  {
    QueryPerformanceFrequency(&ticksPerSecond);
  }
  LARGE_INTEGER current;
  QueryPerformanceCounter(&current);
  return (double)(current.QuadPart) / ticksPerSecond.QuadPart;
#else
  struct timeval current;
  gettimeofday(&current, NULL);
  return (current.tv_sec + current.tv_usec/1000000.0);
#endif
}