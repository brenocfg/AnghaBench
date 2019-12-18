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

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_DATA ; 
 int /*<<< orphan*/  GetLastError () ; 
 int PathGetDriveNumberW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wconvert (char*) ; 
 int /*<<< orphan*/  wfree (char*) ; 
 int /*<<< orphan*/  wlpPath ; 

__attribute__((used)) static __inline int PathGetDriveNumberU(char* lpPath)
{
	int ret = 0;
	DWORD err = ERROR_INVALID_DATA;
	wconvert(lpPath);
	ret = PathGetDriveNumberW(wlpPath);
	err = GetLastError();
	wfree(lpPath);
	SetLastError(err);
	return ret;
}