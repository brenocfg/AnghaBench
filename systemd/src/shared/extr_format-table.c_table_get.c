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
struct TYPE_3__ {void const* data; } ;
typedef  TYPE_1__ TableData ;
typedef  int /*<<< orphan*/  TableCell ;
typedef  int /*<<< orphan*/  Table ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 TYPE_1__* table_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const void *table_get(Table *t, TableCell *cell) {
        TableData *d;

        assert(t);

        d = table_get_data(t, cell);
        if (!d)
                return NULL;

        return d->data;
}