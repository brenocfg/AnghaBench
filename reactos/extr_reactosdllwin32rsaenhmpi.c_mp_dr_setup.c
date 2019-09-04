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
typedef  int mp_word ;
struct TYPE_3__ {scalar_t__* dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  scalar_t__ mp_digit ;

/* Variables and functions */
 scalar_t__ DIGIT_BIT ; 

__attribute__((used)) static void mp_dr_setup(const mp_int *a, mp_digit *d)
{
   /* the casts are required if DIGIT_BIT is one less than
    * the number of bits in a mp_digit [e.g. DIGIT_BIT==31]
    */
   *d = (mp_digit)((((mp_word)1) << ((mp_word)DIGIT_BIT)) - 
        ((mp_word)a->dp[0]));
}