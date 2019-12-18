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
struct TYPE_4__ {char const* color; scalar_t__ type; } ;
typedef  TYPE_1__ TableData ;

/* Variables and functions */
 scalar_t__ TABLE_EMPTY ; 
 char const* ansi_grey () ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static const char* table_data_color(TableData *d) {
        assert(d);

        if (d->color)
                return d->color;

        /* Let's implicitly color all "empty" cells in grey, in case an "empty_string" is set that is not empty */
        if (d->type == TABLE_EMPTY)
                return ansi_grey();

        return NULL;
}