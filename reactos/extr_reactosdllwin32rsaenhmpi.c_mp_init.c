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
struct TYPE_3__ {int alloc; int /*<<< orphan*/  sign; scalar_t__ used; scalar_t__* dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int MP_MEM ; 
 int MP_OKAY ; 
 int MP_PREC ; 
 int /*<<< orphan*/  MP_ZPOS ; 

__attribute__((used)) static int mp_init (mp_int * a)
{
  int i;

  /* allocate memory required and clear it */
  a->dp = HeapAlloc(GetProcessHeap(), 0, sizeof (mp_digit) * MP_PREC);
  if (a->dp == NULL) {
    return MP_MEM;
  }

  /* set the digits to zero */
  for (i = 0; i < MP_PREC; i++) {
      a->dp[i] = 0;
  }

  /* set the used to zero, allocated digits to the default precision
   * and sign to positive */
  a->used  = 0;
  a->alloc = MP_PREC;
  a->sign  = MP_ZPOS;

  return MP_OKAY;
}