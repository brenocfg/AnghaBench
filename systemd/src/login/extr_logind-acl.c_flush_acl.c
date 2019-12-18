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
typedef  scalar_t__ acl_tag_t ;
typedef  int /*<<< orphan*/  acl_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_FIRST_ENTRY ; 
 int /*<<< orphan*/  ACL_NEXT_ENTRY ; 
 scalar_t__ ACL_USER ; 
 scalar_t__ acl_delete_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acl_get_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acl_get_tag_type (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int errno ; 

__attribute__((used)) static int flush_acl(acl_t acl) {
        acl_entry_t i;
        int found;
        bool changed = false;

        assert(acl);

        for (found = acl_get_entry(acl, ACL_FIRST_ENTRY, &i);
             found > 0;
             found = acl_get_entry(acl, ACL_NEXT_ENTRY, &i)) {

                acl_tag_t tag;

                if (acl_get_tag_type(i, &tag) < 0)
                        return -errno;

                if (tag != ACL_USER)
                        continue;

                if (acl_delete_entry(acl, i) < 0)
                        return -errno;

                changed = true;
        }

        if (found < 0)
                return -errno;

        return changed;
}