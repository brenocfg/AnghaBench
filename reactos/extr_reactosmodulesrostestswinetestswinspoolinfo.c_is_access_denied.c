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
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static BOOL is_access_denied(DWORD res, DWORD lasterror)
{
    if (!res && lasterror == ERROR_ACCESS_DENIED)
    {
        static int access_denied_reported = 0;
        if (!access_denied_reported)
        {
            access_denied_reported = 1;
            skip("More access rights are required for many tests\n");
        }
        return TRUE;
    }
    return FALSE;
}