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
struct TYPE_7__ {int winpe; scalar_t__ uses_minint; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ARRAYSIZE (char const**) ; 
 int ComboBox_GetCurSel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyFileA (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFileA (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int INVALID_FILE_SIZE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFilePointerEx (scalar_t__,TYPE_2__ const,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int WINPE_AMD64 ; 
 int WINPE_I386 ; 
 int WINPE_MININT ; 
 int /*<<< orphan*/  WRITE_RETRIES ; 
 char* WindowsErrorString () ; 
 int /*<<< orphan*/  WriteFileWithRetry (scalar_t__,char*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hDiskID ; 
 TYPE_3__ img_report ; 
 int /*<<< orphan*/ * insert_section_data (char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ max (int,int) ; 
 int /*<<< orphan*/  safe_closehandle (scalar_t__) ; 
 int /*<<< orphan*/  safe_free (char*) ; 
 scalar_t__ safe_strnicmp (char*,char const*,int) ; 
 int /*<<< orphan*/  static_sprintf (char*,char*,char,...) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

__attribute__((used)) static BOOL SetupWinPE(char drive_letter)
{
	char src[64], dst[32];
	const char* basedir[3] = { "i386", "amd64", "minint" };
	const char* patch_str_org[2] = { "\\minint\\txtsetup.sif", "\\minint\\system32\\" };
	const char* patch_str_rep[2][2] = { { "\\i386\\txtsetup.sif", "\\i386\\system32\\" } ,
										{ "\\amd64\\txtsetup.sif", "\\amd64\\system32\\" } };
	const char *win_nt_bt_org = "$win_nt$.~bt";
	const char *rdisk_zero = "rdisk(0)";
	const LARGE_INTEGER liZero = { {0, 0} };
	char setupsrcdev[64];
	HANDLE handle = INVALID_HANDLE_VALUE;
	DWORD i, j, size, rw_size, index = 0;
	BOOL r = FALSE;
	char* buffer = NULL;

	if ((img_report.winpe & WINPE_AMD64) == WINPE_AMD64)
		index = 1;
	else if ((img_report.winpe & WINPE_MININT) == WINPE_MININT)
		index = 2;
	// Allow other values than harddisk 1, as per user choice for disk ID
	static_sprintf(setupsrcdev, "SetupSourceDevice = \"\\device\\harddisk%d\\partition1\"",
		ComboBox_GetCurSel(hDiskID));
	// Copy of ntdetect.com in root
	static_sprintf(src, "%c:\\%s\\ntdetect.com", drive_letter, basedir[2*(index/2)]);
	static_sprintf(dst, "%c:\\ntdetect.com", drive_letter);
	CopyFileA(src, dst, TRUE);
	if (!img_report.uses_minint) {
		// Create a copy of txtsetup.sif, as we want to keep the i386/amd64 files unmodified
		static_sprintf(src, "%c:\\%s\\txtsetup.sif", drive_letter, basedir[index]);
		static_sprintf(dst, "%c:\\txtsetup.sif", drive_letter);
		if (!CopyFileA(src, dst, TRUE)) {
			uprintf("Did not copy %s as %s: %s\n", src, dst, WindowsErrorString());
		}
		if (insert_section_data(dst, "[SetupData]", setupsrcdev, FALSE) == NULL) {
			uprintf("Failed to add SetupSourceDevice in %s\n", dst);
			goto out;
		}
		uprintf("Successfully added '%s' to %s\n", setupsrcdev, dst);
	}

	static_sprintf(src, "%c:\\%s\\setupldr.bin", drive_letter,  basedir[2*(index/2)]);
	static_sprintf(dst, "%c:\\BOOTMGR", drive_letter);
	if (!CopyFileA(src, dst, TRUE)) {
		uprintf("Did not copy %s as %s: %s\n", src, dst, WindowsErrorString());
	}

	// \minint with /minint option doesn't require further processing => return true
	// \minint and no \i386 without /minint is unclear => return error
	if (img_report.winpe&WINPE_MININT) {
		if (img_report.uses_minint) {
			uprintf("Detected \\minint directory with /minint option: nothing to patch\n");
			r = TRUE;
		} else if (!(img_report.winpe&(WINPE_I386|WINPE_AMD64))) {
			uprintf("Detected \\minint directory only but no /minint option: not sure what to do\n");
		}
		goto out;
	}

	// At this stage we only handle \i386
	handle = CreateFileA(dst, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handle == INVALID_HANDLE_VALUE) {
		uprintf("Could not open %s for patching: %s\n", dst, WindowsErrorString());
		goto out;
	}
	size = GetFileSize(handle, NULL);
	if (size == INVALID_FILE_SIZE) {
		uprintf("Could not get size for file %s: %s\n", dst, WindowsErrorString());
		goto out;
	}
	buffer = (char*)malloc(size);
	if (buffer == NULL)
		goto out;
	if ((!ReadFile(handle, buffer, size, &rw_size, NULL)) || (size != rw_size)) {
		uprintf("Could not read file %s: %s\n", dst, WindowsErrorString());
		goto out;
	}
	if (!SetFilePointerEx(handle, liZero, NULL, FILE_BEGIN)) {
		uprintf("Could not rewind file %s: %s\n", dst, WindowsErrorString());
		goto out;
	}

	// Patch setupldr.bin
	uprintf("Patching file %s\n", dst);
	// Remove CRC check for 32 bit part of setupldr.bin from Win2k3
	if ((size > 0x2061) && (buffer[0x2060] == 0x74) && (buffer[0x2061] == 0x03)) {
		buffer[0x2060] = 0xeb;
		buffer[0x2061] = 0x1a;
		uprintf("  0x00002060: 0x74 0x03 -> 0xEB 0x1A (disable Win2k3 CRC check)\n");
	}
	for (i=1; i<size-32; i++) {
		for (j=0; j<ARRAYSIZE(patch_str_org); j++) {
			if (safe_strnicmp(&buffer[i], patch_str_org[j], strlen(patch_str_org[j])-1) == 0) {
				uprintf("  0x%08X: '%s' -> '%s'\n", i, &buffer[i], patch_str_rep[index][j]);
				strcpy(&buffer[i], patch_str_rep[index][j]);
				i += (DWORD)max(strlen(patch_str_org[j]), strlen(patch_str_rep[index][j]));	// in case org is a substring of rep
			}
		}
	}

	if (!img_report.uses_minint) {
		// Additional setupldr.bin/bootmgr patching
		for (i=0; i<size-32; i++) {
			// rdisk(0) -> rdisk(#) disk masquerading
			// NB: only the first one seems to be needed
			if (safe_strnicmp(&buffer[i], rdisk_zero, strlen(rdisk_zero)-1) == 0) {
				buffer[i+6] = 0x30 + ComboBox_GetCurSel(hDiskID);
				uprintf("  0x%08X: '%s' -> 'rdisk(%c)'\n", i, rdisk_zero, buffer[i+6]);
			}
			// $WIN_NT$_~BT -> i386/amd64
			if (safe_strnicmp(&buffer[i], win_nt_bt_org, strlen(win_nt_bt_org)-1) == 0) {
				uprintf("  0x%08X: '%s' -> '%s%s'\n", i, &buffer[i], basedir[index], &buffer[i+strlen(win_nt_bt_org)]);
				strcpy(&buffer[i], basedir[index]);
				// This ensures that we keep the terminator backslash
				buffer[i+strlen(basedir[index])] = buffer[i+strlen(win_nt_bt_org)];
				buffer[i+strlen(basedir[index])+1] = 0;
			}
		}
	}

	if (!WriteFileWithRetry(handle, buffer, size, &rw_size, WRITE_RETRIES)) {
		uprintf("Could not write patched file: %s\n", WindowsErrorString());
		goto out;
	}
	r = TRUE;

out:
	safe_closehandle(handle);
	safe_free(buffer);
	return r;
}