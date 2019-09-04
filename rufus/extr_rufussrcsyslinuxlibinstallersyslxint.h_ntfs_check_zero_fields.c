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
struct ntfs_boot_sector {int /*<<< orphan*/  bsZeroed_3; int /*<<< orphan*/  bsZeroed_2; int /*<<< orphan*/  bsZeroed_1; int /*<<< orphan*/ * bsZeroed_0; int /*<<< orphan*/  bsResSectors; } ;

/* Variables and functions */

__attribute__((used)) static inline int ntfs_check_zero_fields(const struct ntfs_boot_sector *sb)
{
    return !sb->bsResSectors && (!sb->bsZeroed_0[0] && !sb->bsZeroed_0[1] &&
            !sb->bsZeroed_0[2]) && !sb->bsZeroed_1 && !sb->bsZeroed_2 &&
            !sb->bsZeroed_3;
}