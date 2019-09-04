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

int THAtomicCompareAndSwap(int volatile *a, int oldvalue, int newvalue)
{
#if defined(USE_C11_ATOMICS)
  return atomic_compare_exchange_strong(a, &oldvalue, newvalue);
#elif defined(USE_MSC_ATOMICS)
  assert(sizeof(int) == sizeof(long));
  return (_InterlockedCompareExchange((long*)a, (long)newvalue, (long)oldvalue) == (long)oldvalue);
#elif defined(USE_GCC_ATOMICS)
  return __sync_bool_compare_and_swap(a, oldvalue, newvalue);
#elif defined(USE_PTHREAD_ATOMICS)
  int ret = 0;
  pthread_mutex_lock(&ptm);
  if(*a == oldvalue) {
    *a = newvalue;
    ret = 1;
  }
  pthread_mutex_unlock(&ptm);
  return ret;
#else
#warning THAtomic is not thread safe
  if(*a == oldvalue) {
    *a = newvalue;
    return 1;
  }
  else
    return 0;
#endif
}