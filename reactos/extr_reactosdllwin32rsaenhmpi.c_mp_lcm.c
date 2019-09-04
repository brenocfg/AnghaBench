#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__ mp_int ;

/* Variables and functions */
 scalar_t__ MP_LT ; 
 int MP_OKAY ; 
 int /*<<< orphan*/  MP_ZPOS ; 
 int /*<<< orphan*/  mp_clear_multi (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_cmp_mag (TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_div (TYPE_1__ const*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mp_gcd (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__*) ; 
 int mp_init_multi (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mp_mul (TYPE_1__ const*,TYPE_1__*,TYPE_1__*) ; 

int mp_lcm (const mp_int * a, const mp_int * b, mp_int * c)
{
  int     res;
  mp_int  t1, t2;


  if ((res = mp_init_multi (&t1, &t2, NULL)) != MP_OKAY) {
    return res;
  }

  /* t1 = get the GCD of the two inputs */
  if ((res = mp_gcd (a, b, &t1)) != MP_OKAY) {
    goto __T;
  }

  /* divide the smallest by the GCD */
  if (mp_cmp_mag(a, b) == MP_LT) {
     /* store quotient in t2 so that t2 * b is the LCM */
     if ((res = mp_div(a, &t1, &t2, NULL)) != MP_OKAY) {
        goto __T;
     }
     res = mp_mul(b, &t2, c);
  } else {
     /* store quotient in t2 so that t2 * a is the LCM */
     if ((res = mp_div(b, &t1, &t2, NULL)) != MP_OKAY) {
        goto __T;
     }
     res = mp_mul(a, &t2, c);
  }

  /* fix the sign to positive */
  c->sign = MP_ZPOS;

__T:
  mp_clear_multi (&t1, &t2, NULL);
  return res;
}