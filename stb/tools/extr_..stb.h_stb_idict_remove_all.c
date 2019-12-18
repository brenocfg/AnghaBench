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
struct TYPE_5__ {int limit; scalar_t__ deleted; scalar_t__ count; scalar_t__ has_del; scalar_t__ has_empty; TYPE_1__* table; } ;
typedef  TYPE_2__ stb_idict ;
struct TYPE_4__ {int /*<<< orphan*/  k; } ;

/* Variables and functions */
 int /*<<< orphan*/  STB_IEMPTY ; 

void stb_idict_remove_all(stb_idict *e)
{
   int n;
   for (n=0; n < e->limit; ++n)
      e->table[n].k = STB_IEMPTY;
   e->has_empty = e->has_del = 0;
   e->count = 0;
   e->deleted = 0;
}