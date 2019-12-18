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
 char* TAKE_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct introspect*) ; 
 int fflush_and_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_fclose (int /*<<< orphan*/ ) ; 

int introspect_finish(struct introspect *i, char **ret) {
        int r;

        assert(i);

        fputs("</node>\n", i->f);

        r = fflush_and_check(i->f);
        if (r < 0)
                return r;

        i->f = safe_fclose(i->f);
        *ret = TAKE_PTR(i->introspection);

        return 0;
}