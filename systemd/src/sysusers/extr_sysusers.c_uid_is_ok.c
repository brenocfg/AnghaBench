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
struct passwd {int dummy; } ;
struct group {char const* gr_name; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {char const* name; } ;
typedef  TYPE_1__ Item ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  GID_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  arg_root ; 
 int /*<<< orphan*/  database_by_gid ; 
 int /*<<< orphan*/  database_by_uid ; 
 int errno ; 
 struct group* getgrgid (int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid (scalar_t__) ; 
 scalar_t__ hashmap_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ordered_hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  streq (char const*,char const*) ; 
 int /*<<< orphan*/  todo_gids ; 
 int /*<<< orphan*/  todo_uids ; 

__attribute__((used)) static int uid_is_ok(uid_t uid, const char *name, bool check_with_gid) {
        struct passwd *p;
        struct group *g;
        const char *n;
        Item *i;

        /* Let's see if we already have assigned the UID a second time */
        if (ordered_hashmap_get(todo_uids, UID_TO_PTR(uid)))
                return 0;

        /* Try to avoid using uids that are already used by a group
         * that doesn't have the same name as our new user. */
        if (check_with_gid) {
                i = ordered_hashmap_get(todo_gids, GID_TO_PTR(uid));
                if (i && !streq(i->name, name))
                        return 0;
        }

        /* Let's check the files directly */
        if (hashmap_contains(database_by_uid, UID_TO_PTR(uid)))
                return 0;

        if (check_with_gid) {
                n = hashmap_get(database_by_gid, GID_TO_PTR(uid));
                if (n && !streq(n, name))
                        return 0;
        }

        /* Let's also check via NSS, to avoid UID clashes over LDAP and such, just in case */
        if (!arg_root) {
                errno = 0;
                p = getpwuid(uid);
                if (p)
                        return 0;
                if (!IN_SET(errno, 0, ENOENT))
                        return -errno;

                if (check_with_gid) {
                        errno = 0;
                        g = getgrgid((gid_t) uid);
                        if (g) {
                                if (!streq(g->gr_name, name))
                                        return 0;
                        } else if (!IN_SET(errno, 0, ENOENT))
                                return -errno;
                }
        }

        return 1;
}