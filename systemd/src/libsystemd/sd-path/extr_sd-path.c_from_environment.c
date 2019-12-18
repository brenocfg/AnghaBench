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
 int ENXIO ; 
 int /*<<< orphan*/  assert (char const**) ; 
 scalar_t__ path_is_absolute (char const*) ; 
 char* secure_getenv (char const*) ; 

__attribute__((used)) static int from_environment(const char *envname, const char *fallback, const char **ret) {
        assert(ret);

        if (envname) {
                const char *e;

                e = secure_getenv(envname);
                if (e && path_is_absolute(e)) {
                        *ret = e;
                        return 0;
                }
        }

        if (fallback) {
                *ret = fallback;
                return 0;
        }

        return -ENXIO;
}