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
typedef  int int64_t ;

/* Variables and functions */
 int U64x (int,int) ; 

int64_t lj_carith_divi64(int64_t a, int64_t b)
{
  if (b == 0 || (a == (int64_t)U64x(80000000,00000000) && b == -1))
    return U64x(80000000,00000000);
  return a / b;
}