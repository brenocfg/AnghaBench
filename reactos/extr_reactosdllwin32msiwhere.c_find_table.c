#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {scalar_t__ col_count; struct TYPE_7__* next; } ;
struct TYPE_6__ {scalar_t__ col_count; TYPE_2__* tables; } ;
typedef  TYPE_1__ MSIWHEREVIEW ;
typedef  TYPE_2__ JOINTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 

__attribute__((used)) static JOINTABLE *find_table(MSIWHEREVIEW *wv, UINT col, UINT *table_col)
{
    JOINTABLE *table = wv->tables;

    if(col == 0 || col > wv->col_count)
         return NULL;

    while (col > table->col_count)
    {
        col -= table->col_count;
        table = table->next;
        assert(table);
    }

    *table_col = col;
    return table;
}