#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int SectorSize; } ;
struct TYPE_9__ {int /*<<< orphan*/  uses_minint; scalar_t__ has_grub4dos; scalar_t__ has_grub2; } ;
struct TYPE_8__ {char* _handle; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ FAKE_FD ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 char* APPLICATION_NAME ; 
 scalar_t__ BT_GRUB2 ; 
 scalar_t__ BT_GRUB4DOS ; 
 scalar_t__ BT_IMAGE ; 
 scalar_t__ BT_NON_BOOTABLE ; 
 scalar_t__ BT_REACTOS ; 
 scalar_t__ BT_SYSLINUX_V4 ; 
 scalar_t__ BT_SYSLINUX_V6 ; 
 int /*<<< orphan*/  ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 int ComboBox_GetItemData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ERROR_NOT_ENOUGH_MEMORY ; 
 int ERROR_READ_FAULT ; 
 int ERROR_SEVERITY_ERROR ; 
 int ERROR_WRITE_FAULT ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int /*<<< orphan*/  FALSE ; 
#define  FS_FAT16 129 
#define  FS_FAT32 128 
 int FormatStatus ; 
 scalar_t__ HAS_KOLIBRIOS (TYPE_2__) ; 
 scalar_t__ HAS_SYSLINUX (TYPE_2__) ; 
 scalar_t__ HAS_WINDOWS (TYPE_2__) ; 
 scalar_t__ HAS_WINPE (TYPE_2__) ; 
 int /*<<< orphan*/  IDC_RUFUS_MBR ; 
 int /*<<< orphan*/  IOCTL_DISK_UPDATE_PROPERTIES ; 
 scalar_t__ IS_FAT (int /*<<< orphan*/ ) ; 
 scalar_t__ IsChecked (int /*<<< orphan*/ ) ; 
 scalar_t__ PARTITION_STYLE_GPT ; 
 TYPE_3__ SelectedDrive ; 
 scalar_t__ TT_BIOS ; 
 scalar_t__ TT_UEFI ; 
 char* WindowsErrorString () ; 
 scalar_t__ _mm_malloc (int,int) ; 
 scalar_t__ allow_dual_uefi_bios ; 
 scalar_t__ boot_type ; 
 int /*<<< orphan*/  fs_type ; 
 int /*<<< orphan*/  hDiskID ; 
 int /*<<< orphan*/  hFileSystem ; 
 TYPE_2__ img_report ; 
 scalar_t__ partition_type ; 
 int /*<<< orphan*/  read_sectors (scalar_t__,int,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  safe_mm_free (unsigned char*) ; 
 int /*<<< orphan*/  set_bytes_per_sector (int) ; 
 scalar_t__ target_type ; 
 int /*<<< orphan*/  uprintf (char const*,...) ; 
 int /*<<< orphan*/  write_grub2_mbr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_grub4dos_mbr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_kolibrios_mbr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reactos_mbr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_rufus_gpt_mbr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_rufus_mbr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sectors (scalar_t__,int,int /*<<< orphan*/ ,int,unsigned char*) ; 
 int /*<<< orphan*/  write_syslinux_mbr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_win7_mbr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_zero_mbr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL WriteMBR(HANDLE hPhysicalDrive)
{
	BOOL r = FALSE;
	DWORD size;
	unsigned char* buffer = NULL;
	FAKE_FD fake_fd = { 0 };
	FILE* fp = (FILE*)&fake_fd;
	const char* using_msg = "Using %s MBR";

//	AnalyzeMBR(hPhysicalDrive, "Drive", FALSE);

	if (SelectedDrive.SectorSize < 512)
		goto out;

	if (partition_type == PARTITION_STYLE_GPT) {
		// Add a notice in the protective MBR
		fake_fd._handle = (char*)hPhysicalDrive;
		set_bytes_per_sector(SelectedDrive.SectorSize);
		uprintf(using_msg, "Rufus protective");
		r = write_rufus_gpt_mbr(fp);
		goto notify;
	}

	// FormatEx rewrites the MBR and removes the LBA attribute of FAT16
	// and FAT32 partitions - we need to correct this in the MBR
	buffer = (unsigned char*)_mm_malloc(SelectedDrive.SectorSize, 16);
	if (buffer == NULL) {
		uprintf("Could not allocate memory for MBR");
		FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|ERROR_NOT_ENOUGH_MEMORY;
		goto out;
	}

	if (!read_sectors(hPhysicalDrive, SelectedDrive.SectorSize, 0, 1, buffer)) {
		uprintf("Could not read MBR\n");
		FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|ERROR_READ_FAULT;
		goto out;
	}

	switch (ComboBox_GetItemData(hFileSystem, ComboBox_GetCurSel(hFileSystem))) {
	case FS_FAT16:
		if (buffer[0x1c2] == 0x0e) {
			uprintf("Partition is already FAT16 LBA...\n");
		} else if ((buffer[0x1c2] != 0x04) && (buffer[0x1c2] != 0x06)) {
			uprintf("Warning: converting a non FAT16 partition to FAT16 LBA: FS type=0x%02x\n", buffer[0x1c2]);
		}
		buffer[0x1c2] = 0x0e;
		break;
	case FS_FAT32:
		if (buffer[0x1c2] == 0x0c) {
			uprintf("Partition is already FAT32 LBA...\n");
		} else if (buffer[0x1c2] != 0x0b) {
			uprintf("Warning: converting a non FAT32 partition to FAT32 LBA: FS type=0x%02x\n", buffer[0x1c2]);
		}
		buffer[0x1c2] = 0x0c;
		break;
	}
	if ((boot_type != BT_NON_BOOTABLE) && (target_type == TT_BIOS)) {
		// Set first partition bootable - masquerade as per the DiskID selected
		buffer[0x1be] = IsChecked(IDC_RUFUS_MBR) ?
			(BYTE)ComboBox_GetItemData(hDiskID, ComboBox_GetCurSel(hDiskID)):0x80;
		uprintf("Set bootable USB partition as 0x%02X\n", buffer[0x1be]);
	}

	if (!write_sectors(hPhysicalDrive, SelectedDrive.SectorSize, 0, 1, buffer)) {
		uprintf("Could not write MBR\n");
		FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|ERROR_WRITE_FAULT;
		goto out;
	}

	fake_fd._handle = (char*)hPhysicalDrive;
	set_bytes_per_sector(SelectedDrive.SectorSize);

	// What follows is really a case statement with complex conditions listed
	// by order of preference
	if ((boot_type == BT_IMAGE) && HAS_WINDOWS(img_report) && (allow_dual_uefi_bios) && (target_type == TT_BIOS))
		goto windows_mbr;

	// Non bootable or forced UEFI (zeroed MBR)
	if ((boot_type == BT_NON_BOOTABLE) || (target_type == TT_UEFI)) {
		uprintf(using_msg, "Zeroed");
		r = write_zero_mbr(fp);
		goto notify;
	}

	// Syslinux
	if ( (boot_type == BT_SYSLINUX_V4) || (boot_type == BT_SYSLINUX_V6) ||
		 ((boot_type == BT_IMAGE) && HAS_SYSLINUX(img_report)) ) {
		uprintf(using_msg, "Syslinux");
		r = write_syslinux_mbr(fp);
		goto notify;
	}

	// Grub 2.0
	if ( ((boot_type == BT_IMAGE) && (img_report.has_grub2)) || (boot_type == BT_GRUB2) ) {
		uprintf(using_msg, "Grub 2.0");
		r = write_grub2_mbr(fp);
		goto notify;
	}

	// Grub4DOS
	if ( ((boot_type == BT_IMAGE) && (img_report.has_grub4dos)) || (boot_type == BT_GRUB4DOS) ) {
		uprintf(using_msg, "Grub4DOS");
		r = write_grub4dos_mbr(fp);
		goto notify;
	}

	// ReactOS
	if (boot_type == BT_REACTOS) {
		uprintf(using_msg, "ReactOS");
		r = write_reactos_mbr(fp);
		goto notify;
	}

	// KolibriOS
	if ( (boot_type == BT_IMAGE) && HAS_KOLIBRIOS(img_report) && (IS_FAT(fs_type))) {
		uprintf(using_msg, "KolibriOS");
		r = write_kolibrios_mbr(fp);
		goto notify;
	}

	// If everything else failed, fall back to a conventional Windows/Rufus MBR
windows_mbr:
	if ((HAS_WINPE(img_report) && !img_report.uses_minint) || (IsChecked(IDC_RUFUS_MBR))) {
		uprintf(using_msg, APPLICATION_NAME);
		r = write_rufus_mbr(fp);
	} else {
		uprintf(using_msg, "Windows 7");
		r = write_win7_mbr(fp);
	}

notify:
	// Tell the system we've updated the disk properties
	if (!DeviceIoControl(hPhysicalDrive, IOCTL_DISK_UPDATE_PROPERTIES, NULL, 0, NULL, 0, &size, NULL))
		uprintf("Failed to notify system about disk properties update: %s\n", WindowsErrorString());

out:
	safe_mm_free(buffer);
	return r;
}