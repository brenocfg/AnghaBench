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
typedef  int /*<<< orphan*/  const mp_int ;

/* Variables and functions */
 scalar_t__ MP_EQ ; 
 scalar_t__ MP_GT ; 
 int MP_NO ; 
 int MP_OKAY ; 
 int MP_VAL ; 
 int MP_YES ; 
 int /*<<< orphan*/  mp_clear (int /*<<< orphan*/  const*) ; 
 scalar_t__ mp_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ mp_cmp_d (int /*<<< orphan*/  const*,int) ; 
 int mp_cnt_lsb (int /*<<< orphan*/  const*) ; 
 int mp_div_2d (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int mp_exptmod (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int mp_init (int /*<<< orphan*/  const*) ; 
 int mp_init_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int mp_sqrmod (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int mp_sub_d (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int mp_prime_miller_rabin (mp_int * a, const mp_int * b, int *result)
{
  mp_int  n1, y, r;
  int     s, j, err;

  /* default */
  *result = MP_NO;

  /* ensure b > 1 */
  if (mp_cmp_d(b, 1) != MP_GT) {
     return MP_VAL;
  }     

  /* get n1 = a - 1 */
  if ((err = mp_init_copy (&n1, a)) != MP_OKAY) {
    return err;
  }
  if ((err = mp_sub_d (&n1, 1, &n1)) != MP_OKAY) {
    goto __N1;
  }

  /* set 2**s * r = n1 */
  if ((err = mp_init_copy (&r, &n1)) != MP_OKAY) {
    goto __N1;
  }

  /* count the number of least significant bits
   * which are zero
   */
  s = mp_cnt_lsb(&r);

  /* now divide n - 1 by 2**s */
  if ((err = mp_div_2d (&r, s, &r, NULL)) != MP_OKAY) {
    goto __R;
  }

  /* compute y = b**r mod a */
  if ((err = mp_init (&y)) != MP_OKAY) {
    goto __R;
  }
  if ((err = mp_exptmod (b, &r, a, &y)) != MP_OKAY) {
    goto __Y;
  }

  /* if y != 1 and y != n1 do */
  if (mp_cmp_d (&y, 1) != MP_EQ && mp_cmp (&y, &n1) != MP_EQ) {
    j = 1;
    /* while j <= s-1 and y != n1 */
    while ((j <= (s - 1)) && mp_cmp (&y, &n1) != MP_EQ) {
      if ((err = mp_sqrmod (&y, a, &y)) != MP_OKAY) {
         goto __Y;
      }

      /* if y == 1 then composite */
      if (mp_cmp_d (&y, 1) == MP_EQ) {
         goto __Y;
      }

      ++j;
    }

    /* if y != n1 then composite */
    if (mp_cmp (&y, &n1) != MP_EQ) {
      goto __Y;
    }
  }

  /* probably prime now */
  *result = MP_YES;
__Y:mp_clear (&y);
__R:mp_clear (&r);
__N1:mp_clear (&n1);
  return err;
}