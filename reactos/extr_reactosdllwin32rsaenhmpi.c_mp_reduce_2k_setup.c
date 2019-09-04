#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  int /*<<< orphan*/  mp_digit ;

/* Variables and functions */
 int MP_OKAY ; 
 int mp_2expt (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mp_clear (TYPE_1__*) ; 
 int mp_count_bits (TYPE_1__ const*) ; 
 int mp_init (TYPE_1__*) ; 
 int s_mp_sub (TYPE_1__*,TYPE_1__ const*,TYPE_1__*) ; 

__attribute__((used)) static int
mp_reduce_2k_setup(const mp_int *a, mp_digit *d)
{
   int res, p;
   mp_int tmp;
   
   if ((res = mp_init(&tmp)) != MP_OKAY) {
      return res;
   }
   
   p = mp_count_bits(a);
   if ((res = mp_2expt(&tmp, p)) != MP_OKAY) {
      mp_clear(&tmp);
      return res;
   }
   
   if ((res = s_mp_sub(&tmp, a, &tmp)) != MP_OKAY) {
      mp_clear(&tmp);
      return res;
   }
   
   *d = tmp.dp[0];
   mp_clear(&tmp);
   return MP_OKAY;
}