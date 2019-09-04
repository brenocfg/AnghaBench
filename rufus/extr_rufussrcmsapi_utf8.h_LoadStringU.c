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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  HINSTANCE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  GetLastError () ; 
 int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walloc (int /*<<< orphan*/ ,int) ; 
 int wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlpBuffer ; 

__attribute__((used)) static __inline int LoadStringU(HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int nBufferMax)
{
	int ret;
	DWORD err = ERROR_INVALID_DATA;
	if (nBufferMax == 0) {
		// read-only pointer to resource mode is not supported
		SetLastError(ERROR_INVALID_PARAMETER);
		return 0;
	}
	// coverity[returned_null]
	walloc(lpBuffer, nBufferMax);
	ret = LoadStringW(hInstance, uID, wlpBuffer, nBufferMax);
	err = GetLastError();
	if ((ret > 0) && ((ret = wchar_to_utf8_no_alloc(wlpBuffer, lpBuffer, nBufferMax)) == 0)) {
		err = GetLastError();
	}
	wfree(lpBuffer);
	SetLastError(err);
	return ret;
}