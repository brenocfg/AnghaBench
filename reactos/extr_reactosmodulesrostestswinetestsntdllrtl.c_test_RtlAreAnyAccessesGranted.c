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
 unsigned int NB_ANY_ACCESSES ; 
 TYPE_1__* any_accesses ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ pRtlAreAnyAccessesGranted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlAreAnyAccessesGranted(void)
{
    unsigned int test_num;
    BOOLEAN result;

    if (!pRtlAreAnyAccessesGranted)
    {
        win_skip("RtlAreAnyAccessesGranted is not available\n");
        return;
    }

    for (test_num = 0; test_num < NB_ANY_ACCESSES; test_num++) {
	result = pRtlAreAnyAccessesGranted(any_accesses[test_num].GrantedAccess,
					   any_accesses[test_num].DesiredAccess);
	ok(any_accesses[test_num].result == result,
           "(test %d): RtlAreAnyAccessesGranted(%08x, %08x) returns %d, expected %d\n",
	   test_num, any_accesses[test_num].GrantedAccess,
	   any_accesses[test_num].DesiredAccess,
	   result, any_accesses[test_num].result);
    } /* for */
}