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
struct TYPE_3__ {int alloc; scalar_t__* dp; int /*<<< orphan*/  sign; scalar_t__ used; } ;
typedef  TYPE_1__ mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MP_MEM ; 
 int MP_OKAY ; 
 int MP_PREC ; 
 int /*<<< orphan*/  MP_ZPOS ; 

__attribute__((used)) static int mp_init_size (mp_int * a, int size)
{
  int x;

  /* pad size so there are always extra digits */
  size += (MP_PREC * 2) - (size % MP_PREC);

  /* alloc mem */
  a->dp = HeapAlloc(GetProcessHeap(), 0, sizeof (mp_digit) * size);
  if (a->dp == NULL) {
    return MP_MEM;
  }

  /* set the members */
  a->used  = 0;
  a->alloc = size;
  a->sign  = MP_ZPOS;

  /* zero the digits */
  for (x = 0; x < size; x++) {
      a->dp[x] = 0;
  }

  return MP_OKAY;
}