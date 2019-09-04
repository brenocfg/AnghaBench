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

/* Variables and functions */
 int MP_OKAY ; 
 int /*<<< orphan*/  mp_clear (int /*<<< orphan*/ *) ; 
 int mp_init (int /*<<< orphan*/ *) ; 
 int mp_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mp_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int
mp_mulmod (const mp_int * a, const mp_int * b, mp_int * c, mp_int * d)
{
  int     res;
  mp_int  t;

  if ((res = mp_init (&t)) != MP_OKAY) {
    return res;
  }

  if ((res = mp_mul (a, b, &t)) != MP_OKAY) {
    mp_clear (&t);
    return res;
  }
  res = mp_mod (&t, c, d);
  mp_clear (&t);
  return res;
}