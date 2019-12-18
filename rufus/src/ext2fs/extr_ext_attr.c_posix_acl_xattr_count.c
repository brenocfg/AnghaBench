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
typedef  int /*<<< orphan*/  posix_acl_xattr_header ;
typedef  int /*<<< orphan*/  posix_acl_xattr_entry ;

/* Variables and functions */

__attribute__((used)) static inline int
posix_acl_xattr_count(size_t size)
{
        if (size < sizeof(posix_acl_xattr_header))
                return -1;
        size -= sizeof(posix_acl_xattr_header);
        if (size % sizeof(posix_acl_xattr_entry))
                return -1;
        return size / sizeof(posix_acl_xattr_entry);
}