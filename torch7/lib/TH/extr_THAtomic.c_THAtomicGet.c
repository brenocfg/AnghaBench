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
 int atomic_load (int volatile*) ; 

int THAtomicGet(int volatile *a)
{
#if defined(USE_C11_ATOMICS)
  return atomic_load(a);
#else
  int value;
  do {
    value = *a;
  } while (!THAtomicCompareAndSwap(a, value, value));
  return value;
#endif
}