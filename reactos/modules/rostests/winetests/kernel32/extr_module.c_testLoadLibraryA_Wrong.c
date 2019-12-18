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
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 scalar_t__ ERROR_MOD_NOT_FOUND ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void testLoadLibraryA_Wrong(void)
{
    HMODULE hModule;

    /* Try to load a nonexistent dll */
    SetLastError(0xdeadbeef);
    hModule = LoadLibraryA("non_ex_pv.dll");
    ok( !hModule, "non_ex_pv.dll should be not loadable\n");
    ok( GetLastError() == ERROR_MOD_NOT_FOUND, "Expected ERROR_MOD_NOT_FOUND, got %d\n", GetLastError() );

    /* Just in case */
    FreeLibrary(hModule);
}