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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_DATA ; 
 scalar_t__ GetFullPathNameW (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  walloc (char*,scalar_t__) ; 
 scalar_t__ wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 int /*<<< orphan*/  wlpBuffer ; 
 int /*<<< orphan*/  wlpFileName ; 

__attribute__((used)) static __inline DWORD GetFullPathNameU(const char* lpFileName, DWORD nBufferLength, char* lpBuffer, char** lpFilePart)
{
	DWORD ret = 0, err = ERROR_INVALID_DATA;
	wchar_t* wlpFilePart;
	wconvert(lpFileName);
	// coverity[returned_null]
	walloc(lpBuffer, nBufferLength);

	// lpFilePart is not supported
	if (lpFilePart != NULL) goto out;

	ret = GetFullPathNameW(wlpFileName, nBufferLength, wlpBuffer, &wlpFilePart);
	err = GetLastError();
	if ((ret != 0) && ((ret = wchar_to_utf8_no_alloc(wlpBuffer, lpBuffer, nBufferLength)) == 0)) {
		err = GetLastError();
	}

out:
	wfree(lpBuffer);
	wfree(lpFileName);
	SetLastError(err);
	return ret;
}