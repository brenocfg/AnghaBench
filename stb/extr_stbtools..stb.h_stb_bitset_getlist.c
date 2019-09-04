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
typedef  int /*<<< orphan*/  stb_bitset ;

/* Variables and functions */
 int /*<<< orphan*/  stb_arr_push (int*,int) ; 
 scalar_t__ stb_bitset_testbit (int /*<<< orphan*/ *,int) ; 

int *stb_bitset_getlist(stb_bitset *out, int start, int end)
{
   int *list = NULL;
   int i;
   for (i=start; i < end; ++i)
      if (stb_bitset_testbit(out, i))
         stb_arr_push(list, i);
   return list;
}