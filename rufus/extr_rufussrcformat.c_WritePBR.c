#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int SectorSize; } ;
struct TYPE_3__ {char* _handle; int _offset; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ FAKE_FD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BT_FREEDOS ; 
 int /*<<< orphan*/  BT_IMAGE ; 
 int /*<<< orphan*/  BT_REACTOS ; 
 int ERROR_SEVERITY_ERROR ; 
 int ERROR_WRITE_FAULT ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int /*<<< orphan*/  FALSE ; 
#define  FS_FAT16 130 
#define  FS_FAT32 129 
#define  FS_NTFS 128 
 int FormatStatus ; 
 int /*<<< orphan*/  HAS_BOOTMGR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAS_KOLIBRIOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAS_WINPE (int /*<<< orphan*/ ) ; 
 TYPE_2__ SelectedDrive ; 
 int /*<<< orphan*/  TRUE ; 
 int actual_fs_type ; 
 int /*<<< orphan*/  boot_type ; 
 int /*<<< orphan*/  bt_to_name () ; 
 int /*<<< orphan*/  img_report ; 
 int /*<<< orphan*/  is_fat_16_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_fat_32_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_ntfs_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bytes_per_sector (int) ; 
 int /*<<< orphan*/  uprintf (char const*,...) ; 
 int /*<<< orphan*/  write_fat_16_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat_16_fd_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat_16_ros_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat_32_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat_32_fd_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat_32_kos_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat_32_nt_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat_32_pe_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_fat_32_ros_br (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_ntfs_br (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_partition_physical_disk_drive_id_fat16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_partition_physical_disk_drive_id_fat32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL WritePBR(HANDLE hLogicalVolume)
{
	int i;
	FAKE_FD fake_fd = { 0 };
	FILE* fp = (FILE*)&fake_fd;
	const char* using_msg = "Using %s %s partition boot record";

	fake_fd._handle = (char*)hLogicalVolume;
	set_bytes_per_sector(SelectedDrive.SectorSize);

	switch (actual_fs_type) {
	case FS_FAT16:
		uprintf(using_msg, bt_to_name(), "FAT16");
		if (!is_fat_16_fs(fp)) {
			uprintf("New volume does not have a FAT16 boot sector - aborting");
			break;
		}
		uprintf("Confirmed new volume has a FAT16 boot sector");
		if (boot_type == BT_FREEDOS) {
			if (!write_fat_16_fd_br(fp, 0)) break;
		} else if (boot_type == BT_REACTOS) {
			if (!write_fat_16_ros_br(fp, 0)) break;
		} else if ((boot_type == BT_IMAGE) && HAS_KOLIBRIOS(img_report)) {
			uprintf("FAT16 is not supported for KolibriOS\n"); break;
		} else {
			if (!write_fat_16_br(fp, 0)) break;
		}
		// Disk Drive ID needs to be corrected on XP
		if (!write_partition_physical_disk_drive_id_fat16(fp))
			break;
		return TRUE;
	case FS_FAT32:
		uprintf(using_msg, bt_to_name(), "FAT32");
		for (i=0; i<2; i++) {
			if (!is_fat_32_fs(fp)) {
				uprintf("New volume does not have a %s FAT32 boot sector - aborting\n", i?"secondary":"primary");
				break;
			}
			uprintf("Confirmed new volume has a %s FAT32 boot sector\n", i?"secondary":"primary");
			uprintf("Setting %s FAT32 boot sector for boot...\n", i?"secondary":"primary");
			if (boot_type == BT_FREEDOS) {
				if (!write_fat_32_fd_br(fp, 0)) break;
			} else if (boot_type == BT_REACTOS) {
				if (!write_fat_32_ros_br(fp, 0)) break;
			} else if ((boot_type == BT_IMAGE) && HAS_KOLIBRIOS(img_report)) {
				if (!write_fat_32_kos_br(fp, 0)) break;
			} else if ((boot_type == BT_IMAGE) && HAS_BOOTMGR(img_report)) {
				if (!write_fat_32_pe_br(fp, 0)) break;
			} else if ((boot_type == BT_IMAGE) && HAS_WINPE(img_report)) {
				if (!write_fat_32_nt_br(fp, 0)) break;
			} else {
				if (!write_fat_32_br(fp, 0)) break;
			}
			// Disk Drive ID needs to be corrected on XP
			if (!write_partition_physical_disk_drive_id_fat32(fp))
				break;
			fake_fd._offset += 6 * SelectedDrive.SectorSize;
		}
		return TRUE;
	case FS_NTFS:
		uprintf(using_msg, bt_to_name(), "NTFS");
		if (!is_ntfs_fs(fp)) {
			uprintf("New volume does not have an NTFS boot sector - aborting\n");
			break;
		}
		uprintf("Confirmed new volume has an NTFS boot sector\n");
		if (!write_ntfs_br(fp)) break;
		// Note: NTFS requires a full remount after writing the PBR. We dismount when we lock
		// and also go through a forced remount, so that shouldn't be an issue.
		// But with NTFS, if you don't remount, you don't boot!
		return TRUE;
	default:
		uprintf("Unsupported FS for FS BR processing - aborting\n");
		break;
	}
	FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|ERROR_WRITE_FAULT;
	return FALSE;
}