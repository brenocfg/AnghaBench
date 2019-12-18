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
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int path_equal_or_files_same (char const*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_absolute (char const*) ; 
 char* strjoina (char const*,char*,char const*) ; 

__attribute__((used)) static bool chroot_symlinks_same(const char *root, const char *wd, const char *a, const char *b) {
        assert(path_is_absolute(wd));

        /* This will give incorrect results if the paths are relative and go outside
         * of the chroot. False negatives are possible. */

        if (!root)
                root = "/";

        a = strjoina(path_is_absolute(a) ? root : wd, "/", a);
        b = strjoina(path_is_absolute(b) ? root : wd, "/", b);
        return path_equal_or_files_same(a, b, 0);
}