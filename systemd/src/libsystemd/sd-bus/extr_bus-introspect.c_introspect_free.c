#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct introspect {int /*<<< orphan*/  introspection; int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct introspect*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_fclose (int /*<<< orphan*/ ) ; 

void introspect_free(struct introspect *i) {
        assert(i);

        /* Normally introspect_finish() does all the work, this is just a backup for error paths */

        safe_fclose(i->f);
        free(i->introspection);
}