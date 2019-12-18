#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uid_t ;
struct stat {scalar_t__ st_gid; scalar_t__ st_uid; } ;
typedef  scalar_t__ gid_t ;
struct TYPE_4__ {scalar_t__ gid_path; scalar_t__ uid_path; } ;
typedef  TYPE_1__ Item ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ root_stat (scalar_t__,struct stat*) ; 

__attribute__((used)) static int read_id_from_file(Item *i, uid_t *_uid, gid_t *_gid) {
        struct stat st;
        bool found_uid = false, found_gid = false;
        uid_t uid = 0;
        gid_t gid = 0;

        assert(i);

        /* First, try to get the gid directly */
        if (_gid && i->gid_path && root_stat(i->gid_path, &st) >= 0) {
                gid = st.st_gid;
                found_gid = true;
        }

        /* Then, try to get the uid directly */
        if ((_uid || (_gid && !found_gid))
            && i->uid_path
            && root_stat(i->uid_path, &st) >= 0) {

                uid = st.st_uid;
                found_uid = true;

                /* If we need the gid, but had no success yet, also derive it from the uid path */
                if (_gid && !found_gid) {
                        gid = st.st_gid;
                        found_gid = true;
                }
        }

        /* If that didn't work yet, then let's reuse the gid as uid */
        if (_uid && !found_uid && i->gid_path) {

                if (found_gid) {
                        uid = (uid_t) gid;
                        found_uid = true;
                } else if (root_stat(i->gid_path, &st) >= 0) {
                        uid = (uid_t) st.st_gid;
                        found_uid = true;
                }
        }

        if (_uid) {
                if (!found_uid)
                        return 0;

                *_uid = uid;
        }

        if (_gid) {
                if (!found_gid)
                        return 0;

                *_gid = gid;
        }

        return 1;
}