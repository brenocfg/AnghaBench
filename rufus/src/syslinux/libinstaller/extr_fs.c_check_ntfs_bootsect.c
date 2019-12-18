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
 int NTFS ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static const char *check_ntfs_bootsect(const void *bs, int *fs_type)
{
    const struct ntfs_boot_sector *sectbuf = bs;

    if (memcmp(&sectbuf->bsOemName, "NTFS    ", 8) &&
	memcmp(&sectbuf->bsOemName, "MSWIN4.0", 8) &&
	memcmp(&sectbuf->bsOemName, "MSWIN4.1", 8))
	return "unknown OEM name but claims NTFS";

    if (fs_type)
	*fs_type = NTFS;

    return NULL;
}