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
typedef  int /*<<< orphan*/  mp_int ;
typedef  scalar_t__ mp_digit ;

/* Variables and functions */
 int MP_NO ; 
 int MP_OKAY ; 
 int MP_YES ; 
 int PRIME_SIZE ; 
 int /*<<< orphan*/ * __prime_tab ; 
 int mp_mod_d (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int mp_prime_is_divisible (const mp_int * a, int *result)
{
  int     err, ix;
  mp_digit res;

  /* default to not */
  *result = MP_NO;

  for (ix = 0; ix < PRIME_SIZE; ix++) {
    /* what is a mod __prime_tab[ix] */
    if ((err = mp_mod_d (a, __prime_tab[ix], &res)) != MP_OKAY) {
      return err;
    }

    /* is the residue zero? */
    if (res == 0) {
      *result = MP_YES;
      return MP_OKAY;
    }
  }

  return MP_OKAY;
}