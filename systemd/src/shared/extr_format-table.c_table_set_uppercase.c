#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int uppercase; int /*<<< orphan*/  formatted; } ;
typedef  TYPE_1__ TableData ;
typedef  int /*<<< orphan*/  TableCell ;
typedef  int /*<<< orphan*/  Table ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_se (TYPE_1__*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int table_dedup_cell (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* table_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int table_set_uppercase(Table *t, TableCell *cell, bool b) {
        TableData *d;
        int r;

        assert(t);
        assert(cell);

        r = table_dedup_cell(t, cell);
        if (r < 0)
                return r;

        assert_se(d = table_get_data(t, cell));

        if (d->uppercase == b)
                return 0;

        d->formatted = mfree(d->formatted);
        d->uppercase = b;
        return 1;
}