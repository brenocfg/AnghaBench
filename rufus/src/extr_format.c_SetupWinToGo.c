#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_6__ {scalar_t__ MediaType; int SectorSize; } ;
struct TYPE_5__ {char** wininst_path; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int APPERR (int /*<<< orphan*/ ) ; 
 char* AltMountVolume (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AltUnmountVolume (char*,scalar_t__) ; 
 int /*<<< orphan*/  ERROR_CANT_ASSIGN_LETTER ; 
 int /*<<< orphan*/  ERROR_ISO_EXTRACT ; 
 int ERROR_NOT_SUPPORTED ; 
 int ERROR_SEVERITY_ERROR ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 scalar_t__ FALSE ; 
 int FP_FORCE ; 
 int FP_LARGE_FAT32 ; 
 int FP_NO_BOOT ; 
 int FP_QUICK ; 
 int /*<<< orphan*/  FS_FAT32 ; 
 scalar_t__ FixedMedia ; 
 int /*<<< orphan*/  FormatPartition (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 int FormatStatus ; 
 unsigned char* GetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__*,scalar_t__) ; 
 scalar_t__ HAS_BOOTMGR_BIOS (TYPE_1__) ; 
 scalar_t__ HAS_BOOTMGR_EFI (TYPE_1__) ; 
 int /*<<< orphan*/  IDR_TOGO_SAN_POLICY_XML ; 
 int /*<<< orphan*/  IDR_TOGO_UNATTEND_XML ; 
 int /*<<< orphan*/  IS_ERROR (int) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEA (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MSG_267 ; 
 char* MountISO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_FILE_COPY ; 
 size_t PI_ESP ; 
 scalar_t__ RunCommand (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__ SelectedDrive ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UnMountISO () ; 
 int /*<<< orphan*/  UpdateProgressWithInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  WimApplyImage (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  _RT_RCDATA ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopenU (char*,char*) ; 
 scalar_t__ fwrite (unsigned char*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hMainInstance ; 
 int /*<<< orphan*/  image_path ; 
 TYPE_1__ img_report ; 
 int nWindowsBuildNumber ; 
 int /*<<< orphan*/ * partition_offset ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,char const*,char const*,...) ; 
 int /*<<< orphan*/ * sysnative_dir ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 
 scalar_t__ usb_debug ; 
 int wim_extra_files ; 
 scalar_t__ wim_nb_files ; 
 scalar_t__ wim_proc_files ; 
 size_t wininst_index ; 
 int /*<<< orphan*/  wintogo_index ; 

__attribute__((used)) static BOOL SetupWinToGo(DWORD DriveIndex, const char* drive_name, BOOL use_esp)
{
#ifdef SET_INTERNAL_DRIVES_OFFLINE
	static char san_policy_path[] = "?:\\san_policy.xml";
#endif
	static char unattend_path[] = "?:\\Windows\\System32\\sysprep\\unattend.xml";
	char *mounted_iso, *ms_efi = NULL, image[128], cmd[MAX_PATH];
	unsigned char *buffer;
	DWORD bufsize;
	ULONG cluster_size;
	FILE* fd;

	uprintf("Windows To Go mode selected");
	// Additional sanity checks
	if ((use_esp) && (SelectedDrive.MediaType != FixedMedia) && (nWindowsBuildNumber < 15000)) {
		FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|ERROR_NOT_SUPPORTED;
		return FALSE;
	}

	// First, we need to access the install.wim image, that resides on the ISO
	mounted_iso = MountISO(image_path);
	if (mounted_iso == NULL) {
		uprintf("Could not mount ISO for Windows To Go installation");
		FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|APPERR(ERROR_ISO_EXTRACT);
		return FALSE;
	}
	static_sprintf(image, "%s%s", mounted_iso, &img_report.wininst_path[wininst_index][2]);
	uprintf("Mounted ISO as '%s'", mounted_iso);

	// Now we use the WIM API to apply that image
	if (!WimApplyImage(image, wintogo_index, drive_name)) {
		uprintf("Failed to apply Windows To Go image");
		if (!IS_ERROR(FormatStatus))
			FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|APPERR(ERROR_ISO_EXTRACT);
		UnMountISO();
		return FALSE;
	}
	UnMountISO();

	if (use_esp) {
		uprintf("Setting up EFI System Partition");
		// According to Ubuntu (https://bugs.launchpad.net/ubuntu/+source/partman-efi/+bug/811485) you want to use FAT32.
		// However, you have to be careful that the cluster size needs to be greater or equal to the sector size, which
		// in turn has an impact on the minimum EFI partition size we can create (see ms_efi_size_MB in drive.c)
		if (SelectedDrive.SectorSize <= 1024)
			cluster_size = 1024;
		else if (SelectedDrive.SectorSize <= 4096)
			cluster_size = 4096;
		else	// Go for broke
			cluster_size = (ULONG)SelectedDrive.SectorSize;
		// Boy do you *NOT* want to specify a label here, and spend HOURS figuring out why your EFI partition cannot boot...
		// Also, we use the Large FAT32 facility Microsoft APIs are *UTTERLY USELESS* for achieving what we want:
		// VDS cannot list ESP volumes (talk about allegedly improving on the old disk and volume APIs, only to
		// completely neuter it) and IVdsDiskPartitionMF::FormatPartitionEx(), which is what you are supposed to
		// use for ESPs, explicitly states: "This method cannot be used to format removable media."
		if (!FormatPartition(DriveIndex, partition_offset[PI_ESP], cluster_size, FS_FAT32, "",
			FP_QUICK | FP_FORCE | FP_LARGE_FAT32 | FP_NO_BOOT)) {
			uprintf("Could not format EFI System Partition");
			return FALSE;
		}
		Sleep(200);
	}

	if (use_esp) {
		// Need to have the ESP mounted to invoke bcdboot
		ms_efi = AltMountVolume(DriveIndex, partition_offset[PI_ESP], FALSE);
		if (ms_efi == NULL) {
			FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | APPERR(ERROR_CANT_ASSIGN_LETTER);
			return FALSE;
		}
	}

	// We invoke the 'bcdboot' command from the host, as the one from the drive produces problems (#558)
	// Also, since Rufus should (usually) be running as a 32 bit app, on 64 bit systems, we need to use
	// 'C:\Windows\Sysnative' and not 'C:\Windows\System32' to invoke bcdboot, as 'C:\Windows\System32'
	// will get converted to 'C:\Windows\SysWOW64' behind the scenes, and there is no bcdboot.exe there.
	static_sprintf(cmd, "%s\\bcdboot.exe %s\\Windows /v /f %s /s %s", sysnative_dir, drive_name,
		HAS_BOOTMGR_BIOS(img_report) ? (HAS_BOOTMGR_EFI(img_report) ? "ALL" : "BIOS") : "UEFI",
		(use_esp)?ms_efi:drive_name);
	uprintf("Enabling boot using command '%s'", cmd);
	if (RunCommand(cmd, sysnative_dir, usb_debug) != 0) {
		// Try to continue... but report a failure
		uprintf("Failed to enable boot");
		FormatStatus = ERROR_SEVERITY_ERROR | FAC(FACILITY_STORAGE) | APPERR(ERROR_ISO_EXTRACT);
	}

	if (use_esp) {
		Sleep(200);
		AltUnmountVolume(ms_efi, FALSE);
	}
	UpdateProgressWithInfo(OP_FILE_COPY, MSG_267, wim_proc_files + 2 * wim_extra_files, wim_nb_files);

	// The following are non fatal if they fail

#ifdef SET_INTERNAL_DRIVES_OFFLINE
	uprintf("Applying 'san_policy.xml', to set the target's internal drives offline...");
	buffer = GetResource(hMainInstance, MAKEINTRESOURCEA(IDR_TOGO_SAN_POLICY_XML),
		_RT_RCDATA, "san_policy.xml", &bufsize, FALSE);
	san_policy_path[0] = drive_name[0];
	fd = fopenU(san_policy_path, "wb");
	if ((fd == NULL) || (fwrite(buffer, 1, bufsize, fd) != bufsize)) {
		uprintf("Could not write '%s'\n", san_policy_path);
		if (fd)
			fclose(fd);
	} else {
		fclose(fd);
		// Can't use the one from the USB (at least for Windows 10 preview), as you'll get
		// "Error: 0x800401f0  An error occurred while initializing COM security".
		// On the other hand, using Windows 8.1 dism against Windows 10 doesn't work either
		// (you get a message about needing to upgrade to latest AIK)...
		static_sprintf(cmd, "dism /Image:%s\\ /Apply-Unattend:%s", drive_name, san_policy_path);
		if (RunCommand(cmd, NULL, TRUE) != 0)
			uprintf("Command '%s' failed to run", cmd);
	}
#endif

	uprintf("Copying 'unattend.xml', to disable the use of the Windows Recovery Environment...");
	buffer = GetResource(hMainInstance, MAKEINTRESOURCEA(IDR_TOGO_UNATTEND_XML),
		_RT_RCDATA, "unattend.xml", &bufsize, FALSE);
	unattend_path[0] = drive_name[0];
	fd = fopenU(unattend_path, "wb");
	if ((fd == NULL) || (fwrite(buffer, 1, bufsize, fd) != bufsize))
		uprintf("Could not write '%s'", unattend_path);
	if (fd != NULL)
		fclose(fd);
	UpdateProgressWithInfo(OP_FILE_COPY, MSG_267, wim_nb_files, wim_nb_files);

	return TRUE;
}