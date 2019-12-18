#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ TOKEN_ELEVATION_TYPE ;
typedef  TYPE_1__ SID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateAndInitializeSid (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOMAIN_ALIAS_RID_ADMINS ; 
 int /*<<< orphan*/  DOMAIN_ALIAS_RID_POWER_USERS ; 
 int FALSE ; 
 int /*<<< orphan*/  FreeSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECURITY_BUILTIN_DOMAIN_RID ; 
 int /*<<< orphan*/  SECURITY_NT_AUTHORITY ; 
 int /*<<< orphan*/  TOKEN_QUERY ; 
 int TRUE ; 
 int /*<<< orphan*/  TokenElevationType ; 
 scalar_t__ TokenElevationTypeDefault ; 
 scalar_t__ TokenElevationTypeLimited ; 
 int /*<<< orphan*/  pCheckTokenMembership (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ pOpenProcessToken (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static BOOL is_process_limited(void)
{
    SID_IDENTIFIER_AUTHORITY NtAuthority = {SECURITY_NT_AUTHORITY};
    PSID Group = NULL;
    BOOL IsInGroup;
    HANDLE token;

    if (!pCheckTokenMembership || !pOpenProcessToken) return FALSE;

    if (!AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                  DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &Group) ||
        !pCheckTokenMembership(NULL, Group, &IsInGroup))
    {
        trace("Could not check if the current user is an administrator\n");
        FreeSid(Group);
        return FALSE;
    }
    FreeSid(Group);

    if (!IsInGroup)
    {
        if (!AllocateAndInitializeSid(&NtAuthority, 2,
                                      SECURITY_BUILTIN_DOMAIN_RID,
                                      DOMAIN_ALIAS_RID_POWER_USERS,
                                      0, 0, 0, 0, 0, 0, &Group) ||
            !pCheckTokenMembership(NULL, Group, &IsInGroup))
        {
            trace("Could not check if the current user is a power user\n");
            return FALSE;
        }
        if (!IsInGroup)
        {
            /* Only administrators and power users can be powerful */
            return TRUE;
        }
    }

    if (pOpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token))
    {
        BOOL ret;
        TOKEN_ELEVATION_TYPE type = TokenElevationTypeDefault;
        DWORD size;

        ret = GetTokenInformation(token, TokenElevationType, &type, sizeof(type), &size);
        CloseHandle(token);
        return (ret && type == TokenElevationTypeLimited);
    }
    return FALSE;
}