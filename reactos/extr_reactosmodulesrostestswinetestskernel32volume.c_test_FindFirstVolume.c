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
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 char* ERROR_FILENAME_EXCED_RANGE ; 
 char* ERROR_MORE_DATA ; 
 char* ERROR_NO_MORE_FILES ; 
 char* GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pFindFirstVolumeA (char*,int) ; 
 scalar_t__ pFindNextVolumeA (scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pFindVolumeClose (scalar_t__) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_FindFirstVolume(void)
{
    char volume[51];
    HANDLE handle;

    /* not present before w2k */
    if (!pFindFirstVolumeA) {
        win_skip("FindFirstVolumeA not found\n");
        return;
    }

    handle = pFindFirstVolumeA( volume, 0 );
    ok( handle == INVALID_HANDLE_VALUE, "succeeded with short buffer\n" );
    ok( GetLastError() == ERROR_MORE_DATA ||  /* XP */
        GetLastError() == ERROR_FILENAME_EXCED_RANGE,  /* Vista */
        "wrong error %u\n", GetLastError() );
    handle = pFindFirstVolumeA( volume, 49 );
    ok( handle == INVALID_HANDLE_VALUE, "succeeded with short buffer\n" );
    ok( GetLastError() == ERROR_FILENAME_EXCED_RANGE, "wrong error %u\n", GetLastError() );
    handle = pFindFirstVolumeA( volume, 51 );
    ok( handle != INVALID_HANDLE_VALUE, "failed err %u\n", GetLastError() );
    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            ok( strlen(volume) == 49, "bad volume name %s\n", volume );
            ok( !memcmp( volume, "\\\\?\\Volume{", 11 ), "bad volume name %s\n", volume );
            ok( !memcmp( volume + 47, "}\\", 2 ), "bad volume name %s\n", volume );
        } while (pFindNextVolumeA( handle, volume, MAX_PATH ));
        ok( GetLastError() == ERROR_NO_MORE_FILES, "wrong error %u\n", GetLastError() );
        pFindVolumeClose( handle );
    }
}