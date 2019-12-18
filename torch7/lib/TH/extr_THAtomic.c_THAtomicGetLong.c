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
 long atomic_load (long volatile*) ; 

long THAtomicGetLong(long volatile *a)
{
#if defined(USE_C11_ATOMICS)
  return atomic_load(a);
#else
  long value;
  do {
    value = *a;
  } while (!THAtomicCompareAndSwapLong(a, value, value));
  return value;
#endif
}