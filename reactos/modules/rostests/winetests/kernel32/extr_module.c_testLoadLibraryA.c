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
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/ * FARPROC ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void testLoadLibraryA(void)
{
    HMODULE hModule, hModule1;
    FARPROC fp;

    SetLastError(0xdeadbeef);
    hModule = LoadLibraryA("kernel32.dll");
    ok( hModule != NULL, "kernel32.dll should be loadable\n");
    ok( GetLastError() == 0xdeadbeef, "GetLastError should be 0xdeadbeef but is %d\n", GetLastError());

    fp = GetProcAddress(hModule, "CreateFileA");
    ok( fp != NULL, "CreateFileA should be there\n");
    ok( GetLastError() == 0xdeadbeef, "GetLastError should be 0xdeadbeef but is %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    hModule1 = LoadLibraryA("kernel32   ");
    ok( hModule1 != NULL, "\"kernel32   \" should be loadable\n" );
    ok( GetLastError() == 0xdeadbeef, "GetLastError should be 0xdeadbeef but is %d\n", GetLastError() );
    ok( hModule == hModule1, "Loaded wrong module\n" );
    FreeLibrary(hModule1);
    FreeLibrary(hModule);
}