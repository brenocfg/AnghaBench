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
typedef  int /*<<< orphan*/  SECURITY_ATTRIBUTES ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* DWORD ;

/* Variables and functions */
 void* ERROR_INVALID_DATA ; 
 void* GetLastError () ; 
 int SHCreateDirectoryExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (void*) ; 
 int /*<<< orphan*/  wconvert (char const*) ; 
 int /*<<< orphan*/  wfree (char const*) ; 
 int /*<<< orphan*/  wpszPath ; 

__attribute__((used)) static __inline int SHCreateDirectoryExU(HWND hwnd, const char* pszPath, SECURITY_ATTRIBUTES *psa)
{
	int ret = ERROR_INVALID_DATA;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(pszPath);
	ret = SHCreateDirectoryExW(hwnd, wpszPath, psa);
	err = GetLastError();
	wfree(pszPath);
	SetLastError(err);
	return ret;
}