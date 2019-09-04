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
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetComputerNameW (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetUserNameW (scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ TRUE ; 
 scalar_t__* computer_name ; 
 int /*<<< orphan*/  ok (scalar_t__,char*) ; 
 scalar_t__* user_name ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL init_access_tests(void)
{
    DWORD dwSize;
    BOOL rc;

    user_name[0] = 0;
    dwSize = ARRAY_SIZE(user_name);
    rc=GetUserNameW(user_name, &dwSize);
    if (rc==FALSE && GetLastError()==ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("GetUserNameW is not available.\n");
        return FALSE;
    }
    ok(rc, "User Name Retrieved\n");

    computer_name[0] = 0;
    dwSize = ARRAY_SIZE(computer_name);
    ok(GetComputerNameW(computer_name, &dwSize), "Computer Name Retrieved\n");
    return TRUE;
}