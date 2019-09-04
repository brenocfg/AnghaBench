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
typedef  int mp_digit ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int DIGIT_BIT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL s_is_power_of_two(mp_digit b, int *p)
{
   int x;

   for (x = 1; x < DIGIT_BIT; x++) {
      if (b == (((mp_digit)1)<<x)) {
         *p = x;
         return TRUE;
      }
   }
   return FALSE;
}