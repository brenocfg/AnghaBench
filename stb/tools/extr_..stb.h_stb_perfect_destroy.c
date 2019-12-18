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
struct TYPE_3__ {scalar_t__ table_mask; scalar_t__ b_mask; int /*<<< orphan*/ * table; int /*<<< orphan*/ * large_bmap; } ;
typedef  TYPE_1__ stb_perfect ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void stb_perfect_destroy(stb_perfect *p)
{
   if (p->large_bmap) free(p->large_bmap);
   if (p->table     ) free(p->table);
   p->large_bmap = NULL;
   p->table      = NULL;
   p->b_mask     = 0;
   p->table_mask = 0;
}