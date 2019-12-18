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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int /*<<< orphan*/  pw_dir; int /*<<< orphan*/  pw_name; int /*<<< orphan*/  pw_gid; } ;
typedef  int /*<<< orphan*/  User ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int manager_add_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int manager_add_user_by_uid(Manager *m, uid_t uid, User **ret_user) {
        struct passwd *p;

        assert(m);

        errno = 0;
        p = getpwuid(uid);
        if (!p)
                return errno_or_else(ENOENT);

        return manager_add_user(m, uid, p->pw_gid, p->pw_name, p->pw_dir, ret_user);
}