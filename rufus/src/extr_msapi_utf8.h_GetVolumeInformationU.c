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
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPDWORD ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetVolumeInformationW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlpFileSystemNameBuffer ; 
 int /*<<< orphan*/  wlpRootPathName ; 
 int /*<<< orphan*/  wlpVolumeNameBuffer ; 

__attribute__((used)) static __inline BOOL GetVolumeInformationU(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer,
	DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength,
	LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize)
{
	BOOL ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(lpRootPathName);
	// coverity[returned_null]
	walloc(lpVolumeNameBuffer, nVolumeNameSize);
	// coverity[returned_null]
	walloc(lpFileSystemNameBuffer, nFileSystemNameSize);

	ret = GetVolumeInformationW(wlpRootPathName, wlpVolumeNameBuffer, nVolumeNameSize,
		lpVolumeSerialNumber, lpMaximumComponentLength, lpFileSystemFlags,
		wlpFileSystemNameBuffer, nFileSystemNameSize);
	err = GetLastError();
	if (ret) {
		if ( ((lpVolumeNameBuffer != NULL) && (wchar_to_utf8_no_alloc(wlpVolumeNameBuffer,
			lpVolumeNameBuffer, nVolumeNameSize) == 0))
		  || ((lpFileSystemNameBuffer != NULL) && (wchar_to_utf8_no_alloc(wlpFileSystemNameBuffer,
			lpFileSystemNameBuffer, nFileSystemNameSize) == 0)) ) {
			err = GetLastError();
			ret = FALSE;
		}
	}
	wfree(lpVolumeNameBuffer);
	wfree(lpFileSystemNameBuffer);
	wfree(lpRootPathName);
	SetLastError(err);
	return ret;
}