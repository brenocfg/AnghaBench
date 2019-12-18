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
struct timeval {double tv_usec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ TimeType ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (scalar_t__*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static TimeType torch_Timer_realtime()
{
#ifdef _WIN32
  TimeType current;
  QueryPerformanceCounter(&current);
  return current;
#else
  struct timeval current;
  gettimeofday(&current, NULL);
  return (current.tv_sec + current.tv_usec/1000000.0);
#endif
}