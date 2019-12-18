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
 int /*<<< orphan*/  FALLBACK_HOSTNAME ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ isempty (int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ streq (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ uname (struct utsname*) ; 

char* gethostname_malloc(void) {
        struct utsname u;

        /* This call tries to return something useful, either the actual hostname
         * or it makes something up. The only reason it might fail is OOM.
         * It might even return "localhost" if that's set. */

        assert_se(uname(&u) >= 0);

        if (isempty(u.nodename) || streq(u.nodename, "(none)"))
                return strdup(FALLBACK_HOSTNAME);

        return strdup(u.nodename);
}