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
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ HKL ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_NOACCESS ; 
 scalar_t__ GetKeyboardLayout (int /*<<< orphan*/ ) ; 
 int GetKeyboardLayoutNameA (char*) ; 
 int GetKeyboardLayoutNameW (int /*<<< orphan*/ *) ; 
 char* GetLastError () ; 
 int KL_NAMELENGTH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_keyboard_layout_name(void)
{
    BOOL ret;
    char klid[KL_NAMELENGTH];

    if (0) /* crashes on native system */
        ret = GetKeyboardLayoutNameA(NULL);

    SetLastError(0xdeadbeef);
    ret = GetKeyboardLayoutNameW(NULL);
    ok(!ret, "got %d\n", ret);
    ok(GetLastError() == ERROR_NOACCESS, "got %d\n", GetLastError());

    if (GetKeyboardLayout(0) != (HKL)(ULONG_PTR)0x04090409) return;

    klid[0] = 0;
    ret = GetKeyboardLayoutNameA(klid);
    ok(ret, "GetKeyboardLayoutNameA failed %u\n", GetLastError());
    ok(!strcmp(klid, "00000409"), "expected 00000409, got %s\n", klid);
}