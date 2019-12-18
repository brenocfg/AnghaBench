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
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int /*<<< orphan*/ * GetProcAddress (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int running_under_wine (void)
{
    HMODULE module = GetModuleHandleA("ntdll.dll");

    if (!module) return 0;
    return (GetProcAddress(module, "wine_server_call") != NULL);
}