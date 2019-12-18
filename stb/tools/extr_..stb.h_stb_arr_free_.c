#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ stb_malloc; } ;
typedef  TYPE_1__ stb__arr ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  stb_arr_check2 (void*) ; 
 TYPE_1__* stb_arrhead2 (void*) ; 
 int /*<<< orphan*/  stb_free (TYPE_1__*) ; 

void stb_arr_free_(void **pp)
{
   void *p = *pp;
   stb_arr_check2(p);
   if (p) {
      stb__arr *q = stb_arrhead2(p);
      if (q->stb_malloc)
         stb_free(q);
      else
         free(q);
   }
   *pp = NULL;
}