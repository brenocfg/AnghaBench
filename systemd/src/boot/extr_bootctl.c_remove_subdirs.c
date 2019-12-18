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
 int rmdir_one (char const*,char const* const) ; 

__attribute__((used)) static int remove_subdirs(const char *root, const char *const *subdirs) {
        int r, q;

        /* We use recursion here to destroy the directories in reverse order. Which should be safe given how
         * short the array is. */

        if (!subdirs[0]) /* A the end of the list */
                return 0;

        r = remove_subdirs(root, subdirs + 1);
        q = rmdir_one(root, subdirs[0]);

        return r < 0 ? r : q;
}