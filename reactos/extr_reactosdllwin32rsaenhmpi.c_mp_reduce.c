#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_1__ ;

/* Type definitions */
struct TYPE_34__ {int used; } ;
typedef  TYPE_1__ mp_int ;
typedef  int mp_digit ;

/* Variables and functions */
 int DIGIT_BIT ; 
 scalar_t__ MP_LT ; 
 int MP_OKAY ; 
 int mp_add (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clear (TYPE_1__*) ; 
 scalar_t__ mp_cmp (TYPE_1__*,TYPE_1__ const*) ; 
 scalar_t__ mp_cmp_d (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mp_init_copy (TYPE_1__*,TYPE_1__*) ; 
 int mp_lshd (TYPE_1__*,int) ; 
 int mp_mod_2d (TYPE_1__*,int,TYPE_1__*) ; 
 int mp_mul (TYPE_1__*,TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_rshd (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mp_set (TYPE_1__*,int) ; 
 int mp_sub (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int s_mp_mul_digs (TYPE_1__*,TYPE_1__ const*,TYPE_1__*,int) ; 
 int s_mp_mul_high_digs (TYPE_1__*,TYPE_1__ const*,TYPE_1__*,int) ; 
 int s_mp_sub (TYPE_1__*,TYPE_1__ const*,TYPE_1__*) ; 

int
mp_reduce (mp_int * x, const mp_int * m, const mp_int * mu)
{
  mp_int  q;
  int     res, um = m->used;

  /* q = x */
  if ((res = mp_init_copy (&q, x)) != MP_OKAY) {
    return res;
  }

  /* q1 = x / b**(k-1)  */
  mp_rshd (&q, um - 1);         

  /* according to HAC this optimization is ok */
  if (((unsigned long) um) > (((mp_digit)1) << (DIGIT_BIT - 1))) {
    if ((res = mp_mul (&q, mu, &q)) != MP_OKAY) {
      goto CLEANUP;
    }
  } else {
    if ((res = s_mp_mul_high_digs (&q, mu, &q, um - 1)) != MP_OKAY) {
      goto CLEANUP;
    }
  }

  /* q3 = q2 / b**(k+1) */
  mp_rshd (&q, um + 1);         

  /* x = x mod b**(k+1), quick (no division) */
  if ((res = mp_mod_2d (x, DIGIT_BIT * (um + 1), x)) != MP_OKAY) {
    goto CLEANUP;
  }

  /* q = q * m mod b**(k+1), quick (no division) */
  if ((res = s_mp_mul_digs (&q, m, &q, um + 1)) != MP_OKAY) {
    goto CLEANUP;
  }

  /* x = x - q */
  if ((res = mp_sub (x, &q, x)) != MP_OKAY) {
    goto CLEANUP;
  }

  /* If x < 0, add b**(k+1) to it */
  if (mp_cmp_d (x, 0) == MP_LT) {
    mp_set (&q, 1);
    if ((res = mp_lshd (&q, um + 1)) != MP_OKAY)
      goto CLEANUP;
    if ((res = mp_add (x, &q, x)) != MP_OKAY)
      goto CLEANUP;
  }

  /* Back off if it's too big */
  while (mp_cmp (x, m) != MP_LT) {
    if ((res = s_mp_sub (x, m, x)) != MP_OKAY) {
      goto CLEANUP;
    }
  }
  
CLEANUP:
  mp_clear (&q);

  return res;
}