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
struct ntfs_boot_sector {int /*<<< orphan*/  NTFS_bsCode; int /*<<< orphan*/  NTFS_bsHead; } ;
struct fat_boot_sector {int /*<<< orphan*/  FAT_bsCode; int /*<<< orphan*/  FAT_bsHead; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_bsCodeLen ; 
 int /*<<< orphan*/  FAT_bsHeadLen ; 
 int NTFS ; 
 int /*<<< orphan*/  NTFS_bsCodeLen ; 
 int /*<<< orphan*/  NTFS_bsHeadLen ; 
 int VFAT ; 
 scalar_t__ boot_sector ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void syslinux_make_bootsect(void *bs, int fs_type)
{
    if (fs_type == VFAT) {
	struct fat_boot_sector *bootsect = bs;
	const struct fat_boot_sector *sbs =
	    (const struct fat_boot_sector *)boot_sector;

	memcpy(&bootsect->FAT_bsHead, &sbs->FAT_bsHead, FAT_bsHeadLen);
	memcpy(&bootsect->FAT_bsCode, &sbs->FAT_bsCode, FAT_bsCodeLen);
    } else if (fs_type == NTFS) {
	struct ntfs_boot_sector *bootsect = bs;
	const struct ntfs_boot_sector *sbs =
	    (const struct ntfs_boot_sector *)boot_sector;

	memcpy(&bootsect->NTFS_bsHead, &sbs->NTFS_bsHead, NTFS_bsHeadLen);
	memcpy(&bootsect->NTFS_bsCode, &sbs->NTFS_bsCode, NTFS_bsCodeLen);
    }
}