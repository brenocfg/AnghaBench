#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;
struct TYPE_3__ {int /*<<< orphan*/ * meta; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 size_t META_ARGV_GID ; 
 size_t META_ARGV_UID ; 
 scalar_t__ SYSTEM_UID_MAX ; 
 int drop_privileges (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int get_user_creds (char const**,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,char const*) ; 
 int parse_gid (int /*<<< orphan*/ ,scalar_t__*) ; 
 int parse_uid (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int change_uid_gid(const Context *context) {
        uid_t uid;
        gid_t gid;
        int r;

        r = parse_uid(context->meta[META_ARGV_UID], &uid);
        if (r < 0)
                return r;

        if (uid <= SYSTEM_UID_MAX) {
                const char *user = "systemd-coredump";

                r = get_user_creds(&user, &uid, &gid, NULL, NULL, 0);
                if (r < 0) {
                        log_warning_errno(r, "Cannot resolve %s user. Proceeding to dump core as root: %m", user);
                        uid = gid = 0;
                }
        } else {
                r = parse_gid(context->meta[META_ARGV_GID], &gid);
                if (r < 0)
                        return r;
        }

        return drop_privileges(uid, gid, 0);
}