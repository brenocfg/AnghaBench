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
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  MAX_PATH ; 
 scalar_t__ SHGetPathFromIDListW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walloc (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ wchar_to_utf8_no_alloc (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wfree (char*) ; 
 int /*<<< orphan*/  wpszPath ; 

__attribute__((used)) static __inline BOOL SHGetPathFromIDListU(LPCITEMIDLIST pidl, char* pszPath)
{
	BOOL ret = FALSE;
	DWORD err = ERROR_INVALID_DATA;
	// coverity[returned_null]
	walloc(pszPath, MAX_PATH);
	ret = SHGetPathFromIDListW(pidl, wpszPath);
	err = GetLastError();
	if ((ret) && (wchar_to_utf8_no_alloc(wpszPath, pszPath, MAX_PATH) == 0)) {
		err = GetLastError();
		ret = FALSE;
	}
	wfree(pszPath);
	SetLastError(err);
	return ret;
}