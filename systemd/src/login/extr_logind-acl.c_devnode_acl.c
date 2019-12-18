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
typedef  int /*<<< orphan*/  acl_t ;
typedef  int /*<<< orphan*/  acl_permset_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int ACL_READ ; 
 int /*<<< orphan*/  ACL_TYPE_ACCESS ; 
 int /*<<< orphan*/  ACL_USER ; 
 int ACL_WRITE ; 
 scalar_t__ acl_add_perm (int /*<<< orphan*/ ,int) ; 
 scalar_t__ acl_calc_mask (int /*<<< orphan*/ *) ; 
 scalar_t__ acl_create_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ acl_delete_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acl_find_uid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_get_file (char const*,int /*<<< orphan*/ ) ; 
 int acl_get_perm (int /*<<< orphan*/ ,int) ; 
 scalar_t__ acl_get_permset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acl_set_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acl_set_qualifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acl_set_tag_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 int flush_acl (int /*<<< orphan*/ ) ; 

int devnode_acl(const char *path,
                bool flush,
                bool del, uid_t old_uid,
                bool add, uid_t new_uid) {

        acl_t acl;
        int r = 0;
        bool changed = false;

        assert(path);

        acl = acl_get_file(path, ACL_TYPE_ACCESS);
        if (!acl)
                return -errno;

        if (flush) {

                r = flush_acl(acl);
                if (r < 0)
                        goto finish;
                if (r > 0)
                        changed = true;

        } else if (del && old_uid > 0) {
                acl_entry_t entry;

                r = acl_find_uid(acl, old_uid, &entry);
                if (r < 0)
                        goto finish;

                if (r > 0) {
                        if (acl_delete_entry(acl, entry) < 0) {
                                r = -errno;
                                goto finish;
                        }

                        changed = true;
                }
        }

        if (add && new_uid > 0) {
                acl_entry_t entry;
                acl_permset_t permset;
                int rd, wt;

                r = acl_find_uid(acl, new_uid, &entry);
                if (r < 0)
                        goto finish;

                if (r == 0) {
                        if (acl_create_entry(&acl, &entry) < 0) {
                                r = -errno;
                                goto finish;
                        }

                        if (acl_set_tag_type(entry, ACL_USER) < 0 ||
                            acl_set_qualifier(entry, &new_uid) < 0) {
                                r = -errno;
                                goto finish;
                        }
                }

                if (acl_get_permset(entry, &permset) < 0) {
                        r = -errno;
                        goto finish;
                }

                rd = acl_get_perm(permset, ACL_READ);
                if (rd < 0) {
                        r = -errno;
                        goto finish;
                }

                wt = acl_get_perm(permset, ACL_WRITE);
                if (wt < 0) {
                        r = -errno;
                        goto finish;
                }

                if (!rd || !wt) {

                        if (acl_add_perm(permset, ACL_READ|ACL_WRITE) < 0) {
                                r = -errno;
                                goto finish;
                        }

                        changed = true;
                }
        }

        if (!changed)
                goto finish;

        if (acl_calc_mask(&acl) < 0) {
                r = -errno;
                goto finish;
        }

        if (acl_set_file(path, ACL_TYPE_ACCESS, acl) < 0) {
                r = -errno;
                goto finish;
        }

        r = 0;

finish:
        acl_free(acl);

        return r;
}