#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t GroupCount; TYPE_1__* Groups; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  Sid; } ;
typedef  TYPE_2__ SID_IDENTIFIER_AUTHORITY ;
typedef  TYPE_3__* PTOKEN_GROUPS ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AllocateAndInitializeSid (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DOMAIN_ALIAS_RID_ADMINS ; 
 scalar_t__ EqualSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,size_t,size_t*) ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SECURITY_BUILTIN_DOMAIN_RID ; 
 int /*<<< orphan*/  SECURITY_NT_AUTHORITY ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TokenGroups ; 

__attribute__((used)) static BOOL is_token_admin(HANDLE token)
{
    PSID administrators = NULL;
    SID_IDENTIFIER_AUTHORITY nt_authority = { SECURITY_NT_AUTHORITY };
    DWORD groups_size;
    PTOKEN_GROUPS groups;
    DWORD group_index;

    /* Create a well-known SID for the Administrators group. */
    if (! AllocateAndInitializeSid(&nt_authority, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                   DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0,
                                   &administrators))
        return FALSE;

    /* Get the group info from the token */
    groups_size = 0;
    GetTokenInformation(token, TokenGroups, NULL, 0, &groups_size);
    groups = HeapAlloc(GetProcessHeap(), 0, groups_size);
    if (groups == NULL)
    {
        FreeSid(administrators);
        return FALSE;
    }
    if (! GetTokenInformation(token, TokenGroups, groups, groups_size, &groups_size))
    {
        HeapFree(GetProcessHeap(), 0, groups);
        FreeSid(administrators);
        return FALSE;
    }

    /* Now check if the token groups include the Administrators group */
    for (group_index = 0; group_index < groups->GroupCount; group_index++)
    {
        if (EqualSid(groups->Groups[group_index].Sid, administrators))
        {
            HeapFree(GetProcessHeap(), 0, groups);
            FreeSid(administrators);
            return TRUE;
        }
    }

    /* If we end up here we didn't find the Administrators group */
    HeapFree(GetProcessHeap(), 0, groups);
    FreeSid(administrators);
    return FALSE;
}