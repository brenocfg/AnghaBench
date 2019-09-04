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
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 char* VirtualAlloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualFree (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualProtect (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* _strupr (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test__strupr(void)
{
    const char str[] = "123";
    char str2[4];
    char *mem, *p;
    DWORD prot;

    mem = VirtualAlloc(NULL, sizeof(str), MEM_COMMIT, PAGE_READWRITE);
    ok(mem != NULL, "VirtualAlloc failed\n");
    memcpy(mem, str, sizeof(str));
    ok(VirtualProtect(mem, sizeof(str), PAGE_READONLY, &prot), "VirtualProtect failed\n");

    strcpy(str2, "aBc");
    p = _strupr(str2);
    ok(p == str2, "_strupr returned %p\n", p);
    ok(!strcmp(str2, "ABC"), "str2 = %s\n", str2);

    p = _strupr(mem);
    ok(p == mem, "_strupr returned %p\n", p);
    ok(!strcmp(mem, "123"), "mem = %s\n", mem);

    if(!setlocale(LC_ALL, "english")) {
        VirtualFree(mem, sizeof(str), MEM_RELEASE);
        win_skip("English locale _strupr tests\n");
        return;
    }

    strcpy(str2, "aBc");
    p = _strupr(str2);
    ok(p == str2, "_strupr returned %p\n", p);
    ok(!strcmp(str2, "ABC"), "str2 = %s\n", str2);

    if (0) /* crashes on Windows */
    {
        p = _strupr(mem);
        ok(p == mem, "_strupr returned %p\n", p);
        ok(!strcmp(mem, "123"), "mem = %s\n", mem);
    }

    setlocale(LC_ALL, "C");
    VirtualFree(mem, sizeof(str), MEM_RELEASE);
}