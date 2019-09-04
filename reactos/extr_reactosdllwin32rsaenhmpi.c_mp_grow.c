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
struct TYPE_3__ {int alloc; scalar_t__* dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  scalar_t__ mp_digit ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int MP_MEM ; 
 int MP_OKAY ; 
 int MP_PREC ; 

__attribute__((used)) static int mp_grow (mp_int * a, int size)
{
  int     i;
  mp_digit *tmp;

  /* if the alloc size is smaller alloc more ram */
  if (a->alloc < size) {
    /* ensure there are always at least MP_PREC digits extra on top */
    size += (MP_PREC * 2) - (size % MP_PREC);

    /* reallocate the array a->dp
     *
     * We store the return in a temporary variable
     * in case the operation failed we don't want
     * to overwrite the dp member of a.
     */
    tmp = HeapReAlloc(GetProcessHeap(), 0, a->dp, sizeof (mp_digit) * size);
    if (tmp == NULL) {
      /* reallocation failed but "a" is still valid [can be freed] */
      return MP_MEM;
    }

    /* reallocation succeeded so set a->dp */
    a->dp = tmp;

    /* zero excess digits */
    i        = a->alloc;
    a->alloc = size;
    for (; i < a->alloc; i++) {
      a->dp[i] = 0;
    }
  }
  return MP_OKAY;
}