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

double _logb (double __x)
{
  register double __val;
#ifdef __GNUC__
  register double __junk;
  __asm __volatile__
    ("fxtract\n\t"
     : "=t" (__junk), "=u" (__val) : "0" (__x));
#else
#pragma message ("REVIEW ME")
  __asm fld [__x];
  __asm fxtract;
  __asm fstp st(0);
  __asm fstp [__val];
#endif /*__GNUC__*/
  return __val;
}