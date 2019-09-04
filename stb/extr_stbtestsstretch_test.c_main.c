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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sb_add (int*,int) ; 
 int sb_count (int*) ; 
 int /*<<< orphan*/  sb_free (int*) ; 
 int /*<<< orphan*/  sb_push (int*,int) ; 

int main(int arg, char **argv)
{
   int i;
   int *arr = NULL;

   for (i=0; i < 1000000; ++i)
      sb_push(arr, i);

   assert(sb_count(arr) == 1000000);
   for (i=0; i < 1000000; ++i)
      assert(arr[i] == i);

   sb_free(arr);
   arr = NULL;

   for (i=0; i < 1000; ++i)
      sb_add(arr, 1000);
   assert(sb_count(arr) == 1000000);

   return 0;
}