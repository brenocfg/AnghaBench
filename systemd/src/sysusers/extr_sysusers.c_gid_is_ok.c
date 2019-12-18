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
struct passwd {int dummy; } ;
struct group {int dummy; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  GID_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UID_TO_PTR (scalar_t__) ; 
 int /*<<< orphan*/  arg_root ; 
 int /*<<< orphan*/  database_by_gid ; 
 int /*<<< orphan*/  database_by_uid ; 
 int errno ; 
 struct group* getgrgid (scalar_t__) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 scalar_t__ hashmap_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ordered_hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  todo_gids ; 
 int /*<<< orphan*/  todo_uids ; 

__attribute__((used)) static int gid_is_ok(gid_t gid) {
        struct group *g;
        struct passwd *p;

        if (ordered_hashmap_get(todo_gids, GID_TO_PTR(gid)))
                return 0;

        /* Avoid reusing gids that are already used by a different user */
        if (ordered_hashmap_get(todo_uids, UID_TO_PTR(gid)))
                return 0;

        if (hashmap_contains(database_by_gid, GID_TO_PTR(gid)))
                return 0;

        if (hashmap_contains(database_by_uid, UID_TO_PTR(gid)))
                return 0;

        if (!arg_root) {
                errno = 0;
                g = getgrgid(gid);
                if (g)
                        return 0;
                if (!IN_SET(errno, 0, ENOENT))
                        return -errno;

                errno = 0;
                p = getpwuid((uid_t) gid);
                if (p)
                        return 0;
                if (!IN_SET(errno, 0, ENOENT))
                        return -errno;
        }

        return 1;
}