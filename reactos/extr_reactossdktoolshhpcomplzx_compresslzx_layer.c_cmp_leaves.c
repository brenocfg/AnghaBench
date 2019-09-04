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
struct h_elem {scalar_t__ freq; int sym; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_leaves(const void *in_a, const void *in_b)
{
  const struct h_elem *a = in_a;
  const struct h_elem *b = in_b;
  
  if (!a->freq && b->freq)
    return 1;
  if (a->freq && !b->freq)
    return -1;
  
  if (a->freq == b->freq)
    return a->sym - b->sym;
      
  return a->freq - b->freq;
}