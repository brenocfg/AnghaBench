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
struct TYPE_3__ {int pos; } ;
typedef  TYPE_1__ dictItem ;
typedef  int U32 ;

/* Variables and functions */

__attribute__((used)) static void ZDICT_removeDictItem(dictItem* table, U32 id)
{
    /* convention : table[0].pos stores nb of elts */
    U32 const max = table[0].pos;
    U32 u;
    if (!id) return;   /* protection, should never happen */
    for (u=id; u<max-1; u++)
        table[u] = table[u+1];
    table->pos--;
}