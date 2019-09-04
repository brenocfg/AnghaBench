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
typedef  int /*<<< orphan*/  path2 ;
typedef  int /*<<< orphan*/  path1 ;
typedef  int /*<<< orphan*/ * HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetModuleHandleA (char const*) ; 
 int /*<<< orphan*/  GetWindowsDirectoryA (char*,int) ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 

__attribute__((used)) static void testNestedLoadLibraryA(void)
{
    static const char dllname[] = "shell32.dll";
    char path1[MAX_PATH], path2[MAX_PATH];
    HMODULE hModule1, hModule2, hModule3;

    /* This is not really a Windows conformance test, but more a Wine
     * regression test. Wine's builtin dlls can be loaded from multiple paths,
     * and this test tries to make sure that Wine does not get confused and
     * really unloads the Unix .so file at the right time. Failure to do so
     * will result in the dll being unloadable.
     * This test must be done with a dll that can be unloaded, which means:
     * - it must not already be loaded
     * - it must not have a 16-bit counterpart
     */
    GetWindowsDirectoryA(path1, sizeof(path1));
    strcat(path1, "\\system\\");
    strcat(path1, dllname);
    hModule1 = LoadLibraryA(path1);
    if (!hModule1)
    {
        /* We must be on Windows, so we cannot test */
        return;
    }

    GetWindowsDirectoryA(path2, sizeof(path2));
    strcat(path2, "\\system32\\");
    strcat(path2, dllname);
    hModule2 = LoadLibraryA(path2);
    ok(hModule2 != NULL, "LoadLibrary(%s) failed\n", path2);

    /* The first LoadLibrary() call may have registered the dll under the
     * system32 path. So load it, again, under the '...\system\...' path so
     * Wine does not immediately notice that it is already loaded.
     */
    hModule3 = LoadLibraryA(path1);
    ok(hModule3 != NULL, "LoadLibrary(%s) failed\n", path1);

    /* Now fully unload the dll */
    ok(FreeLibrary(hModule3), "FreeLibrary() failed\n");
    ok(FreeLibrary(hModule2), "FreeLibrary() failed\n");
    ok(FreeLibrary(hModule1), "FreeLibrary() failed\n");
    ok(GetModuleHandleA(dllname) == NULL, "%s was not fully unloaded\n", dllname);

    /* Try to load the dll again, if refcounting is ok, this should work */
    hModule1 = LoadLibraryA(path1);
    ok(hModule1 != NULL, "LoadLibrary(%s) failed\n", path1);
    if (hModule1 != NULL)
        ok(FreeLibrary(hModule1), "FreeLibrary() failed\n");
}