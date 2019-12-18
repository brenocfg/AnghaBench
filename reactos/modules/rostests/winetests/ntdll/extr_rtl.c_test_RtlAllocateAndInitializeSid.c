#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; } ;
struct TYPE_5__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ SID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/  PSID ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 scalar_t__ STATUS_INVALID_SID ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pRtlAllocateAndInitializeSid (TYPE_2__*,int,int,int,int,int,int,int,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ pRtlFreeSid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlAllocateAndInitializeSid(void)
{
    NTSTATUS ret;
    SID_IDENTIFIER_AUTHORITY sia = {{ 1, 2, 3, 4, 5, 6 }};
    PSID psid;

    if (!pRtlAllocateAndInitializeSid)
    {
        win_skip("RtlAllocateAndInitializeSid is not available\n");
        return;
    }

    ret = pRtlAllocateAndInitializeSid(&sia, 0, 1, 2, 3, 4, 5, 6, 7, 8, &psid);
    ok(!ret, "RtlAllocateAndInitializeSid error %08x\n", ret);
    ret = pRtlFreeSid(psid);
    ok(!ret, "RtlFreeSid error %08x\n", ret);

    /* these tests crash on XP */
    if (0)
    {
        pRtlAllocateAndInitializeSid(NULL, 0, 1, 2, 3, 4, 5, 6, 7, 8, &psid);
        pRtlAllocateAndInitializeSid(&sia, 0, 1, 2, 3, 4, 5, 6, 7, 8, NULL);
    }

    ret = pRtlAllocateAndInitializeSid(&sia, 9, 1, 2, 3, 4, 5, 6, 7, 8, &psid);
    ok(ret == STATUS_INVALID_SID, "wrong error %08x\n", ret);
}