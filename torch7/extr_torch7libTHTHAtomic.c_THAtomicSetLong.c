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

void THAtomicSetLong(long volatile *a, long newvalue)
{
#if defined(USE_C11_ATOMICS)
  atomic_store(a, newvalue);
#elif defined(USE_MSC_ATOMICS)
  _InterlockedExchange(a, newvalue);
#elif defined(USE_GCC_ATOMICS)
  __sync_lock_test_and_set(a, newvalue);
#else
  long oldvalue;
  do {
    oldvalue = *a;
  } while (!THAtomicCompareAndSwapLong(a, oldvalue, newvalue));
#endif
}