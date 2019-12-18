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
 int EDOM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HOST_NAME_MAX ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ hostname_is_valid (char*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strshorten (char*,int /*<<< orphan*/ ) ; 

int shorten_overlong(const char *s, char **ret) {
        char *h, *p;

        /* Shorten an overlong name to HOST_NAME_MAX or to the first dot,
         * whatever comes earlier. */

        assert(s);

        h = strdup(s);
        if (!h)
                return -ENOMEM;

        if (hostname_is_valid(h, false)) {
                *ret = h;
                return 0;
        }

        p = strchr(h, '.');
        if (p)
                *p = 0;

        strshorten(h, HOST_NAME_MAX);

        if (!hostname_is_valid(h, false)) {
                free(h);
                return -EDOM;
        }

        *ret = h;
        return 1;
}