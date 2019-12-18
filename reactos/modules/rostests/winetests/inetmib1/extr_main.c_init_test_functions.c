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

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * LoadLibraryA (char*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*) ; 
 void* pSnmpExtensionInit ; 
 void* pSnmpExtensionQuery ; 

__attribute__((used)) static HMODULE init_test_functions(void)
{
    HMODULE mod = LoadLibraryA("inetmib1");

    ok(mod != NULL, "failed to load inetmib1.dll\n");

    if (!mod) return NULL;

    pSnmpExtensionInit = (void *)GetProcAddress(mod, "SnmpExtensionInit");
    pSnmpExtensionQuery = (void *)GetProcAddress(mod, "SnmpExtensionQuery");

    return mod;
}