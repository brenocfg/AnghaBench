#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_2__ {int member_0; int member_1; int member_2; } ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/ * DLL_DIRECTORY_COOKIE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERROR_MOD_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetModuleFileNameA (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int LOAD_LIBRARY_SEARCH_APPLICATION_DIR ; 
 int LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR ; 
 int LOAD_LIBRARY_SEARCH_SYSTEM32 ; 
 int LOAD_LIBRARY_SEARCH_USER_DIRS ; 
 int /*<<< orphan*/ * LoadLibraryExA (char*,int /*<<< orphan*/ ,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  create_test_dll (char*) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pAddDllDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pRemoveDllDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pSetDllDirectoryA (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_LoadLibraryEx_search_flags(void)
{
    static const struct
    {
        int add_dirs[4];
        int dll_dir;
        int expect;
    } tests[] =
    {
        { { 1, 2, 3 }, 4, 3 }, /* 0 */
        { { 1, 3, 2 }, 4, 2 },
        { { 3, 1 },    4, 1 },
        { { 5, 6 },    4, 4 },
        { { 5, 2 },    4, 2 },
        { { 0 },       4, 4 }, /* 5 */
        { { 0 },       0, 0 },
        { { 6, 5 },    5, 0 },
        { { 1, 1, 2 }, 0, 2 },
    };
    char *p, path[MAX_PATH], buf[MAX_PATH];
    WCHAR bufW[MAX_PATH];
    DLL_DIRECTORY_COOKIE cookies[4];
    unsigned int i, j, k;
    BOOL ret;
    HMODULE mod;

    if (!pAddDllDirectory || !pSetDllDirectoryA) return;

    GetTempPathA( sizeof(path), path );
    GetTempFileNameA( path, "tmp", 0, buf );
    DeleteFileA( buf );
    ret = CreateDirectoryA( buf, NULL );
    ok( ret, "CreateDirectory failed err %u\n", GetLastError() );
    p = buf + strlen( buf );
    for (i = 1; i <= 6; i++)
    {
        sprintf( p, "\\%u", i );
        ret = CreateDirectoryA( buf, NULL );
        ok( ret, "CreateDirectory failed err %u\n", GetLastError() );
        if (i >= 5) continue;  /* dirs 5 and 6 are left empty */
        sprintf( p, "\\%u\\winetestdll.dll", i );
        create_test_dll( buf );
    }
    SetLastError( 0xdeadbeef );
    mod = LoadLibraryExA( "winetestdll.dll", 0, LOAD_LIBRARY_SEARCH_APPLICATION_DIR );
    ok( !mod, "LoadLibrary succeeded\n" );
    ok( GetLastError() == ERROR_MOD_NOT_FOUND, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    mod = LoadLibraryExA( "winetestdll.dll", 0, LOAD_LIBRARY_SEARCH_USER_DIRS );
    ok( !mod, "LoadLibrary succeeded\n" );
    ok( GetLastError() == ERROR_MOD_NOT_FOUND || broken(GetLastError() == ERROR_NOT_ENOUGH_MEMORY),
        "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    mod = LoadLibraryExA( "winetestdll.dll", 0, LOAD_LIBRARY_SEARCH_SYSTEM32 );
    ok( !mod, "LoadLibrary succeeded\n" );
    ok( GetLastError() == ERROR_MOD_NOT_FOUND, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    mod = LoadLibraryExA( "winetestdll.dll", 0, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR );
    ok( !mod, "LoadLibrary succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    mod = LoadLibraryExA( "winetestdll.dll", 0, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32 );
    ok( !mod, "LoadLibrary succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    mod = LoadLibraryExA( "foo\\winetestdll.dll", 0, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR );
    ok( !mod, "LoadLibrary succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    mod = LoadLibraryExA( "\\windows\\winetestdll.dll", 0, LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR );
    ok( !mod, "LoadLibrary succeeded\n" );
    ok( GetLastError() == ERROR_MOD_NOT_FOUND, "wrong error %u\n", GetLastError() );

    for (j = 0; j < sizeof(tests) / sizeof(tests[0]); j++)
    {
        for (k = 0; tests[j].add_dirs[k]; k++)
        {
            sprintf( p, "\\%u", tests[j].add_dirs[k] );
            MultiByteToWideChar( CP_ACP, 0, buf, -1, bufW, MAX_PATH );
            cookies[k] = pAddDllDirectory( bufW );
            ok( cookies[k] != NULL, "failed to add %s\n", buf );
        }
        if (tests[j].dll_dir)
        {
            sprintf( p, "\\%u", tests[j].dll_dir );
            pSetDllDirectoryA( buf );
        }
        else pSetDllDirectoryA( NULL );

        SetLastError( 0xdeadbeef );
        mod = LoadLibraryExA( "winetestdll.dll", 0, LOAD_LIBRARY_SEARCH_USER_DIRS );
        if (tests[j].expect)
        {
            ok( mod != NULL, "%u: LoadLibrary failed err %u\n", j, GetLastError() );
            GetModuleFileNameA( mod, path, MAX_PATH );
            sprintf( p, "\\%u\\winetestdll.dll", tests[j].expect );
            ok( !lstrcmpiA( path, buf ), "%u: wrong module %s expected %s\n", j, path, buf );
        }
        else
        {
            ok( !mod, "%u: LoadLibrary succeeded\n", j );
            ok( GetLastError() == ERROR_MOD_NOT_FOUND || broken(GetLastError() == ERROR_NOT_ENOUGH_MEMORY),
                "%u: wrong error %u\n", j, GetLastError() );
        }
        FreeLibrary( mod );

        for (k = 0; tests[j].add_dirs[k]; k++) pRemoveDllDirectory( cookies[k] );
    }

    for (i = 1; i <= 6; i++)
    {
        sprintf( p, "\\%u\\winetestdll.dll", i );
        DeleteFileA( buf );
        sprintf( p, "\\%u", i );
        RemoveDirectoryA( buf );
    }
    *p = 0;
    RemoveDirectoryA( buf );
}