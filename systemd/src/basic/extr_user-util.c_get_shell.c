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
struct passwd {char const* pw_shell; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ESRCH ; 
 char* NOLOGIN ; 
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

int get_shell(char **_s) {
        struct passwd *p;
        const char *e;
        char *s;
        uid_t u;

        assert(_s);

        /* Take the user specified one */
        e = secure_getenv("SHELL");
        if (e && path_is_valid(e) && path_is_absolute(e)) {
                s = strdup(e);
                if (!s)
                        return -ENOMEM;

                *_s = path_simplify(s, true);
                return 0;
        }

        /* Hardcode shell for root and nobody to avoid NSS */
        u = getuid();
        if (u == 0) {
                s = strdup("/bin/sh");
                if (!s)
                        return -ENOMEM;

                *_s = s;
                return 0;
        }
        if (synthesize_nobody() &&
            u == UID_NOBODY) {
                s = strdup(NOLOGIN);
                if (!s)
                        return -ENOMEM;

                *_s = s;
                return 0;
        }

        /* Check the database... */
        errno = 0;
        p = getpwuid(u);
        if (!p)
                return errno_or_else(ESRCH);

        if (!path_is_valid(p->pw_shell) ||
            !path_is_absolute(p->pw_shell))
                return -EINVAL;

        s = strdup(p->pw_shell);
        if (!s)
                return -ENOMEM;

        *_s = path_simplify(s, true);
        return 0;
}