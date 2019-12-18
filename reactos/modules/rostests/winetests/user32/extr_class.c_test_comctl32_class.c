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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  nameW ;
typedef  int /*<<< orphan*/  WNDCLASSW ;
typedef  int /*<<< orphan*/  WNDCLASSA ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  ULONG_PTR ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int ActivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CreateWindowA (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DeactivateActCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DeleteFileA (char*) ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int GetClassInfoA (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int GetClassInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseActCtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WS_OVERLAPPEDWINDOW ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  comctl32_manifest ; 
 int /*<<< orphan*/  create_manifest_file (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_test_actctx (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_comctl32_class( const char *name )
{
    WNDCLASSA wcA;
    WNDCLASSW wcW;
    BOOL ret;
    HMODULE module;
    WCHAR nameW[20];
    HWND hwnd;

    if (name[0] == '!')
    {
        char path[MAX_PATH];
        ULONG_PTR cookie;
        HANDLE context;

        name++;

        GetTempPathA(sizeof(path)/sizeof(path[0]), path);
        strcat(path, "comctl32_class.manifest");

        create_manifest_file(path, comctl32_manifest);
        context = create_test_actctx(path);
        ret = DeleteFileA(path);
        ok(ret, "Failed to delete manifest file, error %d.\n", GetLastError());

        module = GetModuleHandleA( "comctl32" );
        ok( !module, "comctl32 already loaded\n" );

        ret = ActivateActCtx(context, &cookie);
        ok(ret, "Failed to activate context.\n");

        /* Some systems load modules during context activation. In this case skip the rest of the test. */
        module = GetModuleHandleA( "comctl32" );
        ok( !module || broken(module != NULL) /* Vista/Win7 */, "comctl32 already loaded\n" );
        if (module)
        {
            win_skip("Module loaded during context activation. Skipping tests.\n");
            goto skiptest;
        }

        ret = GetClassInfoA( 0, name, &wcA );
        ok( ret || broken(!ret) /* WinXP */, "GetClassInfoA failed for %s\n", name );
        if (!ret)
            goto skiptest;

        MultiByteToWideChar( CP_ACP, 0, name, -1, nameW, sizeof(nameW)/sizeof(WCHAR) );
        ret = GetClassInfoW( 0, nameW, &wcW );
        ok( ret, "GetClassInfoW failed for %s\n", name );
        module = GetModuleHandleA( "comctl32" );
        ok( module != 0, "comctl32 not loaded\n" );
        FreeLibrary( module );
        module = GetModuleHandleA( "comctl32" );
        ok( !module || broken(module != NULL) /* Vista */, "comctl32 still loaded\n" );
        hwnd = CreateWindowA( name, "test", WS_OVERLAPPEDWINDOW, 0, 0, 10, 10, NULL, NULL, NULL, 0 );
        ok( hwnd != 0, "failed to create window for %s\n", name );
        module = GetModuleHandleA( "comctl32" );
        ok( module != 0, "comctl32 not loaded\n" );
        DestroyWindow( hwnd );

    skiptest:
        ret = DeactivateActCtx(0, cookie);
        ok(ret, "Failed to deactivate context.\n");
        ReleaseActCtx(context);
    }
    else
    {
        module = GetModuleHandleA( "comctl32" );
        ok( !module, "comctl32 already loaded\n" );
        ret = GetClassInfoA( 0, name, &wcA );
        ok( ret || broken(!ret) /* <= winxp */, "GetClassInfoA failed for %s\n", name );
        if (!ret) return;
        MultiByteToWideChar( CP_ACP, 0, name, -1, nameW, sizeof(nameW)/sizeof(WCHAR) );
        ret = GetClassInfoW( 0, nameW, &wcW );
        ok( ret, "GetClassInfoW failed for %s\n", name );
        module = GetModuleHandleA( "comctl32" );
        ok( module != 0, "comctl32 not loaded\n" );
        FreeLibrary( module );
        module = GetModuleHandleA( "comctl32" );
        ok( !module, "comctl32 still loaded\n" );
        hwnd = CreateWindowA( name, "test", WS_OVERLAPPEDWINDOW, 0, 0, 10, 10, NULL, NULL, NULL, 0 );
        ok( hwnd != 0, "failed to create window for %s\n", name );
        module = GetModuleHandleA( "comctl32" );
        ok( module != 0, "comctl32 not loaded\n" );
        DestroyWindow( hwnd );
    }
}