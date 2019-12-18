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
struct TYPE_4__ {struct TYPE_4__* source; struct TYPE_4__* path; } ;
typedef  TYPE_1__ UnitFileChange ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void unit_file_changes_free(UnitFileChange *changes, size_t n_changes) {
        size_t i;

        assert(changes || n_changes == 0);

        for (i = 0; i < n_changes; i++) {
                free(changes[i].path);
                free(changes[i].source);
        }

        free(changes);
}