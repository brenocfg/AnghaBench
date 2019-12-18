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
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  path_hash_ops ; 
 int /*<<< orphan*/  path_simplify (char*,int) ; 
 int set_consume (int /*<<< orphan*/ *,char*) ; 
 int set_ensure_allocated (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int mark_symlink_for_removal(
                Set **remove_symlinks_to,
                const char *p) {

        char *n;
        int r;

        assert(p);

        r = set_ensure_allocated(remove_symlinks_to, &path_hash_ops);
        if (r < 0)
                return r;

        n = strdup(p);
        if (!n)
                return -ENOMEM;

        path_simplify(n, false);

        r = set_consume(*remove_symlinks_to, n);
        if (r == -EEXIST)
                return 0;
        if (r < 0)
                return r;

        return 1;
}