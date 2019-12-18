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

/* Variables and functions */
 int stb_arr_len (short*) ; 

int sum(short *s)
{
   int i,total=0;
   for (i=0; i < stb_arr_len(s); ++i)
      total += s[i];
   return total;
}