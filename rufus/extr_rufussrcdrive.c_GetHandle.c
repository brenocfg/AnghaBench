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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DevPath ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CreateFileA (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DRIVE_ACCESS_RETRIES ; 
 int DRIVE_ACCESS_TIMEOUT ; 
 scalar_t__ DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_SHARING_VIOLATION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FSCTL_ALLOW_EXTENDED_DASD_IO ; 
 int /*<<< orphan*/  FSCTL_LOCK_VOLUME ; 
 int /*<<< orphan*/  FormatStatus ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetTickCount64 () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IS_ERROR (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 scalar_t__ QueryDosDeviceA (char*,char*,int) ; 
 int /*<<< orphan*/  SEARCH_PROCESS_TIMEOUT ; 
 int SearchProcess (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 scalar_t__ TRUE ; 
 char* WindowsErrorString () ; 
 size_t groot_len ; 
 int /*<<< orphan*/  groot_name ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int safe_strlen (char*) ; 
 scalar_t__ safe_strncmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  static_strcpy (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

__attribute__((used)) static HANDLE GetHandle(char* Path, BOOL bLockDrive, BOOL bWriteAccess, BOOL bWriteShare)
{
	int i;
	BYTE access_mask = 0;
	DWORD size;
	uint64_t EndTime;
	HANDLE hDrive = INVALID_HANDLE_VALUE;
	char DevPath[MAX_PATH];

	if ((safe_strlen(Path) < 5) || (Path[0] != '\\') || (Path[1] != '\\') || (Path[3] != '\\'))
		goto out;

	// Resolve a device path, so that we can look for that handle in case of access issues.
	if (safe_strncmp(Path, groot_name, groot_len) == 0)
		static_strcpy(DevPath, &Path[groot_len]);
	else if (QueryDosDeviceA(&Path[4], DevPath, sizeof(DevPath)) == 0)
		strcpy(DevPath, "???");

	for (i = 0; i < DRIVE_ACCESS_RETRIES; i++) {
		// Try without FILE_SHARE_WRITE (unless specifically requested) so that
		// we won't be bothered by the OS or other apps when we set up our data.
		// However this means we might have to wait for an access gap...
		// We keep FILE_SHARE_READ though, as this shouldn't hurt us any, and is
		// required for enumeration.
		hDrive = CreateFileA(Path, GENERIC_READ|(bWriteAccess?GENERIC_WRITE:0),
			FILE_SHARE_READ|(bWriteShare?FILE_SHARE_WRITE:0),
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hDrive != INVALID_HANDLE_VALUE)
			break;
		if ((GetLastError() != ERROR_SHARING_VIOLATION) && (GetLastError() != ERROR_ACCESS_DENIED))
			break;
		if (i == 0) {
			uprintf("Waiting for access on %s [%s]...", Path, DevPath);
		} else if (!bWriteShare && (i > DRIVE_ACCESS_RETRIES/3)) {
			// If we can't seem to get a hold of the drive for some time, try to enable FILE_SHARE_WRITE...
			uprintf("Warning: Could not obtain exclusive rights. Retrying with write sharing enabled...");
			bWriteShare = TRUE;
			// Try to report the process that is locking the drive
			// We also use bit 6 as a flag to indicate that SearchProcess was called.
			access_mask = SearchProcess(DevPath, SEARCH_PROCESS_TIMEOUT, TRUE, TRUE, FALSE) | 0x40;
		}
		Sleep(DRIVE_ACCESS_TIMEOUT / DRIVE_ACCESS_RETRIES);
	}
	if (hDrive == INVALID_HANDLE_VALUE) {
		uprintf("Could not open %s: %s", Path, WindowsErrorString());
		goto out;
	}

	if (bWriteAccess) {
		uprintf("Opened %s for %s write access", Path, bWriteShare?"shared":"exclusive");
	}

	if (bLockDrive) {
		if (DeviceIoControl(hDrive, FSCTL_ALLOW_EXTENDED_DASD_IO, NULL, 0, NULL, 0, &size, NULL)) {
			uprintf("I/O boundary checks disabled");
		}

		EndTime = GetTickCount64() + DRIVE_ACCESS_TIMEOUT;
		do {
			if (DeviceIoControl(hDrive, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &size, NULL))
				goto out;
			if (IS_ERROR(FormatStatus))	// User cancel
				break;
			Sleep(DRIVE_ACCESS_TIMEOUT / DRIVE_ACCESS_RETRIES);
		} while (GetTickCount64() < EndTime);
		// If we reached this section, either we didn't manage to get a lock or the user cancelled
		uprintf("Could not lock access to %s: %s", Path, WindowsErrorString());
		// See if we can report the processes are accessing the drive
		if (!IS_ERROR(FormatStatus) && (access_mask == 0))
			access_mask = SearchProcess(DevPath, SEARCH_PROCESS_TIMEOUT, TRUE, TRUE, FALSE);
		// Try to continue if the only access rights we saw were for read-only
		if ((access_mask & 0x07) != 0x01)
			safe_closehandle(hDrive);
	}

out:
	return hDrive;
}