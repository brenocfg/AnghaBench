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
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char**) ; 
 int /*<<< orphan*/  free_and_replace (char*,char*) ; 
 char* path_join (char const*,char*) ; 

__attribute__((used)) static int patch_root_prefix(char **p, const char *root_dir) {
        char *c;

        assert(p);

        if (!*p)
                return 0;

        c = path_join(root_dir, *p);
        if (!c)
                return -ENOMEM;

        free_and_replace(*p, c);
        return 0;
}