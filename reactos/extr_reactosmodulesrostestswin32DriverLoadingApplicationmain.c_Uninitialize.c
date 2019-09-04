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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UnregisterDriver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
Uninitialize(LPCWSTR lpDriverPath)
{
    if (!UnregisterDriver(DRIVER_NAME))
    {
        wprintf(L"[%lu] Failed to unregister %s\n", GetLastError(), DRIVER_NAME);
        return FALSE;
    }

    return TRUE;
}