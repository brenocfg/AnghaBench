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
struct TYPE_4__ {int /*<<< orphan*/  empty_string; } ;
typedef  TYPE_1__ Table ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 

int table_set_empty_string(Table *t, const char *empty) {
        assert(t);

        return free_and_strdup(&t->empty_string, empty);
}