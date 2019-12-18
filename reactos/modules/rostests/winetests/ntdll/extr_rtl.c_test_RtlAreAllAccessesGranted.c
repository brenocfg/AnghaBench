#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ result; int /*<<< orphan*/  DesiredAccess; int /*<<< orphan*/  GrantedAccess; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 unsigned int NB_ALL_ACCESSES ; 
 TYPE_1__* all_accesses ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ pRtlAreAllAccessesGranted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlAreAllAccessesGranted(void)
{
    unsigned int test_num;
    BOOLEAN result;

    if (!pRtlAreAllAccessesGranted)
    {
        win_skip("RtlAreAllAccessesGranted is not available\n");
        return;
    }

    for (test_num = 0; test_num < NB_ALL_ACCESSES; test_num++) {
	result = pRtlAreAllAccessesGranted(all_accesses[test_num].GrantedAccess,
					   all_accesses[test_num].DesiredAccess);
	ok(all_accesses[test_num].result == result,
           "(test %d): RtlAreAllAccessesGranted(%08x, %08x) returns %d, expected %d\n",
	   test_num, all_accesses[test_num].GrantedAccess,
	   all_accesses[test_num].DesiredAccess,
	   result, all_accesses[test_num].result);
    } /* for */
}