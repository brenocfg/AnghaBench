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
typedef  scalar_t__ acl_tag_t ;
typedef  int /*<<< orphan*/ * acl_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_FIRST_ENTRY ; 
 int /*<<< orphan*/  ACL_NEXT_ENTRY ; 
 scalar_t__ ACL_USER ; 
 int /*<<< orphan*/  acl_free (scalar_t__*) ; 
 int acl_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__* acl_get_qualifier (int /*<<< orphan*/ ) ; 
 scalar_t__ acl_get_tag_type (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int errno ; 

int acl_find_uid(acl_t acl, uid_t uid, acl_entry_t *entry) {
        acl_entry_t i;
        int r;

        assert(acl);
        assert(entry);

        for (r = acl_get_entry(acl, ACL_FIRST_ENTRY, &i);
             r > 0;
             r = acl_get_entry(acl, ACL_NEXT_ENTRY, &i)) {

                acl_tag_t tag;
                uid_t *u;
                bool b;

                if (acl_get_tag_type(i, &tag) < 0)
                        return -errno;

                if (tag != ACL_USER)
                        continue;

                u = acl_get_qualifier(i);
                if (!u)
                        return -errno;

                b = *u == uid;
                acl_free(u);

                if (b) {
                        *entry = i;
                        return 1;
                }
        }
        if (r < 0)
                return -errno;

        return 0;
}