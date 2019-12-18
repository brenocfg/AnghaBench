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
struct ntfs_boot_sector {int /*<<< orphan*/  bsOemName; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ntfs_check_zero_fields (struct ntfs_boot_sector const*) ; 

__attribute__((used)) static inline int ntfs_check_sb_fields(const struct ntfs_boot_sector *sb)
{
    return ntfs_check_zero_fields(sb) &&
            (!memcmp(sb->bsOemName, "NTFS    ", 8) ||
             !memcmp(sb->bsOemName, "MSWIN4.0", 8) ||
             !memcmp(sb->bsOemName, "MSWIN4.1", 8));
}