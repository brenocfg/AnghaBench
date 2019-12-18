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
typedef  int /*<<< orphan*/  volume ;
typedef  char WCHAR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILENAME_EXCED_RANGE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pGetVolumeNameForVolumeMountPointW (char*,char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetVolumeNameForVolumeMountPointW(void)
{
    BOOL ret;
    WCHAR volume[MAX_PATH], path[] = {'c',':','\\',0};
    DWORD len = sizeof(volume) / sizeof(WCHAR);

    /* not present before w2k */
    if (!pGetVolumeNameForVolumeMountPointW) {
        win_skip("GetVolumeNameForVolumeMountPointW not found\n");
        return;
    }

    ret = pGetVolumeNameForVolumeMountPointW(path, volume, 0);
    ok(ret == FALSE, "GetVolumeNameForVolumeMountPointW succeeded\n");
    ok(GetLastError() == ERROR_FILENAME_EXCED_RANGE ||
        GetLastError() == ERROR_INVALID_PARAMETER, /* Vista */
        "wrong error, last=%d\n", GetLastError());

    if (0) { /* these crash on XP */
    ret = pGetVolumeNameForVolumeMountPointW(path, NULL, len);
    ok(ret == FALSE, "GetVolumeNameForVolumeMountPointW succeeded\n");

    ret = pGetVolumeNameForVolumeMountPointW(NULL, volume, len);
    ok(ret == FALSE, "GetVolumeNameForVolumeMountPointW succeeded\n");
    }

    ret = pGetVolumeNameForVolumeMountPointW(path, volume, len);
    ok(ret == TRUE, "GetVolumeNameForVolumeMountPointW failed\n");
}