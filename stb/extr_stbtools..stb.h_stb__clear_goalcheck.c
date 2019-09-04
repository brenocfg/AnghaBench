#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ stb_uint16 ;
struct TYPE_5__ {TYPE_1__* nodes; } ;
typedef  TYPE_2__ stb_matcher ;
struct TYPE_4__ {scalar_t__ active; scalar_t__ goal; } ;

/* Variables and functions */
 int stb_arr_len (scalar_t__*) ; 

__attribute__((used)) static int stb__clear_goalcheck(stb_matcher *m, stb_uint16 *list)
{
   int i, t=0;
   for (i=0; i < stb_arr_len(list); ++i) {
      t += m->nodes[(int) list[i]].goal;
      m->nodes[(int) list[i]].active = 0;
   }
   return t;
}