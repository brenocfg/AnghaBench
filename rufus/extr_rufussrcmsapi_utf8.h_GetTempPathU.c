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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_DATA ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetTempPathW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  walloc (char*,scalar_t__) ; 
 scalar_t__ wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wfree (char*) ; 
 int /*<<< orphan*/  wlpBuffer ; 

__attribute__((used)) static __inline DWORD GetTempPathU(DWORD nBufferLength, char* lpBuffer)
{
	DWORD ret = 0, err = ERROR_INVALID_DATA;
	// coverity[returned_null]
	walloc(lpBuffer, nBufferLength);
	ret = GetTempPathW(nBufferLength, wlpBuffer);
	err = GetLastError();
	if ((ret != 0) && ((ret = wchar_to_utf8_no_alloc(wlpBuffer, lpBuffer, nBufferLength)) == 0)) {
		err = GetLastError();
	}
	wfree(lpBuffer);
	SetLastError(err);
	return ret;
}