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
typedef  int /*<<< orphan*/  stb_uint16 ;
struct TYPE_5__ {TYPE_1__* nodes; } ;
typedef  TYPE_2__ stb_matcher ;
struct TYPE_4__ {int active; } ;

/* Variables and functions */
 int /*<<< orphan*/  stb_arr_push (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static stb_uint16 * stb__add_if_inactive(stb_matcher *m, stb_uint16 *list, int n)
{
   if (!m->nodes[n].active) {
      stb_arr_push(list, n);
      m->nodes[n].active = 1;
   }
   return list;
}