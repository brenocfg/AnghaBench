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

/* Variables and functions */
 int /*<<< orphan*/  THAtomicCompareAndSwap (int volatile*,int,int) ; 

int THAtomicAdd(int volatile *a, int value)
{
#if defined(USE_C11_ATOMICS)
  return atomic_fetch_add(a, value);
#elif defined(USE_MSC_ATOMICS)
  assert(sizeof(int) == sizeof(long));
  return _InterlockedExchangeAdd((long*)a, value);
#elif defined(USE_GCC_ATOMICS)
  return __sync_fetch_and_add(a, value);
#else
  int oldvalue;
  do {
    oldvalue = *a;
  } while (!THAtomicCompareAndSwap(a, oldvalue, (oldvalue + value)));
  return oldvalue;
#endif
}