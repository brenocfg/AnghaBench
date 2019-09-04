#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int used; int* dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  int mp_digit ;

/* Variables and functions */
 int DIGIT_BIT ; 
 int MP_OKAY ; 
 int /*<<< orphan*/  mp_clamp (TYPE_1__*) ; 
 int mp_copy (TYPE_1__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_zero (TYPE_1__*) ; 

__attribute__((used)) static int
mp_mod_2d (const mp_int * a, int b, mp_int * c)
{
  int     x, res;

  /* if b is <= 0 then zero the int */
  if (b <= 0) {
    mp_zero (c);
    return MP_OKAY;
  }

  /* if the modulus is larger than the value than return */
  if (b > a->used * DIGIT_BIT) {
    res = mp_copy (a, c);
    return res;
  }

  /* copy */
  if ((res = mp_copy (a, c)) != MP_OKAY) {
    return res;
  }

  /* zero digits above the last digit of the modulus */
  for (x = (b / DIGIT_BIT) + ((b % DIGIT_BIT) == 0 ? 0 : 1); x < c->used; x++) {
    c->dp[x] = 0;
  }
  /* clear the digit that is not completely outside/inside the modulus */
  c->dp[b / DIGIT_BIT] &= (1 << ((mp_digit)b % DIGIT_BIT)) - 1;
  mp_clamp (c);
  return MP_OKAY;
}