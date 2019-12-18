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
struct TYPE_5__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {TYPE_1__ member_0; } ;
typedef  int* LPDWORD ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CheckDriveAccess (int,scalar_t__) ; 
 int ERROR_SEVERITY_ERROR ; 
 scalar_t__ ERROR_SUCCESS ; 
 int ERROR_WRITE_FAULT ; 
 int FAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FACILITY_STORAGE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 int GetLastError () ; 
 int LastWriteError ; 
 scalar_t__ SCODE_CODE (int) ; 
 scalar_t__ SetFilePointerEx (int /*<<< orphan*/ ,TYPE_2__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int WRITE_TIMEOUT ; 
 int WindowsErrorString () ; 
 scalar_t__ WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ large_drive ; 
 int /*<<< orphan*/  uprintf (char*,...) ; 

BOOL WriteFileWithRetry(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite,
	LPDWORD lpNumberOfBytesWritten, DWORD nNumRetries)
{
	DWORD nTry;
	BOOL readFilePointer;
	LARGE_INTEGER liFilePointer, liZero = { { 0,0 } };

	// Need to get the current file pointer in case we need to retry
	readFilePointer = SetFilePointerEx(hFile, liZero, &liFilePointer, FILE_CURRENT);
	if (!readFilePointer)
		uprintf("Warning: Could not read file pointer %s", WindowsErrorString());

	if (nNumRetries == 0)
		nNumRetries = 1;
	for (nTry = 1; nTry <= nNumRetries; nTry++) {
		// Need to rewind our file position on retry - if we can't even do that, just give up
		if ((nTry > 1) && (!SetFilePointerEx(hFile, liFilePointer, NULL, FILE_BEGIN))) {
			uprintf("Could not set file pointer - Aborting");
			break;
		}
		if (WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, NULL)) {
			LastWriteError = 0;
			if (nNumberOfBytesToWrite == *lpNumberOfBytesWritten)
				return TRUE;
			// Some large drives return 0, even though all the data was written - See github #787 */
			if (large_drive && (*lpNumberOfBytesWritten == 0)) {
				uprintf("Warning: Possible short write");
				return TRUE;
			}
			uprintf("Wrote %d bytes but requested %d", *lpNumberOfBytesWritten, nNumberOfBytesToWrite);
		} else {
			uprintf("Write error %s", WindowsErrorString());
			LastWriteError = ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|GetLastError();
		}
		// If we can't reposition for the next run, just abort
		if (!readFilePointer)
			break;
		if (nTry < nNumRetries) {
			uprintf("Retrying in %d seconds...", WRITE_TIMEOUT / 1000);
			// Don't sit idly but use the downtime to check for conflicting processes...
			Sleep(CheckDriveAccess(WRITE_TIMEOUT, FALSE));
		}
	}
	if (SCODE_CODE(GetLastError()) == ERROR_SUCCESS)
		SetLastError(ERROR_SEVERITY_ERROR|FAC(FACILITY_STORAGE)|ERROR_WRITE_FAULT);
	return FALSE;
}