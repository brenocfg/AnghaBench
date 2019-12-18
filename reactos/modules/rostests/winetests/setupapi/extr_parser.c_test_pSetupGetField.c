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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/ * HINF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * ERROR_CALL_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/ * ERROR_INVALID_PARAMETER ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetupCloseInfFile (int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindFirstLineA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  contents ; 
 int /*<<< orphan*/ * getfield_resA ; 
 int /*<<< orphan*/ ** getfield_resW ; 
 int /*<<< orphan*/  lstrcmpA (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lstrlenA (int /*<<< orphan*/ *) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pSetupGetFieldA (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pSetupGetFieldW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * test_file_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_pSetupGetField(void)
{
    UINT err;
    BOOL ret;
    HINF hinf;
    LPCSTR fieldA;
    LPCWSTR fieldW;
    INFCONTEXT context;
    int i;
    int len;
    BOOL unicode = TRUE;

    SetLastError(0xdeadbeef);
    lstrcmpW(NULL, NULL);
    if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("Using A-functions instead of W\n");
        unicode = FALSE;
    }

    hinf = test_file_contents( contents, &err );
    ok( hinf != NULL, "Expected valid INF file\n" );

    ret = SetupFindFirstLineA( hinf, "FileBranchInfo", NULL, &context );
    ok( ret, "Failed to find first line\n" );

    /* native Windows crashes if a NULL context is sent in */

    for ( i = 0; i < 3; i++ )
    {
        if (unicode)
        {
            fieldW = pSetupGetFieldW( &context, i );
            ok( fieldW != NULL, "Failed to get field %i\n", i );
            ok( !lstrcmpW( getfield_resW[i], fieldW ), "Wrong string returned\n" );
        }
        else
        {
            fieldA = pSetupGetFieldA( &context, i );
            ok( fieldA != NULL, "Failed to get field %i\n", i );
            ok( !lstrcmpA( getfield_resA[i], fieldA ), "Wrong string returned\n" );
        }
    }

    if (unicode)
    {
        fieldW = pSetupGetFieldW( &context, 3 );
        ok( fieldW != NULL, "Failed to get field 3\n" );
        len = lstrlenW( fieldW );
        ok( len == 511 || /* NT4, W2K, XP and W2K3 */
            len == 4096,  /* Vista */
            "Unexpected length, got %d\n", len );

        fieldW = pSetupGetFieldW( &context, 4 );
        ok( fieldW == NULL, "Expected NULL, got %p\n", fieldW );
        ok( GetLastError() == ERROR_INVALID_PARAMETER,
            "Expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError() );
    }
    else
    {
        fieldA = pSetupGetFieldA( &context, 3 );
        ok( fieldA != NULL, "Failed to get field 3\n" );
        len = lstrlenA( fieldA );
        ok( len == 511, /* Win9x, WinME */
            "Unexpected length, got %d\n", len );

        fieldA = pSetupGetFieldA( &context, 4 );
        ok( fieldA == NULL, "Expected NULL, got %p\n", fieldA );
        ok( GetLastError() == ERROR_INVALID_PARAMETER,
            "Expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError() );
    }

    SetupCloseInfFile( hinf );
}