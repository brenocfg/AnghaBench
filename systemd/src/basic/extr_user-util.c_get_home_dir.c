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
typedef  scalar_t__ uid_t ;
struct passwd {char const* pw_dir; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ESRCH ; 
 scalar_t__ UID_NOBODY ; 
 int /*<<< orphan*/  assert (char**) ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ getuid () ; 
 scalar_t__ path_is_absolute (char const*) ; 
 scalar_t__ path_is_valid (char const*) ; 
 char* path_simplify (char*,int) ; 
 char* secure_getenv (char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ synthesize_nobody () ; 

int get_home_dir(char **_h) {
        struct passwd *p;
        const char *e;
        char *h;
        uid_t u;

        assert(_h);

        /* Take the user specified one */
        e = secure_getenv("HOME");
        if (e && path_is_valid(e) && path_is_absolute(e)) {
                h = strdup(e);
                if (!h)
                        return -ENOMEM;

                *_h = path_simplify(h, true);
                return 0;
        }

        /* Hardcode home directory for root and nobody to avoid NSS */
        u = getuid();
        if (u == 0) {
                h = strdup("/root");
                if (!h)
                        return -ENOMEM;

                *_h = h;
                return 0;
        }
        if (synthesize_nobody() &&
            u == UID_NOBODY) {
                h = strdup("/");
                if (!h)
                        return -ENOMEM;

                *_h = h;
                return 0;
        }

        /* Check the database... */
        errno = 0;
        p = getpwuid(u);
        if (!p)
                return errno_or_else(ESRCH);

        if (!path_is_valid(p->pw_dir) ||
            !path_is_absolute(p->pw_dir))
                return -EINVAL;

        h = strdup(p->pw_dir);
        if (!h)
                return -ENOMEM;

        *_h = path_simplify(h, true);
        return 0;
}