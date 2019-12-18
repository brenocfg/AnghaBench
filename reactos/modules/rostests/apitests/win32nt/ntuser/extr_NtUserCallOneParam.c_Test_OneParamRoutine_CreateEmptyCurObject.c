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
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 scalar_t__ NtUserCallOneParam (int,int /*<<< orphan*/ ) ; 
 scalar_t__ NtUserDestroyCursor (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ONEPARAM_ROUTINE_CREATEEMPTYCUROBJECT ; 

void
Test_OneParamRoutine_CreateEmptyCurObject(void) /* XP/2k3 : 0x21, vista 0x25 */
{
    HICON hIcon ;

    /* Test 0 */
    hIcon = (HICON) NtUserCallOneParam(0, _ONEPARAM_ROUTINE_CREATEEMPTYCUROBJECT);
    TEST(hIcon != NULL);

    TEST(NtUserDestroyCursor(hIcon, 0) == TRUE);

    /* Test Garbage */
    hIcon = (HICON) NtUserCallOneParam(0xdeadbeef, _ONEPARAM_ROUTINE_CREATEEMPTYCUROBJECT);
    TEST(hIcon != NULL);

    TEST(NtUserDestroyCursor(hIcon, 0xbaadf00d) == TRUE);

}