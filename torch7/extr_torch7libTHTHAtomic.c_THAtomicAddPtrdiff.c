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

ptrdiff_t THAtomicAddPtrdiff(ptrdiff_t volatile *a, ptrdiff_t value)
{
#if defined(USE_C11_ATOMICS)
  return atomic_fetch_add(a, value);
#elif defined(USE_MSC_ATOMICS)
#ifdef _WIN64
  return _InterlockedExchangeAdd64(a, value);
#else
  return _InterlockedExchangeAdd(a, value);
#endif
#elif defined(USE_GCC_ATOMICS)
  return __sync_fetch_and_add(a, value);
#else
  ptrdiff_t oldvalue;
  do {
    oldvalue = *a;
  } while (!THAtomicCompareAndSwapPtrdiff(a, oldvalue, (oldvalue + value)));
  return oldvalue;
#endif
}