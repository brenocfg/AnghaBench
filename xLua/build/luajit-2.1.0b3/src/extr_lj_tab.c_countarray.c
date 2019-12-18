#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
struct TYPE_3__ {scalar_t__ asize; int /*<<< orphan*/  array; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_1__ GCtab ;

/* Variables and functions */
 unsigned int LJ_MAX_ABITS ; 
 int /*<<< orphan*/  tvisnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tvref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t countarray(const GCtab *t, uint32_t *bins)
{
  uint32_t na, b, i;
  if (t->asize == 0) return 0;
  for (na = i = b = 0; b < LJ_MAX_ABITS; b++) {
    uint32_t n, top = 2u << b;
    TValue *array;
    if (top >= t->asize) {
      top = t->asize-1;
      if (i > top)
	break;
    }
    array = tvref(t->array);
    for (n = 0; i <= top; i++)
      if (!tvisnil(&array[i]))
	n++;
    bins[b] += n;
    na += n;
  }
  return na;
}