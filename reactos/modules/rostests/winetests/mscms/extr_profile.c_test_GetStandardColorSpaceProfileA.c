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
typedef  int /*<<< orphan*/  oldprofile ;
typedef  int /*<<< orphan*/  newprofile ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_ACCESS_DENIED ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_MORE_DATA ; 
 int ERROR_NOT_SUPPORTED ; 
 int GetLastError () ; 
 int LCS_sRGB ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/ * machine ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  pGetStandardColorSpaceProfileA (int /*<<< orphan*/ *,int,char*,int*) ; 
 int /*<<< orphan*/  pSetStandardColorSpaceProfileA (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_GetStandardColorSpaceProfileA( char *standardprofile )
{
    BOOL ret;
    DWORD size;
    CHAR oldprofile[MAX_PATH];
    CHAR newprofile[MAX_PATH];

    /* Parameter checks */

    /* Single invalid parameter checks: */

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 1st param, */
    ret = pGetStandardColorSpaceProfileA(machine, LCS_sRGB, newprofile, &size);
    ok( !ret && GetLastError() == ERROR_NOT_SUPPORTED, "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 2nd param, */
    ret = pGetStandardColorSpaceProfileA(NULL, (DWORD)-1, newprofile, &size);
    ok( !ret && GetLastError() == ERROR_FILE_NOT_FOUND, "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 4th param, */
    ret = pGetStandardColorSpaceProfileA(NULL, LCS_sRGB, newprofile, NULL);
    ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER, "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 3rd param, */
    ret = pGetStandardColorSpaceProfileA(NULL, LCS_sRGB, NULL, &size);
    ok( !ret && GetLastError() == ERROR_INSUFFICIENT_BUFFER, "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = 0;
    SetLastError(0xfaceabee); /* dereferenced 4th param, */
    ret = pGetStandardColorSpaceProfileA(NULL, LCS_sRGB, newprofile, &size);
    ok( !ret && (GetLastError() == ERROR_MORE_DATA || GetLastError() == ERROR_INSUFFICIENT_BUFFER),
        "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    /* Several invalid parameter checks: */

    size = 0;
    SetLastError(0xfaceabee); /* 1st, maybe 2nd and then dereferenced 4th param, */
    ret = pGetStandardColorSpaceProfileA(machine, 0, newprofile, &size);
    ok( !ret && (GetLastError() == ERROR_INVALID_PARAMETER || GetLastError() == ERROR_NOT_SUPPORTED),
        "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    SetLastError(0xfaceabee); /* maybe 2nd and then 4th param, */
    ret = pGetStandardColorSpaceProfileA(NULL, 0, newprofile, NULL);
    ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER, "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = 0;
    SetLastError(0xfaceabee); /* maybe 2nd, then 3rd and dereferenced 4th param, */
    ret = pGetStandardColorSpaceProfileA(NULL, 0, NULL, &size);
    ok( !ret && (GetLastError() == ERROR_INSUFFICIENT_BUFFER || GetLastError() == ERROR_FILE_NOT_FOUND),
        "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* maybe 2nd param. */
    ret = pGetStandardColorSpaceProfileA(NULL, 0, newprofile, &size);
    if (!ret) ok( GetLastError() == ERROR_FILE_NOT_FOUND, "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );
    else ok( !lstrcmpiA( newprofile, "" ) && GetLastError() == 0xfaceabee,
             "GetStandardColorSpaceProfileA() returns %d (GLE=%d)\n", ret, GetLastError() );

    /* Functional checks */

    size = sizeof(oldprofile);
    ret = pGetStandardColorSpaceProfileA( NULL, LCS_sRGB, oldprofile, &size );
    ok( ret, "GetStandardColorSpaceProfileA() failed (%d)\n", GetLastError() );

    SetLastError(0xdeadbeef);
    ret = pSetStandardColorSpaceProfileA( NULL, LCS_sRGB, standardprofile );
    if (!ret && (GetLastError() == ERROR_ACCESS_DENIED))
    {
        skip("Not enough rights for SetStandardColorSpaceProfileA\n");
        return;
    }
    ok( ret, "SetStandardColorSpaceProfileA() failed (%d)\n", GetLastError() );

    size = sizeof(newprofile);
    ret = pGetStandardColorSpaceProfileA( NULL, LCS_sRGB, newprofile, &size );
    ok( ret, "GetStandardColorSpaceProfileA() failed (%d)\n", GetLastError() );

    ret = pSetStandardColorSpaceProfileA( NULL, LCS_sRGB, oldprofile );
    ok( ret, "SetStandardColorSpaceProfileA() failed (%d)\n", GetLastError() );
}