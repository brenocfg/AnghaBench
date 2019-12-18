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
typedef  int /*<<< orphan*/  windowsdir ;
typedef  int UINT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_DIR_NOT_ROOT ; 
 int /*<<< orphan*/  ERROR_INVALID_NAME ; 
 int GetCurrentDirectoryA (int,char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int GetWindowsDirectoryA (char*,int) ; 
 int MAX_PATH ; 
 int SetCurrentDirectoryA (char*) ; 
 int SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pGetVolumeInformationA (char*,char*,int,int*,int*,int*,char*,int) ; 
 int pGetVolumeNameForVolumeMountPointA (char*,char*,int) ; 
 int /*<<< orphan*/  skip (char*,char) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ toupper (char) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetVolumeInformationA(void)
{
    BOOL ret;
    UINT result;
    char Root_Colon[]="C:";
    char Root_Slash[]="C:\\";
    char Root_UNC[]="\\\\?\\C:\\";
    char volume[MAX_PATH+1];
    DWORD vol_name_size=MAX_PATH+1, vol_serial_num=-1, max_comp_len=0, fs_flags=0, fs_name_len=MAX_PATH+1;
    char vol_name_buf[MAX_PATH+1], fs_name_buf[MAX_PATH+1];
    char windowsdir[MAX_PATH+10];
    char currentdir[MAX_PATH+1];

    ok( pGetVolumeInformationA != NULL, "GetVolumeInformationA not found\n");
    if(!pGetVolumeInformationA) {
        return;
    }

    /* get windows drive letter and update strings for testing */
    result = GetWindowsDirectoryA(windowsdir, sizeof(windowsdir));
    ok(result < sizeof(windowsdir), "windowsdir is abnormally long!\n");
    ok(result != 0, "GetWindowsDirectory: error %d\n", GetLastError());
    Root_Colon[0] = windowsdir[0];
    Root_Slash[0] = windowsdir[0];
    Root_UNC[4] = windowsdir[0];

    result = GetCurrentDirectoryA(MAX_PATH, currentdir);
    ok(result, "GetCurrentDirectory: error %d\n", GetLastError());
    /* Note that GetCurrentDir yields no trailing slash for subdirs */

    /* check for NO error on no trailing \ when current dir is root dir */
    ret = SetCurrentDirectoryA(Root_Slash);
    ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());
    ret = pGetVolumeInformationA(Root_Colon, vol_name_buf, vol_name_size, NULL,
            NULL, NULL, fs_name_buf, fs_name_len);
    ok(ret, "GetVolumeInformationA root failed, last error %u\n", GetLastError());

    /* check for error on no trailing \ when current dir is subdir (windows) of queried drive */
    ret = SetCurrentDirectoryA(windowsdir);
    ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = pGetVolumeInformationA(Root_Colon, vol_name_buf, vol_name_size, NULL,
            NULL, NULL, fs_name_buf, fs_name_len);
    ok(!ret && (GetLastError() == ERROR_INVALID_NAME),
        "GetVolumeInformationA did%s fail, last error %u\n", ret ? " not":"", GetLastError());

    /* reset current directory */
    ret = SetCurrentDirectoryA(currentdir);
    ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());

    if (toupper(currentdir[0]) == toupper(windowsdir[0])) {
        skip("Please re-run from another device than %c:\n", windowsdir[0]);
        /* FIXME: Use GetLogicalDrives to find another device to avoid this skip. */
    } else {
        char Root_Env[]="=C:"; /* where MS maintains the per volume directory */
        Root_Env[1] = windowsdir[0];

        /* C:\windows becomes the current directory on drive C: */
        /* Note that paths to subdirs are stored without trailing slash, like what GetCurrentDir yields. */
        ret = SetEnvironmentVariableA(Root_Env, windowsdir);
        ok(ret, "SetEnvironmentVariable %s failed\n", Root_Env);

        ret = SetCurrentDirectoryA(windowsdir);
        ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());
        ret = SetCurrentDirectoryA(currentdir);
        ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());

        /* windows dir is current on the root drive, call fails */
        SetLastError(0xdeadbeef);
        ret = pGetVolumeInformationA(Root_Colon, vol_name_buf, vol_name_size, NULL,
                NULL, NULL, fs_name_buf, fs_name_len);
        ok(!ret && (GetLastError() == ERROR_INVALID_NAME),
           "GetVolumeInformationA did%s fail, last error %u\n", ret ? " not":"", GetLastError());

        /* Try normal drive letter with trailing \ */
        ret = pGetVolumeInformationA(Root_Slash, vol_name_buf, vol_name_size, NULL,
                NULL, NULL, fs_name_buf, fs_name_len);
        ok(ret, "GetVolumeInformationA with \\ failed, last error %u\n", GetLastError());

        ret = SetCurrentDirectoryA(Root_Slash);
        ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());
        ret = SetCurrentDirectoryA(currentdir);
        ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());

        /* windows dir is STILL CURRENT on root drive; the call fails as before,   */
        /* proving that SetCurrentDir did not remember the other drive's directory */
        SetLastError(0xdeadbeef);
        ret = pGetVolumeInformationA(Root_Colon, vol_name_buf, vol_name_size, NULL,
                NULL, NULL, fs_name_buf, fs_name_len);
        ok(!ret && (GetLastError() == ERROR_INVALID_NAME),
           "GetVolumeInformationA did%s fail, last error %u\n", ret ? " not":"", GetLastError());

        /* Now C:\ becomes the current directory on drive C: */
        ret = SetEnvironmentVariableA(Root_Env, Root_Slash); /* set =C:=C:\ */
        ok(ret, "SetEnvironmentVariable %s failed\n", Root_Env);

        /* \ is current on root drive, call succeeds */
        ret = pGetVolumeInformationA(Root_Colon, vol_name_buf, vol_name_size, NULL,
                NULL, NULL, fs_name_buf, fs_name_len);
        ok(ret, "GetVolumeInformationA failed, last error %u\n", GetLastError());

        /* again, SetCurrentDirectory on another drive does not matter */
        ret = SetCurrentDirectoryA(Root_Slash);
        ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());
        ret = SetCurrentDirectoryA(currentdir);
        ok(ret, "SetCurrentDirectory: error %d\n", GetLastError());

        /* \ is current on root drive, call succeeds */
        ret = pGetVolumeInformationA(Root_Colon, vol_name_buf, vol_name_size, NULL,
                NULL, NULL, fs_name_buf, fs_name_len);
        ok(ret, "GetVolumeInformationA failed, last error %u\n", GetLastError());
    }

    /* try null root directory to return "root of the current directory"  */
    ret = pGetVolumeInformationA(NULL, vol_name_buf, vol_name_size, NULL,
            NULL, NULL, fs_name_buf, fs_name_len);
    ok(ret, "GetVolumeInformationA failed on null root dir, last error %u\n", GetLastError());

    /* Try normal drive letter with trailing \  */
    ret = pGetVolumeInformationA(Root_Slash, vol_name_buf, vol_name_size,
            &vol_serial_num, &max_comp_len, &fs_flags, fs_name_buf, fs_name_len);
    ok(ret, "GetVolumeInformationA failed, root=%s, last error=%u\n", Root_Slash, GetLastError());

    /* try again with drive letter and the "disable parsing" prefix */
    SetLastError(0xdeadbeef);
    ret = pGetVolumeInformationA(Root_UNC, vol_name_buf, vol_name_size,
            &vol_serial_num, &max_comp_len, &fs_flags, fs_name_buf, fs_name_len);
    ok(ret, "GetVolumeInformationA did%s fail, root=%s, last error=%u\n", ret ? " not":"", Root_UNC, GetLastError());

    /* try again with device name space  */
    Root_UNC[2] = '.';
    SetLastError(0xdeadbeef);
    ret = pGetVolumeInformationA(Root_UNC, vol_name_buf, vol_name_size,
            &vol_serial_num, &max_comp_len, &fs_flags, fs_name_buf, fs_name_len);
    ok(ret, "GetVolumeInformationA did%s fail, root=%s, last error=%u\n", ret ? " not":"", Root_UNC, GetLastError());

    /* try again with a directory off the root - should generate error  */
    if (windowsdir[strlen(windowsdir)-1] != '\\') strcat(windowsdir, "\\");
    SetLastError(0xdeadbeef);
    ret = pGetVolumeInformationA(windowsdir, vol_name_buf, vol_name_size,
            &vol_serial_num, &max_comp_len, &fs_flags, fs_name_buf, fs_name_len);
    ok(!ret && (GetLastError()==ERROR_DIR_NOT_ROOT),
          "GetVolumeInformationA did%s fail, root=%s, last error=%u\n", ret ? " not":"", windowsdir, GetLastError());
    /* A subdir with trailing \ yields DIR_NOT_ROOT instead of INVALID_NAME */
    if (windowsdir[strlen(windowsdir)-1] == '\\') windowsdir[strlen(windowsdir)-1] = 0;
    SetLastError(0xdeadbeef);
    ret = pGetVolumeInformationA(windowsdir, vol_name_buf, vol_name_size,
            &vol_serial_num, &max_comp_len, &fs_flags, fs_name_buf, fs_name_len);
    ok(!ret && (GetLastError()==ERROR_INVALID_NAME),
          "GetVolumeInformationA did%s fail, root=%s, last error=%u\n", ret ? " not":"", windowsdir, GetLastError());

    if (!pGetVolumeNameForVolumeMountPointA) {
        win_skip("GetVolumeNameForVolumeMountPointA not found\n");
        return;
    }
    /* get the unique volume name for the windows drive  */
    ret = pGetVolumeNameForVolumeMountPointA(Root_Slash, volume, MAX_PATH);
    ok(ret == TRUE, "GetVolumeNameForVolumeMountPointA failed\n");

    /* try again with unique volume name */
    ret = pGetVolumeInformationA(volume, vol_name_buf, vol_name_size,
            &vol_serial_num, &max_comp_len, &fs_flags, fs_name_buf, fs_name_len);
    ok(ret, "GetVolumeInformationA failed, root=%s, last error=%u\n", volume, GetLastError());
}