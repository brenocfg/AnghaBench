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
struct TYPE_4__ {size_t maximum_width; size_t minimum_width; } ;
typedef  TYPE_1__ TableData ;
typedef  int /*<<< orphan*/  Table ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 char* table_data_format (int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t utf8_console_width (char const*) ; 

__attribute__((used)) static int table_data_requested_width(Table *table, TableData *d, size_t *ret) {
        const char *t;
        size_t l;

        t = table_data_format(table, d);
        if (!t)
                return -ENOMEM;

        l = utf8_console_width(t);
        if (l == (size_t) -1)
                return -EINVAL;

        if (d->maximum_width != (size_t) -1 && l > d->maximum_width)
                l = d->maximum_width;

        if (l < d->minimum_width)
                l = d->minimum_width;

        *ret = l;
        return 0;
}