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
struct utsname {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ is_localhost (int /*<<< orphan*/ ) ; 
 scalar_t__ isempty (int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ uname (struct utsname*) ; 

int gethostname_strict(char **ret) {
        struct utsname u;
        char *k;

        /* This call will rather fail than make up a name. It will not return "localhost" either. */

        assert_se(uname(&u) >= 0);

        if (isempty(u.nodename))
                return -ENXIO;

        if (streq(u.nodename, "(none)"))
                return -ENXIO;

        if (is_localhost(u.nodename))
                return -ENXIO;

        k = strdup(u.nodename);
        if (!k)
                return -ENOMEM;

        *ret = k;
        return 0;
}