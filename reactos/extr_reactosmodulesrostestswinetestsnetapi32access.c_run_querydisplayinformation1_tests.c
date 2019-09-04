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
struct TYPE_3__ {scalar_t__ usri1_user_id; int usri1_flags; scalar_t__ usri1_next_index; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  TYPE_1__* PNET_DISPLAY_USER ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ DOMAIN_USER_RID_ADMIN ; 
 scalar_t__ DOMAIN_USER_RID_GUEST ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 int /*<<< orphan*/  MAX_PREFERRED_LENGTH ; 
 int TRUE ; 
 int UF_NORMAL_ACCOUNT ; 
 int UF_SCRIPT ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  pNetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ pNetQueryDisplayInformation (int /*<<< orphan*/ *,int,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void run_querydisplayinformation1_tests(void)
{
    PNET_DISPLAY_USER Buffer, rec;
    DWORD Result, EntryCount;
    DWORD i = 0;
    BOOL hasAdmin = FALSE;
    BOOL hasGuest = FALSE;

    do
    {
        Result = pNetQueryDisplayInformation(
            NULL, 1, i, 1000, MAX_PREFERRED_LENGTH, &EntryCount,
            (PVOID *)&Buffer);

        ok((Result == ERROR_SUCCESS) || (Result == ERROR_MORE_DATA),
           "Information Retrieved\n");
        rec = Buffer;
        for(; EntryCount > 0; EntryCount--)
        {
            if (rec->usri1_user_id == DOMAIN_USER_RID_ADMIN)
            {
                ok(!hasAdmin, "One admin user\n");
                ok(rec->usri1_flags & UF_SCRIPT, "UF_SCRIPT flag is set\n");
                ok(rec->usri1_flags & UF_NORMAL_ACCOUNT, "UF_NORMAL_ACCOUNT flag is set\n");
                hasAdmin = TRUE;
            }
            else if (rec->usri1_user_id == DOMAIN_USER_RID_GUEST)
            {
                ok(!hasGuest, "One guest record\n");
                ok(rec->usri1_flags & UF_SCRIPT, "UF_SCRIPT flag is set\n");
                ok(rec->usri1_flags & UF_NORMAL_ACCOUNT, "UF_NORMAL_ACCOUNT flag is set\n");
                hasGuest = TRUE;
            }

            i = rec->usri1_next_index;
            rec++;
        }

        pNetApiBufferFree(Buffer);
    } while (Result == ERROR_MORE_DATA);

    ok(hasAdmin, "Doesn't have 'Administrator' account\n");
}