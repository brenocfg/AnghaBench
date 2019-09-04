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
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FILENAME_EXCED_RANGE ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INVALID_FUNCTION ; 
 int /*<<< orphan*/  ERROR_INVALID_NAME ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_NOT_A_REPARSE_POINT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 scalar_t__ QueryDosDeviceA (char*,char*,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pGetVolumeNameForVolumeMountPointA (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetVolumeNameForVolumeMountPointA(void)
{
    BOOL ret;
    char volume[MAX_PATH], path[] = "c:\\";
    DWORD len = sizeof(volume), reti;
    char temp_path[MAX_PATH];

    /* not present before w2k */
    if (!pGetVolumeNameForVolumeMountPointA) {
        win_skip("GetVolumeNameForVolumeMountPointA not found\n");
        return;
    }

    reti = GetTempPathA(MAX_PATH, temp_path);
    ok(reti != 0, "GetTempPathA error %d\n", GetLastError());
    ok(reti < MAX_PATH, "temp path should fit into MAX_PATH\n");

    ret = pGetVolumeNameForVolumeMountPointA(path, volume, 0);
    ok(ret == FALSE, "GetVolumeNameForVolumeMountPointA succeeded\n");
    ok(GetLastError() == ERROR_FILENAME_EXCED_RANGE ||
        GetLastError() == ERROR_INVALID_PARAMETER, /* Vista */
        "wrong error, last=%d\n", GetLastError());

    if (0) { /* these crash on XP */
    ret = pGetVolumeNameForVolumeMountPointA(path, NULL, len);
    ok(ret == FALSE, "GetVolumeNameForVolumeMountPointA succeeded\n");

    ret = pGetVolumeNameForVolumeMountPointA(NULL, volume, len);
    ok(ret == FALSE, "GetVolumeNameForVolumeMountPointA succeeded\n");
    }

    ret = pGetVolumeNameForVolumeMountPointA(path, volume, len);
    ok(ret == TRUE, "GetVolumeNameForVolumeMountPointA failed\n");
    ok(!strncmp( volume, "\\\\?\\Volume{", 11),
        "GetVolumeNameForVolumeMountPointA failed to return valid string <%s>\n",
        volume);

    /* test with too small buffer */
    ret = pGetVolumeNameForVolumeMountPointA(path, volume, 10);
    ok(ret == FALSE && GetLastError() == ERROR_FILENAME_EXCED_RANGE,
            "GetVolumeNameForVolumeMountPointA failed, wrong error returned, was %d, should be ERROR_FILENAME_EXCED_RANGE\n",
             GetLastError());

    /* Try on an arbitrary directory */
    /* On FAT filesystems it seems that GetLastError() is set to
       ERROR_INVALID_FUNCTION. */
    ret = pGetVolumeNameForVolumeMountPointA(temp_path, volume, len);
    ok(ret == FALSE && (GetLastError() == ERROR_NOT_A_REPARSE_POINT ||
        GetLastError() == ERROR_INVALID_FUNCTION),
        "GetVolumeNameForVolumeMountPointA failed on %s, last=%d\n",
        temp_path, GetLastError());

    /* Try on a nonexistent dos drive */
    path[2] = 0;
    for (;path[0] <= 'z'; path[0]++) {
        ret = QueryDosDeviceA( path, volume, len);
        if(!ret) break;
    }
    if (path[0] <= 'z')
    {
        path[2] = '\\';
        ret = pGetVolumeNameForVolumeMountPointA(path, volume, len);
        ok(ret == FALSE && GetLastError() == ERROR_FILE_NOT_FOUND,
            "GetVolumeNameForVolumeMountPointA failed on %s, last=%d\n",
            path, GetLastError());

        /* Try without trailing \ and on a nonexistent dos drive  */
        path[2] = 0;
        ret = pGetVolumeNameForVolumeMountPointA(path, volume, len);
        ok(ret == FALSE && GetLastError() == ERROR_INVALID_NAME,
            "GetVolumeNameForVolumeMountPointA failed on %s, last=%d\n",
            path, GetLastError());
    }
}