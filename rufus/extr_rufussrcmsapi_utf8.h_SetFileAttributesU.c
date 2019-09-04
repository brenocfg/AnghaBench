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
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SetFileAttributesW (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int wcslen (int*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 int* wlpFileName ; 

__attribute__((used)) static __inline BOOL SetFileAttributesU(const char* lpFileName, DWORD dwFileAttributes)
{
	BOOL ret = FALSE, err = ERROR_INVALID_DATA;
	wconvert(lpFileName);
	// Unlike Microsoft's version, ours doesn't fail if the string is quoted
	if ((wlpFileName[0] == L'"') && (wlpFileName[wcslen(wlpFileName) - 1] == L'"')) {
		wlpFileName[wcslen(wlpFileName) - 1] = 0;
		ret = SetFileAttributesW(&wlpFileName[1], dwFileAttributes);
	} else {
		ret = SetFileAttributesW(wlpFileName, dwFileAttributes);
	}
	err = GetLastError();
	wfree(lpFileName);
	SetLastError(err);
	return ret;
}