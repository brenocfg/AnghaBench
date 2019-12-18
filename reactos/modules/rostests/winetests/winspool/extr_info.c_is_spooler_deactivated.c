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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ RPC_S_SERVER_UNAVAILABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static BOOL is_spooler_deactivated(DWORD res, DWORD lasterror)
{
    if (!res && lasterror == RPC_S_SERVER_UNAVAILABLE)
    {
        static int deactivated_spooler_reported = 0;
        if (!deactivated_spooler_reported)
        {
            deactivated_spooler_reported = 1;
            skip("The service 'Spooler' is required for many tests\n");
        }
        return TRUE;
    }
    return FALSE;
}