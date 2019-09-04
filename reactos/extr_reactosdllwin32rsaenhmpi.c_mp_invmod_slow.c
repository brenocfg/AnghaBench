#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_1__ ;

/* Type definitions */
struct TYPE_42__ {scalar_t__ sign; } ;
typedef  TYPE_1__ const mp_int ;

/* Variables and functions */
 scalar_t__ MP_EQ ; 
 scalar_t__ MP_LT ; 
 scalar_t__ MP_NEG ; 
 int MP_OKAY ; 
 int MP_VAL ; 
 int mp_add (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mp_clear_multi (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_cmp (TYPE_1__ const*,TYPE_1__ const*) ; 
 scalar_t__ mp_cmp_d (TYPE_1__ const*,int) ; 
 scalar_t__ mp_cmp_mag (TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_copy (TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_div_2 (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  mp_exch (TYPE_1__ const*,TYPE_1__ const*) ; 
 int mp_init_multi (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int mp_iseven (TYPE_1__ const*) ; 
 int mp_isodd (TYPE_1__ const*) ; 
 scalar_t__ mp_iszero (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mp_set (TYPE_1__ const*,int) ; 
 int mp_sub (TYPE_1__ const*,TYPE_1__ const*,TYPE_1__ const*) ; 

int mp_invmod_slow (const mp_int * a, mp_int * b, mp_int * c)
{
  mp_int  x, y, u, v, A, B, C, D;
  int     res;

  /* b cannot be negative */
  if (b->sign == MP_NEG || mp_iszero(b) == 1) {
    return MP_VAL;
  }

  /* init temps */
  if ((res = mp_init_multi(&x, &y, &u, &v, 
                           &A, &B, &C, &D, NULL)) != MP_OKAY) {
     return res;
  }

  /* x = a, y = b */
  if ((res = mp_copy (a, &x)) != MP_OKAY) {
    goto __ERR;
  }
  if ((res = mp_copy (b, &y)) != MP_OKAY) {
    goto __ERR;
  }

  /* 2. [modified] if x,y are both even then return an error! */
  if (mp_iseven (&x) == 1 && mp_iseven (&y) == 1) {
    res = MP_VAL;
    goto __ERR;
  }

  /* 3. u=x, v=y, A=1, B=0, C=0,D=1 */
  if ((res = mp_copy (&x, &u)) != MP_OKAY) {
    goto __ERR;
  }
  if ((res = mp_copy (&y, &v)) != MP_OKAY) {
    goto __ERR;
  }
  mp_set (&A, 1);
  mp_set (&D, 1);

top:
  /* 4.  while u is even do */
  while (mp_iseven (&u) == 1) {
    /* 4.1 u = u/2 */
    if ((res = mp_div_2 (&u, &u)) != MP_OKAY) {
      goto __ERR;
    }
    /* 4.2 if A or B is odd then */
    if (mp_isodd (&A) == 1 || mp_isodd (&B) == 1) {
      /* A = (A+y)/2, B = (B-x)/2 */
      if ((res = mp_add (&A, &y, &A)) != MP_OKAY) {
         goto __ERR;
      }
      if ((res = mp_sub (&B, &x, &B)) != MP_OKAY) {
         goto __ERR;
      }
    }
    /* A = A/2, B = B/2 */
    if ((res = mp_div_2 (&A, &A)) != MP_OKAY) {
      goto __ERR;
    }
    if ((res = mp_div_2 (&B, &B)) != MP_OKAY) {
      goto __ERR;
    }
  }

  /* 5.  while v is even do */
  while (mp_iseven (&v) == 1) {
    /* 5.1 v = v/2 */
    if ((res = mp_div_2 (&v, &v)) != MP_OKAY) {
      goto __ERR;
    }
    /* 5.2 if C or D is odd then */
    if (mp_isodd (&C) == 1 || mp_isodd (&D) == 1) {
      /* C = (C+y)/2, D = (D-x)/2 */
      if ((res = mp_add (&C, &y, &C)) != MP_OKAY) {
         goto __ERR;
      }
      if ((res = mp_sub (&D, &x, &D)) != MP_OKAY) {
         goto __ERR;
      }
    }
    /* C = C/2, D = D/2 */
    if ((res = mp_div_2 (&C, &C)) != MP_OKAY) {
      goto __ERR;
    }
    if ((res = mp_div_2 (&D, &D)) != MP_OKAY) {
      goto __ERR;
    }
  }

  /* 6.  if u >= v then */
  if (mp_cmp (&u, &v) != MP_LT) {
    /* u = u - v, A = A - C, B = B - D */
    if ((res = mp_sub (&u, &v, &u)) != MP_OKAY) {
      goto __ERR;
    }

    if ((res = mp_sub (&A, &C, &A)) != MP_OKAY) {
      goto __ERR;
    }

    if ((res = mp_sub (&B, &D, &B)) != MP_OKAY) {
      goto __ERR;
    }
  } else {
    /* v - v - u, C = C - A, D = D - B */
    if ((res = mp_sub (&v, &u, &v)) != MP_OKAY) {
      goto __ERR;
    }

    if ((res = mp_sub (&C, &A, &C)) != MP_OKAY) {
      goto __ERR;
    }

    if ((res = mp_sub (&D, &B, &D)) != MP_OKAY) {
      goto __ERR;
    }
  }

  /* if not zero goto step 4 */
  if (mp_iszero (&u) == 0)
    goto top;

  /* now a = C, b = D, gcd == g*v */

  /* if v != 1 then there is no inverse */
  if (mp_cmp_d (&v, 1) != MP_EQ) {
    res = MP_VAL;
    goto __ERR;
  }

  /* if it's too low */
  while (mp_cmp_d(&C, 0) == MP_LT) {
      if ((res = mp_add(&C, b, &C)) != MP_OKAY) {
         goto __ERR;
      }
  }
  
  /* too big */
  while (mp_cmp_mag(&C, b) != MP_LT) {
      if ((res = mp_sub(&C, b, &C)) != MP_OKAY) {
         goto __ERR;
      }
  }
  
  /* C is now the inverse */
  mp_exch (&C, c);
  res = MP_OKAY;
__ERR:mp_clear_multi (&x, &y, &u, &v, &A, &B, &C, &D, NULL);
  return res;
}