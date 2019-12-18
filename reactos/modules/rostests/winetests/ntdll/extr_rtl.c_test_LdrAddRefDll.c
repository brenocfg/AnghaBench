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
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  int /*<<< orphan*/ * BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * FreeLibrary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  LDR_ADDREF_DLL_PIN ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pLdrAddRefDll (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_LdrAddRefDll(void)
{
    HMODULE mod, mod2;
    NTSTATUS status;
    BOOL ret;

    if (!pLdrAddRefDll)
    {
        win_skip( "LdrAddRefDll not supported\n" );
        return;
    }

    mod = LoadLibraryA("comctl32.dll");
    ok(mod != NULL, "got %p\n", mod);
    ret = FreeLibrary(mod);
    ok(ret, "got %d\n", ret);

    mod2 = GetModuleHandleA("comctl32.dll");
    ok(mod2 == NULL, "got %p\n", mod2);

    /* load, addref and release 2 times */
    mod = LoadLibraryA("comctl32.dll");
    ok(mod != NULL, "got %p\n", mod);
    status = pLdrAddRefDll(0, mod);
    ok(status == STATUS_SUCCESS, "got 0x%08x\n", status);
    ret = FreeLibrary(mod);
    ok(ret, "got %d\n", ret);

    mod2 = GetModuleHandleA("comctl32.dll");
    ok(mod2 != NULL, "got %p\n", mod2);
    ret = FreeLibrary(mod);
    ok(ret, "got %d\n", ret);

    mod2 = GetModuleHandleA("comctl32.dll");
    ok(mod2 == NULL, "got %p\n", mod2);

    /* pin refcount */
    mod = LoadLibraryA("comctl32.dll");
    ok(mod != NULL, "got %p\n", mod);
    status = pLdrAddRefDll(LDR_ADDREF_DLL_PIN, mod);
    ok(status == STATUS_SUCCESS, "got 0x%08x\n", status);

    ret = FreeLibrary(mod);
    ok(ret, "got %d\n", ret);
    ret = FreeLibrary(mod);
    ok(ret, "got %d\n", ret);
    ret = FreeLibrary(mod);
    ok(ret, "got %d\n", ret);
    ret = FreeLibrary(mod);
    ok(ret, "got %d\n", ret);

    mod2 = GetModuleHandleA("comctl32.dll");
    ok(mod2 != NULL, "got %p\n", mod2);
}