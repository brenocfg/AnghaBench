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

/* Variables and functions */
 int /*<<< orphan*/  assert (char**) ; 
 int chase_symlinks (char*,int /*<<< orphan*/ *,unsigned int,char**,int /*<<< orphan*/ *) ; 
 int free_and_replace (char*,char*) ; 
 int log_error_errno (int,char*,char*) ; 

__attribute__((used)) static int chase_symlinks_and_update(char **p, unsigned flags) {
        char *chased;
        int r;

        assert(p);

        if (!*p)
                return 0;

        r = chase_symlinks(*p, NULL, flags, &chased, NULL);
        if (r < 0)
                return log_error_errno(r, "Failed to resolve path %s: %m", *p);

        return free_and_replace(*p, chased);
}