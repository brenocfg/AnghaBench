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
struct TYPE_3__ {int used; int* dp; } ;
typedef  TYPE_1__ mp_int ;
typedef  int mp_digit ;

/* Variables and functions */
 int DIGIT_BIT ; 

int
mp_count_bits (const mp_int * a)
{
  int     r;
  mp_digit q;

  /* shortcut */
  if (a->used == 0) {
    return 0;
  }

  /* get number of digits and add that */
  r = (a->used - 1) * DIGIT_BIT;
  
  /* take the last digit and count the bits in it */
  q = a->dp[a->used - 1];
  while (q > 0) {
    ++r;
    q >>= ((mp_digit) 1);
  }
  return r;
}