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
typedef  char WCHAR ;
typedef  char const* LPCWSTR ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/ * DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/ * ERROR_MOD_NOT_FOUND ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS ; 
 int /*<<< orphan*/  GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT ; 
 int /*<<< orphan*/ * GetLastError () ; 
 int GetModuleHandleExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int GetModuleHandleExW (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void testGetModuleHandleEx(void)
{
    static const WCHAR kernel32W[] = {'k','e','r','n','e','l','3','2',0};
    static const WCHAR nosuchmodW[] = {'n','o','s','u','c','h','m','o','d',0};
    BOOL ret;
    DWORD error;
    HMODULE mod, mod_kernel32;

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExA( 0, NULL, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExA( 0, "kernel32", NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExA( 0, "kernel32", &mod );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( mod != (HMODULE)0xdeadbeef, "got %p\n", mod );
    FreeLibrary( mod );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExA( 0, "nosuchmod", &mod );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_MOD_NOT_FOUND, "got %u\n", error );
    ok( mod == NULL, "got %p\n", mod );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExW( 0, NULL, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExW( 0, kernel32W, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExW( 0, kernel32W, &mod );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( mod != (HMODULE)0xdeadbeef, "got %p\n", mod );
    FreeLibrary( mod );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExW( 0, nosuchmodW, &mod );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_MOD_NOT_FOUND, "got %u\n", error );
    ok( mod == NULL, "got %p\n", mod );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, "kernel32", NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, "kernel32", &mod );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( mod != (HMODULE)0xdeadbeef, "got %p\n", mod );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, "nosuchmod", &mod );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_MOD_NOT_FOUND, "got %u\n", error );
    ok( mod == NULL, "got %p\n", mod );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, NULL, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, kernel32W, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, kernel32W, &mod );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( mod != (HMODULE)0xdeadbeef, "got %p\n", mod );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, nosuchmodW, &mod );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_MOD_NOT_FOUND, "got %u\n", error );
    ok( mod == NULL, "got %p\n", mod );

    mod_kernel32 = LoadLibraryA( "kernel32" );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, NULL, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)mod_kernel32, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)mod_kernel32, &mod );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( mod == mod_kernel32, "got %p\n", mod );
    FreeLibrary( mod );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExA( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)0xbeefdead, &mod );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_MOD_NOT_FOUND, "got %u\n", error );
    ok( mod == NULL, "got %p\n", mod );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, NULL, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    ret = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)mod_kernel32, NULL );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_INVALID_PARAMETER, "got %u\n", error );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)mod_kernel32, &mod );
    ok( ret, "unexpected failure %u\n", GetLastError() );
    ok( mod == mod_kernel32, "got %p\n", mod );
    FreeLibrary( mod );

    SetLastError( 0xdeadbeef );
    mod = (HMODULE)0xdeadbeef;
    ret = GetModuleHandleExW( GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCWSTR)0xbeefdead, &mod );
    error = GetLastError();
    ok( !ret, "unexpected success\n" );
    ok( error == ERROR_MOD_NOT_FOUND, "got %u\n", error );
    ok( mod == NULL, "got %p\n", mod );

    FreeLibrary( mod_kernel32 );
}