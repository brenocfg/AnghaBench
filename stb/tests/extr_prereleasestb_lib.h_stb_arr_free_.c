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
typedef  int /*<<< orphan*/  stb__arr ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stb_arr_check2 (void*) ; 
 int /*<<< orphan*/ * stb_arrhead2 (void*) ; 

void stb_arr_free_(void **pp)
{
   void *p = *pp;
   stb_arr_check2(p);
   if (p) {
      stb__arr *q = stb_arrhead2(p);
      free(q);
   }
   *pp = NULL;
}