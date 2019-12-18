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
 int /*<<< orphan*/  ACL_GROUP ; 
 scalar_t__ ACL_MASK ; 
 int /*<<< orphan*/  ACL_NEXT_ENTRY ; 
 int /*<<< orphan*/  ACL_USER ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acl_calc_mask (int /*<<< orphan*/ *) ; 
 int acl_get_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ acl_get_tag_type (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int errno ; 

int calc_acl_mask_if_needed(acl_t *acl_p) {
        acl_entry_t i;
        int r;
        bool need = false;

        assert(acl_p);

        for (r = acl_get_entry(*acl_p, ACL_FIRST_ENTRY, &i);
             r > 0;
             r = acl_get_entry(*acl_p, ACL_NEXT_ENTRY, &i)) {
                acl_tag_t tag;

                if (acl_get_tag_type(i, &tag) < 0)
                        return -errno;

                if (tag == ACL_MASK)
                        return 0;

                if (IN_SET(tag, ACL_USER, ACL_GROUP))
                        need = true;
        }
        if (r < 0)
                return -errno;

        if (need && acl_calc_mask(acl_p) < 0)
                return -errno;

        return need;
}