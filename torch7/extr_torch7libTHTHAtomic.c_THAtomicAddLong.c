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
 int /*<<< orphan*/  THAtomicCompareAndSwapLong (long volatile*,long,long) ; 

long THAtomicAddLong(long volatile *a, long value)
{
#if defined(USE_C11_ATOMICS)
  return atomic_fetch_add(a, value);
#elif defined(USE_MSC_ATOMICS)
  return _InterlockedExchangeAdd(a, value);
#elif defined(USE_GCC_ATOMICS)
  return __sync_fetch_and_add(a, value);
#else
  long oldvalue;
  do {
    oldvalue = *a;
  } while (!THAtomicCompareAndSwapLong(a, oldvalue, (oldvalue + value)));
  return oldvalue;
#endif
}