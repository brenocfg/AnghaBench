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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  THAtomicCompareAndSwapPtrdiff (int /*<<< orphan*/  volatile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void THAtomicSetPtrdiff(ptrdiff_t volatile *a, ptrdiff_t newvalue)
{
#if defined(USE_C11_ATOMICS)
  atomic_store(a, newvalue);
#elif defined(USE_MSC_ATOMICS)
#ifdef _WIN64
  _InterlockedExchange64(a, newvalue);
#else
  _InterlockedExchange(a, newvalue);
#endif
#elif defined(USE_GCC_ATOMICS)
  __sync_lock_test_and_set(a, newvalue);
#else
  ptrdiff_t oldvalue;
  do {
    oldvalue = *a;
  } while (!THAtomicCompareAndSwapPtrdiff(a, oldvalue, newvalue));
#endif
}