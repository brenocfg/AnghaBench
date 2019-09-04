#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int SectorSize; int SectorsPerTrack; } ;
struct TYPE_6__ {scalar_t__ has_grub2; scalar_t__ has_grub4dos; } ;
struct TYPE_5__ {char* _handle; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ FAKE_FD ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
#define  BT_GRUB2 129 
#define  BT_GRUB4DOS 128 
 int BT_IMAGE ; 
 int FALSE ; 
 unsigned char* GetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  HAS_SYSLINUX (TYPE_2__) ; 
 int /*<<< orphan*/  IDC_OLD_BIOS_FIXES ; 
 int /*<<< orphan*/  IDR_GR_GRUB2_CORE_IMG ; 
 int /*<<< orphan*/  IDR_GR_GRUB_GRLDR_MBR ; 
 int /*<<< orphan*/  IsBufferInDB (unsigned char*,scalar_t__) ; 
 scalar_t__ IsChecked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEA (int /*<<< orphan*/ ) ; 
 int MB ; 
 scalar_t__ PARTITION_STYLE_GPT ; 
 TYPE_3__ SelectedDrive ; 
 int TRUE ; 
 int /*<<< orphan*/  _RT_RCDATA ; 
 int boot_type ; 
 unsigned char* grub2_buf ; 
 scalar_t__ grub2_len ; 
 int /*<<< orphan*/  hMainInstance ; 
 TYPE_2__ img_report ; 
 scalar_t__ partition_type ; 
 int /*<<< orphan*/  safe_free (unsigned char*) ; 
 int /*<<< orphan*/  set_bytes_per_sector (int) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 
 int write_data (int /*<<< orphan*/ *,int,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL WriteSBR(HANDLE hPhysicalDrive)
{
	// TODO: Do we need anything special for 4K sectors?
	DWORD size, max_size, mbr_size = 0x200;
	int r, sub_type = boot_type;
	unsigned char* buf = NULL;
	FAKE_FD fake_fd = { 0 };
	FILE* fp = (FILE*)&fake_fd;

	if (partition_type == PARTITION_STYLE_GPT)
		return TRUE;

	fake_fd._handle = (char*)hPhysicalDrive;
	set_bytes_per_sector(SelectedDrive.SectorSize);
	// Ensure that we have sufficient space for the SBR
	max_size = IsChecked(IDC_OLD_BIOS_FIXES) ?
		(DWORD)(SelectedDrive.SectorsPerTrack * SelectedDrive.SectorSize) : 1*MB;
	max_size -= mbr_size;
	// Syslinux has precedence over Grub
	if ((boot_type == BT_IMAGE) && (!HAS_SYSLINUX(img_report))) {
		if (img_report.has_grub4dos)
			sub_type = BT_GRUB4DOS;
		if (img_report.has_grub2)
			sub_type = BT_GRUB2;
	}

	switch (sub_type) {
	case BT_GRUB4DOS:
		uprintf("Writing Grub4Dos SBR");
		buf = GetResource(hMainInstance, MAKEINTRESOURCEA(IDR_GR_GRUB_GRLDR_MBR), _RT_RCDATA, "grldr.mbr", &size, FALSE);
		if ((buf == NULL) || (size <= mbr_size)) {
			uprintf("grldr.mbr is either not present or too small");
			return FALSE;
		}
		buf = &buf[mbr_size];
		size -= mbr_size;
		break;
	case BT_GRUB2:
		if (grub2_buf != NULL) {
			uprintf("Writing Grub 2.0 SBR (from download) %s",
				IsBufferInDB(grub2_buf, grub2_len)?"✓":"✗");
			buf = grub2_buf;
			size = (DWORD)grub2_len;
		} else {
			uprintf("Writing Grub 2.0 SBR (from embedded)");
			buf = GetResource(hMainInstance, MAKEINTRESOURCEA(IDR_GR_GRUB2_CORE_IMG), _RT_RCDATA, "core.img", &size, FALSE);
			if (buf == NULL) {
				uprintf("Could not access core.img");
				return FALSE;
			}
		}
		break;
	default:
		// No need to write secondary block
		return TRUE;
	}

	if (size > max_size) {
		uprintf("  SBR size is too large - You may need to uncheck 'Add fixes for old BIOSes'.");
		return FALSE;
	}
	r = write_data(fp, mbr_size, buf, (uint64_t)size);
	safe_free(grub2_buf);
	return (r != 0);
}