#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  info ;
struct TYPE_4__ {scalar_t__ lpBaseOfDll; int /*<<< orphan*/ * EntryPoint; } ;
typedef  TYPE_1__ MODULEINFO ;
typedef  scalar_t__ HMODULE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pK32GetModuleInformation (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int) ; 

__attribute__((used)) static void testK32GetModuleInformation(void)
{
    MODULEINFO info;
    HMODULE mod;
    BOOL ret;

    mod = GetModuleHandleA(NULL);
    memset(&info, 0xAA, sizeof(info));
    ret = pK32GetModuleInformation(GetCurrentProcess(), mod, &info, sizeof(info));
    ok(ret, "K32GetModuleInformation failed for main module\n");
    ok(info.lpBaseOfDll == mod, "Wrong info.lpBaseOfDll = %p, expected %p\n", info.lpBaseOfDll, mod);
    ok(info.EntryPoint != NULL, "Expected nonzero entrypoint\n");

    mod = GetModuleHandleA("kernel32.dll");
    memset(&info, 0xAA, sizeof(info));
    ret = pK32GetModuleInformation(GetCurrentProcess(), mod, &info, sizeof(info));
    ok(ret, "K32GetModuleInformation failed for kernel32 module\n");
    ok(info.lpBaseOfDll == mod, "Wrong info.lpBaseOfDll = %p, expected %p\n", info.lpBaseOfDll, mod);
    ok(info.EntryPoint != NULL, "Expected nonzero entrypoint\n");
}