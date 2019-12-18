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
typedef  int /*<<< orphan*/  newprofileA ;
typedef  int /*<<< orphan*/  newprofile ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
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
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcmpiA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * machineW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int pGetStandardColorSpaceProfileW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int pSetStandardColorSpaceProfileW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_GetStandardColorSpaceProfileW( WCHAR *standardprofileW )
{
    BOOL ret;
    DWORD size;
    WCHAR oldprofile[MAX_PATH];
    WCHAR newprofile[MAX_PATH];
    CHAR newprofileA[MAX_PATH];

    /* Parameter checks */

    /* Single invalid parameter checks: */

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 1st param, */
    ret = pGetStandardColorSpaceProfileW(machineW, LCS_sRGB, newprofile, &size);
    ok( !ret && GetLastError() == ERROR_NOT_SUPPORTED, "GetStandardColorSpaceProfileW() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 2nd param, */
    ret = pGetStandardColorSpaceProfileW(NULL, (DWORD)-1, newprofile, &size);
    ok( !ret && GetLastError() == ERROR_FILE_NOT_FOUND, "GetStandardColorSpaceProfileW() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 2nd param, */
    ret = pGetStandardColorSpaceProfileW(NULL, 0, newprofile, &size);
    ok( (!ret && GetLastError() == ERROR_FILE_NOT_FOUND) ||
        broken(ret), /* Win98 and WinME */
        "GetStandardColorSpaceProfileW() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 3rd param, */
    ret = pGetStandardColorSpaceProfileW(NULL, LCS_sRGB, NULL, &size);
    ok( !ret || broken(ret) /* win98 */, "GetStandardColorSpaceProfileW succeeded\n" );
    ok( GetLastError() == ERROR_INSUFFICIENT_BUFFER ||
        broken(GetLastError() == 0xfaceabee) /* win98 */,
        "GetStandardColorSpaceProfileW() returns GLE=%u\n", GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* 4th param, */
    ret = pGetStandardColorSpaceProfileW(NULL, LCS_sRGB, newprofile, NULL);
    ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER, "GetStandardColorSpaceProfileW() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = 0;
    SetLastError(0xfaceabee); /* dereferenced 4th param. */
    ret = pGetStandardColorSpaceProfileW(NULL, LCS_sRGB, newprofile, &size);
    ok( !ret || broken(ret) /* win98 */, "GetStandardColorSpaceProfileW succeeded\n" );
    ok( GetLastError() == ERROR_MORE_DATA ||
        GetLastError() == ERROR_INSUFFICIENT_BUFFER ||
        broken(GetLastError() == 0xfaceabee) /* win98 */,
        "GetStandardColorSpaceProfileW() returns GLE=%u\n", GetLastError() );

    /* Several invalid parameter checks: */

    size = 0;
    SetLastError(0xfaceabee); /* 1st, maybe 2nd and then dereferenced 4th param, */
    ret = pGetStandardColorSpaceProfileW(machineW, 0, newprofile, &size);
    ok( !ret && (GetLastError() == ERROR_INVALID_PARAMETER || GetLastError() == ERROR_NOT_SUPPORTED),
        "GetStandardColorSpaceProfileW() returns %d (GLE=%d)\n", ret, GetLastError() );

    SetLastError(0xfaceabee); /* maybe 2nd and then 4th param, */
    ret = pGetStandardColorSpaceProfileW(NULL, 0, newprofile, NULL);
    ok( !ret && GetLastError() == ERROR_INVALID_PARAMETER, "GetStandardColorSpaceProfileW() returns %d (GLE=%d)\n", ret, GetLastError() );

    size = 0;
    SetLastError(0xfaceabee); /* maybe 2nd, then 3rd and dereferenced 4th param, */
    ret = pGetStandardColorSpaceProfileW(NULL, 0, NULL, &size);
    ok( !ret || broken(ret) /* win98 */, "GetStandardColorSpaceProfileW succeeded\n" );
    ok( GetLastError() == ERROR_INSUFFICIENT_BUFFER ||
        GetLastError() == ERROR_FILE_NOT_FOUND ||
        broken(GetLastError() == 0xfaceabee) /* win98 */,
        "GetStandardColorSpaceProfileW() returns GLE=%u\n", GetLastError() );

    size = sizeof(newprofile);
    SetLastError(0xfaceabee); /* maybe 2nd param. */
    ret = pGetStandardColorSpaceProfileW(NULL, 0, newprofile, &size);
    if (!ret) ok( GetLastError() == ERROR_FILE_NOT_FOUND, "GetStandardColorSpaceProfileW() returns %d (GLE=%d)\n", ret, GetLastError() );
    else
    {
        WideCharToMultiByte(CP_ACP, 0, newprofile, -1, newprofileA, sizeof(newprofileA), NULL, NULL);
        ok( !lstrcmpiA( newprofileA, "" ) && GetLastError() == 0xfaceabee,
             "GetStandardColorSpaceProfileW() returns %d (GLE=%d)\n", ret, GetLastError() );
    }

    /* Functional checks */

    size = sizeof(oldprofile);
    ret = pGetStandardColorSpaceProfileW( NULL, LCS_sRGB, oldprofile, &size );
    ok( ret, "GetStandardColorSpaceProfileW() failed (%d)\n", GetLastError() );

    SetLastError(0xdeadbeef);
    ret = pSetStandardColorSpaceProfileW( NULL, LCS_sRGB, standardprofileW );
    if (!ret && (GetLastError() == ERROR_ACCESS_DENIED))
    {
        skip("Not enough rights for SetStandardColorSpaceProfileW\n");
        return;
    }
    ok( ret, "SetStandardColorSpaceProfileW() failed (%d)\n", GetLastError() );

    size = sizeof(newprofile);
    ret = pGetStandardColorSpaceProfileW( NULL, LCS_sRGB, newprofile, &size );
    ok( ret, "GetStandardColorSpaceProfileW() failed (%d)\n", GetLastError() );

    ret = pSetStandardColorSpaceProfileW( NULL, LCS_sRGB, oldprofile );
    ok( ret, "SetStandardColorSpaceProfileW() failed (%d)\n", GetLastError() );
}