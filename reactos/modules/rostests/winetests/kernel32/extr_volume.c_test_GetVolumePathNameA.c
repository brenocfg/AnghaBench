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
typedef  int /*<<< orphan*/  volume_path ;
typedef  int /*<<< orphan*/  test_paths ;
typedef  int /*<<< orphan*/  cwd ;
typedef  int UINT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FILENAME_EXCED_RANGE ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_NAME ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_MORE_DATA ; 
 int /*<<< orphan*/  ExpandEnvironmentStringsA (char const*,char*,int) ; 
 scalar_t__ GetCurrentDirectoryA (int,char*) ; 
 scalar_t__ GetLastError () ; 
 int MAX_PATH ; 
 scalar_t__ NO_ERROR ; 
 scalar_t__ SetEnvironmentVariableA (char*,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pGetVolumePathNameA (char const*,char*,size_t) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetVolumePathNameA(void)
{
    char volume_path[MAX_PATH], cwd[MAX_PATH];
    struct {
        const char *file_name;
        const char *path_name;
        DWORD       path_len;
        DWORD       error;
        DWORD       broken_error;
    } test_paths[] = {
        { /* test 0: NULL parameters, 0 output length */
            NULL, NULL, 0,
            ERROR_INVALID_PARAMETER, 0xdeadbeef /* winxp */
        },
        { /* test 1: empty input, NULL output, 0 output length */
            "", NULL, 0,
            ERROR_INVALID_PARAMETER, 0xdeadbeef /* winxp */
        },
        { /* test 2: valid input, NULL output, 0 output length */
            "C:\\", NULL, 0,
            ERROR_INVALID_PARAMETER, ERROR_FILENAME_EXCED_RANGE /* winxp */
        },
        { /* test 3: valid input, valid output, 0 output length */
            "C:\\", "C:\\", 0,
            ERROR_INVALID_PARAMETER, ERROR_FILENAME_EXCED_RANGE /* winxp */
        },
        { /* test 4: valid input, valid output, 1 output length */
            "C:\\", "C:\\", 1,
            ERROR_FILENAME_EXCED_RANGE, NO_ERROR
        },
        { /* test 5: valid input, valid output, valid output length */
            "C:\\", "C:\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 6: lowercase input, uppercase output, valid output length */
            "c:\\", "C:\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 7: poor quality input, valid output, valid output length */
            "C::", "C:\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 8: really bogus input, valid output, 1 output length */
            "\\\\$$$", "C:\\", 1,
            ERROR_INVALID_NAME, ERROR_FILENAME_EXCED_RANGE
        },
        { /* test 9: a reasonable DOS path that is guaranteed to exist */
            "C:\\windows\\system32", "C:\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 10: a reasonable DOS path that shouldn't exist */
            "C:\\windows\\system32\\AnInvalidFolder", "C:\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 11: a reasonable NT-converted DOS path that shouldn't exist */
            "\\\\?\\C:\\AnInvalidFolder", "\\\\?\\C:\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 12: an unreasonable NT-converted DOS path */
            "\\\\?\\InvalidDrive:\\AnInvalidFolder", "\\\\?\\InvalidDrive:\\" /* win2k, winxp */,
            sizeof(volume_path),
            ERROR_INVALID_NAME, NO_ERROR
        },
        { /* test 13: an unreasonable NT volume path */
            "\\\\?\\Volume{00000000-00-0000-0000-000000000000}\\AnInvalidFolder",
            "\\\\?\\Volume{00000000-00-0000-0000-000000000000}\\" /* win2k, winxp */,
            sizeof(volume_path),
            ERROR_INVALID_NAME, NO_ERROR
        },
        { /* test 14: an unreasonable NT-ish path */
            "\\\\ReallyBogus\\InvalidDrive:\\AnInvalidFolder",
            "\\\\ReallyBogus\\InvalidDrive:\\" /* win2k, winxp */, sizeof(volume_path),
            ERROR_INVALID_NAME, NO_ERROR
        },
        { /* test 15: poor quality input, valid output, valid (but short) output length */
            "C::", "C:\\", 4,
            NO_ERROR, ERROR_MORE_DATA
        },
        { /* test 16: unused drive letter */
            "M::", "C:\\", 4,
            ERROR_FILE_NOT_FOUND, ERROR_MORE_DATA
        },
        { /* test 17: an unreasonable DOS path */
            "InvalidDrive:\\AnInvalidFolder", "%CurrentDrive%\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 18: a reasonable device path */
            "\\??\\CdRom0", "%CurrentDrive%\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 19: an unreasonable device path */
            "\\??\\ReallyBogus", "%CurrentDrive%\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 20 */
            "C:", "C:", 2,
            ERROR_FILENAME_EXCED_RANGE, NO_ERROR
        },
        { /* test 21 */
            "C:", "C:", 3,
            NO_ERROR, ERROR_FILENAME_EXCED_RANGE
        },
        { /* test 22 */
            "C:\\", "C:", 2,
            ERROR_FILENAME_EXCED_RANGE, NO_ERROR
        },
        { /* test 23 */
            "C:\\", "C:", 3,
            NO_ERROR, ERROR_FILENAME_EXCED_RANGE
        },
        { /* test 24 */
            "C::", "C:", 2,
            ERROR_FILENAME_EXCED_RANGE, NO_ERROR
        },
        { /* test 25 */
            "C::", "C:", 3,
            NO_ERROR, ERROR_FILENAME_EXCED_RANGE
        },
        { /* test 26 */
            "C::", "C:\\", 4,
            NO_ERROR, ERROR_MORE_DATA
        },
        { /* test 27 */
            "C:\\windows\\system32\\AnInvalidFolder", "C:", 3,
            NO_ERROR, ERROR_FILENAME_EXCED_RANGE
        },
        { /* test 28 */
            "\\\\?\\C:\\AnInvalidFolder", "\\\\?\\C:", 3,
            ERROR_FILENAME_EXCED_RANGE, NO_ERROR
        },
        { /* test 29 */
            "\\\\?\\C:\\AnInvalidFolder", "\\\\?\\C:", 6,
            ERROR_FILENAME_EXCED_RANGE, NO_ERROR
        },
        { /* test 30 */
            "\\\\?\\C:\\AnInvalidFolder", "\\\\?\\C:", 7,
            NO_ERROR, ERROR_FILENAME_EXCED_RANGE
        },
        { /* test 31 */
            "\\\\?\\c:\\AnInvalidFolder", "\\\\?\\c:", 7,
            NO_ERROR, ERROR_FILENAME_EXCED_RANGE
        },
        { /* test 32 */
            "C:/", "C:\\", 4,
            NO_ERROR, ERROR_MORE_DATA
        },
        { /* test 33 */
            "M:/", "", 4,
            ERROR_FILE_NOT_FOUND, ERROR_MORE_DATA
        },
        { /* test 34 */
            "C:ABC:DEF:\\AnInvalidFolder", "C:\\", 4,
            NO_ERROR, ERROR_MORE_DATA
        },
        { /* test 35 */
            "?:ABC:DEF:\\AnInvalidFolder", "?:\\" /* win2k, winxp */, sizeof(volume_path),
            ERROR_FILE_NOT_FOUND, NO_ERROR
        },
        { /* test 36 */
            "relative/path", "%CurrentDrive%\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 37 */
            "/unix-style/absolute/path", "%CurrentDrive%\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 38 */
            "\\??\\C:\\NonExistent", "%CurrentDrive%\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 39 */
            "\\??\\M:\\NonExistent", "%CurrentDrive%\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 40 */
            "somefile:def", "%CurrentDrive%\\", sizeof(volume_path),
            NO_ERROR, NO_ERROR
        },
        { /* test 41 */
            "s:omefile", "S:\\" /* win2k, winxp */, sizeof(volume_path),
            ERROR_FILE_NOT_FOUND, NO_ERROR
        },
    };
    BOOL ret, success;
    DWORD error;
    UINT i;

    /* GetVolumePathNameA is not present before w2k */
    if (!pGetVolumePathNameA)
    {
        win_skip("required functions not found\n");
        return;
    }

    /* Obtain the drive of the working directory */
    ret = GetCurrentDirectoryA( sizeof(cwd), cwd );
    ok( ret, "Failed to obtain the current working directory.\n" );
    cwd[2] = 0;
    ret = SetEnvironmentVariableA( "CurrentDrive", cwd );
    ok( ret, "Failed to set an environment variable for the current working drive.\n" );

    for (i=0; i<sizeof(test_paths)/sizeof(test_paths[0]); i++)
    {
        BOOL broken_ret = test_paths[i].broken_error == NO_ERROR;
        char *output = (test_paths[i].path_name != NULL ? volume_path : NULL);
        BOOL expected_ret = test_paths[i].error == NO_ERROR;

        volume_path[0] = 0;
        if (test_paths[i].path_len < sizeof(volume_path))
            volume_path[ test_paths[i].path_len ] = 0x11;

        SetLastError( 0xdeadbeef );
        ret = pGetVolumePathNameA( test_paths[i].file_name, output, test_paths[i].path_len );
        error = GetLastError();
        ok(ret == expected_ret || broken(ret == broken_ret),
                                "GetVolumePathName test %d %s unexpectedly.\n",
                                i, test_paths[i].error == NO_ERROR ? "failed" : "succeeded");

        if (ret)
        {
            char path_name[MAX_PATH];

            ExpandEnvironmentStringsA( test_paths[i].path_name, path_name, MAX_PATH);
            /* If we succeeded then make sure the path is correct */
            success = (strcmp( volume_path, path_name ) == 0)
                      || broken(strcasecmp( volume_path, path_name ) == 0) /* XP */;
            ok(success, "GetVolumePathName test %d unexpectedly returned path %s (expected %s).\n",
                        i, volume_path, path_name);
        }
        else
        {
            /* On success Windows always returns ERROR_MORE_DATA, so only worry about failure */
            success = (error == test_paths[i].error || broken(error == test_paths[i].broken_error));
            ok(success, "GetVolumePathName test %d unexpectedly returned error 0x%x (expected 0x%x).\n",
                        i, error, test_paths[i].error);
        }

        if (test_paths[i].path_len < sizeof(volume_path))
            ok(volume_path[ test_paths[i].path_len ] == 0x11,
               "GetVolumePathName test %d corrupted byte after end of buffer.\n", i);
    }
}