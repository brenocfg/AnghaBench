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
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TRUE ; 
 int /*<<< orphan*/  pGetPrinterW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL check_win9x(void)
{
    if (pGetPrinterW)
    {
        SetLastError(0xdeadbeef);
        pGetPrinterW(NULL, 0, NULL, 0, NULL);
        return (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED);
    }
    else
    {
        return TRUE;
    }
}