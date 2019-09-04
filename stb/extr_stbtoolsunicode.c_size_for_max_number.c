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
typedef  int uint32 ;

/* Variables and functions */

size_t size_for_max_number(uint32 number)
{
   if (number == 0) return 0;
   if (number < 256) return 1;
   if (number < 256*256) return 2;
   if (number < 256*256*256) return 3;
   return 4;
}