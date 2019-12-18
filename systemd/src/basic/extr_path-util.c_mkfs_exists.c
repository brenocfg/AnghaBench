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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int binary_is_good (char const*) ; 
 scalar_t__ streq (char const*,char*) ; 
 char* strjoina (char*,char const*) ; 

int mkfs_exists(const char *fstype) {
        const char *mkfs;

        assert(fstype);

        if (streq(fstype, "auto"))
                return -EINVAL;

        mkfs = strjoina("mkfs.", fstype);
        return binary_is_good(mkfs);
}