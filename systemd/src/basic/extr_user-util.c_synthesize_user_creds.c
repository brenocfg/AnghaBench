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
typedef  scalar_t__ gid_t ;
typedef  int /*<<< orphan*/  UserCredsFlags ;

/* Variables and functions */
 int ENOMEDIUM ; 
 scalar_t__ FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GID_NOBODY ; 
 char* NOBODY_USER_NAME ; 
 char* NOLOGIN ; 
 scalar_t__ STR_IN_SET (char const*,char*,char*) ; 
 scalar_t__ UID_NOBODY ; 
 int /*<<< orphan*/  USER_CREDS_CLEAN ; 
 scalar_t__ synthesize_nobody () ; 

__attribute__((used)) static int synthesize_user_creds(
                const char **username,
                uid_t *uid, gid_t *gid,
                const char **home,
                const char **shell,
                UserCredsFlags flags) {

        /* We enforce some special rules for uid=0 and uid=65534: in order to avoid NSS lookups for root we hardcode
         * their user record data. */

        if (STR_IN_SET(*username, "root", "0")) {
                *username = "root";

                if (uid)
                        *uid = 0;
                if (gid)
                        *gid = 0;

                if (home)
                        *home = "/root";

                if (shell)
                        *shell = "/bin/sh";

                return 0;
        }

        if (synthesize_nobody() &&
            STR_IN_SET(*username, NOBODY_USER_NAME, "65534")) {
                *username = NOBODY_USER_NAME;

                if (uid)
                        *uid = UID_NOBODY;
                if (gid)
                        *gid = GID_NOBODY;

                if (home)
                        *home = FLAGS_SET(flags, USER_CREDS_CLEAN) ? NULL : "/";

                if (shell)
                        *shell = FLAGS_SET(flags, USER_CREDS_CLEAN) ? NULL : NOLOGIN;

                return 0;
        }

        return -ENOMEDIUM;
}