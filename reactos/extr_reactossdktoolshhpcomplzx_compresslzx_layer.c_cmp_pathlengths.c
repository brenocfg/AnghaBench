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
struct h_elem {scalar_t__ pathlength; int sym; } ;

/* Variables and functions */

__attribute__((used)) static int
cmp_pathlengths(const void *in_a, const void *in_b)
{
  const struct h_elem *a = in_a;
  const struct h_elem *b = in_b;
  
  if (a->pathlength == b->pathlength)
#if 0
    return a->sym - b->sym;
#else
  /* see note on canonical pathlengths */
    return b->sym - a->sym;
#endif
  return b->pathlength - a->pathlength;
}