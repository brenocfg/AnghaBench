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

/* Variables and functions */
 scalar_t__ GetPrivateProfileString (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int ST_DEV_NOTWORK ; 
 int ST_DEV_OK ; 
 int ST_NEUTRAL ; 
 int ST_ROS_CRASH ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gl_ini_file ; 

__attribute__((used)) static int hw_check_ini(wchar_t *name)
{
	wchar_t buff[MAX_PATH];

	if (GetPrivateProfileString(L"HW", name, NULL, buff, MAX_PATH, gl_ini_file) == 0) {
		return ST_NEUTRAL;
	}
	if (_wcsicmp(buff, L"ok") == 0) return ST_DEV_OK;
	if (_wcsicmp(buff, L"notwork") == 0) return ST_DEV_NOTWORK;
	if (_wcsicmp(buff, L"crash") == 0) return ST_ROS_CRASH;
	return ST_NEUTRAL;
}