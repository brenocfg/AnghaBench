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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int ENOTDIR ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int mkdir_userns (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ path_startswith (char const*,char const*) ; 
 int strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int strspn (char const*,char*) ; 

__attribute__((used)) static int mkdir_userns_p(const char *prefix, const char *path, mode_t mode, uid_t uid_shift) {
        const char *p, *e;
        int r;

        assert(path);

        if (prefix && !path_startswith(path, prefix))
                return -ENOTDIR;

        /* create every parent directory in the path, except the last component */
        p = path + strspn(path, "/");
        for (;;) {
                char t[strlen(path) + 1];

                e = p + strcspn(p, "/");
                p = e + strspn(e, "/");

                /* Is this the last component? If so, then we're done */
                if (*p == 0)
                        break;

                memcpy(t, path, e - path);
                t[e-path] = 0;

                if (prefix && path_startswith(prefix, t))
                        continue;

                r = mkdir_userns(t, mode, uid_shift);
                if (r < 0)
                        return r;
        }

        return mkdir_userns(path, mode, uid_shift);
}