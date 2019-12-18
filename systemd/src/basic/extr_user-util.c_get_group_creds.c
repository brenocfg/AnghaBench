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
struct group {char* gr_name; int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  UserCredsFlags ;

/* Variables and functions */
 int EBADMSG ; 
 int /*<<< orphan*/  ESRCH ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GID_NOBODY ; 
 char* NOBODY_GROUP_NAME ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*) ; 
 int /*<<< orphan*/  USER_CREDS_ALLOW_MISSING ; 
 int /*<<< orphan*/  assert (char const**) ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 struct group* getgrnam (char const*) ; 
 int /*<<< orphan*/  gid_is_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_gid (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ synthesize_nobody () ; 

int get_group_creds(const char **groupname, gid_t *gid, UserCredsFlags flags) {
        struct group *g;
        gid_t id;

        assert(groupname);

        /* We enforce some special rules for gid=0: in order to avoid NSS lookups for root we hardcode its data. */

        if (STR_IN_SET(*groupname, "root", "0")) {
                *groupname = "root";

                if (gid)
                        *gid = 0;

                return 0;
        }

        if (synthesize_nobody() &&
            STR_IN_SET(*groupname, NOBODY_GROUP_NAME, "65534")) {
                *groupname = NOBODY_GROUP_NAME;

                if (gid)
                        *gid = GID_NOBODY;

                return 0;
        }

        if (parse_gid(*groupname, &id) >= 0) {
                errno = 0;
                g = getgrgid(id);

                if (g)
                        *groupname = g->gr_name;
                else if (FLAGS_SET(flags, USER_CREDS_ALLOW_MISSING)) {
                        if (gid)
                                *gid = id;

                        return 0;
                }
        } else {
                errno = 0;
                g = getgrnam(*groupname);
        }

        if (!g)
                return errno_or_else(ESRCH);

        if (gid) {
                if (!gid_is_valid(g->gr_gid))
                        return -EBADMSG;

                *gid = g->gr_gid;
        }

        return 0;
}