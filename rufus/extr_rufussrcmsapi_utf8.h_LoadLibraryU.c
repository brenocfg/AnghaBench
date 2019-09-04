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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HMODULE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LoadLibraryW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlpFileName ; 

__attribute__((used)) static __inline HMODULE LoadLibraryU(LPCSTR lpFileName)
{
	HMODULE ret;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(lpFileName);
	ret = LoadLibraryW(wlpFileName);
	err = GetLastError();
	wfree(lpFileName);
	SetLastError(err);
	return ret;
}