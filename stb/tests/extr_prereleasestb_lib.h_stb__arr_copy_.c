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
typedef  void stb__arr ;
struct TYPE_3__ {int limit; int len; } ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stb_arr_check2 (void*) ; 
 TYPE_1__* stb_arrhead2 (void*) ; 

void * stb__arr_copy_(void *p, int elem_size)
{
   stb__arr *q;
   if (p == NULL) return p;
   q = (stb__arr *) malloc(sizeof(*q) + elem_size * stb_arrhead2(p)->limit);
   stb_arr_check2(p);
   memcpy(q, stb_arrhead2(p), sizeof(*q) + elem_size * stb_arrhead2(p)->len);
   return q+1;
}