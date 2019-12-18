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
struct passwd {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_name; } ;
struct group {int /*<<< orphan*/  gr_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 struct passwd* getpwnam (char const*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool check_user_has_group_with_same_name(const char *name) {
        struct passwd *p;
        struct group *g;

        assert(name);

        p = getpwnam(name);
        if (!p ||
            !streq(p->pw_name, name))
                return false;

        g = getgrgid(p->pw_gid);
        if (!g ||
            !streq(g->gr_name, name))
                return false;

        return true;
}