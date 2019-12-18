#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  char WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  MediaType; } ;
typedef  char* LPCSTR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CANCELLED ; 
 int ERROR_GEN_FAILURE ; 
 int ERROR_SEVERITY_ERROR ; 
 int /*<<< orphan*/  EnableVolumeCompression ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FPF_COMPRESSED ; 
 int FP_COMPRESSION ; 
 int FP_QUICK ; 
 size_t FS_EXFAT ; 
 int /*<<< orphan*/ * FileSystemLabel ; 
 int /*<<< orphan*/  FormatEx ; 
 int /*<<< orphan*/  FormatExCallback ; 
 int FormatStatus ; 
 int /*<<< orphan*/  GetLastError () ; 
 char* GetLogicalName (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HRESULT_CODE (int) ; 
 scalar_t__ IS_ERROR (int) ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  MSG_220 ; 
 int /*<<< orphan*/  MSG_222 ; 
 int /*<<< orphan*/  PF_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_INIT_OR_OUT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintInfoDebug (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int SCODE_CODE (int /*<<< orphan*/ ) ; 
 TYPE_1__ SelectedDrive ; 
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 size_t WRITE_RETRIES ; 
 int /*<<< orphan*/  WRITE_TIMEOUT ; 
 int /*<<< orphan*/  WindowsErrorString () ; 
 scalar_t__ dur_mins ; 
 scalar_t__ dur_secs ; 
 int /*<<< orphan*/  fmifs ; 
 float format_percent ; 
 scalar_t__ pfEnableVolumeCompression (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfFormatEx (char*,int /*<<< orphan*/ ,char*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_free (char*) ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ task_number ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 
 char* utf8_to_wchar (char*) ; 
 size_t wcslen (char*) ; 

__attribute__((used)) static BOOL FormatNative(DWORD DriveIndex, uint64_t PartitionOffset, DWORD ClusterSize, LPCSTR FSName, LPCSTR Label, DWORD Flags)
{
	BOOL r = FALSE;
	PF_DECL(FormatEx);
	PF_DECL(EnableVolumeCompression);
	char *locale, *VolumeName = NULL;
	WCHAR* wVolumeName = NULL, *wLabel = utf8_to_wchar(Label), *wFSName = utf8_to_wchar(FSName);
	size_t i;

	if ((strcmp(FSName, FileSystemLabel[FS_EXFAT]) == 0) && !((dur_mins == 0) && (dur_secs == 0))) {
		PrintInfoDebug(0, MSG_220, FSName, dur_mins, dur_secs);
	} else {
		PrintInfoDebug(0, MSG_222, FSName);
	}
	VolumeName = GetLogicalName(DriveIndex, PartitionOffset, TRUE, TRUE);
	wVolumeName = utf8_to_wchar(VolumeName);
	if (wVolumeName == NULL) {
		uprintf("Could not read volume name");
		FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|ERROR_GEN_FAILURE;
		goto out;
	}
	// Hey, nice consistency here, Microsoft! -  FormatEx() fails if wVolumeName has
	// a trailing backslash, but EnableCompression() fails without...
	wVolumeName[wcslen(wVolumeName)-1] = 0;		// Remove trailing backslash

	// LoadLibrary("fmifs.dll") appears to changes the locale, which can lead to
	// problems with tolower(). Make sure we restore the locale. For more details,
	// see http://comments.gmane.org/gmane.comp.gnu.mingw.user/39300
	locale = setlocale(LC_ALL, NULL);
	PF_INIT_OR_OUT(FormatEx, fmifs);
	PF_INIT(EnableVolumeCompression, fmifs);
	setlocale(LC_ALL, locale);

	if (ClusterSize < 0x200) {
		// 0 is FormatEx's value for default, which we need to use for UDF
		ClusterSize = 0;
		uprintf("Using default cluster size");
	} else {
		uprintf("Using cluster size: %d bytes", ClusterSize);
	}
	format_percent = 0.0f;
	task_number = 0;

	uprintf("%s format was selected", (Flags & FP_QUICK) ? "Quick" : "Slow");
	for (i = 0; i < WRITE_RETRIES; i++) {
		pfFormatEx(wVolumeName, SelectedDrive.MediaType, wFSName, wLabel,
			(Flags & FP_QUICK), ClusterSize, FormatExCallback);
		if (!IS_ERROR(FormatStatus) || (HRESULT_CODE(FormatStatus) == ERROR_CANCELLED))
			break;
		uprintf("%s - Retrying...", WindowsErrorString());
		Sleep(WRITE_TIMEOUT);
	}
	if (IS_ERROR(FormatStatus))
		goto out;

	if (Flags & FP_COMPRESSION) {
		wVolumeName[wcslen(wVolumeName)] = '\\';	// Add trailing backslash back again
		if (pfEnableVolumeCompression(wVolumeName, FPF_COMPRESSED)) {
			uprintf("Enabled NTFS compression");
		} else {
			uprintf("Could not enable NTFS compression: %s", WindowsErrorString());
		}
	}

	if (!IS_ERROR(FormatStatus)) {
		uprintf("Format completed.");
		r = TRUE;
	}

out:
	if (!r && !IS_ERROR(FormatStatus))
		FormatStatus = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|SCODE_CODE(GetLastError());
	safe_free(VolumeName);
	safe_free(wVolumeName);
	safe_free(wLabel);
	safe_free(wFSName);
	return r;
}